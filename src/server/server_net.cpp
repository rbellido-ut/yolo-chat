#include "server_net.h"

int ServerNetwork::start_server(int port) {
    if ((listensocket_ = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        set_error("Couldn't create listen socket");
        return 0;
    }

    int arg = 1;
    if (setsockopt(listensocket_, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1)
    {
        set_error("Couldn't set socket options");
        return 0;
    }


    bzero((char *)&server_, sizeof(struct sockaddr_in));
    server_.sin_family = AF_INET;
    server_.sin_port = htons(port);
    server_.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any client

    if (bind(listensocket_, (struct sockaddr *)&server_, sizeof(server_)) == -1)
    {
        set_error("Error binding the listening socket");
        return 0;
    }

    // Listen for connections
    // queue up to LISTENQ connect requests
    listen(listensocket_, LISTENQ);

    while (1)
    {
        rset_ = allset_;               // structure assignment
        nready_ = select(nready_ + 1, &rset_, NULL, NULL, NULL);

        if (FD_ISSET(listensocket_, &rset_)) // new client connection
        {
            client_len_ = sizeof(client_addr_);
            if ((acceptsocket_ = accept(listensocket_, (struct sockaddr *) &client_addr_, &client_len_)) == -1)
            {
                //SystemFatal("accept error");
                set_error("accept error");
                return 0;
            }

             //printf(" Remote Address:  %s\n", inet_ntoa(client_addr.sin_addr));

            for (i = 0; i < FD_SETSIZE; i++)
                if (client_[i] < 0)
                {
                    client_[i] = acceptsocket_;	// save descriptor
                    break;
                }

            if (i == FD_SETSIZE)
            {
                set_error("too many clients!");
                return 0;
            }

            FD_SET (acceptsocket_, &allset_);     // add new descriptor to set
            if (acceptsocket_ > nready_)
                nready_ = acceptsocket_;	// for select

            if (i > maxi_)
                maxi_ = i;	// new max index in client[] array

            if (--nready_ <= 0)
                continue;	// no more readable descriptors
         }

        for (i = 0; i <= maxi_; i++)	// check all clients for data
        {
            if ((sockfd_ = client_[i]) < 0)
                continue;

            if (FD_ISSET(sockfd_, &rset_))
            {
                int n = 0;

                bp = buf;
                bytes_to_read_ = BUFFER_LEN;
                while ((n = read(sockfd_, bp, bytes_to_read_)) > 0)
                {
                    bp += n;
                    bytes_to_read_ -= n;
                }
                write(sockfd_, buf, BUFFER_LEN);   // echo to client

                if (n == 0) // connection closed by client
                {
                    //printf(" Remote Address:  %s closed connection\n", inet_ntoa(client_addr.sin_addr));
                    close(sockfd_);
                    FD_CLR(sockfd_, &allset_);
                    client_[i] = -1;
                }

                if (--nready_ <= 0)
                    break;        // no more readable descriptors
            }
        }
    }
    return 1;
}

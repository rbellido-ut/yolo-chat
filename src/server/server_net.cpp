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

    return 1;
}

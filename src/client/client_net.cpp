/*---------------------------------------------------------------------------------------
--	SOURCE FILE: client_net - Contains all the
--
--	PROGRAM: yolo-chat
--
--	FUNCTIONS: initClient(),
--
--	DATE:	March 19, 2013
--
--	REVISIONS:
--
--
--	DESIGNERS: Ronald Bellido
--
--	PROGRAMMERS: Ronald Bellido
--
--	NOTES:
--
---------------------------------------------------------------------------------------*/
#include "client_net.h"

int ClientNetwork::start_client(const int port, const char * host)
{
    if ((connectsocket_= socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        set_error("Couldn't create socket");
        return 0;
    }

    bzero((char *)&server_, sizeof(struct sockaddr_in));
    server_.sin_family = AF_INET;
    server_.sin_port = htons(port);
    if ((hostentptr_ = gethostbyname(host)) == NULL)
    {
        set_error("Failed getting hostname.");
        return 0;
    }

    bcopy(hostentptr_->h_addr, (char *)&server_.sin_addr, hostentptr_->h_length);

    if (connect(connectsocket_, (struct sockaddr *)&server_, sizeof(server_)) == -1)
    {
        set_error("Couldn't connect");
        return 0;
    }

    return 1;
}

void ClientNetwork::send_text(std::string text)
{
    int textlen = text.size();
    send(connectsocket_, text.c_str(), textlen, 0);
}

std::string ClientNetwork::receive_text()
{
    int bytesread = 0;
    char buffer[BUFFER_LEN];
    char * bufferptr = buffer;
    int bytes_to_read = BUFFER_LEN;
    std::string received_text;
    while ((bytesread = recv(connectsocket_, buffer, bytes_to_read, 0)) < BUFFER_LEN)
    {
        bufferptr += bytesread;
        bytes_to_read -= bytesread;
    }

    received_text = buffer;

    return received_text;
}

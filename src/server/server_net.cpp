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
        set_error("couldn't set socket options");
        return 0;
    }



    return 1;
}

#include "utils.h"

namespace ServerNet {
    class ServerNetwork;
}

class ServerNetwork {

public:
    ServerNetwork() {
        acceptsocket_ = 0;
        listensocket_ = 0;
    }

    ~ServerNetwork() {
        close(acceptsocket_);
        close(listensocket_);
    }

    int start_server(int port);

    std::string get_error() {
        return error_;
    }

private:
    int acceptsocket_, listensocket_, sockfd_;
    int i, nready_, bytes_to_read_, maxi_;
    socklen_t client_len_;
    int maxfd_, client_[FD_SETSIZE];
    std::string error_;
    struct sockaddr_in server_;
    struct sockaddr_in client_addr_;
    fd_set rset_, allset_;

    char *bp, buf[BUFFER_LEN];

    void set_error(std::string errormsg) {
        error_ = errormsg;
    }
};

//TODO: create a class that subclasses QObject or QThread
//for handling threaded I/O

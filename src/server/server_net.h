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
    int acceptsocket_;
    int listensocket_;
    std::string error_;
    struct sockaddr_in server_;
    struct sockaddr_in client_addr;

    void set_error(std::string errormsg) {
        error_ = errormsg;
    }
};

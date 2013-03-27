#ifndef CLIENTNET_H
#define CLIENTNET_H
#include "utils.h"

namespace ClientNet {
    class ClientNetwork;
}

class ClientNetwork {
public:
    ClientNetwork(){
        connectsocket_ = 0;
        error_ = "";
    }

    ~ClientNetwork(){
        close(connectsocket_);
    }
    int start_client(int port, char * host);

    void send_text(std::string text);
    std::string receive_text();

    std::string get_error() {
        return error_;
    }

private:
    int connectsocket_;
    struct hostent *hostentptr_;
    struct sockaddr_in server_;
    std::string error_;

    void set_error(std::string errormsg) {
        error_ = errormsg;
    }
};

#endif // CLIENTNET_H

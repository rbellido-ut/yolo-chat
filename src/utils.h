#ifndef UTILS_H
#define UTILS_H

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <strings.h>
#include <iostream>
#include <pthread.h>

#include <QObject>

#define DEFAULT_PORT 7000
#define DEFAULT_HOST "localhost"
#define BUFFER_LEN 255
#define LISTENQ 5

#endif // UTILS_H

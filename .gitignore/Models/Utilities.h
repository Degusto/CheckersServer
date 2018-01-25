//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_UTILITIES_H
#define CHECKERSSERVER_UTILITIES_H

#include <netdb.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#define ERROR(e) { perror(e); exit(EXIT_FAILURE); }
#define SERVER_PORT 1234
#define QUEUE_SIZE 5
#define BUFFER_SIZE 64

#endif //CHECKERSSERVER_UTILITIES_H

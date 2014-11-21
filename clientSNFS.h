//
//  clientSNFS.h
//  
//
//  Created by Adam on 11/20/14.
//
//

#ifndef _clientSNFS_h
#define _clientSNFS_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>


struct fileStat {
    
    int fd;
    struct timeval *accessed;
    struct timeval *modified;
    struct timeval *creation;
    int size;
    
};


void error(const char *msg);
void setServer(char *serverIP, int port);
int openFile(char *name);
int readFile(int fd, void *buf);
int writeFile(int fd, void *buf);
int statFile(int fd, struct fileStat *buf);
int closeFile(int fd);




#endif

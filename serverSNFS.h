//
//  serverSNFS.h
//  
//
//  Created by Adam on 11/20/14.
//
//

#ifndef _serverSNFS_h
#define _serverSNFS_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

struct fileStat {
    
    int fd;
    struct timeval *accessed;
    struct timeval *modified;
    struct timeval *creation;
    int size;
    
};


void* handle_request(int *connection);
void error(const char *msg);
static int host2IpAddr(char *anIpName);

#endif

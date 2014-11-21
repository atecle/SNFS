//
//  serverSNFS.h
//  
//
//  Created by Adam on 11/20/14.
//
//

#ifndef _serverSNFS_h
#define _serverSNFS_h



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

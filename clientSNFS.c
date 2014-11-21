


#include "clientSNFS.h"


struct sockaddr_in client_addr, server_addr;
char ip[32];
int port;
int sessionSocket;

void error(const char *msg) {
    perror(msg);

}

static int host2IpAddr(char *anIpName){
    /* input   : hostname in ip format such as cs.rutgers.edu
     * returns : 0 if any error ipaddr otherwise
     * output  : -
     * desc    : resolves an ip name.
     */
    
    struct hostent *hostEntry;
    struct in_addr *scratch;
    
    if ((hostEntry = gethostbyname ( anIpName )) == (struct hostent*) NULL)
        return 0;
    
    scratch = (struct in_addr *) hostEntry->h_addr;
    
    return (ntohl(scratch->s_addr));
    
}


void setServer(char *serverIP, int port_num) {
    
    
    
    memset ((void*)&client_addr,0,sizeof(client_addr));
    memset ((void*)&server_addr,0,sizeof(server_addr));
    
    sessionSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sessionSocket < 0) error("Error creating socket");
    
    server_addr.sin_addr.s_addr = htonl(host2IpAddr(serverIP));
    server_addr.sin_port = htons (port_num);
    server_addr.sin_family = AF_INET;
    
    
    int t = connect (sessionSocket, (struct sockaddr *)&server_addr, sizeof (server_addr));
    
    if (t < 0) error("Connection failed");
    
}

int openFile(char *name) {
    
    write(sessionSocket, name, strlen(name));
    char buffer[256];
    
    read(sessionSocket, buffer, 256);
    
    close(sessionSocket);
    
    
    return 0;
}

int readFile(int fd, void *buf) {
    
    return 0;
    
}

int writeFile(int fd, void *buf) {
    
    return 0;
    
}

int statFile(int fd, struct fileStat *buf) {
    
    return 0;
    
}

int closeFile(int fd) {
    
    return 0;
    
}




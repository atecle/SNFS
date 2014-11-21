#include "serverSNFS.h"

int port;
char *root_path;

void error(const char *msg)
{
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

void* handle_request(int *connection) {
    
    char buffer[256];
    bzero(buffer, 256);
    int sockfd = *connection;
    int n = read(sockfd, buffer, 255);
    
    
    if (n < 0) error("Error reading from socket");
    
    printf("Here is the message: %s\n",buffer);
    n = write(sockfd,"I got your message",18);
    if (n < 0) error("ERROR writing to socket");
    close(sockfd);
    close(*connection);
    return NULL;
    
}

int main(int argc, char *argv[]) {
    
    
    if (argc != 5) {
        fprintf(stderr, "Wrong number of arguments\n");
        return -1;
    }
    
    
    if (!strcmp(argv[1], "-port")) {
        port = atoi(argv[2]);
    }
    else if (!strcmp(argv[1], "-mount")) {
        root_path = strdup(argv[2]);
    }
    else {
        fprintf(stderr, "Invalid options\n");
        return -1;
    }
    
    
    if (!strcmp(argv[3], "-port")) {
        port = atoi(argv[4]);
    }
    else if (!strcmp(argv[3], "-mount")) {
        root_path = strdup(argv[4]);
    }
    else {
        fprintf(stderr, "Invalid options\n");
        return -1;
    }
    
    int status;
    
    if ((status = mkdir(root_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) == -1) {
        fprintf(stderr, "Directory already exists\n");
        exit(1);
    }
    
    exit(0);
    
    
    int serverSocket, clilen, true = 1;
    char hostname[32];
    
    gethostname(hostname, 32);
    
    
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        
        fprintf(stderr, "Error creating socket");
        return -1;
    }
    
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEPORT, &true, sizeof(int)) == -1) error("Error in setsockopt()");
    
   
    
    struct sockaddr_in server_addr, client_addr;
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr =  INADDR_ANY; //htonl(host2IpAddr (hostname));
    bzero(&(server_addr.sin_zero), 8);
    
    
    if(bind(serverSocket, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in))) error("Error binding socket");
    
    
    if (listen(serverSocket, 5) == -1) error("Error in listen()");
    
    fflush(stdout);
    
    while (1) {
        
        clilen = sizeof(client_addr);
        //int *connection = (int*)malloc(sizeof(int));
        int conn;
        conn = accept(serverSocket, (struct sockaddr *)&client_addr, (socklen_t * __restrict) &clilen);
        if (conn < 0) error("Error in accept()");
        handle_request(&conn);                          // here is where you would spawn a thread
        
    }
    
    close(serverSocket);
    free(root_path);
    
    
    
    
    return 0;
}
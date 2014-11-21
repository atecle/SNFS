

#include <stdio.h>
#include <stdlib.h>
#include "clientSNFS.h"


int main(int argc, char *argv[]) {
    
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <serverIP> <server port> <file to write>\n", argv[0]);
        exit(1);
    }
    
    
    setServer(argv[1], atoi(argv[2]));
    
    openFile("hi serveR\n");
    
    return 0;
}
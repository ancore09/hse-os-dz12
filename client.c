#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFLEN 512 
#define PORT 8888 

void die(char *s) {
    perror(s);
    exit(1);
}

int main() {
    struct sockaddr_in si_me, si_other; 
    int s;
    socklen_t slen = sizeof(si_other); 
    char buf[BUFLEN];
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        die("socket");
    }

    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr *) &si_me, sizeof(si_me)) == -1) {
        die("bind");
    }

    while (1) {
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1) {
            die("recvfrom()");
        }

        puts(buf);
    }

    close(s);
    return 0;
}
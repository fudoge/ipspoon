#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFLEN 1024

void iptohostname(int af, char* input_addr) {
    int ret;
    void* req_addr;
    socklen_t addr_len;
    if(af == AF_INET) {
        static struct sockaddr_in addr;
        struct in_addr converted;

        ret = inet_pton(AF_INET, input_addr, &converted);
        if (ret <= 0) {
            if (ret == 0)
                fprintf(stderr, "Invalid IPv4 address: %s\n", input_addr);
            else
                perror("inet_pton");
            exit(EXIT_FAILURE);
        }

        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr = converted;
            
        req_addr = (struct sockaddr *)&addr;
        addr_len = sizeof(addr);
    } else {
        static struct sockaddr_in6 addr;
        struct in6_addr converted;

        ret = inet_pton(AF_INET6, input_addr, &converted);
        if(ret <= 0) {
            if(ret == 0)
                fprintf(stderr, "Invalid IPv6 address: %s\n", input_addr);
            else 
                perror("inet_pton");
            exit(EXIT_FAILURE);
        }

        memset(&addr, 0, sizeof(addr));
        addr.sin6_family = AF_INET6;
        addr.sin6_addr = converted;

        req_addr = (struct sockaddr *)&addr;
        addr_len = sizeof(addr);
    } 

    char hbuf[BUFLEN];
    ret = getnameinfo(req_addr, addr_len, hbuf, sizeof(hbuf), NULL, 0, NI_NAMEREQD);
    if (ret != 0) {
        fprintf(stderr, "getnameinfo: %s\n", gai_strerror(ret));
        exit(EXIT_FAILURE);
    }

    printf("Domain of address - %s\n", input_addr);
    printf("   - %s\n", hbuf);
}

void hostnametoips(char* hostname) {
    struct addrinfo *res, *p;
    int ret;
    char ipstr[INET6_ADDRSTRLEN];

    if((ret = getaddrinfo(hostname, NULL, NULL, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "IP Addresses for %s:\n\n", hostname);
    for(p = res; p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;

        if(p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;            
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;            
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("    %s: %s\n", ipver, ipstr);
    }
    freeaddrinfo(res);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <option> <address or hostname>\n\t-4 <address>: get hostname from ipv4 address\n\t-6 <address>: get hostname from ipv6 address\n\t-h <hostname>: get ip addresses from hostname\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if(strcmp(argv[1], "-h") == 0) 
        hostnametoips(argv[2]);
    else if(strcmp(argv[1], "-4") == 0)
        iptohostname(AF_INET, argv[2]);
    else if(strcmp(argv[1], "-6") == 0)
        iptohostname(AF_INET6, argv[2]);
    else { 
        fprintf(stderr, "Usage: %s <option> <address or hostname>\n\t-4 <address>: get hostname from ipv4 address\n\t-6 <address>: get hostname from ipv6 address\n\t-h <hostname>: get ip addresses from hostname\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

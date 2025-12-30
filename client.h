#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#endif
#include "struc.h"

#define DEF_PORT 50100
#define MAX_LEN_NAMES 10
#define MAX_NUM_CLIENTS 5
#define MAX_LEN_BUFFER 256
#define MAX_LEN_ADDR 32
#define BROADCAST -1


typedef struct {
    int cid;
    int sock;
    int flags;
    struct sockaddr_in addr;
    char name[MAX_LEN_NAMES];
} CLIENT;

void setup_client(char* , u_short );
int control_requests();
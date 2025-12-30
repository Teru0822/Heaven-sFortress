#include <errno.h>
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif
#include <vector>
#include "../client.h"

static CLIENT clients[MAX_NUM_CLIENTS];
static int num_clients;
static fd_set mask;
static CONTAINER data;
static int sock; // UDPソケットをグローバルに定義

void setup_server(int, u_short);
int control_requests();
void terminate_server();

static void send_data(int, void *, int, struct sockaddr_in *);
static int receive_data(int, void *, int, struct sockaddr_in *);
static void handle_error(const char *);

// サーバ起動処理
void setup_server(int num_cl, u_short port)
{
    struct sockaddr_in sv_addr;

    fprintf(stderr, "Server setup is started.\n");

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        handle_error("WSAStartup failed");
    }
#endif

    num_clients = num_cl;

    // UDPソケットの作成
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        handle_error("socket()");
    }
    fprintf(stderr, "socket() for UDP is done successfully.\n");

    sv_addr.sin_family      = AF_INET;
    sv_addr.sin_port        = htons(port);
    sv_addr.sin_addr.s_addr = INADDR_ANY;

    // ソケットにバインド
    if (bind(sock, (struct sockaddr *)&sv_addr, sizeof(sv_addr)) != 0) {
        handle_error("bind()");
    }
    fprintf(stderr, "bind() is done successfully.\n");

    // クライアント数分の受け取り処理
    for (int i = 0; i < num_clients; i++) {
        socklen_t len = sizeof(clients[i].addr);
        if (receive_data(i, &data, sizeof(data), &clients[i].addr) < 0) {
            handle_error("receive_data()");
        }
        clients[i].cid = i;
        fprintf(stderr, "Client %d is accepted (name=%s, address=%s, port=%d).\n",
            i, clients[i].name, inet_ntoa(clients[i].addr.sin_addr), ntohs(clients[i].addr.sin_port));
    }

    // クライアントに初期データを送信
    for (int i = 0; i < num_clients; i++) {
        send_data(i, &num_clients, sizeof(int), &clients[i].addr); // クライアント番号
        send_data(i, &i, sizeof(int), &clients[i].addr);           // クライアントid
        for (int j = 0; j < num_clients; j++) {
            send_data(i, &clients[j], sizeof(CLIENT), &clients[i].addr);
        }
    }

    FD_ZERO(&mask);
#ifndef _WIN32
    FD_SET(0, &mask); // 標準入力を監視する
#endif

    fprintf(stderr, "Server setup is done.\n");
}

bool checkMap(int c[8][8])
{
    for(int i = 0;i < 8;i++)
    {
        for(int j = 0;j < 8;j++)
        {
            if(c[i][j] != 0)
                return false;
        }
    }
    return true;
}

// 出入力処理を管理する関数
int control_requests()
{
    fd_set read_flag;
    FD_ZERO(&read_flag);
    FD_SET(sock, &read_flag); // 全クライアントからのデータを受け取るUDPソケットを監視
#ifndef _WIN32
    if (FD_ISSET(0, &mask)) FD_SET(0, &read_flag);
#endif
    CONTAINER data;
    memset(&data, 0, sizeof(CONTAINER));
    CONTAINER *data_array = (CONTAINER *)malloc(num_clients * sizeof(CONTAINER));
    if (data_array == NULL) {
        perror("malloc failed");
        return -1;
    }
    memset(data_array, 0, num_clients * sizeof(CONTAINER));

    int datasize = 0;
    bool chessFound = false;
    Game game;
    std::vector<int> checkChessPlayer;
    for (int i = 0; i < num_clients; i++) {
        if (FD_ISSET(sock, &read_flag)) {
            // データの受け取り
            struct sockaddr_in addr;
            socklen_t addr_len = sizeof(addr);

            int recv_result = receive_data(i, &data, sizeof(data), &addr);
            if (recv_result > 0) {
                data.command = 1;
                // cidに基づいて適切なインデックスに保存（実際には受信データのcidを使うべき）
                // ただし、この実装では単純化のためにループ変数を暫定的に使用
                memcpy(&data_array[i], &data, sizeof(CONTAINER)); 
                if(data.game[0].stts == 3)
                {
                    checkChessPlayer.push_back(i);
                }
                else if(data.game[0].stts == 5)
                    data.game[0].stts = 0;
                datasize++;
            }
        }
    }
    

    // 受け取ったデータがある場合、ブロードキャスト
    if (datasize > 0) {
        if(checkChessPlayer.size() == 2)
        {
            data_array[checkChessPlayer[0]].game[0].stts = 4;
            data_array[checkChessPlayer[0]].game[0].mycolor = 0;
            data_array[checkChessPlayer[1]].game[0].stts = 4;
            data_array[checkChessPlayer[1]].game[0].mycolor = 1;
        }
        int memInt[num_clients];
        for(int i =0;i< num_clients;i++)
        {
            memInt[i] = -1;
            memInt[i] = data_array[i].cid;
        }
        bool cont = false;
        for(int i = 0;i<num_clients;i++)
        {
            if(memInt[i] > -1)
            {
                for(int j = i+1;j<num_clients-i-1;j++)
                {
                    if(memInt[i] == memInt[j])
                        cont = true;
                }
            }
        }
        if(cont == false)
        {

            send_data(BROADCAST, data_array, num_clients * sizeof(CONTAINER), NULL);
        }
    }

    // メモリを解放
    free(data_array);
    return 1;
}

// メッセージ送信処理
static void send_data(int cid, void *data, int size, struct sockaddr_in *addr)
{
    if (cid == BROADCAST) {
        for (int i = 0; i < num_clients; i++) {
            if (sendto(sock, data, size, 0, (struct sockaddr *)&clients[i].addr, sizeof(clients[i].addr)) < 0) {
                handle_error("sendto()");
            }
        }
    } else {
        if (sendto(sock, data, size, 0, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
            handle_error("sendto()");
        }
    }
}

// データ受信処理
static int receive_data(int cid, void *data, int size, struct sockaddr_in *addr)
{
    socklen_t addr_len = sizeof(*addr);
    return recvfrom(sock, data, size, 0, (struct sockaddr *)addr, &addr_len);
}

// メッセージ入力処理
static void handle_error(const char *message)
{
    perror(message);
    fprintf(stderr, "%d\n", errno);
    exit(1);
}

// 終了処理
void terminate_server(void)
{
#ifdef _WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif
    fprintf(stderr, "Server socket is closed.\n");
    exit(0);
}

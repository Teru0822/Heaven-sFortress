// program1
#include <errno.h>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif
#include <vector>
#include  "client.h"

// client
char user_name[MAX_LEN_NAMES];
int n_clients;
int my_id;
int key1;
int key2;
uint8_t my_result[30];
extern bool found1;
extern bool found2;
extern int chessMyColor;
#ifdef _WIN32
static SOCKET sock;
#else
static int sock;
#endif
extern int original_turn;
extern int fin;
extern int my_kill_count;
static struct sockaddr_in sv_addr;
static CLIENT clients[MAX_NUM_CLIENTS];
void setup_client(char*, u_short);
int control_requests();
void terminate_client();
static int in_command(void);
static int exe_command(void);
static void send_data(void*, int);
extern void makeAnim(float r, float g, float b, obj o[], GLuint tex, int anim , int MaxFrame);
static int receive_data(void*, int);
static void handle_error(const char*);

extern Game game[4];
extern Scene scene;
extern Position myPosition;
extern Position tradePos;
extern vihicle tankPos;
extern vihicle sportsPos;
CONTAINER* data_array;
movingCharPosition m_charPosition[MAX_NUM_CLIENTS];
chessInfoNet CIN;
uint8_t eneD[4];
extern chess_info ci;
extern bool firing;

extern int chessMap[8][8];

extern obj human;
extern obj sports_mainBody;
extern obj sports1light;
extern obj tankLower;
extern obj tankUpper;
extern obj tankBarrel;
extern obj canon;
extern obj explosion;
extern obj map_player;
extern obj back[25];
extern obj dash[16];
extern obj forward[26];
extern obj Idle[75];
extern obj jump[102];
extern obj left[22];
extern obj right[22];
extern obj sports2_mainbody;
extern obj sports2light;
extern obj sports3_mainbody;
extern obj sports3light;
extern obj sports4_mainbody;
extern obj sports4light;
extern obj text[26];
extern obj result_chess_win;
extern obj result_chess_lose;
extern obj result_tank_1st;
extern obj result_tank_2nd;
extern obj result_tank_3rd;
extern obj result_tank_4th;
extern obj result_shooting_kill;
extern obj result_shooting_suevived;
extern obj result_race_1st;
extern obj result_race_2nd;
extern obj result_race_3rd;
extern obj result_race_4th;
extern obj result_get_item_cheap;
extern obj result_get_item_normal;
extern obj result_get_item_expensive;
extern obj HP_frame;
extern obj HP_bar;
extern cheapObj num_0;
extern cheapObj num_1;
extern cheapObj num_2;
extern cheapObj num_3;
extern cheapObj num_4;
extern cheapObj num_5;
extern cheapObj num_6;
extern cheapObj num_7;
extern cheapObj num_8;
extern cheapObj num_9;

int checkGameStts(int s,int t)
{
    int p = 0;
    for(int i = 0;i < n_clients - 1;i++)
    {
        if(m_charPosition[i].game[s].stts == t)
            p++;
    }
    return p;
}

// クライアント接続開始時の処理
void setup_client(char* server_name, u_short port)
{
    fprintf(stderr, "Setting up client...\n");
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        handle_error("WSAStartup failed");
    }
#endif

    struct hostent *serv_host;
    struct sockaddr_in local_sv_addr; // Use a local variable for setup

    // サーバのホスト名解決
    serv_host = gethostbyname(server_name);
    if (serv_host == NULL) {
        handle_error("gethostbyname()");
    }
    fprintf(stderr, "Host resolution successful: %s\n", server_name);

    // UDPソケットの作成
    sock = socket(AF_INET, SOCK_DGRAM, 0);
#ifdef _WIN32
    if (sock == INVALID_SOCKET) {
#else
    if (sock < 0) {
#endif
        handle_error("socket()");
    }
    fprintf(stderr, "Socket created successfully.\n");

    // サーバのアドレス設定
    memset(&local_sv_addr, 0, sizeof(local_sv_addr));
    local_sv_addr.sin_family = AF_INET;
    local_sv_addr.sin_port   = htons(port);
    memcpy(&local_sv_addr.sin_addr, serv_host->h_addr, serv_host->h_length);

    // sv_addr を static 変数に保存
    ::sv_addr = local_sv_addr; 
    
    fprintf(stderr, "Input your name: ");
    if (fgets(user_name, sizeof(user_name), stdin) == NULL) {
        handle_error("fgets()");
    }
    user_name[strlen(user_name) - 1] = '\0';
    send_data(user_name, MAX_LEN_NAMES);
    printf("my name is : %s\n",user_name);
    fprintf(stderr, "Waiting for other clients...\n");
    receive_data(&n_clients, sizeof(int));
    fprintf(stderr, "Number of clients = %d.\n", n_clients);
    receive_data(&my_id, sizeof(int));
    fprintf(stderr, "Your ID = %d.\n", my_id);
    for (int i = 0; i < n_clients; i++) {
        receive_data(&clients[i], sizeof(CLIENT));
    }
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

int control_requests()
{
    fd_set read_flag;
    FD_ZERO(&read_flag);
#ifndef _WIN32
    FD_SET(0, &read_flag);    // 標準入力
#endif
    FD_SET(sock, &read_flag); // UDPソケット

    struct timeval timeout;
    timeout.tv_sec  = 0;     // 秒
    timeout.tv_usec = 30000; // タイムアウトを30ミリ秒に設定

#ifdef _WIN32
    int max_fd = 0; // Winsock select ignores this
#else
    int max_fd = (int)sock; // ソケットの最大ファイルディスクリプタ
#endif
    int result = 1;

    // データ送信
    int k = 0;
    CONTAINER data;
    memset(&data, 0, sizeof(CONTAINER));
    switch (scene) {
    case scene_5:
        std::memcpy(data.game[0].CIN.cm,CIN.cm,sizeof(CIN.cm));
        data.game[0].CIN.ci = CIN.ci;
        data.game[0].CIN.f = CIN.f;
        data.game[0].CIN.thisTurn = original_turn;
        data.game[0].mycolor = game[0].mycolor;
        data.pos = myPosition;
        break;
    case scene_6:
        data.vc = tankPos;
        data.pos = tradePos;
        break;
    case scene_7:
        data.vc = sportsPos;
        break;
    case scene_8:
        data.pos = myPosition;
        data.eneDamage[0] = eneD[0];
        data.eneDamage[1] = eneD[1];
        data.eneDamage[2] = eneD[2];
        data.eneDamage[3] = eneD[3];
        data.game[2].havingItems[my_id] = game[2].havingItems[my_id];
        break;
    default:
        data.pos = myPosition;
        data.eneDamage[0] = 0;
        data.eneDamage[1] = 0;
        data.eneDamage[2] = 0;
        data.eneDamage[3] = 0;
        break;
    }
    data.cid = my_id;
    memcpy(data.result, my_result, sizeof(my_result));
    memcpy(data.name, user_name, sizeof(user_name));
    data.game[0].stts = game[0].stts;
    data.game[1].stts = game[1].stts;
    data.game[2].stts = game[2].stts;
    data.game[3].stts = game[3].stts;
    data.game[1].p_NUM = game[1].p_NUM;
    data.game[2].p_NUM = game[2].p_NUM;
    data.game[3].p_NUM = game[3].p_NUM;
    send_data(&data, sizeof(CONTAINER));

    // `select()` で読み込み可能か確認する
#ifdef _WIN32
    int select_result = select(max_fd + 1, &read_flag, NULL, NULL, &timeout);
#else
    int select_result = select(max_fd + 1, &read_flag, NULL, NULL, &timeout);
#endif
    if (select_result == -1) {
        perror("select failed");
        return -1;
    }

    // サーバーからのデータがあるか確認
    if (FD_ISSET(sock, &read_flag)) {
        // データ受信
        data_array = (CONTAINER*)malloc(n_clients * sizeof(CONTAINER));
        if (data_array == NULL) {
            perror("malloc failed");
            return -1;
        }
        memset(data_array, 0, n_clients * sizeof(CONTAINER));

        int recv_result = receive_data(data_array, n_clients * sizeof(CONTAINER));
        if (recv_result == -1) {
            perror("receive_data failed");
            free(data_array);
            return -1;
        }
        std::vector<int> ch;
        bool cont = false;
        for(int i=0;i < n_clients;i++) 
        {
            ch.push_back(data_array[i].cid);
            if(ch.size() < 2)
            {
                continue;
            }
            else if(ch.size() == 2)
            {
                if(ch[0] == ch[1])
                {
                    cont = true;
                    break;
                }
            }
            else if(ch.size() == 3)
            {
                if(ch[0] == ch[2])
                {
                    cont = true;
                    break;                    
                }
                else if(ch[1] == ch[2])
                {
                    cont = true;
                    break;                    
                }
            }
            else
            {
                if(ch[0] == ch[3])
                {
                    cont = true;
                    break;
                }
                else if(ch[1] == ch[3])
                {
                    cont = true;
                    break;                    
                }
                else if(ch[2] == ch[3])
                {
                    cont = true;
                    break;                    
                }                
            }
        }
        if(cont == true)
            return result;

        k = 0;
        for (int i = 0; i < n_clients; i++) {
            CONTAINER c = data_array[i];
            if (c.cid != my_id && c.command != 0) //自分以外のデータ
            {
                switch (scene) {
                case scene_5://chess
                    if(c.game[0].CIN.thisTurn > original_turn)
                    {
                        CIN.ci = c.game[0].CIN.ci;
                        ci = c.game[0].CIN.ci;
                        original_turn = c.game[0].CIN.thisTurn;
                        if(c.game[0].CIN.f == 1)
                            found1 = false;
                        if(c.game[0].CIN.f == 2)
                            found2 = false;
                        //check for key piece
                        // key1 = (rand() % 5) + 2;//2~6
                        // key2 = (rand() % 5) + 8;//8~12
                        // while(key1 == key2)
                        // {
                        //     key2 = (rand() % 6) + 1;
                        // }
                        for (int i = 0; i < 8; i++)
                        {
                            for (int j = 0; j < 8; j++)
                            {
                                chessMap[i][j] = c.game[0].CIN.cm[7 - i][7 - j];
                            }
                        }                 
                    }
                    break;
                case scene_6:
                    m_charPosition[k].vc = c.vc;
                    m_charPosition[k].pos = c.pos;
                    break;
                case scene_7:
                    m_charPosition[k].vc = c.vc;
                    break;
                default:
                    if(c.game[2].havingItems[c.cid] != game[2].havingItems[c.cid])
                    {
                        game[2].havingItems[c.cid] = c.game[2].havingItems[c.cid];
                    }
                    for(int d = 0;d < 4;d++)
                    {
                        if(eneD[d] < c.eneDamage[d])
                        {
                            eneD[d] = c.eneDamage[d];
                            printf("recieve increase num\n");
                        }
                    }

                    //two player else me plays chess game
                    if(checkGameStts(0,4) > 1 && c.game[0].CIN.thisTurn > original_turn)
                    {
                        for (int i = 0; i < 8; i++)
                        {
                            for (int j = 0; j < 8; j++)
                            {
                                if(original_turn % 2 == 0)//if white
                                    chessMap[i][j] = c.game[0].CIN.cm[i][j];    
                                else
                                    chessMap[i][j] = c.game[0].CIN.cm[7 - i][7 - j];
                            }
                        }
                        CIN.ci = c.game[0].CIN.ci;
                        original_turn++;
                    }
                    if(checkGameStts(0,4) == 0)
                    {
                        original_turn = 0;
                        initChessPos();
                        int tempMap[8][8] = {
                        {2, 3, 4, 5, 6, 4, 3, 2},
                        {1, 1, 1, 1, 1, 1, 1, 1},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {7, 7, 7, 7, 7, 7, 7, 7},
                        {8, 9, 10, 11, 12, 10, 9, 8}};
                        for(int i = 0;i < 8;i++)
                        {
                            for(int j = 0;j<8;j++)
                            {
                                chessMap[i][j] = tempMap[i][j];
                            }
                        }
                    }
                    if(game[1].p_NUM < c.game[1].p_NUM)
                        game[1].p_NUM = c.game[1].p_NUM;
                    if(game[2].p_NUM < c.game[2].p_NUM)
                        game[2].p_NUM = c.game[2].p_NUM;
                    if(game[3].p_NUM < c.game[3].p_NUM)
                        game[3].p_NUM = c.game[3].p_NUM;
                    m_charPosition[k].pos = c.pos;
                    break;
                }
                for(int j = 0; j< 4;j++)
                {
                    m_charPosition[k].game[j] = c.game[j];
                }
                m_charPosition[k].id = c.cid;
                memcpy(m_charPosition[k].name, c.name, sizeof(c.name));
                memcpy(m_charPosition[k].result, c.result, sizeof(c.result));
                k++;
            }
            else if(c.cid == my_id && c.command != 0)
            {
                for(int d = 0;d < 4;d++)
                {
                    if(eneD[d] < c.eneDamage[d])
                    {
                        eneD[d] = c.eneDamage[d];
                        printf("recieve increase num\n");
                    }
                }
                if(c.game[0].stts > game[0].stts)
                {
                    game[0].stts = c.game[0].stts;
                    game[0].mycolor = c.game[0].mycolor;
                }
            }
        }
        if(game[0].stts == 2)
        {
            //自分がホストで誰かがjoinしたらゲームスタート
            if(checkGameStts(0,3) > 0)
                game[0].stts = 3;
        } 
    }
    return result;
}

static void send_data(void* data, int size)
{
    if ((data == NULL) || (size <= 0)) {
        fprintf(stderr, "send_data(): data is illegal.\n");
        exit(1);
    }
    if (sendto(sock, (const char*)data, size, 0, (struct sockaddr*)&sv_addr, sizeof(sv_addr)) == -1) {
        handle_error("sendto()");
    }
}

static int receive_data(void* data, int size)
{
    if ((data == NULL) || (size <= 0)) {
        fprintf(stderr, "receive_data(): data is illegal.\n");
        exit(1);
    }
    socklen_t addr_len = sizeof(sv_addr);
    return recvfrom(sock, (char*)data, size, 0, (struct sockaddr*)&sv_addr, &addr_len);
}

void handle_error(const char* message)
{
    perror(message);
    fprintf(stderr, "%d\n", errno);
    exit(1);
}

void terminate_client()
{
    fprintf(stderr, "Closing client socket...\n");
#ifdef _WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif
    fprintf(stderr, "Connection is closed.\n");
    exit(0);
}

void make_chess_win(int p)
{
    //数字はまずz軸に対して180度回転させてz軸正に0.267105移動して74倍する
    //y:9.70466 
    result_chess_win.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 9.70466f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();

}

void makeHP(uint8_t damage)
{
    HP_frame.make(1,1,0);
    int d = damage / 3;
    int i ;
    for(i = 0;i < 32;i++)
    {
        if(i < 32-d)
        {
            glPushMatrix();
            glTranslatef(0,-0.004139378667f * i,0);
            HP_bar.make(0,1,0);
            glPopMatrix();
        }
        else
        {
            glPushMatrix();
            glTranslatef(0,-0.004139378667f * i,0);
            HP_bar.make(1,0,0);
            glPopMatrix();
        }
    }
}

void make_MYHP()
{
    HP_frame.make(1,1,0);
    int myhp = 100 - eneD[my_id];
    int d = eneD[my_id] / 3;
    int i ;
    float num_scale = 0.8f;
    for(i = 0;i < 32;i++)
    {
        if(i < 32-d)
        {
            glPushMatrix();
            glTranslatef(0,-0.004139378667f * i,0);
            HP_bar.make(0,1,0);
            glPopMatrix();
        }
        else
        {
            glPushMatrix();
            glTranslatef(0,-0.004139378667f * i,0);
            HP_bar.make(1,0,0);
            glPopMatrix();
        }
    }
    int dec3 = myhp / 100;
    int dec2 = (myhp % 100) / 10;
    int dec1 = (myhp % 10);
    if(dec3 != 0)                               //100
    {
        glPushMatrix();
        glTranslatef(0,0.021807,0.081012);
        glScalef(num_scale,num_scale,num_scale);
        glTranslatef(0,0,0.016115);
        num_1.make(1,1,1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0.015764,0.081012);
        glScalef(num_scale,num_scale,num_scale);
        glTranslatef(0,0,0.016115);
        num_0.make(1,1,1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0,0.007882,0.081012);
        glScalef(num_scale,num_scale,num_scale);
        glTranslatef(0,0,0.016115);
        num_0.make(1,1,1);
        glPopMatrix();
    }
    else if(dec3 == 0 && dec2 != 0)             //10~99
    {
        switch(dec2)
        {
            case 1:
                glPushMatrix();
                glTranslatef(0,0.015764,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_1.make(1,1,1);
                glPopMatrix();
                break;
            case 2:
                glPushMatrix();
                glTranslatef(0,0.015764,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_2.make(1,1,1);
                glPopMatrix();
                break;
            case 3:
                glPushMatrix();
                glTranslatef(0,0.015764,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_3.make(1,1,1);
                glPopMatrix();
                break;
            case 4:
                glPushMatrix();
                glTranslatef(0,0.015764,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_4.make(1,1,1);
                glPopMatrix();
                break;
            case 5:
                glPushMatrix();
                glTranslatef(0,0.015764,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_5.make(1,1,1);
                glPopMatrix();
                break;
            case 6:
                glPushMatrix();
                glTranslatef(0,0.015764,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_6.make(1,1,1);
                glPopMatrix();
                break;
            case 7:
                glPushMatrix();
                glTranslatef(0,0.015764,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_7.make(1,1,1);
                glPopMatrix();
                break;
            case 8:
                glPushMatrix();
                glTranslatef(0,0.015764,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_8.make(1,1,1);
                glPopMatrix();
                break;
            case 9:
                glPushMatrix();
                glTranslatef(0,0.015764,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_9.make(1,1,1);
                glPopMatrix();
                break;
        }
        switch(dec1)
        {
            case 0:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_0.make(1,1,1);
                glPopMatrix();
                break;
            case 1:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_1.make(1,1,1);
                glPopMatrix();
                break;
            case 2:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_2.make(1,1,1);
                glPopMatrix();
                break;
            case 3:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_3.make(1,1,1);
                glPopMatrix();
                break;
            case 4:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_4.make(1,1,1);
                glPopMatrix();
                break;
            case 5:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_5.make(1,1,1);
                glPopMatrix();
                break;
            case 6:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_6.make(1,1,1);
                glPopMatrix();
                break;
            case 7:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_7.make(1,1,1);
                glPopMatrix();
                break;
            case 8:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_8.make(1,1,1);
                glPopMatrix();
                break;
            case 9:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_9.make(1,1,1);
                glPopMatrix();
                break;
        }
    }
    else if(dec3 == 0 && dec2 == 0 && dec1 >= 0)//1~9
    {
        switch(dec1)
        {
            case 1:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_1.make(1,1,1);
                glPopMatrix();
                break;
            case 2:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_2.make(1,1,1);
                glPopMatrix();
                break;
            case 3:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_3.make(1,1,1);
                glPopMatrix();
                break;
            case 4:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_4.make(1,1,1);
                glPopMatrix();
                break;
            case 5:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_5.make(1,1,1);
                glPopMatrix();
                break;
            case 6:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_6.make(1,1,1);
                glPopMatrix();
                break;
            case 7:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_7.make(1,1,1);
                glPopMatrix();
                break;
            case 8:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_8.make(1,1,1);
                glPopMatrix();
                break;
            case 9:
                glPushMatrix();
                glTranslatef(0,0.007882,0.081012);
                glScalef(num_scale,num_scale,num_scale);
                glTranslatef(0,0,0.016115);
                num_9.make(1,1,1);
                glPopMatrix();
                break;
        }
    }
    else                                        //0
    {
        glPushMatrix();
        glTranslatef(0,0.007882,0.081012);
        glScalef(num_scale,num_scale,num_scale);
        glTranslatef(0,0,0.016115);
        num_0.make(1,0,0);
        glPopMatrix();
    }
}

void make_chess_lose(int p)
{
    result_chess_lose.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 9.70466f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();
}

void make_race_1st(int p)
{
    //y:7.98491
    result_race_1st.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 7.98491f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();
}

void make_race_2nd(int p)
{
    result_race_2nd.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 7.98491f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();
}

void make_race_3rd(int p)
{
    result_race_3rd.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 7.98491f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();
}

void make_race_4th(int p)
{
    result_race_4th.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 7.98491f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();
}

void make_tank_1st(int p)
{
    //y:11.0409
    result_tank_1st.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 11.0409f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();
}

void make_tank_2nd(int p)
{
    result_tank_2nd.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 11.0409f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();
}

void make_tank_3rd(int p)
{
    result_tank_3rd.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 11.0409f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();
}

void make_tank_4th(int p)
{
    result_tank_4th.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 11.0409f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();
}

void make_shooting_survived(int p)
{
    //y:9.32115
    result_shooting_suevived.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 9.32115f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();

}

void make_shooting_kill(int p)
{
    result_shooting_kill.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 9.32115f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();
}

void make_get_item_cheap(int p)
{
    //y:8.36832 
    result_get_item_cheap.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 8.36832f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();
}

void make_get_item_normal(int p)
{
    //y:7.58979
    result_get_item_normal.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 7.58979f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();
}

void make_get_item_expensive(int p)
{
    //y:9.13524
    result_get_item_expensive.make(1.0f,1.0f,1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 9.13524f, 0.290341f);
    glScalef(74.0f,74.0f,74.0f);
    glRotatef(180.0f, 0, 0, 1);
    glTranslatef(0.0f, 0.0f, 0.016115f);
    switch (p)
    {
    case 0:
        num_0.make(1.0f, 1.0f, 1.0f);
        break;
    case 1:
        num_1.make(1.0f, 1.0f, 1.0f);
        break;
    case 2:
        num_2.make(1.0f, 1.0f, 1.0f);
        break;
    case 3:
        num_3.make(1.0f, 1.0f, 1.0f);
        break;
    case 4:
        num_4.make(1.0f, 1.0f, 1.0f);
        break;
    case 5:
        num_5.make(1.0f, 1.0f, 1.0f);
        break;
    case 6:
        num_6.make(1.0f, 1.0f, 1.0f);
        break;
    case 7:
        num_7.make(1.0f, 1.0f, 1.0f);
        break;
    case 8:
        num_8.make(1.0f, 1.0f, 1.0f);
        break;
    case 9:
        num_9.make(1.0f, 1.0f, 1.0f);
        break;
    }
    glPopMatrix();
}

void makeResultArray(uint8_t r,int t,int p)
{
    glPushMatrix();
    //p = 0 = left,p = 1 = right    
    if(p == 0) 
    {
        glTranslatef(0.0f, -12.699f, 4.3371f - (1.192f * t));
    }
    else
    {
        glTranslatef(0.0f, 0.62454f, 4.3371f - (1.192f * t));
    }
    switch (r)
    {
    case 1:
        make_chess_win(8);
        break;
    case 2:
        make_chess_lose(4);
        break;
    case 3:
        make_race_1st(8);
        break;
    case 4:
        make_race_2nd(6);
        break;
    case 5:
        make_race_3rd(4);
        break;
    case 6:
        make_race_4th(2);
        break;
    case 7:
        make_tank_1st(8);
        break;
    case 8:
        make_tank_2nd(6);
        break;
    case 9:
        make_tank_3rd(4);
        break;
    case 10:
        make_tank_4th(2);
        break;
    case 11:
        make_shooting_survived(4);
        break;
    case 12:
        make_shooting_kill(2);
        break;
    case 13:
        make_get_item_cheap(2);
        break;
    case 14:
        make_get_item_normal(4);
        break;
    case 15:
        make_get_item_expensive(6);
        break;
    }
    glPopMatrix();
}

bool compare_points(const res_point &a, const res_point &b) {
    return a.points > b.points;
}

void makeResult()
{
    res_point all_points[4];
    res_point sorted_points[4];
    uint8_t points = 0;
    //my result
    switch (my_id) 
    {
    case 0:        
        glPushMatrix();
        glTranslatef(-50.4905f, -22.4039f, 10.6473f);
        glRotatef(25.0f, 0, 0, 1);
        glRotatef(8.0f, 0, 1, 0);

        //sum 30 game points
        for(int i = 0;i < 30;i++)
        {
            if(my_result[i] == 0)
                break;
            switch (my_result[i])
            {
            case 1:
                points += 8;
                break;
            case 2:
                points += 4;
                break;
            case 3:
                points += 8;
                break;
            case 4:
                points += 6;
                break;
            case 5:
                points += 4;
                break;
            case 6:
                points += 2;
                break;
            case 7:
                points += 8;
                break;
            case 8:
                points += 6;
                break;
            case 9:
                points += 4;
                break;
            case 10:
                points += 2;
                break;
            case 11:
                points += 4;
                break;
            case 12:
                points += 2;
                break;
            case 13:
                points += 2;
                break;
            case 14:
                points += 4;
                break;
            case 15:
                points += 6;
                break;
            }
            makeResultArray(my_result[i],i,0);
        }
        

        all_points[0].index = my_id;
        all_points[0].points = points;

        //name
        for(int i =0;i < 10;i++)
        {
            char c = user_name[i];
            if(c == '\0')
                break;
            glPushMatrix();
            glTranslatef(0.196045f, -12.4715f + (0.5f * i), 6.86016f);
            glScalef(1.6518f,1.6518f,1.6518f);
            glRotatef(180.0f, 0, 0, 1);
            if(c == 'A' || c ==  'a')
            {
                text[0].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'B' || c ==  'b')
            {
                text[1].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'C' || c ==  'c')
            {
                text[2].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'D' || c ==  'd')
            {
                text[3].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'E' || c ==  'e')
            {
                text[4].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'F' || c ==  'f')
            {
                text[5].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'G' || c ==  'g')
            {
                text[6].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'H' || c ==  'h')
            {
                text[7].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'I' || c ==  'i')
            {
                text[8].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'J' || c ==  'j')
            {
                text[9].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'K' || c ==  'k')
            {
                text[10].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'L' || c ==  'l')
            {
                text[11].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'M' || c ==  'm')
            {
                text[12].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'N' || c ==  'n')
            {
                text[13].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'O' || c ==  'o')
            {
                text[14].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'P' || c ==  'p')
            {
                text[15].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'Q' || c ==  'q')
            {
                text[16].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'R' || c ==  'r')
            {
                text[17].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'S' || c ==  's')
            {
                text[18].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'T' || c ==  't')
            {
                text[19].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'U' || c ==  'u')
            {
                text[20].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'V' || c ==  'v')
            {
                text[21].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'W' || c ==  'w')
            {
                text[22].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'X' || c ==  'x')
            {
                text[23].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'Y' || c ==  'y')
            {
                text[24].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'Z' || c ==  'z')
            {
                text[25].make(1.0f,1.0f,1.0f);
            }            
            glPopMatrix();
        }
        glPopMatrix();
        break;
    case 1:
        glPushMatrix();
        glTranslatef(-50.4905f, -22.4039f, 10.6473f);
        glRotatef(25.0f, 0, 0, 1);
        glRotatef(8.0f, 0, 1, 0);

        for(int i = 0;i < 30;i++)
        {
            if(my_result[i] == 0)
                break;
            switch (my_result[i])
            {
            case 1:
                points += 8;
                break;
            case 2:
                points += 4;
                break;
            case 3:
                points += 8;
                break;
            case 4:
                points += 6;
                break;
            case 5:
                points += 4;
                break;
            case 6:
                points += 2;
                break;
            case 7:
                points += 8;
                break;
            case 8:
                points += 6;
                break;
            case 9:
                points += 4;
                break;
            case 10:
                points += 2;
                break;
            case 11:
                points += 4;
                break;
            case 12:
                points += 2;
                break;
            case 13:
                points += 2;
                break;
            case 14:
                points += 4;
                break;
            case 15:
                points += 6;
                break;
            }
            makeResultArray(my_result[i],i,1);
        }
        all_points[0].index = my_id;
        all_points[0].points = points;

        for(int i =0;i < 10;i++)
        {
            char c = user_name[i];
            if(c == '\0')
                break;
            glPushMatrix();
            glTranslatef(0.196045f, 0.82167f + (0.5f * i), 6.86016f);
            glScalef(1.6518f,1.6518f,1.6518f);
            glRotatef(180.0f, 0, 0, 1);
            if(c == 'A' || c ==  'a')
            {
                text[0].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'B' || c ==  'b')
            {
                text[1].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'C' || c ==  'c')
            {
                text[2].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'D' || c ==  'd')
            {
                text[3].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'E' || c ==  'e')
            {
                text[4].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'F' || c ==  'f')
            {
                text[5].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'G' || c ==  'g')
            {
                text[6].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'H' || c ==  'h')
            {
                text[7].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'I' || c ==  'i')
            {
                text[8].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'J' || c ==  'j')
            {
                text[9].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'K' || c ==  'k')
            {
                text[10].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'L' || c ==  'l')
            {
                text[11].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'M' || c ==  'm')
            {
                text[12].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'N' || c ==  'n')
            {
                text[13].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'O' || c ==  'o')
            {
                text[14].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'P' || c ==  'p')
            {
                text[15].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'Q' || c ==  'q')
            {
                text[16].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'R' || c ==  'r')
            {
                text[17].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'S' || c ==  's')
            {
                text[18].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'T' || c ==  't')
            {
                text[19].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'U' || c ==  'u')
            {
                text[20].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'V' || c ==  'v')
            {
                text[21].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'W' || c ==  'w')
            {
                text[22].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'X' || c ==  'x')
            {
                text[23].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'Y' || c ==  'y')
            {
                text[24].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'Z' || c ==  'z')
            {
                text[25].make(1.0f,1.0f,1.0f);
            }            
            glPopMatrix();
        }
        glPopMatrix();
        break;   
    case 2:
        glPushMatrix();
        glTranslatef(-50.923f, 25.811f, 10.6473f);
        glRotatef(-27.677f, 0, 0, 1);
        glRotatef(8.0f, 0, 1, 0);
        for(int i = 0;i < 30;i++)
        {
            if(my_result[i] == 0)
                break;
            switch (my_result[i])
            {
            case 1:
                points += 8;
                break;
            case 2:
                points += 4;
                break;
            case 3:
                points += 8;
                break;
            case 4:
                points += 6;
                break;
            case 5:
                points += 4;
                break;
            case 6:
                points += 2;
                break;
            case 7:
                points += 8;
                break;
            case 8:
                points += 6;
                break;
            case 9:
                points += 4;
                break;
            case 10:
                points += 2;
                break;
            case 11:
                points += 4;
                break;
            case 12:
                points += 2;
                break;
            case 13:
                points += 2;
                break;
            case 14:
                points += 4;
                break;
            case 15:
                points += 6;
                break;
            }
            makeResultArray(my_result[i],i,0);
        }
        all_points[0].index = my_id;
        all_points[0].points = points;

        for(int i =0;i < 10;i++)
        {
            char c = user_name[i];
            if(c == '\0')
                break;
            glPushMatrix();
            glTranslatef(0.196045f, -12.4715f + (0.5f * i), 6.86016f);
            glScalef(1.6518f,1.6518f,1.6518f);
            glRotatef(180.0f, 0, 0, 1);
            if(c == 'A' || c ==  'a')
            {
                text[0].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'B' || c ==  'b')
            {
                text[1].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'C' || c ==  'c')
            {
                text[2].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'D' || c ==  'd')
            {
                text[3].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'E' || c ==  'e')
            {
                text[4].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'F' || c ==  'f')
            {
                text[5].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'G' || c ==  'g')
            {
                text[6].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'H' || c ==  'h')
            {
                text[7].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'I' || c ==  'i')
            {
                text[8].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'J' || c ==  'j')
            {
                text[9].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'K' || c ==  'k')
            {
                text[10].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'L' || c ==  'l')
            {
                text[11].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'M' || c ==  'm')
            {
                text[12].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'N' || c ==  'n')
            {
                text[13].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'O' || c ==  'o')
            {
                text[14].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'P' || c ==  'p')
            {
                text[15].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'Q' || c ==  'q')
            {
                text[16].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'R' || c ==  'r')
            {
                text[17].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'S' || c ==  's')
            {
                text[18].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'T' || c ==  't')
            {
                text[19].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'U' || c ==  'u')
            {
                text[20].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'V' || c ==  'v')
            {
                text[21].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'W' || c ==  'w')
            {
                text[22].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'X' || c ==  'x')
            {
                text[23].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'Y' || c ==  'y')
            {
                text[24].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'Z' || c ==  'z')
            {
                text[25].make(1.0f,1.0f,1.0f);
            }            
            glPopMatrix();
        }
        glPopMatrix();    
        break;   
    case 3:
        glPushMatrix();
        glTranslatef(-50.923f, 25.811f, 10.6473f);
        glRotatef(-27.677f, 0, 0, 1);
        glRotatef(8.0f, 0, 1, 0);
        for(int i = 0;i < 30;i++)
        {
            if(my_result[i] == 0)
                break;
            switch (my_result[i])
            {
            case 1:
                points += 8;
                break;
            case 2:
                points += 4;
                break;
            case 3:
                points += 8;
                break;
            case 4:
                points += 6;
                break;
            case 5:
                points += 4;
                break;
            case 6:
                points += 2;
                break;
            case 7:
                points += 8;
                break;
            case 8:
                points += 6;
                break;
            case 9:
                points += 4;
                break;
            case 10:
                points += 2;
                break;
            case 11:
                points += 4;
                break;
            case 12:
                points += 2;
                break;
            case 13:
                points += 2;
                break;
            case 14:
                points += 4;
                break;
            case 15:
                points += 6;
                break;
            }
            makeResultArray(my_result[i],i,1);
        }
        all_points[0].index = my_id;
        all_points[0].points = points;
        
        for(int i =0;i < 10;i++)
        {
            char c = user_name[i];
            if(c == '\0')
                break;
            glPushMatrix();
            glTranslatef(0.196045f, 0.82167f + (0.5f * i), 6.86016f);
            glScalef(1.6518f,1.6518f,1.6518f);
            glRotatef(180.0f, 0, 0, 1);
            if(c == 'A' || c ==  'a')
            {
                text[0].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'B' || c ==  'b')
            {
                text[1].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'C' || c ==  'c')
            {
                text[2].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'D' || c ==  'd')
            {
                text[3].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'E' || c ==  'e')
            {
                text[4].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'F' || c ==  'f')
            {
                text[5].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'G' || c ==  'g')
            {
                text[6].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'H' || c ==  'h')
            {
                text[7].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'I' || c ==  'i')
            {
                text[8].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'J' || c ==  'j')
            {
                text[9].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'K' || c ==  'k')
            {
                text[10].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'L' || c ==  'l')
            {
                text[11].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'M' || c ==  'm')
            {
                text[12].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'N' || c ==  'n')
            {
                text[13].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'O' || c ==  'o')
            {
                text[14].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'P' || c ==  'p')
            {
                text[15].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'Q' || c ==  'q')
            {
                text[16].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'R' || c ==  'r')
            {
                text[17].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'S' || c ==  's')
            {
                text[18].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'T' || c ==  't')
            {
                text[19].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'U' || c ==  'u')
            {
                text[20].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'V' || c ==  'v')
            {
                text[21].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'W' || c ==  'w')
            {
                text[22].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'X' || c ==  'x')
            {
                text[23].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'Y' || c ==  'y')
            {
                text[24].make(1.0f,1.0f,1.0f);
            }
            else if(c == 'Z' || c ==  'z')
            {
                text[25].make(1.0f,1.0f,1.0f);
            }            
            glPopMatrix();
        }
        glPopMatrix();   
        break;   
    }

    //enemy result
    for (int i = 0; i < n_clients - 1; i++) {
        int id     = m_charPosition[i].id;
        char cn[10];
        points = 0;
        memcpy(cn, m_charPosition[i].name, sizeof(m_charPosition[i].name));
        switch (id) {
        case 0:
            glPushMatrix();
            glTranslatef(-50.4905f, -22.4039f, 10.6473f);
            glRotatef(25.0f, 0, 0, 1);
            glRotatef(8.0f, 0, 1, 0);
            for(int j = 0;j < 30;j++)
            {
                if(m_charPosition[i].result[j] == 0)
                    break;
                switch (m_charPosition[i].result[j])
                {
                case 1:
                    points += 8;
                    break;
                case 2:
                    points += 4;
                    break;
                case 3:
                    points += 8;
                    break;
                case 4:
                    points += 6;
                    break;
                case 5:
                    points += 4;
                    break;
                case 6:
                    points += 2;
                    break;
                case 7:
                    points += 8;
                    break;
                case 8:
                    points += 6;
                    break;
                case 9:
                    points += 4;
                    break;
                case 10:
                    points += 2;
                    break;
                case 11:
                    points += 4;
                    break;
                case 12:
                    points += 2;
                    break;
                case 13:
                    points += 2;
                    break;
                case 14:
                    points += 4;
                    break;
                case 15:
                    points += 6;
                    break;
                }
                makeResultArray(m_charPosition[i].result[j],j,0);
            }
            all_points[i + 1].index = id;
            all_points[i + 1].points = points;
            for(int j  = 0;j<10;j++)
            {
                char c = cn[j];
                if(c == '\0')
                    break;
                glPushMatrix();
                glTranslatef(0.196045f, -12.4715f + (0.5f * j), 6.86016f);
                glScalef(1.6518f,1.6518f,1.6518f);
                glRotatef(180.0f, 0, 0, 1);
                if(c == 'A' || c ==  'a')
                {
                    text[0].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'B' || c ==  'b')
                {
                    text[1].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'C' || c ==  'c')
                {
                    text[2].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'D' || c ==  'd')
                {
                    text[3].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'E' || c ==  'e')
                {
                    text[4].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'F' || c ==  'f')
                {
                    text[5].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'G' || c ==  'g')
                {
                    text[6].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'H' || c ==  'h')
                {
                    text[7].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'I' || c ==  'i')
                {
                    text[8].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'J' || c ==  'j')
                {
                    text[9].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'K' || c ==  'k')
                {
                    text[10].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'L' || c ==  'l')
                {
                    text[11].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'M' || c ==  'm')
                {
                    text[12].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'N' || c ==  'n')
                {
                    text[13].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'O' || c ==  'o')
                {
                    text[14].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'P' || c ==  'p')
                {
                    text[15].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Q' || c ==  'q')
                {
                    text[16].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'R' || c ==  'r')
                {
                    text[17].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'S' || c ==  's')
                {
                    text[18].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'T' || c ==  't')
                {
                    text[19].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'U' || c ==  'u')
                {
                    text[20].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'V' || c ==  'v')
                {
                    text[21].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'W' || c ==  'w')
                {
                    text[22].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'X' || c ==  'x')
                {
                    text[23].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Y' || c ==  'y')
                {
                    text[24].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Z' || c ==  'z')
                {
                    text[25].make(1.0f,1.0f,1.0f);
                }            
                glPopMatrix();
            }
            glPopMatrix();
            break;
        case 1:
            glPushMatrix();
            glTranslatef(-50.4905f, -22.4039f, 10.6473f);
            glRotatef(25.0f, 0, 0, 1);
            glRotatef(8.0f, 0, 1, 0);
            for(int j = 0;j < 30;j++)
            {
                if(m_charPosition[i].result[j] == 0)
                    break;
                switch (m_charPosition[i].result[j])
                {
                case 1:
                    points += 8;
                    break;
                case 2:
                    points += 4;
                    break;
                case 3:
                    points += 8;
                    break;
                case 4:
                    points += 6;
                    break;
                case 5:
                    points += 4;
                    break;
                case 6:
                    points += 2;
                    break;
                case 7:
                    points += 8;
                    break;
                case 8:
                    points += 6;
                    break;
                case 9:
                    points += 4;
                    break;
                case 10:
                    points += 2;
                    break;
                case 11:
                    points += 4;
                    break;
                case 12:
                    points += 2;
                    break;
                case 13:
                    points += 2;
                    break;
                case 14:
                    points += 4;
                    break;
                case 15:
                    points += 6;
                    break;
                }
                makeResultArray(m_charPosition[i].result[j],j,1);
            }
            all_points[i + 1].index = id;
            all_points[i + 1].points = points;
            for(int j  = 0;j<10;j++)
            {
                char c = cn[j];
                if(c == '\0')
                    break;
                glPushMatrix();
                glTranslatef(0.196045f, 0.82167f + (0.5f * j), 6.86016f);
                glScalef(1.6518f,1.6518f,1.6518f);
                glRotatef(180.0f, 0, 0, 1);
                if(c == 'A' || c ==  'a')
                {
                    text[0].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'B' || c ==  'b')
                {
                    text[1].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'C' || c ==  'c')
                {
                    text[2].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'D' || c ==  'd')
                {
                    text[3].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'E' || c ==  'e')
                {
                    text[4].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'F' || c ==  'f')
                {
                    text[5].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'G' || c ==  'g')
                {
                    text[6].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'H' || c ==  'h')
                {
                    text[7].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'I' || c ==  'i')
                {
                    text[8].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'J' || c ==  'j')
                {
                    text[9].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'K' || c ==  'k')
                {
                    text[10].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'L' || c ==  'l')
                {
                    text[11].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'M' || c ==  'm')
                {
                    text[12].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'N' || c ==  'n')
                {
                    text[13].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'O' || c ==  'o')
                {
                    text[14].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'P' || c ==  'p')
                {
                    text[15].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Q' || c ==  'q')
                {
                    text[16].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'R' || c ==  'r')
                {
                    text[17].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'S' || c ==  's')
                {
                    text[18].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'T' || c ==  't')
                {
                    text[19].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'U' || c ==  'u')
                {
                    text[20].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'V' || c ==  'v')
                {
                    text[21].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'W' || c ==  'w')
                {
                    text[22].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'X' || c ==  'x')
                {
                    text[23].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Y' || c ==  'y')
                {
                    text[24].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Z' || c ==  'z')
                {
                    text[25].make(1.0f,1.0f,1.0f);
                }            
                glPopMatrix();
            }
            glPopMatrix();
            break;
        case 2:
            glPushMatrix();
            glTranslatef(-50.923f, 25.811f, 10.6473f);
            glRotatef(-27.677f, 0, 0, 1);
            glRotatef(8.0f, 0, 1, 0);
            for(int j = 0;j < 30;j++)
            {
                if(m_charPosition[i].result[j] == 0)
                    break;
                switch (m_charPosition[i].result[j])
                {
                case 1:
                    points += 8;
                    break;
                case 2:
                    points += 4;
                    break;
                case 3:
                    points += 8;
                    break;
                case 4:
                    points += 6;
                    break;
                case 5:
                    points += 4;
                    break;
                case 6:
                    points += 2;
                    break;
                case 7:
                    points += 8;
                    break;
                case 8:
                    points += 6;
                    break;
                case 9:
                    points += 4;
                    break;
                case 10:
                    points += 2;
                    break;
                case 11:
                    points += 4;
                    break;
                case 12:
                    points += 2;
                    break;
                case 13:
                    points += 2;
                    break;
                case 14:
                    points += 4;
                    break;
                case 15:
                    points += 6;
                    break;
                }
                makeResultArray(m_charPosition[i].result[j],j,0);
            }
            all_points[i + 1].index = id;
            all_points[i + 1].points = points;
            for(int j  = 0;j<10;j++)
            {
                char c = cn[j];
                if(c == '\0')
                    break;
                glPushMatrix();
                glTranslatef(0.196045f, -12.4715f + (0.5f * j), 6.86016f);
                glScalef(1.6518f,1.6518f,1.6518f);
                glRotatef(180.0f, 0, 0, 1);
                if(c == 'A' || c ==  'a')
                {
                    text[0].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'B' || c ==  'b')
                {
                    text[1].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'C' || c ==  'c')
                {
                    text[2].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'D' || c ==  'd')
                {
                    text[3].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'E' || c ==  'e')
                {
                    text[4].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'F' || c ==  'f')
                {
                    text[5].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'G' || c ==  'g')
                {
                    text[6].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'H' || c ==  'h')
                {
                    text[7].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'I' || c ==  'i')
                {
                    text[8].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'J' || c ==  'j')
                {
                    text[9].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'K' || c ==  'k')
                {
                    text[10].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'L' || c ==  'l')
                {
                    text[11].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'M' || c ==  'm')
                {
                    text[12].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'N' || c ==  'n')
                {
                    text[13].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'O' || c ==  'o')
                {
                    text[14].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'P' || c ==  'p')
                {
                    text[15].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Q' || c ==  'q')
                {
                    text[16].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'R' || c ==  'r')
                {
                    text[17].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'S' || c ==  's')
                {
                    text[18].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'T' || c ==  't')
                {
                    text[19].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'U' || c ==  'u')
                {
                    text[20].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'V' || c ==  'v')
                {
                    text[21].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'W' || c ==  'w')
                {
                    text[22].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'X' || c ==  'x')
                {
                    text[23].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Y' || c ==  'y')
                {
                    text[24].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Z' || c ==  'z')
                {
                    text[25].make(1.0f,1.0f,1.0f);
                }            
                glPopMatrix();
            }
            glPopMatrix();
            break;
        case 3:
            glPushMatrix();
            glTranslatef(-50.923f, 25.811f, 10.6473f);
            glRotatef(-27.677f, 0, 0, 1);
            glRotatef(8.0f, 0, 1, 0);
            for(int j = 0;j < 30;j++)
            {
                if(m_charPosition[i].result[j] == 0)
                    break;
                switch (m_charPosition[i].result[j])
                {
                case 1:
                    points += 8;
                    break;
                case 2:
                    points += 4;
                    break;
                case 3:
                    points += 8;
                    break;
                case 4:
                    points += 6;
                    break;
                case 5:
                    points += 4;
                    break;
                case 6:
                    points += 2;
                    break;
                case 7:
                    points += 8;
                    break;
                case 8:
                    points += 6;
                    break;
                case 9:
                    points += 4;
                    break;
                case 10:
                    points += 2;
                    break;
                case 11:
                    points += 4;
                    break;
                case 12:
                    points += 2;
                    break;
                case 13:
                    points += 2;
                    break;
                case 14:
                    points += 4;
                    break;
                case 15:
                    points += 6;
                    break;
                }
                makeResultArray(m_charPosition[i].result[j],j,1);
            }
            all_points[i + 1].index = id;
            all_points[i + 1].points = points;
            for(int j  = 0;j<10;j++)
            {
                char c = cn[j];
                if(c == '\0')
                    break;
                glPushMatrix();
                glTranslatef(0.196045f, 0.82167f + (0.5f * j), 6.86016f);
                glScalef(1.6518f,1.6518f,1.6518f);
                glRotatef(180.0f, 0, 0, 1);
                if(c == 'A' || c ==  'a')
                {
                    text[0].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'B' || c ==  'b')
                {
                    text[1].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'C' || c ==  'c')
                {
                    text[2].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'D' || c ==  'd')
                {
                    text[3].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'E' || c ==  'e')
                {
                    text[4].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'F' || c ==  'f')
                {
                    text[5].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'G' || c ==  'g')
                {
                    text[6].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'H' || c ==  'h')
                {
                    text[7].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'I' || c ==  'i')
                {
                    text[8].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'J' || c ==  'j')
                {
                    text[9].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'K' || c ==  'k')
                {
                    text[10].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'L' || c ==  'l')
                {
                    text[11].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'M' || c ==  'm')
                {
                    text[12].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'N' || c ==  'n')
                {
                    text[13].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'O' || c ==  'o')
                {
                    text[14].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'P' || c ==  'p')
                {
                    text[15].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Q' || c ==  'q')
                {
                    text[16].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'R' || c ==  'r')
                {
                    text[17].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'S' || c ==  's')
                {
                    text[18].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'T' || c ==  't')
                {
                    text[19].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'U' || c ==  'u')
                {
                    text[20].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'V' || c ==  'v')
                {
                    text[21].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'W' || c ==  'w')
                {
                    text[22].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'X' || c ==  'x')
                {
                    text[23].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Y' || c ==  'y')
                {
                    text[24].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Z' || c ==  'z')
                {
                    text[25].make(1.0f,1.0f,1.0f);
                }            
                glPopMatrix();
            }
            glPopMatrix();
            break;
        }
    }


    for (int i = 0; i < n_clients; i++) {
        int maxIndex = -1;
        int maxPoints = -1;

        for (int j = 0; j < n_clients; j++) {
            bool alreadySorted = false;

            for (int k = 0; k < i; k++) {
                if (all_points[j].index == sorted_points[k].index) {
                    alreadySorted = true;
                    break;
                }
            }

            if (alreadySorted) continue;

            // 得点が同じ場合は、id が若いほうを選ぶ
            if (all_points[j].points > maxPoints ||
                (all_points[j].points == maxPoints && all_points[j].index < all_points[maxIndex].index)) {
                maxPoints = all_points[j].points;
                maxIndex = j;
            }
        }

        if (maxIndex != -1) {
            sorted_points[i] = all_points[maxIndex];
        }
    }



    //for (int i = 0; i < n_clients; i++) {
    //    int maxIndex = -1;
    //    int maxPoints = -1;

    //    for (int j = 0; j < n_clients; j++) {
    //        bool alreadySorted = false;

    //        for (int k = 0; k < i; k++) {
    //            if (all_points[j].index == sorted_points[k].index) {
    //                alreadySorted = true;
    //                break;
    //            }
    //        }

    //        if (alreadySorted) continue;

    //        if (all_points[j].points > maxPoints) {
    //            maxPoints = all_points[j].points;
    //            maxIndex = j;
    //        }
    //    }

    //    if (maxIndex != -1) {
    //        sorted_points[i] = all_points[maxIndex];
    //    }
    //}

    //total result
    glPushMatrix();
    glTranslatef(-81.783f,5.9977f,34.647f);
    glRotatef(22.0f, 0, 1, 0);
    for(int i = 0; i < n_clients; i++)
    {
        if(sorted_points[i].points / 10 != 0)
        {
            //2桁
            int n1 = sorted_points[i].points / 10;
            int n2 = sorted_points[i].points % 10;
            glPushMatrix();
            glTranslatef(0.0f, 5.807f, 6.038215f - (3.6466f * i));
            glScalef(229.0625f,229.0625f,229.0625f);
            glRotatef(180.0f, 0, 0, 1);
            switch(n1)
            {
                case 1:
                    num_1.make(1,1,1);
                    break;
                case 2:
                    num_2.make(1,1,1);
                    break;
                case 3:
                    num_3.make(1,1,1);
                    break;
                case 4:
                    num_4.make(1,1,1);
                    break;
                case 5:
                    num_5.make(1,1,1);
                    break;
                case 6:
                    num_6.make(1,1,1);
                    break;
                case 7:
                    num_7.make(1,1,1);
                    break;
                case 8:
                    num_8.make(1,1,1);
                    break;
                case 9:
                    num_9.make(1,1,1);
                    break;
            }
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0.0f, 7.534f, 6.038215f - (3.6466f * i));
            glScalef(229.0625f,229.0625f,229.0625f);
            glRotatef(180.0f, 0, 0, 1);
            switch(n2)
            {
                case 0:
                    num_0.make(1,1,1);
                    break;
                case 1:
                    num_1.make(1,1,1);
                    break;
                case 2:
                    num_2.make(1,1,1);
                    break;
                case 3:
                    num_3.make(1,1,1);
                    break;
                case 4:
                    num_4.make(1,1,1);
                    break;
                case 5:
                    num_5.make(1,1,1);
                    break;
                case 6:
                    num_6.make(1,1,1);
                    break;
                case 7:
                    num_7.make(1,1,1);
                    break;
                case 8:
                    num_8.make(1,1,1);
                    break;
                case 9:
                    num_9.make(1,1,1);
                    break;
            }
            glPopMatrix();
        }
        else
        {
            int n1 = sorted_points[i].points % 10;
            glPushMatrix();
            glTranslatef(0.0f, 7.534f, 6.038215f - (3.6466f * i));
            glScalef(229.0625f,229.0625f,229.0625f);
            glRotatef(180.0f, 0, 0, 1);
            switch(n1)
            {
                case 0:
                    num_0.make(1,1,1);
                    break;
                case 1:
                    num_1.make(1,1,1);
                    break;
                case 2:
                    num_2.make(1,1,1);
                    break;
                case 3:
                    num_3.make(1,1,1);
                    break;
                case 4:
                    num_4.make(1,1,1);
                    break;
                case 5:
                    num_5.make(1,1,1);
                    break;
                case 6:
                    num_6.make(1,1,1);
                    break;
                case 7:
                    num_7.make(1,1,1);
                    break;
                case 8:
                    num_8.make(1,1,1);
                    break;
                case 9:
                    num_9.make(1,1,1);
                    break;
            }
            glPopMatrix();
        }


        if(my_id == sorted_points[i].index)
        {
            for(int j =0;j < 10;j++)
            {
                char c = user_name[j];
                if(c == '\0')
                    break;
                glPushMatrix();
                glTranslatef(0.0f, -12.4715f + (1.7586f * j), 2.6284f - (3.7311f * i));
                glScalef(4.674f,4.674f,4.674f);
                glRotatef(180.0f, 0, 0, 1);
                if(c == 'A' || c ==  'a')
                {
                    text[0].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'B' || c ==  'b')
                {
                    text[1].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'C' || c ==  'c')
                {
                    text[2].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'D' || c ==  'd')
                {
                    text[3].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'E' || c ==  'e')
                {
                    text[4].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'F' || c ==  'f')
                {
                    text[5].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'G' || c ==  'g')
                {
                    text[6].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'H' || c ==  'h')
                {
                    text[7].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'I' || c ==  'i')
                {
                    text[8].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'J' || c ==  'j')
                {
                    text[9].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'K' || c ==  'k')
                {
                    text[10].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'L' || c ==  'l')
                {
                    text[11].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'M' || c ==  'm')
                {
                    text[12].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'N' || c ==  'n')
                {
                    text[13].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'O' || c ==  'o')
                {
                    text[14].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'P' || c ==  'p')
                {
                    text[15].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Q' || c ==  'q')
                {
                    text[16].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'R' || c ==  'r')
                {
                    text[17].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'S' || c ==  's')
                {
                    text[18].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'T' || c ==  't')
                {
                    text[19].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'U' || c ==  'u')
                {
                    text[20].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'V' || c ==  'v')
                {
                    text[21].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'W' || c ==  'w')
                {
                    text[22].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'X' || c ==  'x')
                {
                    text[23].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Y' || c ==  'y')
                {
                    text[24].make(1.0f,1.0f,1.0f);
                }
                else if(c == 'Z' || c ==  'z')
                {
                    text[25].make(1.0f,1.0f,1.0f);
                }            
                glPopMatrix();
            }
        }
        else
        {
            for(int j = 0;j < n_clients-1; j++)
            {
                if(m_charPosition[j].id == sorted_points[i].index)
                {

                    for(int k  = 0;k<10;k++)
                    {
                        char c = m_charPosition[j].name[k];
                        if(c == '\0')
                            break;
                        glPushMatrix();
                        glTranslatef(0.0f, -12.4715f + (1.7586f * k), 2.6284f - (3.7311f * i));
                        glScalef(4.674f,4.674f,4.674f);
                        glRotatef(180.0f, 0, 0, 1);
                        if(c == 'A' || c ==  'a')
                        {
                            text[0].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'B' || c ==  'b')
                        {
                            text[1].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'C' || c ==  'c')
                        {
                            text[2].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'D' || c ==  'd')
                        {
                            text[3].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'E' || c ==  'e')
                        {
                            text[4].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'F' || c ==  'f')
                        {
                            text[5].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'G' || c ==  'g')
                        {
                            text[6].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'H' || c ==  'h')
                        {
                            text[7].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'I' || c ==  'i')
                        {
                            text[8].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'J' || c ==  'j')
                        {
                            text[9].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'K' || c ==  'k')
                        {
                            text[10].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'L' || c ==  'l')
                        {
                            text[11].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'M' || c ==  'm')
                        {
                            text[12].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'N' || c ==  'n')
                        {
                            text[13].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'O' || c ==  'o')
                        {
                            text[14].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'P' || c ==  'p')
                        {
                            text[15].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'Q' || c ==  'q')
                        {
                            text[16].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'R' || c ==  'r')
                        {
                            text[17].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'S' || c ==  's')
                        {
                            text[18].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'T' || c ==  't')
                        {
                            text[19].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'U' || c ==  'u')
                        {
                            text[20].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'V' || c ==  'v')
                        {
                            text[21].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'W' || c ==  'w')
                        {
                            text[22].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'X' || c ==  'x')
                        {
                            text[23].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'Y' || c ==  'y')
                        {
                            text[24].make(1.0f,1.0f,1.0f);
                        }
                        else if(c == 'Z' || c ==  'z')
                        {
                            text[25].make(1.0f,1.0f,1.0f);
                        }            
                        glPopMatrix();
                    }
                }
            }
        }
    }
    glPopMatrix();
}

void makeEnemyName(char* name,Position p)
{
    //get string count
    int string_count = 0;
    for(int j= 0; j< 10;j++)
    {
        char t = name[j];
        if(t == '\0')
            break;
        string_count++;
    }

    float radian_name = atan2f(p.y - myPosition.y, p.x - myPosition.x);
    glPushMatrix();
    glTranslatef(p.x, p.y, p.z + 1.0f);
    glRotatef((radian_name * 180.0 / PI) , 0, 0, 1);

    for(int i = 0; i< string_count;i++)
    {
        char c = name[i];
        //float dis = sqrt((p.x - myPosition.x)*(p.x - myPosition.x) + (p.y - myPosition.y)*(p.y - myPosition.y));
        glPushMatrix();
        glTranslatef(0.0f, ((string_count / 2) - i) * 0.32f, 0.0f);
        if(c == 'A' || c ==  'a')
        {
            text[0].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'B' || c ==  'b')
        {
            text[1].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'C' || c ==  'c')
        {
            text[2].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'D' || c ==  'd')
        {
            text[3].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'E' || c ==  'e')
        {
            text[4].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'F' || c ==  'f')
        {
            text[5].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'G' || c ==  'g')
        {
            text[6].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'H' || c ==  'h')
        {
            text[7].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'I' || c ==  'i')
        {
            text[8].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'J' || c ==  'j')
        {
            text[9].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'K' || c ==  'k')
        {
            text[10].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'L' || c ==  'l')
        {
            text[11].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'M' || c ==  'm')
        {
            text[12].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'N' || c ==  'n')
        {
            text[13].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'O' || c ==  'o')
        {
            text[14].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'P' || c ==  'p')
        {
            text[15].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'Q' || c ==  'q')
        {
            text[16].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'R' || c ==  'r')
        {
            text[17].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'S' || c ==  's')
        {
            text[18].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'T' || c ==  't')
        {
            text[19].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'U' || c ==  'u')
        {
            text[20].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'V' || c ==  'v')
        {
            text[21].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'W' || c ==  'w')
        {
            text[22].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'X' || c ==  'x')
        {
            text[23].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'Y' || c ==  'y')
        {
            text[24].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'Z' || c ==  'z')
        {
            text[25].make(1.0f,1.0f,1.0f);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void makeEnemyTankName(char* name,vihicle v)
{
    //get string count
    int string_count = 0;
    for(int j= 0; j< 10;j++)
    {
        char t = name[j];
        if(t == '\0')
            break;
        string_count++;
    }

    float radian_name = atan2f(v.y - tankPos.y, v.x - tankPos.x);
    glPushMatrix();
    glTranslatef(v.x, v.y, v.z + 9.0f);
    glRotatef((radian_name * 180.0 / PI) , 0, 0, 1);
    glScalef(8,8,8);
    for(int i = 0; i< string_count;i++)
    {
        char c = name[i];
        //float dis = sqrt((p.x - myPosition.x)*(p.x - myPosition.x) + (p.y - myPosition.y)*(p.y - myPosition.y));
        glPushMatrix();
        glTranslatef(0.0f, ((string_count / 2) - i) * 0.32f, 0.0f);
        if(c == 'A' || c ==  'a')
        {
            text[0].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'B' || c ==  'b')
        {
            text[1].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'C' || c ==  'c')
        {
            text[2].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'D' || c ==  'd')
        {
            text[3].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'E' || c ==  'e')
        {
            text[4].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'F' || c ==  'f')
        {
            text[5].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'G' || c ==  'g')
        {
            text[6].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'H' || c ==  'h')
        {
            text[7].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'I' || c ==  'i')
        {
            text[8].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'J' || c ==  'j')
        {
            text[9].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'K' || c ==  'k')
        {
            text[10].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'L' || c ==  'l')
        {
            text[11].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'M' || c ==  'm')
        {
            text[12].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'N' || c ==  'n')
        {
            text[13].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'O' || c ==  'o')
        {
            text[14].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'P' || c ==  'p')
        {
            text[15].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'Q' || c ==  'q')
        {
            text[16].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'R' || c ==  'r')
        {
            text[17].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'S' || c ==  's')
        {
            text[18].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'T' || c ==  't')
        {
            text[19].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'U' || c ==  'u')
        {
            text[20].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'V' || c ==  'v')
        {
            text[21].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'W' || c ==  'w')
        {
            text[22].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'X' || c ==  'x')
        {
            text[23].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'Y' || c ==  'y')
        {
            text[24].make(1.0f,1.0f,1.0f);
        }
        else if(c == 'Z' || c ==  'z')
        {
            text[25].make(1.0f,1.0f,1.0f);
        }
        glPopMatrix();
    }
    glPopMatrix();

}

void makeEnemyPeople(int animFrame)
{
    for (int i = 0; i < n_clients - 1; i++) {
        int id     = m_charPosition[i].id;
        Position p = m_charPosition[i].pos;
        uint8_t d = p.dash;
        float alpha = p.alpha + (PI / 2.0f);
        makeEnemyName(m_charPosition[i].name, p);

        switch (id) {
        case 0:
            if(d == anim_idle) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 0, 0, Idle, Idle[0].textureID, animFrame , 75);
                glPopMatrix();
            }
            else if(d == anim_forward) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 0, 0, forward, forward[0].textureID, animFrame , 26);
                glPopMatrix();
            }
            else if(d == anim_dash)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 0, 0, dash, dash[0].textureID, animFrame / 2 , 16);
                glPopMatrix();                
            }
            else if(d == anim_jump)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 0, 0, jump, jump[0].textureID, animFrame , 41);
                glPopMatrix();  
            }
            else if(d == anim_right)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 0, 0, right, right[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_left)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 0, 0, left, left[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_back)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 0, 0, back, back[0].textureID, animFrame , 25);
                glPopMatrix();  
            }
            break;
        case 1:
            if(d == anim_idle) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 1, 0, Idle, Idle[0].textureID, animFrame , 75);
                glPopMatrix();
            }
            else if(d == anim_forward) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 1, 0, forward, forward[0].textureID, animFrame , 26);
                glPopMatrix();
            }
            else if(d == anim_dash)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 1, 0, dash, dash[0].textureID, animFrame / 2 , 16);
                glPopMatrix();                
            }
            else if(d == anim_jump)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 1, 0, jump, jump[0].textureID, animFrame, 41);
                glPopMatrix();  
            }
            else if(d == anim_right)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 1, 0, right, right[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_left)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 1, 0, left, left[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_back)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 1, 0, back, back[0].textureID, animFrame , 25);
                glPopMatrix();  
            }         
            break;
        case 2:
            if(d == anim_idle) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 0, 1, Idle, Idle[0].textureID, animFrame , 75);
                glPopMatrix();
            }
            else if(d == anim_forward) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 0, 1, forward, forward[0].textureID, animFrame , 26);
                glPopMatrix();
            }
            else if(d == anim_dash)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 0, 1, dash, dash[0].textureID, animFrame / 2 , 16);
                glPopMatrix();                
            }
            else if(d == anim_jump)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 0, 1, jump, jump[0].textureID, animFrame, 41);
                glPopMatrix();  
            }
            else if(d == anim_right)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 0, 1, right, right[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_left)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 0, 1, left, left[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_back)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 0, 1, back, back[0].textureID, animFrame , 25);
                glPopMatrix();  
            }
            break;
        case 3:
            if(d == anim_idle) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 1, 0, Idle, Idle[0].textureID, animFrame , 75);
                glPopMatrix();
            }
            else if(d == anim_forward) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 1, 0, forward, forward[0].textureID, animFrame , 26);
                glPopMatrix();
            }
            else if(d == anim_dash)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 1, 0, dash, dash[0].textureID, animFrame / 2 , 16);
                glPopMatrix();                
            }
            else if(d == anim_jump)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 1, 0, jump, jump[0].textureID, animFrame, 41);
                glPopMatrix();  
            }
            else if(d == anim_right)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 1, 0, right, right[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_left)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 1, 0, left, left[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_back)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 1, 0, back, back[0].textureID, animFrame , 25);
                glPopMatrix();  
            }
            break;
        }
    }
}

double cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

Point subtract(const Point& a, const Point& b) {
    return {a.x - b.x, a.y - b.y};
}

bool getCrossPoint(const Point& p1,const Point& p2,const Point& pp1,const Point& pp2,Point& result)
{
    Point p1p2 = subtract(p2, p1);
    Point q1q2 = subtract(pp2, pp1);
    Point p1q1 = subtract(pp1, p1);

    float det = cross(p1p2, q1q2);
    if (std::abs(det) < 1e-9) {
        return false; // 平行または一致
    }

    float t = cross(p1q1, q1q2) / det;
    float u = cross(p1q1, p1p2) / det;

    if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
        result =  {p1.x + t * p1p2.x, p1.y + t * p1p2.y} ;
        return true;
    }

    return false; // 線分上に交点がない
}

void makeEnemyPeople_T(int animFrame)
{
    for (int i = 0; i < n_clients - 1; i++) {
        int id     = m_charPosition[i].id;
        Position p = m_charPosition[i].pos;
        Game g = m_charPosition[i].game[2];
        uint8_t d = p.dash;
        float alpha = p.alpha + (PI / 2.0f);
        if(eneD[my_id] == 100 && fin == 0)
        {
            switch(checkGameStts(2,5))
            {
                case 0:
                    game[2].stts = 5;
                    fin = 1;
                    printf("Im dead\n");
                    break;
                case 1:
                    game[2].stts = 5;
                    fin = 2;
                    printf("Im dead\n");
                    break;
                case 2:
                    game[2].stts = 5;
                    fin = 3;
                    printf("Im dead\n");
                    break;
            }
        }
        if(eneD[id] >= 100 || g.stts == 5)//死んでいる敵は表示しない
        {
            continue;
        }


        makeEnemyName(m_charPosition[i].name, p);
        // glLineWidth(2.0f);
        // glPushMatrix();
        // glBegin(GL_LINES);
        // glColor3f(1, 0, 0);
        // glVertex3f(p.x , p.y , p.z );
        // glVertex3f((cosf(p.alpha )*cosf(p.sita) * 100.0f) + p.x ,(sinf(p.alpha )*cosf(p.sita) * 100.0f) + p.y , sinf(p.sita)*100.0f + p.z ); 
        // glEnd();
        // glPopMatrix();
        //高さは1階だと、1.8553~3.815  
        //2階だと、8.175655~10.135655  length : 1.96  よって、当たり判定は(p.z - 1.8553) ~ (p.z + 1.9597)
        
        //caldamage
        if(firing == true && eneD[my_id] != 100)//自分が死んでいたらダメージ計算しない
        {
            std::vector<Point> points;
            points = {{p.x - 0.5f,p.y - 0.5f},{p.x - 0.5f,p.y + 0.5f},{p.x + 0.5f,p.y + 0.5f},{p.x + 0.5f,p.y - 0.5f},{p.x - 0.5f,p.y - 0.5f}};
            Point pp1 = {myPosition.x,myPosition.y};
            Point pp2 = {(cosf(myPosition.alpha )*cosf(myPosition.sita) * 1000.0f) + myPosition.x,(sinf(myPosition.alpha )*cosf(myPosition.sita) * 1000.0f) + myPosition.y};
            for (size_t i = 0; i < points.size() - 1; ++i)
            {
                Point p1 = points[i];
                Point p2 = points[i + 1];
                Point cp;
                if (getCrossPoint(pp1,pp2,p1, p2,cp))
                {
                    float crossZ = (sqrt((myPosition.x - cp.x)*(myPosition.x - cp.x) + (myPosition.y - cp.y)*(myPosition.y-cp.y)) / sqrt((myPosition.x - pp2.x)*(myPosition.x - pp2.x) + (myPosition.y - pp2.y)* (myPosition.y - pp2.y))) * (sinf(myPosition.sita)*1000.0f) + myPosition.z;
                    if(crossZ < p.z + 1.9597f && crossZ > p.z - 1.8553f)
                    {
                        if(eneD[id] < 100)
                        {
                            eneD[id] += 3;
                            if(eneD[id] > 100)
                            {
                                eneD[id] = 100;
                                my_kill_count++;
                            }
                        }
                    }
                    break;
                }
            }
        }
        switch (id) {
        case 0:
            if(d == anim_idle) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 0, 0, Idle, Idle[0].textureID, animFrame , 75);
                glPopMatrix();
            }
            else if(d == anim_forward) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 0, 0, forward, forward[0].textureID, animFrame , 26);
                glPopMatrix();
            }
            else if(d == anim_dash)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 0, 0, dash, dash[0].textureID, animFrame / 2 , 16);
                glPopMatrix();                
            }
            else if(d == anim_jump)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 0, 0, jump, jump[0].textureID, animFrame , 41);
                glPopMatrix();  
            }
            else if(d == anim_right)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 0, 0, right, right[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_left)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 0, 0, left, left[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_back)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 0, 0, back, back[0].textureID, animFrame , 25);
                glPopMatrix();  
            }
            break;
        case 1:
            if(d == anim_idle) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 1, 0, Idle, Idle[0].textureID, animFrame , 75);
                glPopMatrix();
            }
            else if(d == anim_forward) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 1, 0, forward, forward[0].textureID, animFrame , 26);
                glPopMatrix();
            }
            else if(d == anim_dash)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 1, 0, dash, dash[0].textureID, animFrame / 2 , 16);
                glPopMatrix();                
            }
            else if(d == anim_jump)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 1, 0, jump, jump[0].textureID, animFrame, 41);
                glPopMatrix();  
            }
            else if(d == anim_right)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 1, 0, right, right[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_left)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 1, 0, left, left[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_back)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 1, 0, back, back[0].textureID, animFrame , 25);
                glPopMatrix();  
            }         
            break;
        case 2:
            if(d == anim_idle) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 0, 1, Idle, Idle[0].textureID, animFrame , 75);
                glPopMatrix();
            }
            else if(d == anim_forward) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 0, 1, forward, forward[0].textureID, animFrame , 26);
                glPopMatrix();
            }
            else if(d == anim_dash)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 0, 1, dash, dash[0].textureID, animFrame / 2 , 16);
                glPopMatrix();                
            }
            else if(d == anim_jump)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 0, 1, jump, jump[0].textureID, animFrame, 41);
                glPopMatrix();  
            }
            else if(d == anim_right)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 0, 1, right, right[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_left)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 0, 1, left, left[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_back)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(0, 0, 1, back, back[0].textureID, animFrame , 25);
                glPopMatrix();  
            }
            break;
        case 3:
            if(d == anim_idle) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 1, 0, Idle, Idle[0].textureID, animFrame , 75);
                glPopMatrix();
            }
            else if(d == anim_forward) 
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 1, 0, forward, forward[0].textureID, animFrame , 26);
                glPopMatrix();
            }
            else if(d == anim_dash)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 1, 0, dash, dash[0].textureID, animFrame / 2 , 16);
                glPopMatrix();                
            }
            else if(d == anim_jump)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 1, 0, jump, jump[0].textureID, animFrame, 41);
                glPopMatrix();  
            }
            else if(d == anim_right)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 1, 0, right, right[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_left)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 1, 0, left, left[0].textureID, animFrame , 22);
                glPopMatrix();  
            }
            else if(d == anim_back)
            {
                glPushMatrix();
                glTranslatef(p.x, p.y, p.z - 1.856706f);
                glRotatef(alpha / PI * 180.0, 0, 0, 1);
                makeAnim(1, 1, 0, back, back[0].textureID, animFrame , 25);
                glPopMatrix();  
            }
            break;
        }
    }
}

void makeEnemySportsCarIcon()
{
    for (int i = 0; i < n_clients - 1; i++) {
        int id    = m_charPosition[i].id;
        vihicle v = m_charPosition[i].vc;
        std::pair<double, double> dd = W2D(v.x, v.y);
        glPushMatrix();
        glTranslatef(-0.000099,dd.first, dd.second);
        glRotatef(-v.angle, 1, 0, 0);
        switch (id) {
        case 0:
            map_player.make(1.0f, 0.0f, 0.0f);
            break;
        case 1:
            map_player.make(0.0f, 1.0f, 0.0f);
            break;
        case 2:
            map_player.make(0.0f, 0.0f, 1.0f);
            break;
        case 3:
            map_player.make(1.0f, 1.0f, 0.0f);
            break;	
        }
        glPopMatrix();
    }
}

void makeEnemySportsCar()
{
    for (int i = 0; i < n_clients - 1; i++) {
        int id    = m_charPosition[i].id;
        vihicle v = m_charPosition[i].vc;
        if(v.type == 0)
        {
            switch (id) {
            case 0:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports_mainBody.makeWithTex_Color(0.6, 0, 0);
                sports1light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            case 1:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports_mainBody.makeWithTex_Color(0, 0.6, 0);
                sports1light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            case 2:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports_mainBody.makeWithTex_Color(0, 0, 0.6);
                sports1light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            case 3:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports_mainBody.makeWithTex_Color(0.6, 0.6, 0);
                sports1light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            }
        }
        else if(v.type == 1)
        {
            switch (id) {
            case 0:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports2_mainbody.makeWithTex_Color(0.6, 0, 0);
                sports2light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            case 1:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports2_mainbody.makeWithTex_Color(0, 0.6, 0);
                sports2light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            case 2:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports2_mainbody.makeWithTex_Color(0, 0, 0.6);
                sports2light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            case 3:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports2_mainbody.makeWithTex_Color(0.6, 0.6, 0);
                sports2light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            }
        }
        else if(v.type == 2)
        {
            switch (id) {
            case 0:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports3_mainbody.makeWithTex_Color(0.6, 0, 0);
                sports3light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            case 1:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports3_mainbody.makeWithTex_Color(0, 0.6, 0);
                sports3light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            case 2:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports3_mainbody.makeWithTex_Color(0, 0, 0.6);
                sports3light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            case 3:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports3_mainbody.makeWithTex_Color(0.6, 0.6, 0);
                sports3light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            }
        }
        else if(v.type == 3)
        {
            switch (id) {
            case 0:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports4_mainbody.makeWithTex_Color(0.6, 0, 0);
                sports4light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            case 1:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports4_mainbody.makeWithTex_Color(0, 0.6, 0);
                sports4light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            case 2:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports4_mainbody.makeWithTex_Color(0, 0, 0.6);
                sports4light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            case 3:
                glPushMatrix();
                glTranslatef(v.x, v.y, v.z);
                glRotatef(v.angle, 0, 0, 1);
                sports4_mainbody.makeWithTex_Color(0.6, 0.6, 0);
                sports4light.makeWithTex(1.0f,1.0f,1.0f);
                glPopMatrix();
                break;
            }            
        }
    }
}

void makeEnemyTank()
{
    for (int i = 0; i < n_clients - 1; i++) {
        int id    = m_charPosition[i].id;
        vihicle v = m_charPosition[i].vc;
        Position p = m_charPosition[i].pos;

        if(v.damage > 95)
            continue;
        if(p.damage == 100)//30damage : r = 20
        {
            float exDis = sqrt((p.x - tankPos.x) * (p.x - tankPos.x) + (p.y - tankPos.y) * (p.y - tankPos.y));
            if(exDis < 20)
            {
                tankPos.damage += 10.0f + (20.0f / exDis) ;
            }
                
        }
        makeEnemyTankName(m_charPosition[i].name, v);
        if(p.kind == false)
        {
            glPushMatrix();
            glTranslatef(p.x + cosf(p.alpha) * canonFirstSpeed * (p.canonCoolTime / 4.0), p.y + sinf(p.alpha) * canonFirstSpeed * (p.canonCoolTime / 4.0), p.z);
            glRotatef((p.alpha * 180.0 / PI) + 90.0, 0, 0, 1);
            glRotatef(-(p.sita * 180.0 / PI) / 3.0, 1, 0, 0);
            canon.makeWithTex(1, 1, 1);
            glPopMatrix();
        }
        else
        {
            float a = atan2f(p.y - tankPos.y, p.x - tankPos.x);
			glPushMatrix();
			glTranslatef(p.x, p.y, p.z);
			glRotatef((a * 180.0 / PI) + 90.0, 0, 0, 1);
			explosion.makeWithTex(1, 1, 1);
			glPopMatrix();
        }
        switch (id) {
        case 0:
            glPushMatrix();
            glTranslatef(v.x, v.y, v.z);
            glRotatef(v.alpha, 0, 0, 1);
            tankBarrel.makeWithTex(1.0f,1.0f,1.0f);
            tankUpper.makeWithTex(1.0f,1.0f,1.0f);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(v.x, v.y, v.z);
            glRotatef(v.angle, 0, 0, 1);
            tankLower.makeWithTex(1.0f,1.0f,1.0f);
            glPopMatrix();
            break;
        case 1:
            glPushMatrix();
            glTranslatef(v.x, v.y, v.z);
            glRotatef(v.alpha, 0, 0, 1);
            tankBarrel.makeWithTex(1.0f,1.0f,1.0f);
            tankUpper.makeWithTex(1.0f,1.0f,1.0f);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(v.x, v.y, v.z);
            glRotatef(v.angle, 0, 0, 1);
            tankLower.makeWithTex(1.0f,1.0f,1.0f);
            glPopMatrix();
            break;
        case 2:
            glPushMatrix();
            glTranslatef(v.x, v.y, v.z);
            glRotatef(v.alpha, 0, 0, 1);
            tankBarrel.makeWithTex(1.0f,1.0f,1.0f);
            tankUpper.makeWithTex(1.0f,1.0f,1.0f);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(v.x, v.y, v.z);
            glRotatef(v.angle, 0, 0, 1);
            tankLower.makeWithTex(1.0f,1.0f,1.0f);
            glPopMatrix();
            break;
        case 3:
            glPushMatrix();
            glTranslatef(v.x, v.y, v.z);
            glRotatef(v.alpha, 0, 0, 1);
            tankBarrel.makeWithTex(1.0f,1.0f,1.0f);
            tankUpper.makeWithTex(1.0f,1.0f,1.0f);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(v.x, v.y, v.z);
            glRotatef(v.angle, 0, 0, 1);
            tankLower.makeWithTex(1.0f,1.0f,1.0f);
            glPopMatrix();
            break;
        }
    }
}
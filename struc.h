#pragma once
#ifndef SERVER_BUILD
#include <GL/glew.h>
#ifdef __APPLE__
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
#else
    #include <GL/freeglut.h>
#endif
#ifndef __APPLE__
    #include <SDL2/SDL_opengl_glext.h>
#endif
#include <SDL2/SDL_mixer.h>
#endif
#include <stdlib.h>
#include <iostream>
#include <limits>
#include <cstring>
#include <vector>
#include <math.h>
#include <algorithm>

#ifndef STRUC_H
#define STRUC_H
#define ARRAY_MAX 510000
#define TEXT_ARRAY_MAX 20000
#define MAX_GAME_PLAY 20
#define PI 3.14159265f
#define canonFirstSpeed 6.0

void makeEnemyPeople();
void makeEnemyPeople_T();
void makeEnemySportsCar();
void makeEnemySportsCarIcon();
void makeEnemyTank();

void loadInitMesh(int);
void loadReturnfromGame(int);
void loadRaceGameMesh(int);
void loadTankGameMesh(int);
void loadChessGameMesh(int);
void loadShootingGameMesh(int);

void UnloadParkMesh();
void UnloadChessMesh();
void UnloadRaceMesh();
void UnloadShootingMesh();
void UnloadTankMesh();

void makeResult();
void initChessPos();
int checkGameStts(int s,int t);
std::pair<double, double> W2D(float x,float y);
extern int chessMap[8][8];

struct Position {
	float x,y,z,alpha,sita;
	uint8_t damage,dash,kind;
	int canonCoolTime;
};

struct explodePos
{
	float x,y,z;
	bool c;
};
	

struct vihicle {
	float x, y, z, vecX, vecY, sportsBodyVec, angle, alpha;
	uint8_t lap = 0;
	uint8_t type = 0;
	uint8_t damage = 0;
};

struct piece_position
{
	int pos[2];
};

struct chess_info
{
	piece_position bb1;
	piece_position bb2;
	piece_position bn1;
	piece_position bn2;
	piece_position br1;
	piece_position br2;
	piece_position bq;
	piece_position bk;
	piece_position bp1;
	piece_position bp2;
	piece_position bp3;
	piece_position bp4;
	piece_position bp5;
	piece_position bp6;
	piece_position bp7;
	piece_position bp8;

	piece_position wb1;
	piece_position wb2;
	piece_position wn1;
	piece_position wn2;
	piece_position wr1;
	piece_position wr2;
	piece_position wq;
	piece_position wk;
	piece_position wp1;
	piece_position wp2;
	piece_position wp3;
	piece_position wp4;
	piece_position wp5;
	piece_position wp6;
	piece_position wp7;
	piece_position wp8;

};

extern bool found1;
extern bool found2;

struct chessInfoNet
{
	chess_info ci;
	int thisTurn;
	uint8_t f = 0;
	int cm[8][8];
};

struct res_point
{
	uint8_t index;
	uint8_t points = 0;
};

enum result
{
	get_non,
	chess_win,
	chess_lose,
	race_1st,
	race_2nd,
	race_3rd,
    race_4th,
	tank_1st,
	tank_2nd,
	tank_3rd,
	tank_4th,
	shooting_survived,
	shooting_kill,
	get_item_cheap,
	get_item_normal,
	get_item_expensive,
};

struct Game
{
	uint8_t stts = 0;
	uint8_t ctrlID = 255;
	uint8_t mycolor = -1;
	chessInfoNet CIN;
	uint8_t gameLap = 3;
	uint8_t p_NUM = 0;
	uint8_t havingItems[4];//1,3,5,(4),(6),(8),(9)
};

struct CONTAINER {
    uint8_t cid;
	char name[10];
    char command = 0;
    struct Position pos;
    struct vihicle vc;
	struct Game game[4];
	uint8_t result[30];
	uint8_t eneDamage[4];
};

struct movingCharPosition {
    Position pos;
    vihicle vc;
    uint8_t id;
	char name[10];
	Game game[4];
	uint8_t result[30];
};

struct Point3D
{
	float x, y, z;
};

struct Point
{
	float x, y;
};

struct stair
{
	Point3D seg11;
	Point3D seg12;
	Point3D seg21;
	Point3D seg22;
};
int checkGameStts(int,int);

enum Scene {
    scene_1, 
    scene_2, 
    scene_3, 
    scene_4, 
    scene_5, 
    scene_6, 
    scene_7, 
    scene_8  
};

enum motionAnim
{
	anim_idle,
	anim_forward,
	anim_dash,
	anim_jump,
	anim_right,
	anim_left,
	anim_back

};


#ifndef SERVER_BUILD
class obj
{
public:
	void load(const char*,int);
	void load(const char*,bool);
	void load(const char*,const char*,int);
	void load(const char*,const char*);
	void make(float,float,float);
	void make_Color(float,float,float);
    void makeWithTex(float r, float g, float b);
	void makeWithTex_Color(float r, float g, float b);
	void setupVBO();
	void Uninit();
	FILE* Data;
	GLuint vertexVBO = 0;  // 頂点座標用VBO
	GLuint normalVBO = 0;  // 法線用VBO
	GLuint uvVBO = 0;      // UV座標用VBO
	std::vector<GLfloat> vertex; // 頂点座標を格納
	std::vector<GLfloat> flat;   // 法線を格納
	std::vector<GLfloat> UV;     // テクスチャ座標を格納
	GLuint textureID;
	int vertexDataSize = 0;
	int flatDataSize = 0;
	int UVDataSize = 0;
	//void createDisplayList();
};

class cheapObj
{
public:
	void load(const char*,int);
	void load(const char*,bool);
	void load(const char*, const char*,int);
	void make(float, float, float);
	void make_Color(float, float, float);
	void makeWithBlend(float, float, float,float);
	void Uninit();
	FILE* Data;
	std::vector<GLfloat> vertex; // 頂点座標を格納
	std::vector<GLfloat> flat;   // 法線を格納
	std::vector<GLfloat> UV;     // テクスチャ座標を格納
	GLuint textureID;
	int vertexDataSize = 0;
	int flatDataSize = 0;
	int UVDataSize = 0;

};
#endif

#endif
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#ifdef _OPENMP
#include <omp.h>
#endif
#include "struc.h"


#define ARRAY_MAX 510000
#define TEXT_ARRAY_MAX 20000
#define WALLCOUNT_MAX 1000
#define circle_x -0.00041
#define world_chess_size 0.00828
#define chess_map_x -0.0879
#define chess_map_y 0.072

#define tyousei 0.0041

#define WARP_WIDTH 900
#define WARP_HEIGHT 500
#define movingSpeed 0.1
#define tankMovingSpeed 0.24
#define gTime 40
#define aincradZ 40
#define aincradRad 550
#define chessSita -0.32837870904956801
#define chessAlpha 1.5742871761322021
#define chessMyPosX -0.0195458960
#define chessMyPosY -1.80217910
#define chessMyPosZ 3.57245994
#define chessAimX -0.022850209847098470
#define chessAimY -0.85561841726303101
#define chessAimZ 3.2499511241912842
#define DCX 1445.0
#define DCY 81.0
#define DCW 48.625
#define DCH 48.5
#define NCX 1154.0
#define NCY 76.0
#define NCW 38.125
#define NCH 38.75
#define speedLev 30.0f

#define OBJCOUNT 148

struct FireWorksPos
{
	float x, y, z;
	bool random = false;
	int FireWorkCount = 0;
};


enum chess_stts
{
	get_piece,
	set_piece
};

enum chess_kind_piece
{
	br1,
	br2,
	bn1,
	bn2,
	bb1,
	bb2,
	bq,
	bk,
	bp1,
	bp2,
	bp3,
	bp4,
	bp5,
	bp6,
	bp7,
	bp8,
	wr1,
	wr2,
	wn1,
	wn2,
	wb1,
	wb2,
	wq,
	wk,
	wp1,
	wp2,
	wp3,
	wp4,
	wp5,
	wp6,
	wp7,
	wp8

};

enum aim
{
	normalPos,
	goingRight,
	goingLeft,
	aimingPos
};

struct Point2D
{
	float x;
	float y;
};

GLuint loadTexture(const char*);
void motionController();
void motionController_T();
void SceneController();
void scene1(int, int, int, int);
void scene2(int, int, int, int);
void scene3(int, int, int, int);
void scene4(int, int, int, int);
void scene5(int, int, int, int);
void scene6(int, int, int, int);
void scene7(int, int, int, int);
void scene8(int, int, int, int);

float cul2PointDistance(float,float,float,float);

int ignore_key_repeat_event_filter(void*, SDL_Event*);
void initItemInfo(int);
void InitialProc();
void keyDown(unsigned char, int, int);
void keyUp(unsigned char, int, int);
void clicking(int, int);
void clicked_down(int , int , int );
void clicked_up(int , int, int );

void FireWork(FireWorksPos*);
void makeAnim(float r, float g, float b, obj o[], GLuint tex, int anim, int MaxFrame);
void passiveMotion(int, int);

void CollisionController();
void tankMotionController();
void sportsMotionController();

bool Collision_C();

void preReadPoints();
void readAnim(int);

void makeChess_2D_icon(int[8][8], chess_stts, int, int, int, int, int, float, float,float,float,chess_info, chess_kind_piece);

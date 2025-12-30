#include "func.h"

bool join = false;

extern Game game[4];

extern float cul2PointDistance(float x1,float y1,float x2,float y2);

int fin = 0;
int tarminalTime = 0;
int my_kill_count = 0;
int p1OBJrotate = 0;
int p2OBJrotate = 0;
int p3OBJrotate = 0;
int p4OBJrotate = 0;
extern int doorANIMcount;
extern int my_id;
extern int n_clients;
extern int chessMyColor;
extern int animFrame;
extern int mainloopcount;
extern int torque;
extern int terminate_anim_count;
extern int key1;
extern int key2;
extern float main_rotate;
extern float sita;
extern float alpha;
extern float piece_width;
extern float angle;
extern bool doorANIM;
extern bool doorAIM;
extern bool coltype;
extern int checkGameStts(int,int);
extern Position lookingPosition;
extern Position AIMPos;
extern Position myPosition;
extern vihicle tankPos;
extern vihicle sportsPos;
extern SDL_Window* window;
extern chess_stts cs;
extern chess_info ci;
extern Scene scene;
extern chessInfoNet CIN;
extern uint8_t eneD[4];

extern Mix_Music* BGM_park; // 広場
extern Mix_Music* BGM_loading; // ロード
extern Mix_Music* BGM_chess; // チェス
extern Mix_Music* BGM_shooting_park; // シューティング広場用
extern Mix_Music* BGM_tank_park; // 戦車広場用
extern Mix_Music* BGM_race_park; // レース広場用


extern GLuint parkBuildings;

extern Point game1_chess_position;
extern Point game2_tank_position;
extern Point game3_race_position;
extern Point game4_shooting_position;

extern obj game2_human_head;
extern obj disitalTable;
extern obj lamp1;
extern obj lamp2;
extern obj grass;
extern obj horse_statue1;
extern obj horse_statue2;
extern obj inside_road;
extern obj pedestal;
extern obj dirt;
extern obj house_brick;
extern obj house_roof;
extern obj house_window;
extern obj house_white;
extern obj house_door;
extern obj main_statue_base;
extern obj main_statue_brick;
extern obj main_statue_mini;
extern obj main_statue_ring;
extern obj main_statue_cristal;
extern obj tarkov_hat;
extern obj tarkov_top;
extern obj tarkov_face;
extern obj tarkov_counter;
extern obj aincrad_top;
extern obj skyOutSide;
extern obj skyInSide;
extern obj aincrad_road;
extern obj fence;
extern obj door_frame;
extern obj door_left;
extern obj door_right;
extern obj createchessmatch;
extern obj createracematch;
extern obj createshootingmatch;
extern obj createtankmatch;
extern obj waitingforplayers;
extern obj jointhisgame;
extern obj selectyourcar;
extern obj howmanyplayers;
extern obj game0_hair;
extern obj game0_head;
extern obj game0_top;
extern obj game0_pants;
extern obj game0_counter;
extern obj game2_chess_house;
extern obj game2_chess_black;
extern obj game2_chess_white;
extern obj game2_fani_table;
extern obj game2_sofa;
extern obj game2_Floor;
extern obj game1_basket;
extern obj game1_cat;
extern obj game1_deco;
extern obj game1_floor;
extern obj game1_kawara1;
extern obj game1_kawara2;
extern obj game1_kawara3;
extern obj game1_kawara4;
extern obj game1_light;
extern obj game1_ninja;
extern obj game1_post;
extern obj game1_table;
extern obj game1_wall;
extern obj game3_canon;
extern obj game3_chair;
extern obj game3_chest;
extern obj game3_frag;
extern obj game3_gate;
extern obj game3_ground;
extern obj game3_human_body;
extern obj game3_human_cloth;
extern obj game3_roof;
extern obj game3_wall;


extern obj game4_asphaltfuly;
extern obj game4_base_cars;
extern obj game4_car1;
extern obj game4_car2;
extern obj game4_car3;
extern obj game4_car4;
extern obj game4_floor;
extern obj game4_garden_acce;
extern obj game4_human;
extern obj game4_lamp_hock;
extern obj game4_light;
extern obj game4_roof;
extern obj game4_stair;
extern obj game4_table1;
extern obj game4_table2;
extern obj game4_tree_branch;
extern obj game4_tree_leaves;
extern obj game4_wall;
extern obj game4_wood2;
extern obj game4_wood_chair;
extern obj game4_wood_panel;
extern obj game4_wood_poll;
extern obj game4_wood_table;
extern obj game4_sofa;

extern obj chess_chair;
extern obj chess_table;
extern obj chess_map;
extern obj chess_set_board;
extern obj chess_WB1;
extern obj chess_WB2;
extern obj chess_WR1;
extern obj chess_WR2;
extern obj chess_WK;
extern obj chess_WQ;
extern obj chess_WN1;
extern obj chess_WN2;
extern obj chess_WP1;
extern obj chess_WP2;
extern obj chess_WP3;
extern obj chess_WP4;
extern obj chess_WP5;
extern obj chess_WP6;
extern obj chess_WP7;
extern obj chess_WP8;
extern obj chess_BB1;
extern obj chess_BB2;
extern obj chess_BK;
extern obj chess_BN1;
extern obj chess_BN2;
extern obj chess_BQ;
extern obj chess_BR1;
extern obj chess_BR2;
extern obj chess_BP1;
extern obj chess_BP2;
extern obj chess_BP3;
extern obj chess_BP4;
extern obj chess_BP5;
extern obj chess_BP6;
extern obj chess_BP7;
extern obj chess_BP8;
extern obj ui_car1;
extern obj ui_car2;
extern obj ui_car3;
extern obj ui_car4;

extern cheapObj open;

extern void makeEnemyPeople(int);
extern void makeResult();

void scene4(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);
	motionController();
	CollisionController();

	unsigned int angleZ = sin(lookingPosition.z * 20.0 / 180.0 * PI);
	AIMPos.x = myPosition.x - (sin(lookingPosition.x * 20.0 / 180.0 * PI) * (1.0 - angleZ));
	AIMPos.y = myPosition.y + (cos(lookingPosition.x * 20.0 / 180.0 * PI) * (1.0 - angleZ));
	AIMPos.z = 0.5f + (sin(lookingPosition.z * 20.0 / 180.0 * PI) * 2.0);
	sita = atan2(AIMPos.z, 1);
	alpha = atan2(AIMPos.y - myPosition.y, AIMPos.x - myPosition.x);
	double aimX = myPosition.x + (cosf(sita) * cosf(alpha));
	double aimY = myPosition.y + (cosf(sita) * sinf(alpha));
	double aimZ = myPosition.z + sinf(sita);
	gluLookAt(myPosition.x, myPosition.y, myPosition.z,
		aimX, aimY, aimZ,
		0, 0, 1);
	glPointSize(4);
	glBegin(GL_POINTS);
	glColor3f(1, 1, 1);
	glVertex3f(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
	glEnd();

    myPosition.sita = sita;	
	myPosition.alpha = alpha;

	main_rotate += 0.7f;
	aincrad_top.makeWithTex(0.4f, 0.4f, 0.4f);
	main_statue_brick.makeWithTex(0.6f, 0.6f, 0.6f);
	main_statue_base.makeWithTex(0.6f, 0.6f, 0.6f);
	disitalTable.makeWithTex(1.0f, 1.0f, 1.0f);
	house_brick.makeWithTex(0.5f, 0.5f, 0.5f);
	house_door.makeWithTex(0.5f, 0.5f, 0.5f);
	house_roof.makeWithTex(0.5f, 0.5f, 0.5f);
	house_window.makeWithTex(0.5f, 0.5f, 0.5f);
	house_white.make(0.5f, 0.5f, 0.5f);
	lamp1.makeWithTex(0.5f, 0.5f, 0.5f);
	lamp2.makeWithTex(0.5f, 0.5f, 0.5f);
	door_frame.makeWithTex(0.4f, 0.4f, 0.4f);
	aincrad_road.makeWithTex(0.4f, 0.4f, 0.4f);
	fence.make(0, 0, 0);
	inside_road.makeWithTex(0.4f, 0.4f, 0.4f);
	grass.makeWithTex(0.4f, 0.4f, 0.4f);
	horse_statue1.makeWithTex(1.0f, 1.0f, 1.0f);
	horse_statue2.makeWithTex(1.0f, 1.0f, 1.0f);
	pedestal.makeWithTex(0.4f, 0.4f, 0.4f);
	game0_hair.makeWithTex(1.0f, 1.0f, 1.0f);
	game0_head.makeWithTex(1.0f, 1.0f, 1.0f);
	game0_top.makeWithTex(1.0f, 1.0f, 1.0f);
	game0_pants.makeWithTex(1.0f, 1.0f, 1.0f);	
	game2_chess_house.makeWithTex(1.0f, 1.0f, 1.0f);
	game2_chess_black.makeWithTex(1.0f, 1.0f, 1.0f);
	game2_chess_white.makeWithTex(1.0f, 1.0f, 1.0f);
	game2_fani_table.makeWithTex(1.0f, 1.0f, 1.0f);
	game2_sofa.makeWithTex(1.0f, 1.0f, 1.0f);
	game2_Floor.makeWithTex(1.0f, 1.0f, 1.0f);
	skyOutSide.makeWithTex(1.0f, 1.0f, 1.0f);
	skyInSide.makeWithTex(1.0f, 1.0f, 1.0f);
	game1_basket.makeWithTex(1.0f, 1.0f, 1.0f);
	game1_cat.makeWithTex(1.0f, 1.0f, 1.0f);
	game1_deco.makeWithTex(1.0f, 1.0f, 1.0f);
	game1_floor.makeWithTex(1.0f, 1.0f, 1.0f);
	game1_kawara1.makeWithTex(1.0f, 1.0f, 1.0f);
	game1_kawara2.makeWithTex(1.0f, 1.0f, 1.0f);
	game1_kawara3.makeWithTex(1.0f, 1.0f, 1.0f);
	game1_kawara4.makeWithTex(1.0f, 1.0f, 1.0f);
	game1_light.makeWithTex(1.0f, 1.0f, 1.0f);
	game1_ninja.makeWithTex(1.0f, 1.0f, 1.0f);
	game1_post.makeWithTex(1.0f, 1.0f, 1.0f);
	game1_table.makeWithTex(1.0f, 1.0f, 1.0f);
	game1_wall.makeWithTex(1.0f, 1.0f, 1.0f);
	game3_canon.makeWithTex(1.0f, 1.0f, 1.0f);
	game3_chair.makeWithTex(1.0f, 1.0f, 1.0f);
	game3_chest.makeWithTex(1.0f, 1.0f, 1.0f);
	game3_frag.make(0,0,0);
	game3_gate.makeWithTex(1.0f, 1.0f, 1.0f);
	game3_ground.makeWithTex(1.0f, 1.0f, 1.0f);
	game3_human_body.makeWithTex(1.0f, 1.0f, 1.0f);
	game3_human_cloth.makeWithTex(1.0f, 1.0f, 1.0f);
	game3_roof.makeWithTex(1.0f, 1.0f, 1.0f);
	game3_wall.makeWithTex(1.0f, 1.0f, 1.0f);

	game4_asphaltfuly.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_base_cars.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_car1.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_car2.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_car3.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_car4.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_floor.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_garden_acce.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_human.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_lamp_hock.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_light.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_roof.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_stair.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_table1.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_table2.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_tree_branch.make(0.458824f,0.458824f,0.458824f);
	game4_tree_leaves.make(0.208335f,0.359993f,0.13972f);
	game4_wall.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_wood2.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_wood_chair.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_wood_panel.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_wood_poll.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_wood_table.makeWithTex(1.0f, 1.0f, 1.0f);
	game4_sofa.makeWithTex(1.0f, 1.0f, 1.0f);

	glPushMatrix();
	glRotatef(main_rotate / 7.0f, 0.0f, 0.0f, 1.0f);
	main_statue_cristal.makeWithTex(0.6f, 0.6f, 0.6f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.21414f, -3.97813f, 8.05898f + (sinf(main_rotate * PI / 180.0f) * 2.0f));
	glRotatef(main_rotate, 0.0f, 0.0f, 1.0f);
	main_statue_mini.makeWithTex(0.6f, 0.6f, 0.6f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.21414f, 3.97813f, 15.0872f + (sinf((main_rotate + 90.0f) * PI / 180.0f) * 2.0f));
	glRotatef(main_rotate, 0.0f, 0.0f, 1.0f);
	main_statue_mini.makeWithTex(0.6f, 0.6f, 0.6f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 10.0431);
	glRotatef(-23.5231f + (sinf(main_rotate * 1.5f * PI / 180.0f) * 8.0f), 1.0f, 0.0f, 0.0f);
	glRotatef(-main_rotate, 0.0f, 0.0f, 1.0f);
	main_statue_ring.makeWithTex(0.6f, 0.6f, 0.6f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.154599f, 0.0f, 18.8697f);
	glRotatef(23.0877f + (sinf((main_rotate + 90.0f) * 1.5f * PI / 180.0f) * 8.0f), 1.0f, 0.0f, 0.0f);
	glRotatef(main_rotate, 0.0f, 0.0f, 1.0f);
	glScalef(0.3266189f, 0.3266189f, 0.3266189f);
	main_statue_ring.makeWithTex(0.6f, 0.6f, 0.6f);
	glPopMatrix();

	makeResult();


	if (doorANIM == true)
	{
		doorANIMcount++;
		if (doorANIMcount < 700)
		{
			glPushMatrix();
			glTranslatef(162.86f, 4.8468f, 0.0f);
			glRotatef(doorANIMcount / 10.0f, 0.0f, 0.0f, 1.0f);
			door_right.makeWithTex(0.4f, 0.4f, 0.4f);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(162.86f, -4.8959f, 0.0f);
			glRotatef(doorANIMcount / -10.0f, 0.0f, 0.0f, 1.0f);
			door_left.makeWithTex(0.4f, 0.4f, 0.4f);
			glPopMatrix();
		}
		else if (doorANIMcount > 900)
		{
			glPushMatrix();
			glTranslatef(162.86f, 4.8468f, 0.0f);
			glRotatef((1600 - doorANIMcount) / 10.0f, 0.0f, 0.0f, 1.0f);
			door_right.makeWithTex(0.4f, 0.4f, 0.4f);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(162.86f, -4.8959f, 0.0f);
			glRotatef((1600 - doorANIMcount) / -10.0f, 0.0f, 0.0f, 1.0f);
			door_left.makeWithTex(0.4f, 0.4f, 0.4f);
			glPopMatrix();
			if (doorANIMcount == 1600)
			{
				doorAIM = false;
				doorANIMcount = 0;
				doorANIM = false;
			}
		}
		else
		{

			glPushMatrix();
			glTranslatef(162.86f, 4.8468f, 0.0f);
			glRotatef(70.0f, 0.0f, 0.0f, 1.0f);
			door_right.makeWithTex(0.4f, 0.4f, 0.4f);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(162.86f, -4.8959f, 0.0f);
			glRotatef(-70.0f, 0.0f, 0.0f, 1.0f);
			door_left.makeWithTex(0.4f, 0.4f, 0.4f);
			glPopMatrix();
		}
	}
	else
	{
		if ((myPosition.x < 168.2 && myPosition.x > 162.5 && myPosition.x - aimX > 0.0) || (myPosition.x > 158.2 && myPosition.x < 162.5 && myPosition.x - aimX < 0.0))
		{
			doorAIM = true;
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			open.make(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		glPushMatrix();
		glTranslatef(162.86f, 4.8468f, 0.0f);
		glRotatef(doorANIMcount / 10.0f, 0.0f, 0.0f, 1.0f);
		door_right.makeWithTex(0.4f, 0.4f, 0.4f);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(162.86f, -4.8959f, 0.0f);
		glRotatef(doorANIMcount / -10.0f, 0.0f, 0.0f, 1.0f);
		door_left.makeWithTex(0.4f, 0.4f, 0.4f);
		glPopMatrix();
	}
	
	animFrame++;
	makeEnemyPeople(animFrame);

	if(checkGameStts(0,4) > 1)
	{
		glPushMatrix();
		glTranslatef(0.565668f, -53.538679f, -0.703f);
		glRotatef(-9.2149f, 0.0f, 0.0f, 1.0f);
		chess_chair.makeWithTex(1.0f, 1.0f, 1.0f);
		chess_set_board.makeWithTex(1.0f, 1.0f, 1.0f);
		chess_table.makeWithTex(1.0f, 1.0f, 1.0f);

		if (chessMap[7 - CIN.ci.bb1.pos[0]][7 - CIN.ci.bb1.pos[1]] == 4)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bb1.pos[1] - 2) * piece_width, (CIN.ci.bb1.pos[0] - 7) * -piece_width, 0);
			chess_BB1.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.bb2.pos[0]][7 - CIN.ci.bb2.pos[1]] == 4)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bb2.pos[1] - 5) * piece_width, (CIN.ci.bb2.pos[0] - 7) * -piece_width, 0);
			chess_BB2.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.bk.pos[0]][7 - CIN.ci.bk.pos[1]] == 5)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bk.pos[1] - 4) * piece_width, (CIN.ci.bk.pos[0] - 7) * -piece_width, 0);
			chess_BK.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.bn1.pos[0]][7 - CIN.ci.bn1.pos[1]] == 3)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bn1.pos[1] - 1) * piece_width, (CIN.ci.bn1.pos[0] - 7) * -piece_width, 0);
			chess_BN1.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.bn2.pos[0]][7 - CIN.ci.bn2.pos[1]] == 3)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bn2.pos[1] - 6) * piece_width, (CIN.ci.bn2.pos[0] - 7) * -piece_width, 0);
			chess_BN2.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.bp1.pos[0]][7 - CIN.ci.bp1.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef(CIN.ci.bp1.pos[1] * piece_width, (6 - CIN.ci.bp1.pos[0]) * piece_width, 0);
			chess_BP1.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.bp2.pos[0]][7 - CIN.ci.bp2.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp2.pos[1] - 1) * piece_width, (6 - CIN.ci.bp2.pos[0]) * piece_width, 0);
			chess_BP2.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.bp3.pos[0]][7 - CIN.ci.bp3.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp3.pos[1] - 2) * piece_width, (6 - CIN.ci.bp3.pos[0]) * piece_width, 0);
			chess_BP3.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.bp4.pos[0]][7 - CIN.ci.bp4.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp4.pos[1] - 3) * piece_width, (6 - CIN.ci.bp4.pos[0]) * piece_width, 0);
			chess_BP4.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.bp5.pos[0]][7 - CIN.ci.bp5.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp5.pos[1] - 4) * piece_width, (6 - CIN.ci.bp5.pos[0]) * piece_width, 0);
			chess_BP5.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.bp6.pos[0]][7 - CIN.ci.bp6.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp6.pos[1] - 5) * piece_width, (6 - CIN.ci.bp6.pos[0]) * piece_width, 0);
			chess_BP6.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.bp7.pos[0]][7 - CIN.ci.bp7.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp7.pos[1] - 6) * piece_width, (6 - CIN.ci.bp7.pos[0]) * piece_width, 0);
			chess_BP7.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.bp8.pos[0]][7 - CIN.ci.bp8.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp8.pos[1] - 7) * piece_width, (6 - CIN.ci.bp8.pos[0]) * piece_width, 0);
			chess_BP8.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.bq.pos[0]][7 - CIN.ci.bq.pos[1]] == 6)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bq.pos[1] - 3) * piece_width, (CIN.ci.bq.pos[0] - 7) * -piece_width, 0);
			chess_BQ.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.br1.pos[0]][7 - CIN.ci.br1.pos[1]] == 2)
		{
			glPushMatrix();
			glTranslatef(CIN.ci.br1.pos[1] * piece_width, (CIN.ci.br1.pos[0] - 7) * -piece_width, 0);
			chess_BR1.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.br2.pos[0]][7 - CIN.ci.br2.pos[1]] == 2)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.br2.pos[1] - 7) * piece_width, (CIN.ci.br2.pos[0] - 7) * -piece_width, 0);
			chess_BR2.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wb1.pos[0]][CIN.ci.wb1.pos[1]] == 10)
		{
			glPushMatrix();
			glTranslatef((2 - CIN.ci.wb1.pos[1]) * piece_width, CIN.ci.wb1.pos[0] * -piece_width, 0);
			chess_WB1.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wb2.pos[0]][CIN.ci.wb2.pos[1]] == 10)
		{
			glPushMatrix();
			glTranslatef((5 - CIN.ci.wb2.pos[1]) * piece_width, CIN.ci.wb2.pos[0] * -piece_width, 0);
			chess_WB2.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wk.pos[0]][7 - CIN.ci.wk.pos[1]] == 11)
		{
			glPushMatrix();
			glTranslatef((4 - CIN.ci.wk.pos[1]) * -piece_width, CIN.ci.wk.pos[0] * -piece_width, 0);
			chess_WK.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wq.pos[0]][7 - CIN.ci.wq.pos[1]] == 12)
		{
			glPushMatrix();
			glTranslatef((3 - CIN.ci.wq.pos[1]) * -piece_width, CIN.ci.wq.pos[0] * -piece_width, 0);
			chess_WQ.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wn1.pos[0]][CIN.ci.wn1.pos[1]] == 9)
		{
			glPushMatrix();
			glTranslatef((1 - CIN.ci.wn1.pos[1]) * piece_width, CIN.ci.wn1.pos[0] * -piece_width, 0);
			chess_WN1.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wn2.pos[0]][CIN.ci.wn2.pos[1]] == 9)
		{
			glPushMatrix();
			glTranslatef((6 - CIN.ci.wn2.pos[1]) * piece_width, CIN.ci.wn2.pos[0] * -piece_width, 0);
			chess_WN2.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wr1.pos[0]][CIN.ci.wr1.pos[1]] == 8)
		{
			glPushMatrix();
			glTranslatef(-CIN.ci.wr1.pos[1] * piece_width, -CIN.ci.wr1.pos[0] * piece_width, 0);
			chess_WR1.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wr2.pos[0]][CIN.ci.wr2.pos[1]] == 8)
		{
			glPushMatrix();
			glTranslatef((7 - CIN.ci.wr2.pos[1]) * piece_width, -CIN.ci.wr2.pos[0] * piece_width, 0);
			chess_WR2.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wp1.pos[0]][CIN.ci.wp1.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef(-CIN.ci.wp1.pos[1] * piece_width, (CIN.ci.wp1.pos[0] - 1) * -piece_width, 0);
			chess_WP1.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wp2.pos[0]][CIN.ci.wp2.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((1 - CIN.ci.wp2.pos[1]) * piece_width, (CIN.ci.wp2.pos[0] - 1) * -piece_width, 0);
			chess_WP2.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wp3.pos[0]][CIN.ci.wp3.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((2 - CIN.ci.wp3.pos[1]) * piece_width, (CIN.ci.wp3.pos[0] - 1) * -piece_width, 0);
			chess_WP3.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wp4.pos[0]][CIN.ci.wp4.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((3 - CIN.ci.wp4.pos[1]) * piece_width, (CIN.ci.wp4.pos[0] - 1) * -piece_width, 0);
			chess_WP4.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wp5.pos[0]][CIN.ci.wp5.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((4 - CIN.ci.wp5.pos[1]) * piece_width, (CIN.ci.wp5.pos[0] - 1) * -piece_width, 0);
			chess_WP5.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wp6.pos[0]][CIN.ci.wp6.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((5 - CIN.ci.wp6.pos[1]) * piece_width, (CIN.ci.wp6.pos[0] - 1) * -piece_width, 0);
			chess_WP6.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wp7.pos[0]][CIN.ci.wp7.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((6 - CIN.ci.wp7.pos[1]) * piece_width, (CIN.ci.wp7.pos[0] - 1) * -piece_width, 0);
			chess_WP7.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		if (chessMap[7 - CIN.ci.wp8.pos[0]][CIN.ci.wp8.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((7 - CIN.ci.wp8.pos[1]) * piece_width, (CIN.ci.wp8.pos[0] - 1) * -piece_width, 0);
			chess_WP8.makeWithTex(1.0f, 1.0f, 1.0f);
			glPopMatrix();
		}
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		glTranslatef(0.565668f, -53.538679f, -0.703f);
		glRotatef(-9.2149f, 0.0f, 0.0f, 1.0f);
		chess_chair.makeWithTex(1.0f, 1.0f, 1.0f);
		chess_table.makeWithTex(1.0f, 1.0f, 1.0f);
		glPopMatrix();
	}

	if(cul2PointDistance(myPosition.x, myPosition.y,game1_chess_position.x, game1_chess_position.y) < 5.0f)//chess
	{
		if(p1OBJrotate == 0)
		{
			Mix_PlayMusic(BGM_chess, -1);
		}
		p1OBJrotate++;

		join = false;
		if(checkGameStts(0,2) > 0)
		{
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			jointhisgame.make(1.0f,1.0f,1.0f);
			glPopMatrix();	
			join = true;
		}
		else if(game[0].stts == 4)
		{
			terminate_anim_count = 0;
			myPosition.dash = anim_idle;
			key1 = (rand() % 5) + 2;//2~6
			key2 = (rand() % 5) + 8;//8~12

			if(game[0].mycolor == 0)
			{
				//チェスのロード
				mainloopcount = 4;

				//広場のアンロード
				UnloadParkMesh();
				SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
				SDL_ShowCursor(SDL_ENABLE);
				cs = get_piece;
				chessMyColor = 0;
				scene = scene_5;
				game[0].stts = 3;
				game[0].mycolor = 0;
				CIN.ci = ci;
				CIN.f = 0;
				myPosition.x = 0.97035f;
				myPosition.y = -50.971f;
				myPosition.alpha = (-99.2149f) * PI / 180.0f;
			}
			else
			{
				//チェスのロード
				mainloopcount = 4;

				//広場のアンロード
				UnloadParkMesh();

				SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
				SDL_ShowCursor(SDL_ENABLE);
				cs = get_piece;
				chessMyColor = 1;
				scene = scene_5;
				game[0].stts = 3;
				game[0].mycolor = 1;
				CIN.ci = ci;
				CIN.f = 0;
				myPosition.x = 0.13845f;
				myPosition.y = -55.999f;
				myPosition.alpha = (-266.93f) * PI / 180.0f;
				int ck[8][8];
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
						ck[i][j] = chessMap[7-i][7-j] ;
				}
				for(int i = 0; i < 8; i++)   
				{
					for(int j = 0; j < 8; j++)
						chessMap[i][j] = ck[i][j];
				}				
			}
		}
		else if(game[0].stts == 2)
		{
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			waitingforplayers.make(1.0f,1.0f,1.0f);
			glPopMatrix();	
		}
		else if(checkGameStts(0,0) == n_clients - 1 && game[0].stts < 2 && checkGameStts(0,1) == 0)
		{
			
			game[0].stts = 1;
			game[0].ctrlID = my_id + 1;
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			createchessmatch.make(1.0f,1.0f,1.0f);
			glPopMatrix();
		}
	}
	else
	{
		if(p1OBJrotate != 0)
		{
			Mix_PlayMusic(BGM_park, -1);
		}
		p1OBJrotate = 0;

		game[0].stts = 0;
		game[0].ctrlID = 0;
	}

	if(cul2PointDistance(myPosition.x,myPosition.y,game3_race_position.x,game3_race_position.y) < 5.0f)//カーレース
	{
		if(p2OBJrotate == 0)
		{
			Mix_PlayMusic(BGM_race_park, -1);
		}
		p2OBJrotate++;

		if((game[1].stts == 0 || game[1].stts == 10) && checkGameStts(1,3) > 0)
		{
			game[1].stts = 10;
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			jointhisgame.make(1.0f,1.0f,1.0f);
			glPopMatrix();				
		}
		else if((game[1].stts == 5 && checkGameStts(1,5) == game[1].p_NUM - 1))
		{
			//カーレースのロード

			mainloopcount = 3;
			//広場のアンロード
			UnloadParkMesh();

			scene = scene_7;
			myPosition.z = 2.7;
			lookingPosition.x = 9.0;
			lookingPosition.y = 0;
			lookingPosition.z = 0;
			sportsPos.vecX = 0;
			sportsPos.vecY = -1.0;
			sportsPos.lap = 0;
			torque = 0;		
			animFrame = 0;
			fin = 0;
			tarminalTime = 0;
			switch (my_id)
			{
			case 0:
				sportsPos.x = 18.0f;
				break;
			case 1:
				sportsPos.x = 12.0f;
				break;
			case 2:
				sportsPos.x = 6.0f;
			}
		}
		else if(game[1].stts == 5)
		{
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			waitingforplayers.make(1.0f,1.0f,1.0f);
			glPopMatrix();		
		}
		else if((game[1].stts == 3 && checkGameStts(1,3) == game[1].p_NUM - 1) || game[1].stts == 4 || (checkGameStts(1,4) > 0 && game[1].stts == 3))//select car
		{
			game[1].stts = 4;
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			ui_car1.makeWithTex(1,1,1);
			ui_car2.makeWithTex(1,1,1);
			ui_car3.makeWithTex(1,1,1);
			ui_car4.makeWithTex(1,1,1);
			selectyourcar.make(1.0f,1.0f,1.0f);
			glPopMatrix();				
		}
		else if(game[1].stts == 3)//wait players
		{
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			waitingforplayers.make(1.0f,1.0f,1.0f);
			glPopMatrix();		
		}
		else if(game[1].stts == 2)//setting player count
		{
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			howmanyplayers.make(1.0f,1.0f,1.0f);
			glPopMatrix();
		}
		else if(checkGameStts(1,0) == n_clients - 1 && game[1].stts < 2)//everyone else me stts = 0
		{
			game[1].stts = 1;
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			createracematch.make(1.0f,1.0f,1.0f);
			glPopMatrix();
		}
	}
	else
	{
		if(p2OBJrotate != 0)
		{
			Mix_PlayMusic(BGM_park, -1);
		}
		p2OBJrotate = 0;

		game[1].stts = 0;
	}

	if(cul2PointDistance(myPosition.x,myPosition.y,game4_shooting_position.x,game4_shooting_position.y) < 5.0f)//shooting
	{
		if(p3OBJrotate == 0)
		{
			Mix_PlayMusic(BGM_shooting_park, -1);
		}
		p3OBJrotate++;

		if((game[2].stts == 0 || game[2].stts == 10) && checkGameStts(2,3) > 0)
		{
			game[2].stts = 10;
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			jointhisgame.make(1.0f,1.0f,1.0f);
			glPopMatrix();				
		}
		else if(game[2].stts == 3 && checkGameStts(2,3) == game[2].p_NUM - 1)
		{
			eneD[0] = 0;
			eneD[1] = 0;
			eneD[2] = 0;
			eneD[3] = 0;
			animFrame = 0;
			fin = 0;
			my_kill_count = 0;
			game[2].havingItems[0] = 0;
			game[2].havingItems[1] = 0;
			game[2].havingItems[2] = 0;
			game[2].havingItems[3] = 0;
			tarminalTime = 0;
			//シューティングのロード
			mainloopcount = 5;
			//広場のアンロード
			UnloadParkMesh();
			scene = scene_8;
			glViewport(0, 0, 1924, 1061);
			glMatrixMode(GL_PROJECTION);			// �ˉe�s��𑀍삷��
			glLoadIdentity();						// �s���������
			gluPerspective(80.0, 1924.0 / 1061.0, 0.001, 5000);
			glMatrixMode(GL_MODELVIEW);
			switch (my_id)
			{
			case 0:
				myPosition.x = -9.76f;
				myPosition.y = -52.665f;
				myPosition.z = 1.8553f;
				break;
			case 1:
				myPosition.x = 48.48f;
				myPosition.y = 5.2269f;
				myPosition.z = 1.8553f;
				break;
			case 2:
				myPosition.x = -48.307f;
				myPosition.y = 19.115f;
				myPosition.z = 1.8553f + 5.8836f;
				coltype = true;
				break;
			case 3:
				myPosition.x = 37.0f;
				myPosition.y = 17.0f;
				myPosition.z = 1.8553f + 5.8836f;
				coltype = true;
				break;
			}
			//-0.6447
		}
		else if(game[2].stts == 3)//wait players
		{
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			waitingforplayers.make(1.0f,1.0f,1.0f);
			glPopMatrix();		
		}
		else if(game[2].stts == 2)//setting player count
		{
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			howmanyplayers.make(1.0f,1.0f,1.0f);
			glPopMatrix();
		}
		else if(checkGameStts(2,0) == n_clients - 1 && game[2].stts < 2)//everyone else me stts = 0
		{
			game[2].stts = 1;
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			createshootingmatch.make(1.0f,1.0f,1.0f);
			glPopMatrix();
		}
	}
	else
	{
		if(p3OBJrotate != 0)
		{
			Mix_PlayMusic(BGM_park, -1);
		}
		p3OBJrotate = 0;
		game[2].stts = 0;
	}

	if(cul2PointDistance(myPosition.x,myPosition.y,game2_tank_position.x,game2_tank_position.y) < 5.0f)//tank
	{

		if(p4OBJrotate == 0)
		{
			Mix_PlayMusic(BGM_tank_park, -1);
		}
		p4OBJrotate++;
		if((game[3].stts == 0 || game[3].stts == 10) && checkGameStts(3,3) > 0)
		{
			game[3].stts = 10;
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			jointhisgame.make(1.0f,1.0f,1.0f);
			glPopMatrix();				
		}
		else if(game[3].stts == 3 && checkGameStts(3,3) == game[3].p_NUM - 1)
		{
			//戦車のロード
			mainloopcount = 6;
			//広場のアンロード
			UnloadParkMesh();
			tankPos.damage = 0;
			animFrame = 0;
			fin = 0;
			tarminalTime = 0;
			scene = scene_6;
			lookingPosition.y = 0;
			lookingPosition.z = 0;
			switch (my_id)
			{
			case 0:
				tankPos.x = 159.9f;
				tankPos.y = -70.48f;
				lookingPosition.x = 0.0f;
				tankPos.vecX = PI;
				break;
			case 1:
				tankPos.x = -116.28f;
				tankPos.y = -116.1f;
				lookingPosition.x = -4.5f;
				tankPos.vecX = -PI / 2.0f;
				break;
			case 2:
				tankPos.x = -102.39f;
				tankPos.y = 192.31f;
				lookingPosition.x = -9.0f;
				tankPos.vecX = 0.0f;
				break;
			case 3:
				tankPos.x = 17.22f;
				tankPos.y = 140.81f;
				lookingPosition.x = -13.5f;
				tankPos.vecX = PI / 2.0f;
				break;
			}
		}
		else if(game[3].stts == 3)//wait players
		{
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			waitingforplayers.make(1.0f,1.0f,1.0f);
			glPopMatrix();		
		}
		else if(game[3].stts == 2)//setting player count
		{
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			howmanyplayers.make(1.0f,1.0f,1.0f);
			glPopMatrix();
		}
		else if(checkGameStts(3,0) == n_clients - 1 && game[3].stts < 2)//everyone else me stts = 0
		{
			game[3].stts = 1;
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11f), myPosition.y + ((aimY - myPosition.y) * 0.11f), myPosition.z + ((aimZ - myPosition.z) * 0.11f));
			glRotatef(alpha / PI * 180.0f, 0.0f, 0.0f, 1.0f);
			glRotatef(sita / PI * 180.0f, 0.0f, -1.0f, 0.0f);
			createtankmatch.make(1.0f,1.0f,1.0f);
			glPopMatrix();
		}
	}
	else
	{
		if(p4OBJrotate != 0)
		{
			Mix_PlayMusic(BGM_park, -1);
		}
		p4OBJrotate = 0;
		game[3].stts = 0;
	}
}

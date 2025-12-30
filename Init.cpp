#include "func.h"
#include "client.h"
#define g 0.0098f

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern int mainloopcount;
extern int currentFrame;
extern int currentMeshNum;
extern int chessMap[8][8];
extern bool found1;
extern bool found2;
GLuint parkBuildings;
Game game[4];
extern void roadAnimMesh(int ff,int ef,const char* path,const char* tex,obj o[]);
extern float lightposMat[];
extern float radius_aincrad;
extern float height_aincrad;
extern float jumpSpeed;
extern float jumpingHeight;
chess_info ci;
int original_turn = 0;
extern int key1;
extern int key2;
extern chessInfoNet CIN;
extern Scene scene;
extern SDL_Window* window;
extern Position myPosition;
extern explodePos explosionPos;
extern Position lookingPosition;
extern vihicle tankPos;
extern vihicle sportsPos;
std::vector<std::pair<int, std::vector<Point>>> entranceWall;
std::vector<std::pair<int, std::vector<Point>>> robyWall;
std::vector<std::pair<int, std::vector<Point>>> tankWall;
std::vector<std::pair<int, std::vector<Point>>> tarkovWall;
std::vector<std::pair<int, std::vector<Point>>> tarkovWall2;
std::vector<std::pair<int, std::vector<Point>>> sportsWall;
extern uint8_t my_result[30];

extern Mix_Music* BGM_title; // タイトル
extern Mix_Music* BGM_loading; // ロード
extern Mix_Music* BGM_park; // 広場
extern Mix_Music* BGM_chess; // チェス
extern Mix_Music* BGM_race_ingame; // レースゲーム用
extern Mix_Music* BGM_tank_ingame; // 戦車ゲーム用
extern Mix_Music* BGM_shooting_ingame; // シューティングゲーム用

stair stair1;
stair stair2;
stair stair3;
stair stair4;
stair stair5;
stair stair6;
stair stair7;
stair stair8;
stair stair9;

stair stairXMinus1;
stair stairXMinus2;
stair stairXMinus3;


//全般
obj skyOutSide;
obj skyInSide;
obj aincrad_top;
obj aincrad_bot;
obj aincrad_lower;
obj aincrad_lower_lower;
obj aincrad_road;
obj aincrad_sword;
obj aincrad_house;
obj human;
obj text[26];

//GUI
obj title;
obj titleFrame;
obj titleShield;
obj createchessmatch;
obj createracematch;
obj createshootingmatch;
obj createtankmatch;
obj waitingforplayers;
obj selectyourcar;
obj howmanyplayers;
obj text_go;
obj jointhisgame;
obj result_chess_win;
obj result_chess_lose;
obj result_tank_1st;
obj result_tank_2nd;
obj result_tank_3rd;
obj result_tank_4th;
obj result_shooting_kill;
obj result_shooting_suevived;
obj result_race_1st;
obj result_race_2nd;
obj result_race_3rd;
obj result_race_4th;
obj result_get_item_cheap;
obj result_get_item_normal;
obj result_get_item_expensive;
obj ui_key;
obj ui_ammo;
obj ui_car1;
obj ui_car2;
obj ui_car3;
obj ui_car4;
obj yourturn;
obj enemyturn;
obj HP_bar;
obj HP_frame;
cheapObj GUI;
cheapObj open;
cheapObj chess_masu;
cheapObj chess_circle;
cheapObj chess_P;
cheapObj chess_R;
cheapObj chess_B;
cheapObj chess_N;
cheapObj chess_K;
cheapObj chess_Q;
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

//エントランスorロビー
obj FireWorks;
obj fence;
obj door_frame;
obj door_right;
obj door_left;
obj lamp1;
obj lamp2;
obj door;
obj inside_road;
obj grass;
obj horse_statue1;
obj horse_statue2;
obj pedestal;
obj dirt;
obj disitalTable;
obj main_statue_base;
obj main_statue_ring;
obj main_statue_mini;
obj main_statue_brick;
obj main_statue_cristal;
obj house_door;
obj house_window;
obj house_white;
obj house_brick;
obj house_roof;
obj tarkov_hat;
obj tarkov_top;
obj tarkov_face;
obj tarkov_counter;
obj game0_hair;
obj game0_head;
obj game0_top;
obj game0_pants;
obj game0_counter;
obj game2_chess_house;
obj game2_chess_black;
obj game2_chess_white;
obj game2_fani_table;
obj game2_sofa;
obj game2_Floor;
obj game1_basket;
obj game1_cat;
obj game1_deco;
obj game1_floor;
obj game1_kawara1;
obj game1_kawara2;
obj game1_kawara3;
obj game1_kawara4;
obj game1_light;
obj game1_ninja;
obj game1_post;
obj game1_table;
obj game1_wall;
obj game3_canon;
obj game3_chair;
obj game3_chest;
obj game3_frag;
obj game3_gate;
obj game3_ground;
obj game3_human_body;
obj game3_human_cloth;
obj game3_roof;
obj game3_wall;
obj game4_asphaltfuly;
obj game4_base_cars;
obj game4_car1;
obj game4_car2;
obj game4_car3;
obj game4_car4;
obj game4_floor;
obj game4_garden_acce;
obj game4_human;
obj game4_lamp_hock;
obj game4_light;
obj game4_roof;
obj game4_stair;
obj game4_sofa;
obj game4_table1;
obj game4_table2;
obj game4_tree_branch;
obj game4_tree_leaves;
obj game4_wall;
obj game4_wood2;
obj game4_wood_chair;
obj game4_wood_panel;
obj game4_wood_poll;
obj game4_wood_table;

Point game1_chess_position;
Point game2_tank_position;
Point game3_race_position;
Point game4_shooting_position;

//チェス
obj chess_chair;
obj chess_map;
obj chess_set_board;
obj chess_table;
obj chess_BB1;
obj chess_BB2;
obj chess_BK;
obj chess_BN1;
obj chess_BN2;
obj chess_BQ;
obj chess_BR1;
obj chess_BR2;
obj chess_BP1;
obj chess_BP2;
obj chess_BP3;
obj chess_BP4;
obj chess_BP5;
obj chess_BP6;
obj chess_BP7;
obj chess_BP8;
obj chess_WB1;
obj chess_WB2;
obj chess_WK;
obj chess_WN1;
obj chess_WN2;
obj chess_WQ;
obj chess_WR1;
obj chess_WR2;
obj chess_WP1;
obj chess_WP2;
obj chess_WP3;
obj chess_WP4;
obj chess_WP5;
obj chess_WP6;
obj chess_WP7;
obj chess_WP8;
obj game2_chess_house_playing;
obj game2_chess_black_playing;
obj game2_Floor_playing;
obj text_w[29];
obj text_i[29];
obj text_n[29];
obj text_l[29];
obj text_o[29];
obj text_s[29];
obj text_e[29];

//戦車
obj tankLower;
obj tankUpper;
obj tankBarrel;
obj canon;
obj explosion;
obj tankground;
obj tankmap;
obj dropPosition;

//カーレース
obj road;
obj sports_mainBody;
obj sports_plane;
obj sports_wheel_right;
obj sports_wheel_left;
obj sports_speedtext;
obj sports_speedtext_red;
obj sports_stick;
obj sports_back;
obj sports_road;
obj sports_grass;
obj sports_dirt;
obj sports_tire;
obj sports_wall;
obj sports1light;
obj map_wall;
obj map_tire;
obj map_road;
obj map_grass;
obj map_player;
obj sports_lap;
obj sports2_mainbody;
obj sports2_plane;
obj sports2_right;
obj sports2_left;
obj sports2light;
obj sports_1st;
obj sports_2nd;
obj sports_3rd;
obj sports_4th;
obj sports3light;
obj sports3_Right;
obj sports3_Left;
obj sports3_mainbody;
obj sports3_plane;
obj sports4light;
obj sports4_Right;
obj sports4_Left;
obj sports4_mainbody;
obj sports4_plane;
obj anim_1st_1[29];
obj anim_1st_s[29];
obj anim_1st_t[29];
obj anim_2nd_2[29];
obj anim_2nd_n[29];
obj anim_2nd_d[29];
obj anim_3rd_3[29];
obj anim_3rd_r[29];
obj anim_3rd_d[29];
obj anim_4th_4[29];
obj anim_4th_t[29];
obj anim_4th_h[29];

//シューティング
obj Reciever;
obj Foregrip;
obj Handguard;
obj Scope;
obj Silencer;
obj Stock;
obj Base;
obj Mount;
obj Charge;
obj Hand;
obj Ret;
obj fireFlash;
obj base_ground;
obj inner_ground;
obj labslogo;
obj stair_flat;
obj stair_naname;
obj stair_long;
obj tarkov_fence;
obj lightPM;
obj rooms;
obj item_case_1;
obj item_case_2;
obj tarkov_item_egg;
obj tarkov_item_cat;
obj tarkov_item_ledx;
obj escape1;
obj escape2;
obj escape3;
obj anim_survived_s[29];
obj anim_survived_u[29];
obj anim_survived_r[29];
obj anim_survived_v1[29];
obj anim_survived_i[29];
obj anim_survived_v2[29];
obj anim_survived_e[29];
obj anim_survived_d[29];
obj getitem;

int ignore_key_repeat_event_filter(void* userdata, SDL_Event* event) {
	if (event->type == SDL_KEYDOWN && event->key.repeat != 0) {
		return 0;
	}
	if (event->type == SDL_MOUSEMOTION) {
		int x = event->motion.x;
		int y = event->motion.y;
		if (x != WARP_WIDTH || y != WARP_HEIGHT) {
			return 1;
		}
		else {
			return 0;
		}
	}
	return 1;
}

void UnloadAnimMeshs(int f,int e,obj o[])
{
	for(int i = 0; i < e-f+1;i++)
	{
		o[i].Uninit();
	}
}

void UnloadParkMesh()
{
	Mix_PlayMusic(BGM_loading, -1);
	//sky
	skyOutSide.Uninit();
	skyInSide.Uninit();

	//outside object
	aincrad_bot.Uninit();
	aincrad_top.Uninit();
	aincrad_sword.Uninit();
	aincrad_lower.Uninit();
	FireWorks.Uninit();
	title.Uninit();
	titleShield.Uninit();
	titleFrame.Uninit();
	aincrad_road.Uninit();
	aincrad_house.Uninit();
	fence.Uninit();

	//inside object
	door_frame.Uninit();
	door_left.Uninit();
	door_right.Uninit();
	game0_head.Uninit();
	disitalTable.Uninit();
	lamp1.Uninit();
	lamp2.Uninit();
	grass.Uninit();
	horse_statue1.Uninit();
	horse_statue2.Uninit();
	inside_road.Uninit();
	pedestal.Uninit();
	dirt.Uninit();
	house_brick.Uninit();
	house_roof.Uninit();
	house_window.Uninit();
	house_white.Uninit();
	house_door.Uninit();
	main_statue_base.Uninit();
	main_statue_brick.Uninit();
	main_statue_mini.Uninit();
	main_statue_ring.Uninit();
	main_statue_cristal.Uninit();
	tarkov_hat.Uninit();
	tarkov_top.Uninit();
	tarkov_face.Uninit();
	tarkov_counter.Uninit();
	game0_head.Uninit();
	game0_top.Uninit();
	game0_pants.Uninit();
	game0_counter.Uninit();
	game2_chess_house.Uninit();
	game2_chess_black.Uninit();
	game2_chess_white.Uninit();
	game2_fani_table.Uninit();
	game2_sofa.Uninit();
	game2_Floor.Uninit();

	game1_basket.Uninit();
	game1_cat.Uninit();
	game1_deco.Uninit();
	game1_floor.Uninit();
	game1_kawara1.Uninit();
	game1_kawara2.Uninit();
	game1_kawara3.Uninit();
	game1_kawara4.Uninit();
	game1_light.Uninit();
	game1_ninja.Uninit();
	game1_post.Uninit();
	game1_table.Uninit();
	game1_wall.Uninit();

	game3_canon.Uninit();
	game3_chair.Uninit();
	game3_chest.Uninit();
	game3_frag.Uninit();
	game3_gate.Uninit();
	game3_ground.Uninit();
	game3_human_body.Uninit();
	game3_human_cloth.Uninit();
	game3_roof.Uninit();
	game3_wall.Uninit();

	//unload chess
	chess_chair.Uninit();
	chess_table.Uninit();
	chess_map.Uninit();
	chess_set_board.Uninit();
	chess_WB1.Uninit();
	chess_WB2.Uninit();
	chess_WR1.Uninit();
	chess_WR2.Uninit();
	chess_WK.Uninit();
	chess_WQ.Uninit();
	chess_WN1.Uninit();
	chess_WN2.Uninit();
	chess_WP1.Uninit();
	chess_WP2.Uninit();
	chess_WP3.Uninit();
	chess_WP4.Uninit();
	chess_WP5.Uninit();
	chess_WP6.Uninit();
	chess_WP7.Uninit();
	chess_WP8.Uninit();
	chess_BB1.Uninit();
	chess_BB2.Uninit();
	chess_BK.Uninit();
	chess_BN1.Uninit();
	chess_BN2.Uninit();
	chess_BQ.Uninit();
	chess_BR1.Uninit();
	chess_BR2.Uninit();
	chess_BP1.Uninit();
	chess_BP2.Uninit();
	chess_BP3.Uninit();
	chess_BP4.Uninit();
	chess_BP5.Uninit();
	chess_BP6.Uninit();
	chess_BP7.Uninit();
	chess_BP8.Uninit();

	//unload race
	game4_asphaltfuly.Uninit();
	game4_base_cars.Uninit();
	game4_car1.Uninit();
	game4_car2.Uninit();
	game4_car3.Uninit();
	game4_car4.Uninit();
	game4_floor.Uninit();
	game4_garden_acce.Uninit();
	game4_human.Uninit();
	game4_lamp_hock.Uninit();
	game4_light.Uninit();
	game4_roof.Uninit();
	game4_stair.Uninit();
	game4_table1.Uninit();
	game4_table2.Uninit();
	game4_tree_branch.Uninit();
	game4_tree_leaves.Uninit();
	game4_wall.Uninit();
	game4_wood2.Uninit();
	game4_wood_chair.Uninit();
	game4_wood_panel.Uninit();
	game4_wood_poll.Uninit();
	game4_wood_table.Uninit();
	game4_sofa.Uninit();

	//text message
	createchessmatch.Uninit();
	createracematch.Uninit();
	createshootingmatch.Uninit();
	createtankmatch.Uninit();
	jointhisgame.Uninit();
	howmanyplayers.Uninit();
	selectyourcar.Uninit();
	result_chess_win.Uninit();
	result_chess_lose.Uninit();
	result_tank_1st.Uninit();
	result_tank_2nd.Uninit();
	result_tank_3rd.Uninit();
	result_tank_4th.Uninit();
	result_shooting_kill.Uninit();
	result_shooting_suevived.Uninit();
	result_race_1st.Uninit();
	result_race_2nd.Uninit();
	result_race_3rd.Uninit();
	result_race_4th.Uninit();
	result_get_item_cheap.Uninit();
	result_get_item_normal.Uninit();
	result_get_item_expensive.Uninit();


}

void UnloadChessMesh()
{
	Mix_PlayMusic(BGM_loading, -1);

	chess_chair.Uninit();
	chess_table.Uninit();
	chess_map.Uninit();
	chess_set_board.Uninit();
	chess_WB1.Uninit();
	chess_WB2.Uninit();
	chess_WR1.Uninit();
	chess_WR2.Uninit();
	chess_WK.Uninit();
	chess_WQ.Uninit();
	chess_WN1.Uninit();
	chess_WN2.Uninit();
	chess_WP1.Uninit();
	chess_WP2.Uninit();
	chess_WP3.Uninit();
	chess_WP4.Uninit();
	chess_WP5.Uninit();
	chess_WP6.Uninit();
	chess_WP7.Uninit();
	chess_WP8.Uninit();
	chess_BB1.Uninit();
	chess_BB2.Uninit();
	chess_BK.Uninit();
	chess_BN1.Uninit();
	chess_BN2.Uninit();
	chess_BQ.Uninit();
	chess_BR1.Uninit();
	chess_BR2.Uninit();
	chess_BP1.Uninit();
	chess_BP2.Uninit();
	chess_BP3.Uninit();
	chess_BP4.Uninit();
	chess_BP5.Uninit();
	chess_BP6.Uninit();
	chess_BP7.Uninit();
	chess_BP8.Uninit();

	game2_chess_house_playing.Uninit();
	game2_chess_black_playing.Uninit();
	game2_Floor_playing.Uninit();

	grass.Uninit();
	skyInSide.Uninit();

	house_brick.Uninit();
	house_roof.Uninit();
	house_window.Uninit();
	house_white.Uninit();
	house_door.Uninit();

	UnloadAnimMeshs(0,28,text_w);
	UnloadAnimMeshs(0,28,text_i);
	UnloadAnimMeshs(0,28,text_n);
	UnloadAnimMeshs(0,28,text_l);
	UnloadAnimMeshs(0,28,text_o);
	UnloadAnimMeshs(0,28,text_s);
	UnloadAnimMeshs(0,28,text_e);

}

void UnloadRaceMesh()
{
	Mix_PlayMusic(BGM_loading, -1);


	skyOutSide.Uninit();
	sports_mainBody.Uninit();
	sports_plane.Uninit();
	sports_wheel_right.Uninit();
	sports_wheel_left.Uninit();
	sports_road.Uninit();
	sports_back.Uninit();
	sports_speedtext.Uninit();
	sports_speedtext_red.Uninit();
	sports_stick.Uninit();
	sports_grass.Uninit();
	sports_dirt.Uninit();
	sports_tire.Uninit();
	sports_wall.Uninit();
	sports1light.Uninit();
	map_wall.Uninit();
	map_tire.Uninit();
	map_road.Uninit();
	map_grass.Uninit();
	map_player.Uninit();
	sports_lap.Uninit();
	sports2_mainbody.Uninit();
	sports2_left.Uninit();
	sports2_right.Uninit();
	sports2_plane.Uninit();
	sports2light.Uninit();
	sports_1st.Uninit();
	sports_2nd.Uninit();
	sports_3rd.Uninit();
	sports_4th.Uninit();
	text_go.Uninit();
	sports3_Left.Uninit();
	sports3_Right.Uninit();
	sports3_mainbody.Uninit();
	sports3_plane.Uninit();
	sports3light.Uninit();
	sports4_Left.Uninit();
	sports4_Right.Uninit();
	sports4_mainbody.Uninit();
	sports4_plane.Uninit();
	sports4light.Uninit();

	UnloadAnimMeshs(0,28,anim_1st_1);
	UnloadAnimMeshs(0,28,anim_1st_s);
	UnloadAnimMeshs(0,28,anim_1st_t);
	UnloadAnimMeshs(0,28,anim_2nd_2);
	UnloadAnimMeshs(0,28,anim_2nd_n);
	UnloadAnimMeshs(0,28,anim_2nd_d);
	UnloadAnimMeshs(0,28,anim_3rd_3);
	UnloadAnimMeshs(0,28,anim_3rd_r);
	UnloadAnimMeshs(0,28,anim_3rd_d);
	UnloadAnimMeshs(0,28,anim_4th_4);
	UnloadAnimMeshs(0,28,anim_4th_t);
	UnloadAnimMeshs(0,28,anim_4th_h);
}

void UnloadShootingMesh()
{
	Mix_PlayMusic(BGM_loading, -1);


	Reciever.Uninit();
	Foregrip.Uninit();
	Handguard.Uninit();
	Scope.Uninit();
	Silencer.Uninit();
	Stock.Uninit();
	Base.Uninit();
	Mount.Uninit();
	Charge.Uninit();
	Hand.Uninit();
	Ret.Uninit();
	base_ground.Uninit();
	inner_ground.Uninit();
	labslogo.Uninit();
	stair_flat.Uninit();
	stair_long.Uninit();
	stair_naname.Uninit();
	lightPM.Uninit();
	tarkov_fence.Uninit();
	rooms.Uninit();
	fireFlash.Uninit();
	item_case_1.Uninit();
	item_case_2.Uninit();
	tarkov_item_cat.Uninit();
	tarkov_item_egg.Uninit();
	tarkov_item_ledx.Uninit();
	escape1.Uninit();
	escape2.Uninit();
	escape3.Uninit();
	getitem.Uninit();
	UnloadAnimMeshs(0,28,anim_survived_s);
	UnloadAnimMeshs(0,28,anim_survived_u);
	UnloadAnimMeshs(0,28,anim_survived_r);
	UnloadAnimMeshs(0,28,anim_survived_v1);
	UnloadAnimMeshs(0,28,anim_survived_i);
	UnloadAnimMeshs(0,28,anim_survived_v2);
	UnloadAnimMeshs(0,28,anim_survived_e);
	UnloadAnimMeshs(0,28,anim_survived_d);
}

void UnloadTankMesh()
{
	Mix_PlayMusic(BGM_loading, -1);


	tankUpper.Uninit();
	tankBarrel.Uninit();
	tankLower.Uninit();
	canon.Uninit();
	explosion.Uninit();
	tankground.Uninit();
	tankmap.Uninit();
	dropPosition.Uninit();

	UnloadAnimMeshs(0,28,anim_1st_1);
	UnloadAnimMeshs(0,28,anim_1st_s);
	UnloadAnimMeshs(0,28,anim_1st_t);
	UnloadAnimMeshs(0,28,anim_2nd_2);
	UnloadAnimMeshs(0,28,anim_2nd_n);
	UnloadAnimMeshs(0,28,anim_2nd_d);
	UnloadAnimMeshs(0,28,anim_3rd_3);
	UnloadAnimMeshs(0,28,anim_3rd_r);
	UnloadAnimMeshs(0,28,anim_3rd_d);
	UnloadAnimMeshs(0,28,anim_4th_4);
	UnloadAnimMeshs(0,28,anim_4th_t);
	UnloadAnimMeshs(0,28,anim_4th_h);
}

void loadReturnfromGame(int frame)//ゲームからロビーに戻るときにロードするメッシュ
{
	int oc = 145;

	switch (frame)
	{
	case 0:
		skyInSide.load("config/mesh/skyInSide.txt", "config/image/pureskyinside.jpg",oc);
		break;
	case 1:
		door_frame.load("config/mesh/door_frame.txt", "config/image/door.jpg",oc);
		break;
	case 2:
		door_left.load("config/mesh/door_left.txt", "config/image/door.jpg",oc);
		break;
	case 3:
		door_right.load("config/mesh/door_right.txt", "config/image/door.jpg",oc);
		break;
	case 4:
		game0_hair.load("config/mesh/game0_hair.txt", "config/image/game0_hair.png",oc);
		break;
	case 5:
		disitalTable.load("config/mesh/disitalTable.txt", "config/image/disitalTable.png",oc);
		break;
	case 6:
		lamp1.load("config/mesh/lamp1.txt", "config/image/lamp.jpg",oc);
		break;
	case 7:
		lamp2.load("config/mesh/lamp2.txt", "config/image/lamp.jpg",oc);
		break;
	case 8:
		grass.load("config/mesh/grass.txt", "config/image/grass.jpg",oc);
		break;
	case 9:
		horse_statue1.load("config/mesh/horse_statue1.txt", "config/image/horse_statue1.png",oc);
		break;
	case 10:
		horse_statue2.load("config/mesh/horse_statue2.txt", "config/image/horse_statue2.png",oc);
		break;
	case 11:
		inside_road.load("config/mesh/inside_road.txt", "config/image/aincrad_road.jpg",oc);
		break;
	case 12:
		pedestal.load("config/mesh/pedestal.txt", "config/image/pedestal.png",oc);
		break;
	case 13:
		dirt.load("config/mesh/dirt.txt", "config/image/dirt.jpg",oc);
		break;
	case 14:
		house_brick.load("config/mesh/house_brick.txt", "config/image/house_brick.jpg",oc);
		break;
	case 15:
		house_roof.load("config/mesh/house_roof.txt", "config/image/house_roof.jpg",oc);
		break;
	case 16:
		house_window.load("config/mesh/house_window.txt", "config/image/house_window.jpg",oc);
		break;
	case 17:
		house_white.load("config/mesh/house_white.txt",oc);
		break;
	case 18:
		house_door.load("config/mesh/house_door.txt", "config/image/house_door.jpg",oc);
		break;
	case 19:
		main_statue_base.load("config/mesh/main_statue_base.txt", "config/image/cristal.png",oc);
		break;
	case 20:
		main_statue_brick.load("config/mesh/main_statue_brick.txt", "config/image/house_brick.jpg",oc);
		break;
	case 21:
		main_statue_mini.load("config/mesh/main_statue_mini.txt", "config/image/mini.png",oc);
		break;
	case 22:
		main_statue_ring.load("config/mesh/main_statue_ring.txt", "config/image/ring.png",oc);
		break;
	case 23:
		main_statue_cristal.load("config/mesh/main_statue_cristal.txt", "config/image/cristal.png",oc);
		break;
	case 24:
		tarkov_hat.load("config/mesh/game1_tarkov_hat.txt", "config/image/game1_tarkov_hat.png",oc);
		break;
	case 25:
		tarkov_top.load("config/mesh/game1_tarkov_top.txt", "config/image/game1_tarkov_top.png",oc);
		break;
	case 26:
		tarkov_face.load("config/mesh/game1_tarkov_face.txt", "config/image/game1_tarkov_face.png",oc);
		break;
	case 27:
		tarkov_counter.load("config/mesh/game1_tarkov_counter.txt", "config/image/game1_tarkov_counter.png",oc);
		break;
	case 28:
		chess_chair.load("config/mesh/chess_chair.txt", "config/image/chess_chair.png",oc);
		break;
	case 29:
		chess_table.load("config/mesh/chess_table.txt", "config/image/chess_table.png",oc);
		break;
	case 30:
		chess_map.load("config/mesh/chess_map.txt", "config/image/chess_set_board.png",oc);
		break;
	case 31:
		chess_set_board.load("config/mesh/chess_set_board.txt", "config/image/chess_set_board.png",oc);
		break;
	case 32:
		chess_WB1.load("config/mesh/WB1.txt", "config/image/chess_set_white.png",oc);
		break;
	case 33:
		chess_WB2.load("config/mesh/WB2.txt", "config/image/chess_set_white.png",oc);
		break;
	case 34:
		chess_WR1.load("config/mesh/WR1.txt", "config/image/chess_set_white.png",oc);
		break;
	case 35:
		chess_WR2.load("config/mesh/WR2.txt", "config/image/chess_set_white.png",oc);
		break;
	case 36:
		chess_WK.load("config/mesh/WK.txt", "config/image/chess_set_white.png",oc);
		break;
	case 37:
		chess_WQ.load("config/mesh/WQ.txt", "config/image/chess_set_white.png",oc);
		break;
	case 38:
		chess_WN1.load("config/mesh/WN1.txt", "config/image/chess_set_white.png",oc);
		break;
	case 39:
		chess_WN2.load("config/mesh/WN2.txt", "config/image/chess_set_white.png",oc);
		break;
	case 40:
		chess_WP1.load("config/mesh/WP1.txt", "config/image/chess_set_white.png",oc);
		break;
	case 41:
		chess_WP2.load("config/mesh/WP2.txt", "config/image/chess_set_white.png",oc);
		break;
	case 42:
		chess_WP3.load("config/mesh/WP3.txt", "config/image/chess_set_white.png",oc);
		break;
	case 43:
		chess_WP4.load("config/mesh/WP4.txt", "config/image/chess_set_white.png",oc);
		break;
	case 44:
		chess_WP5.load("config/mesh/WP5.txt", "config/image/chess_set_white.png",oc);
		break;
	case 45:
		chess_WP6.load("config/mesh/WP6.txt", "config/image/chess_set_white.png",oc);
		break;
	case 46:
		chess_WP7.load("config/mesh/WP7.txt", "config/image/chess_set_white.png",oc);
		break;
	case 47:
		chess_WP8.load("config/mesh/WP8.txt", "config/image/chess_set_white.png",oc);
		break;
	case 48:
		chess_BB1.load("config/mesh/BB1.txt", "config/image/chess_set_black.png",oc);
		break;
	case 49:
		chess_BB2.load("config/mesh/BB2.txt", "config/image/chess_set_black.png",oc);
		break;
	case 50:
		chess_BK.load("config/mesh/BK.txt", "config/image/chess_set_black.png",oc);
		break;
	case 51:
		chess_BN1.load("config/mesh/BN1.txt", "config/image/chess_set_black.png",oc);
		break;
	case 52:
		chess_BN2.load("config/mesh/BN2.txt", "config/image/chess_set_black.png",oc);
		break;
	case 53:
		chess_BQ.load("config/mesh/BQ.txt", "config/image/chess_set_black.png",oc);
		break;
	case 54:
		chess_BR1.load("config/mesh/BR1.txt", "config/image/chess_set_black.png",oc);
		break;
	case 55:
		chess_BR2.load("config/mesh/BR2.txt", "config/image/chess_set_black.png",oc);
		break;
	case 56:
		chess_BP1.load("config/mesh/BP1.txt", "config/image/chess_set_black.png",oc);
		break;
	case 57:
		chess_BP2.load("config/mesh/BP2.txt", "config/image/chess_set_black.png",oc);
		break;
	case 58:
		chess_BP3.load("config/mesh/BP3.txt", "config/image/chess_set_black.png",oc);
		break;
	case 59:
		chess_BP4.load("config/mesh/BP4.txt", "config/image/chess_set_black.png",oc);
		break;
	case 60:
		chess_BP5.load("config/mesh/BP5.txt", "config/image/chess_set_black.png",oc);
		break;
	case 61:
		chess_BP6.load("config/mesh/BP6.txt", "config/image/chess_set_black.png",oc);
		break;
	case 62:
		chess_BP7.load("config/mesh/BP7.txt", "config/image/chess_set_black.png",oc);
		break;
	case 63:
		chess_BP8.load("config/mesh/BP8.txt", "config/image/chess_set_black.png",oc);
		break;
	case 64:
		FireWorks.load("config/mesh/FireWorks.txt",oc);
		break;
	case 65:
		createchessmatch.load("config/mesh/createchessmatch.txt",oc);
		break;
	case 66:
		jointhisgame.load("config/mesh/jointhisgame.txt",oc);
		break;
	case 67:
		game0_head.load("config/mesh/game0_head.txt","config/image/game0_head.png",oc);
		break;
	case 68:
	    game0_top.load("config/mesh/game0_top.txt","config/image/game0_top.png",oc);
		break;
	case 69:
		game0_pants.load("config/mesh/game0_pants.txt","config/image/game0_pants.png",oc);
		break;
	case 70:
		game0_counter.load("config/mesh/game0_counter.txt","config/image/game1_tarkov_counter.png",oc);
		break;
	case 71:
		howmanyplayers.load("config/mesh/howmanyplayers.txt",oc);
		break;
	case 72:
		selectyourcar.load("config/mesh/selectyourcar.txt",oc);
		break;
	case 73:
		createracematch.load("config/mesh/createracematch.txt",oc);
		break;
	case 74:
		createshootingmatch.load("config/mesh/createshootingmatch.txt",oc);
		break;
	case 75:
		createtankmatch.load("config/mesh/createtankmatch.txt",oc);
		break;
	case 76:
	    game2_chess_house.load("config/mesh/game2_chess_house.txt", "config/image/game2_chess_house.png", oc);
		break;
	case 77:
	    game2_chess_black.load("config/mesh/game2_chess_black.txt", "config/image/game2_chess_black.png", oc);
		break;
	case 78:
	    game2_chess_white.load("config/mesh/game2_chess_white.txt", "config/image/game2_chess_white.png", oc);
		break;
	case 79:
	    game2_fani_table.load("config/mesh/game2_fani_table.txt", "config/image/game2_fani_table.png", oc);
		break;
	case 80:
	    game2_sofa.load("config/mesh/game2_sofa.txt", "config/image/game2_sofa.png", oc);
		break;
	case 81:
	    game2_Floor.load("config/mesh/game2_Floor.txt", "config/image/game2_Floor.png", oc);
		break;
	case 82:
	    game1_basket.load("config/mesh/game1_basket.txt", "config/image/game1_basket.jpg", oc);
		break;
	case 83:
	    game1_cat.load("config/mesh/game1_cat.txt", "config/image/game1_cat.png", oc);
		break;
	case 84:
	    game1_deco.load("config/mesh/game1_deco.txt", "config/image/game1_deco.jpg", oc);
		break;
	case 85:
	    game1_floor.load("config/mesh/game1_floor.txt", "config/image/game1_floor.png", oc);
		break;
	case 86:
	    game1_kawara1.load("config/mesh/game1_kawara1.txt", "config/image/game1_kawara1.png", oc);
		break;
	case 87:
	    game1_kawara2.load("config/mesh/game1_kawara2.txt", "config/image/game1_kawara2.png", oc);
		break;
	case 88:
	    game1_kawara3.load("config/mesh/game1_kawara3.txt", "config/image/game1_kawara3.png", oc);
		break;
	case 89:
	    game1_kawara4.load("config/mesh/game1_kawara4.txt", "config/image/game1_kawara4.png", oc);
		break;
	case 90:
	    game1_light.load("config/mesh/game1_light.txt", "config/image/game1_light.jpg", oc);
		break;
	case 91:
	    game1_ninja.load("config/mesh/game1_ninja.txt", "config/image/game1_ninja.png", oc);
		break;
	case 92:
	    game1_post.load("config/mesh/game1_post.txt", "config/image/game1_post.png", oc);
		break;
	case 93:
	    game1_table.load("config/mesh/game1_table.txt", "config/image/game1_table.png", oc);
		break;
	case 94:
	    game1_wall.load("config/mesh/game1_wall.txt", "config/image/game1_wall.png", oc);
		break;
	case 95:
		result_chess_lose.load("config/mesh/result_chess_lose.txt",oc);
		break;
	case 96:
		result_chess_win.load("config/mesh/result_chess_win.txt",oc);
		break;
	case 97:
		result_get_item_cheap.load("config/mesh/result_get_item_cheap.txt",oc);
		break;
	case 98:
		result_get_item_normal.load("config/mesh/result_get_item_normal.txt",oc);
		break;
	case 99:
		result_get_item_expensive.load("config/mesh/result_get_item_expensive.txt",oc);
		break;
	case 100:
		result_race_1st.load("config/mesh/result_race_1st.txt",oc);
		break;
	case 101:
		result_race_2nd.load("config/mesh/result_race_2nd.txt",oc);
		break;
	case 102:
		result_race_3rd.load("config/mesh/result_race_3rd.txt",oc);
		break;
	case 103:
		result_race_4th.load("config/mesh/result_race_4th.txt",oc);
		break;
	case 104:
		result_tank_1st.load("config/mesh/result_tank_1st.txt",oc);
		break;
	case 105:
		result_tank_2nd.load("config/mesh/result_tank_2nd.txt",oc);
		break;
	case 106:
		result_shooting_kill.load("config/mesh/result_shooting_kill.txt",oc);
		break;
	case 107:
		result_shooting_suevived.load("config/mesh/result_shooting_survived.txt",oc);
		break;
	case 108:
		aincrad_top.load("config/mesh/aincrad_top.txt", "config/image/aincrad_top.png",oc);
		break;
	case 109:
		game3_canon.load("config/mesh/game3_canon.txt","config/image/game3_canon.png",oc);
		break;
	case 110:
		game3_chair.load("config/mesh/game3_chair.txt","config/image/game3_chair.jpg",oc);
		break;
	case 111:
		game3_chest.load("config/mesh/game3_chest.txt","config/image/game3_chest.jpg",oc);
		break;
	case 112:
		game3_frag.load("config/mesh/game3_frag.txt",oc);
		break;
	case 113:
		game3_gate.load("config/mesh/game3_gate.txt","config/image/game3_gate.jpg",oc);
		break;
	case 114:
		game3_ground.load("config/mesh/game3_ground.txt","config/image/game3_ground.jpg",oc);
		break;
	case 115:
		game3_human_body.load("config/mesh/game3_human_body.txt","config/image/game3_human_body.png",oc);
		break;
	case 116:
		game3_human_cloth.load("config/mesh/game3_human_cloth.txt","config/image/game3_human_cloth.png",oc);
		break;
	case 117:
		game3_roof.load("config/mesh/game3_roof.txt","config/image/game3_roof.png",oc);
		break;
	case 118:
		game3_wall.load("config/mesh/game3_wall.txt","config/image/game3_wall.png",oc);
		break;
	case 119:
		game4_asphaltfuly.load("config/mesh/game4_asphaltfuly.txt","config/image/game4_asphaltfuly.png",oc);
		break;
	case 120:
		game4_base_cars.load("config/mesh/game4_base_cars.txt","config/image/game4_base_cars.png",oc);
		break;
	case 121:
		game4_car1.load("config/mesh/game4_car1.txt","config/image/game4_car1.png",oc);
		break;
	case 122:
		game4_car2.load("config/mesh/game4_car2.txt","config/image/game4_car2.png",oc);
		break;
	case 123:
		game4_car3.load("config/mesh/game4_car3.txt","config/image/game4_car3.png",oc);
		break;
	case 124:
		game4_car4.load("config/mesh/game4_car4.txt","config/image/game4_car4.png",oc);
		break;
	case 125:
		game4_floor.load("config/mesh/game4_floor.txt","config/image/game4_floor.jpg",oc);
		break;
	case 126:
		game4_garden_acce.load("config/mesh/game4_garden_acce.txt","config/image/game4_garden_acce.jpg",oc);
		break;
	case 127:
		game4_human.load("config/mesh/game4_human.txt","config/image/game4_human.png",oc);
		break;
	case 128:
		game4_lamp_hock.load("config/mesh/game4_lamp_hock.txt","config/image/game4_lamp_hock.jpg",oc);
		break;
	case 129:
		game4_light.load("config/mesh/game4_light.txt","config/image/game4_light.jpg",oc);
		break;
	case 130:
		game4_roof.load("config/mesh/game4_roof.txt","config/image/game4_roof.png",oc);
		break;
	case 131:
		game4_stair.load("config/mesh/game4_stair.txt","config/image/game4_stair.jpg",oc);
		break;
	case 132:
		game4_table1.load("config/mesh/game4_table1.txt","config/image/game4_table1.png",oc);
		break;
	case 133:
		game4_table2.load("config/mesh/game4_table2.txt","config/image/game4_table2.jpg",oc);
		break;
	case 134:
		game4_tree_branch.load("config/mesh/game4_tree_branch.txt",oc);
		break;
	case 135:
		game4_tree_leaves.load("config/mesh/game4_tree_leaves.txt",oc);
		break;
	case 136:
		game4_wall.load("config/mesh/game4_wall.txt","config/image/game4_wall.jpg",oc);
		break;
	case 137:
		game4_wood2.load("config/mesh/game4_wood2.txt","config/image/game4_wood2.jpg",oc);
		break;
	case 138:
		game4_wood_chair.load("config/mesh/game4_wood_chair.txt","config/image/game4_wood_chair.jpg",oc);
		break;
	case 139:
		game4_wood_panel.load("config/mesh/game4_wood_panel.txt","config/image/game4_wood_panel.jpg",oc);
		break;
	case 140:
		game4_wood_poll.load("config/mesh/game4_wood_poll.txt","config/image/game4_wood_poll.jpg",oc);
		break;
	case 141:
		game4_wood_table.load("config/mesh/game4_wood_table.txt","config/image/game4_wood_table.png",oc);
		break;
	case 142:
	    game4_sofa.load("config/mesh/game4_sofa.txt","config/image/game4_sofa.jpg",oc);
		break;
	case 143:
		result_tank_3rd.load("config/mesh/result_tank_3rd.txt",oc);
		break;
	case 144:
		result_tank_4th.load("config/mesh/result_tank_4th.txt",oc);
		break;
	default:
		mainloopcount = 7;
		currentMeshNum = 0;
		game[1].stts = 0;
		game[2].stts = 0;
		game[3].stts = 0;
		Mix_PlayMusic(BGM_park, -1);

		break;
	}
}

void loadInitMesh(int frame)//最初の一回だけ
{

	int oc = 192;
	switch (frame)
	{
	case 0:
		skyOutSide.load("config/mesh/skyOutSide.txt", "config/image/puresky.jpg",oc);
		break;
	case 1:
		skyInSide.load("config/mesh/skyInSide.txt", "config/image/pureskyinside.jpg",oc);
		break;
	case 2:
		aincrad_bot.load("config/mesh/aincrad_bot.txt", "config/image/aincrad_bot.jpg",oc);
		break;
	case 3:
		aincrad_top.load("config/mesh/aincrad_top.txt", "config/image/aincrad_top.png",oc);
		break;
	case 4:
		aincrad_sword.load("config/mesh/aincrad_sword.txt", "config/image/aincrad_sword.png",oc);
		break;
	case 5:
		aincrad_lower.load("config/mesh/aincrad_lower.txt", "config/image/aincrad_lower.png",oc);
		break;
	case 6:
		open.load("config/mesh/open.txt",oc);
		break;
	case 7:
		FireWorks.load("config/mesh/FireWorks.txt",oc);
		break;
	case 8:
		title.load("config/mesh/title.txt", "config/image/title.png",oc);
		break;
	case 9:
		titleShield.load("config/mesh/titleShield.txt",oc);
		break;
	case 10:
		titleFrame.load("config/mesh/titleFrame.txt",oc);
		break;
	case 11:
		aincrad_road.load("config/mesh/aincrad_road.txt", "config/image/aincrad_road.jpg",oc);
		break;
	case 12:
		fence.load("config/mesh/Fence.txt",oc);
		break;
	case 13:
		door_frame.load("config/mesh/door_frame.txt", "config/image/door.jpg",oc);
		break;
	case 14:
		door_left.load("config/mesh/door_left.txt", "config/image/door.jpg",oc);
		break;
	case 15:
		door_right.load("config/mesh/door_right.txt", "config/image/door.jpg",oc);
		break;
	case 16:
		game0_hair.load("config/mesh/game0_hair.txt", "config/image/game0_hair.png",oc);
		break;
	case 17:
		disitalTable.load("config/mesh/disitalTable.txt", "config/image/disitalTable.png",oc);
		break;
	case 18:
		lamp1.load("config/mesh/lamp1.txt", "config/image/lamp.jpg",oc);
		break;
	case 19:
		lamp2.load("config/mesh/lamp2.txt", "config/image/lamp.jpg",oc);
		break;
	case 20:
		grass.load("config/mesh/grass.txt", "config/image/grass.jpg",oc);
		break;
	case 21:
		horse_statue1.load("config/mesh/horse_statue1.txt", "config/image/horse_statue1.png",oc);
		break;
	case 22:
		horse_statue2.load("config/mesh/horse_statue2.txt", "config/image/horse_statue2.png",oc);
		break;
	case 23:
		inside_road.load("config/mesh/inside_road.txt", "config/image/aincrad_road.jpg",oc);
		break;
	case 24:
		pedestal.load("config/mesh/pedestal.txt", "config/image/pedestal.png",oc);
		break;
	case 25:
		dirt.load("config/mesh/dirt.txt", "config/image/dirt.jpg",oc);
		break;
	case 26:
		house_brick.load("config/mesh/house_brick.txt", "config/image/house_brick.jpg",oc);
		break;
	case 27:
		house_roof.load("config/mesh/house_roof.txt", "config/image/house_roof.jpg",oc);
		break;
	case 28:
		house_window.load("config/mesh/house_window.txt", "config/image/house_window.jpg",oc);
		break;
	case 29:
		house_white.load("config/mesh/house_white.txt",oc);
		break;
	case 30:
		house_door.load("config/mesh/house_door.txt", "config/image/house_door.jpg",oc);
		break;
	case 31:
		main_statue_base.load("config/mesh/main_statue_base.txt", "config/image/cristal.png",oc);
		break;
	case 32:
		main_statue_brick.load("config/mesh/main_statue_brick.txt", "config/image/house_brick.jpg",oc);
		break;
	case 33:
		main_statue_mini.load("config/mesh/main_statue_mini.txt", "config/image/mini.png",oc);
		break;
	case 34:
		main_statue_ring.load("config/mesh/main_statue_ring.txt", "config/image/ring.png",oc);
		break;
	case 35:
		main_statue_cristal.load("config/mesh/main_statue_cristal.txt", "config/image/cristal.png",oc);
		break;
	case 36:
		tarkov_hat.load("config/mesh/game1_tarkov_hat.txt", "config/image/game1_tarkov_hat.png",oc);
		break;
	case 37:
		tarkov_top.load("config/mesh/game1_tarkov_top.txt", "config/image/game1_tarkov_top.png",oc);
		break;
	case 38:
		tarkov_face.load("config/mesh/game1_tarkov_face.txt", "config/image/game1_tarkov_face.png",oc);
		break;
	case 39:
		tarkov_counter.load("config/mesh/game1_tarkov_counter.txt", "config/image/game1_tarkov_counter.png",oc);
		break;
	case 40:
		chess_chair.load("config/mesh/chess_chair.txt", "config/image/chess_chair.png",oc);
		break;
	case 41:
		chess_table.load("config/mesh/chess_table.txt", "config/image/chess_table.png",oc);
		break;
	case 42:
		chess_map.load("config/mesh/chess_map.txt", "config/image/chess_set_board.png",oc);
		break;
	case 43:
		chess_set_board.load("config/mesh/chess_set_board.txt", "config/image/chess_set_board.png",oc);
		break;
	case 44:
		chess_WB1.load("config/mesh/WB1.txt", "config/image/chess_set_white.png",oc);
		break;
	case 45:
		chess_WB2.load("config/mesh/WB2.txt", "config/image/chess_set_white.png",oc);
		break;
	case 46:
		chess_WR1.load("config/mesh/WR1.txt", "config/image/chess_set_white.png",oc);
		break;
	case 47:
		chess_WR2.load("config/mesh/WR2.txt", "config/image/chess_set_white.png",oc);
		break;
	case 48:
		chess_WK.load("config/mesh/WK.txt", "config/image/chess_set_white.png",oc);
		break;
	case 49:
		chess_WQ.load("config/mesh/WQ.txt", "config/image/chess_set_white.png",oc);
		break;
	case 50:
		chess_WN1.load("config/mesh/WN1.txt", "config/image/chess_set_white.png",oc);
		break;
	case 51:
		chess_WN2.load("config/mesh/WN2.txt", "config/image/chess_set_white.png",oc);
		break;
	case 52:
		chess_WP1.load("config/mesh/WP1.txt", "config/image/chess_set_white.png",oc);
		break;
	case 53:
		chess_WP2.load("config/mesh/WP2.txt", "config/image/chess_set_white.png",oc);
		break;
	case 54:
		chess_WP3.load("config/mesh/WP3.txt", "config/image/chess_set_white.png",oc);
		break;
	case 55:
		chess_WP4.load("config/mesh/WP4.txt", "config/image/chess_set_white.png",oc);
		break;
	case 56:
		chess_WP5.load("config/mesh/WP5.txt", "config/image/chess_set_white.png",oc);
		break;
	case 57:
		chess_WP6.load("config/mesh/WP6.txt", "config/image/chess_set_white.png",oc);
		break;
	case 58:
		chess_WP7.load("config/mesh/WP7.txt", "config/image/chess_set_white.png",oc);
		break;
	case 59:
		chess_WP8.load("config/mesh/WP8.txt", "config/image/chess_set_white.png",oc);
		break;
	case 60:
		chess_BB1.load("config/mesh/BB1.txt", "config/image/chess_set_black.png",oc);
		break;
	case 61:
		chess_BB2.load("config/mesh/BB2.txt", "config/image/chess_set_black.png",oc);
		break;
	case 62:
		chess_BK.load("config/mesh/BK.txt", "config/image/chess_set_black.png",oc);
		break;
	case 63:
		chess_BN1.load("config/mesh/BN1.txt", "config/image/chess_set_black.png",oc);
		break;
	case 64:
		chess_BN2.load("config/mesh/BN2.txt", "config/image/chess_set_black.png",oc);
		break;
	case 65:
		chess_BQ.load("config/mesh/BQ.txt", "config/image/chess_set_black.png",oc);
		break;
	case 66:
		chess_BR1.load("config/mesh/BR1.txt", "config/image/chess_set_black.png",oc);
		break;
	case 67:
		chess_BR2.load("config/mesh/BR2.txt", "config/image/chess_set_black.png",oc);
		break;
	case 68:
		chess_BP1.load("config/mesh/BP1.txt", "config/image/chess_set_black.png",oc);
		break;
	case 69:
		chess_BP2.load("config/mesh/BP2.txt", "config/image/chess_set_black.png",oc);
		break;
	case 70:
		chess_BP3.load("config/mesh/BP3.txt", "config/image/chess_set_black.png",oc);
		break;
	case 71:
		chess_BP4.load("config/mesh/BP4.txt", "config/image/chess_set_black.png",oc);
		break;
	case 72:
		chess_BP5.load("config/mesh/BP5.txt", "config/image/chess_set_black.png",oc);
		break;
	case 73:
		chess_BP6.load("config/mesh/BP6.txt", "config/image/chess_set_black.png",oc);
		break;
	case 74:
		chess_BP7.load("config/mesh/BP7.txt", "config/image/chess_set_black.png",oc);
		break;
	case 75:
		chess_BP8.load("config/mesh/BP8.txt", "config/image/chess_set_black.png",oc);
		break;
	case 76:
		aincrad_house.load("config/mesh/aincrad_house.txt", "config/image/aincrad_house.png",oc);
		break;
	case 77:
		createchessmatch.load("config/mesh/createchessmatch.txt",oc);
		break;
	case 78:
		waitingforplayers.load("config/mesh/waitingforplayers.txt",oc);
		break;
	case 79:
		jointhisgame.load("config/mesh/jointhisgame.txt",oc);
		break;
	case 80:
		game0_head.load("config/mesh/game0_head.txt","config/image/game0_head.png",oc);
		break;
	case 81:
	    game0_top.load("config/mesh/game0_top.txt","config/image/game0_top.png",oc);
		break;
	case 82:
		game0_pants.load("config/mesh/game0_pants.txt","config/image/game0_pants.png",oc);
		break;
	case 83:
		game0_counter.load("config/mesh/game0_counter.txt","config/image/game1_tarkov_counter.png",oc);
		break;
	case 84:
		howmanyplayers.load("config/mesh/howmanyplayers.txt",oc);
		break;
	case 85:
		selectyourcar.load("config/mesh/selectyourcar.txt",oc);
		break;
	case 86:
		createracematch.load("config/mesh/createracematch.txt",oc);
		break;
	case 87:
		createshootingmatch.load("config/mesh/createshootingmatch.txt",oc);
		break;
	case 88:
		createtankmatch.load("config/mesh/createtankmatch.txt",oc);
		break;
	case 89:
		text[0].load("config/mesh/a.txt",oc);
		break;
	case 90:
		text[1].load("config/mesh/b.txt",oc);
		break;
	case 91:
		text[2].load("config/mesh/c.txt",oc);
		break;
	case 92:
		text[3].load("config/mesh/d.txt",oc);
		break;
	case 93:
		text[4].load("config/mesh/e.txt",oc);
		break;
	case 94:
		text[5].load("config/mesh/f.txt",oc);
		break;
	case 95:
		text[6].load("config/mesh/g.txt",oc);
		break;
	case 96:
		text[7].load("config/mesh/h.txt",oc);
		break;
	case 97:
		text[8].load("config/mesh/i.txt",oc);
		break;
	case 98:
		text[9].load("config/mesh/j.txt",oc);
		break;
	case 99:
		text[10].load("config/mesh/k.txt",oc);
		break;
	case 100:
		text[11].load("config/mesh/l.txt",oc);
		break;
	case 101:
		text[12].load("config/mesh/m.txt",oc);
		break;
	case 102:
		text[13].load("config/mesh/n.txt",oc);
		break;
	case 103:
		text[14].load("config/mesh/o.txt",oc);
		break;
	case 104:
		text[15].load("config/mesh/p.txt",oc);
		break;
	case 105:
		text[16].load("config/mesh/q.txt",oc);
		break;
	case 106:
		text[17].load("config/mesh/r.txt",oc);
		break;
	case 107:
		text[18].load("config/mesh/s.txt",oc);
		break;
	case 108:
		text[19].load("config/mesh/t.txt",oc);
		break;
	case 109:
		text[20].load("config/mesh/u.txt",oc);
		break;
	case 110:
		text[21].load("config/mesh/v.txt",oc);
		break;
	case 111:
		text[22].load("config/mesh/w.txt",oc);
		break;
	case 112:
		text[23].load("config/mesh/x.txt",oc);
		break;
	case 113:
		text[24].load("config/mesh/y.txt",oc);
		break;
	case 114:
		text[25].load("config/mesh/z.txt",oc);
		break;
	case 115:
	    game2_chess_house.load("config/mesh/game2_chess_house.txt", "config/image/game2_chess_house.png", oc);
		break;
	case 116:
	    game2_chess_black.load("config/mesh/game2_chess_black.txt", "config/image/game2_chess_black.png", oc);
		break;
	case 117:
	    game2_chess_white.load("config/mesh/game2_chess_white.txt", "config/image/game2_chess_white.png", oc);
		break;
	case 118:
	    game2_fani_table.load("config/mesh/game2_fani_table.txt", "config/image/game2_fani_table.png", oc);
		break;
	case 119:
	    game2_sofa.load("config/mesh/game2_sofa.txt", "config/image/game2_sofa.png", oc);
		break;
	case 120:
	    game2_Floor.load("config/mesh/game2_Floor.txt", "config/image/game2_Floor.png", oc);
		break;
	case 121:
	    game1_basket.load("config/mesh/game1_basket.txt", "config/image/game1_basket.jpg", oc);
		break;
	case 122:
	    game1_cat.load("config/mesh/game1_cat.txt", "config/image/game1_cat.png", oc);
		break;
	case 123:
	    game1_deco.load("config/mesh/game1_deco.txt", "config/image/game1_deco.jpg", oc);
		break;
	case 124:
	    game1_floor.load("config/mesh/game1_floor.txt", "config/image/game1_floor.png", oc);
		break;
	case 125:
	    game1_kawara1.load("config/mesh/game1_kawara1.txt", "config/image/game1_kawara1.png", oc);
		break;
	case 126:
	    game1_kawara2.load("config/mesh/game1_kawara2.txt", "config/image/game1_kawara2.png", oc);
		break;
	case 127:
	    game1_kawara3.load("config/mesh/game1_kawara3.txt", "config/image/game1_kawara3.png", oc);
		break;
	case 128:
	    game1_kawara4.load("config/mesh/game1_kawara4.txt", "config/image/game1_kawara4.png", oc);
		break;
	case 129:
	    game1_light.load("config/mesh/game1_light.txt", "config/image/game1_light.jpg", oc);
		break;
	case 130:
	    game1_ninja.load("config/mesh/game1_ninja.txt", "config/image/game1_ninja.png", oc);
		break;
	case 131:
	    game1_post.load("config/mesh/game1_post.txt", "config/image/game1_post.png", oc);
		break;
	case 132:
	    game1_table.load("config/mesh/game1_table.txt", "config/image/game1_table.png", oc);
		break;
	case 133:
	    game1_wall.load("config/mesh/game1_wall.txt", "config/image/game1_wall.png", oc);
		break;
	case 134:
		result_chess_lose.load("config/mesh/result_chess_lose.txt",oc);
		break;
	case 135:
		result_chess_win.load("config/mesh/result_chess_win.txt",oc);
		break;
	case 136:
		result_get_item_cheap.load("config/mesh/result_get_item_cheap.txt",oc);
		break;
	case 137:
		result_get_item_normal.load("config/mesh/result_get_item_normal.txt",oc);
		break;
	case 138:
		result_get_item_expensive.load("config/mesh/result_get_item_expensive.txt",oc);
		break;
	case 139:
		result_race_1st.load("config/mesh/result_race_1st.txt",oc);
		break;
	case 140:
		result_race_2nd.load("config/mesh/result_race_2nd.txt",oc);
		break;
	case 141:
		result_race_3rd.load("config/mesh/result_race_3rd.txt",oc);
		break;
	case 142:
		result_race_4th.load("config/mesh/result_race_4th.txt",oc);
		break;
	case 143:
		result_tank_1st.load("config/mesh/result_tank_1st.txt",oc);
		break;
	case 144:
		result_tank_2nd.load("config/mesh/result_tank_2nd.txt",oc);
		break;
	case 145:
		result_shooting_kill.load("config/mesh/result_shooting_kill.txt",oc);
		break;
	case 146:
		result_shooting_suevived.load("config/mesh/result_shooting_survived.txt",oc);
		break;
	case 147:
		yourturn.load("config/mesh/yourturn.txt",oc);
		break;
	case 148:
		enemyturn.load("config/mesh/enemyturn.txt",oc);
		break;
	case 149:
		game3_canon.load("config/mesh/game3_canon.txt","config/image/game3_canon.png",oc);
		break;
	case 150:
		game3_chair.load("config/mesh/game3_chair.txt","config/image/game3_chair.jpg",oc);
		break;
	case 151:
		game3_chest.load("config/mesh/game3_chest.txt","config/image/game3_chest.jpg",oc);
		break;
	case 152:
		game3_frag.load("config/mesh/game3_frag.txt",oc);
		break;
	case 153:
		game3_gate.load("config/mesh/game3_gate.txt","config/image/game3_gate.jpg",oc);
		break;
	case 154:
		game3_ground.load("config/mesh/game3_ground.txt","config/image/game3_ground.jpg",oc);
		break;
	case 155:
		game3_human_body.load("config/mesh/game3_human_body.txt","config/image/game3_human_body.png",oc);
		break;
	case 156:
		game3_human_cloth.load("config/mesh/game3_human_cloth.txt","config/image/game3_human_cloth.png",oc);
		break;
	case 157:
		game3_roof.load("config/mesh/game3_roof.txt","config/image/game3_roof.png",oc);
		break;
	case 158:
		game3_wall.load("config/mesh/game3_wall.txt","config/image/game3_wall.png",oc);
		break;
	case 159:
		HP_bar.load("config/mesh/HP_bar.txt",oc);
		break;
	case 160:
		HP_frame.load("config/mesh/HP_frame.txt",oc);
		break;
	case 161:
		game4_asphaltfuly.load("config/mesh/game4_asphaltfuly.txt","config/image/game4_asphaltfuly.png",oc);
		break;
	case 162:
		game4_base_cars.load("config/mesh/game4_base_cars.txt","config/image/game4_base_cars.png",oc);
		break;
	case 163:
		game4_car1.load("config/mesh/game4_car1.txt","config/image/game4_car1.png",oc);
		break;
	case 164:
		game4_car2.load("config/mesh/game4_car2.txt","config/image/game4_car2.png",oc);
		break;
	case 165:
		game4_car3.load("config/mesh/game4_car3.txt","config/image/game4_car3.png",oc);
		break;
	case 166:
		game4_car4.load("config/mesh/game4_car4.txt","config/image/game4_car4.png",oc);
		break;
	case 167:
		game4_floor.load("config/mesh/game4_floor.txt","config/image/game4_floor.jpg",oc);
		break;
	case 168:
		game4_garden_acce.load("config/mesh/game4_garden_acce.txt","config/image/game4_garden_acce.jpg",oc);
		break;
	case 169:
		game4_human.load("config/mesh/game4_human.txt","config/image/game4_human.png",oc);
		break;
	case 170:
		game4_lamp_hock.load("config/mesh/game4_lamp_hock.txt","config/image/game4_lamp_hock.jpg",oc);
		break;
	case 171:
		game4_light.load("config/mesh/game4_light.txt","config/image/game4_light.jpg",oc);
		break;
	case 172:
		game4_roof.load("config/mesh/game4_roof.txt","config/image/game4_roof.png",oc);
		break;
	case 173:
		game4_stair.load("config/mesh/game4_stair.txt","config/image/game4_stair.jpg",oc);
		break;
	case 174:
		game4_table1.load("config/mesh/game4_table1.txt","config/image/game4_table1.png",oc);
		break;
	case 175:
		game4_table2.load("config/mesh/game4_table2.txt","config/image/game4_table2.jpg",oc);
		break;
	case 176:
		game4_tree_branch.load("config/mesh/game4_tree_branch.txt",oc);
		break;
	case 177:
		game4_tree_leaves.load("config/mesh/game4_tree_leaves.txt",oc);
		break;
	case 178:
		game4_wall.load("config/mesh/game4_wall.txt","config/image/game4_wall.jpg",oc);
		break;
	case 179:
		game4_wood2.load("config/mesh/game4_wood2.txt","config/image/game4_wood2.jpg",oc);
		break;
	case 180:
		game4_wood_chair.load("config/mesh/game4_wood_chair.txt","config/image/game4_wood_chair.jpg",oc);
		break;
	case 181:
		game4_wood_panel.load("config/mesh/game4_wood_panel.txt","config/image/game4_wood_panel.jpg",oc);
		break;
	case 182:
		game4_wood_poll.load("config/mesh/game4_wood_poll.txt","config/image/game4_wood_poll.jpg",oc);
		break;
	case 183:
		game4_wood_table.load("config/mesh/game4_wood_table.txt","config/image/game4_wood_table.png",oc);
		break;
	case 184:
		game4_sofa.load("config/mesh/game4_sofa.txt","config/image/game4_sofa.jpg",oc);
		break;
	case 185:
		ui_key.load("config/mesh/ui_key.txt",oc);
		break;
	case 186:
		ui_ammo.load("config/mesh/ui_ammo.txt",oc);
		break;
	case 187:
		ui_car1.load("config/mesh/ui_car1.txt","config/image/ui_car1.png",oc);
		break;
	case 188:
		ui_car2.load("config/mesh/ui_car2.txt","config/image/ui_car2.png",oc);
		break;
	case 189:
		ui_car3.load("config/mesh/ui_car3.txt","config/image/ui_car3.png",oc);
		break;
	case 190:
		result_tank_3rd.load("config/mesh/result_tank_3rd.txt",oc);
		break;
	case 191:
		result_tank_4th.load("config/mesh/result_tank_4th.txt",oc);
		break;
	case 192:
		ui_car4.load("config/mesh/ui_car4.txt","config/image/ui_car4.png",oc);
		break;
	default:
		mainloopcount = 7;
		currentMeshNum = 0;
		Mix_PlayMusic(BGM_title, -1);

		break;


	}
}

void loadRaceGameMesh(int frame)
{
	int oc = 41;
	switch (frame)
	{
	case 0:
		sports_mainBody.load("config/mesh/sports_mainBody.txt", "config/image/sportscar.png",oc);
		break;
	case 1:
		sports_plane.load("config/mesh/sports_plane.txt", "config/image/sportscar.png",oc);
		break;
	case 2:
		sports_wheel_right.load("config/mesh/sports_wheel_right.txt", "config/image/sports_wheel.png",oc);
		break;
	case 3:
		sports_wheel_left.load("config/mesh/sports_wheel_left.txt", "config/image/sports_wheel.png",oc);
		break;
	case 4:
		sports_road.load("config/mesh/sports_road.txt", "config/image/sports_road.png",oc);
		break;
	case 5:
		sports_back.load("config/mesh/sports_back.txt",oc);
		break;
	case 6:
		sports_speedtext.load("config/mesh/sports_speedtext.txt",oc);
		break;
	case 7:
		sports_speedtext_red.load("config/mesh/sports_speedtext_red.txt",oc);
		break;
	case 8:
		sports_stick.load("config/mesh/sports_stick.txt",oc);
		break;
	case 9:
		sports_grass.load("config/mesh/sports_grass.txt", "config/image/sports_grass.png",oc);
		break;
	case 10:
		sports_dirt.load("config/mesh/sports_dirt.txt", "config/image/sports_dirt.png",oc);
		break;
	case 11:
		sports_tire.load("config/mesh/sports_tire.txt", "config/image/sports_tire.png",oc);
		break;
	case 12:
		sports_wall.load("config/mesh/sports_wall.txt", "config/image/sports_wall.png",oc);
		break;
	case 13:
		sports1light.load("config/mesh/sports1light.txt", "config/image/sports1light.png",oc);
		break;
	case 14:
		map_wall.load("config/mesh/map_wall.txt", "config/image/sports_wall.png",oc);
		break;
	case 15:
		map_tire.load("config/mesh/map_tire.txt", "config/image/sports_tire.png",oc);
		break;
	case 16:
		map_road.load("config/mesh/map_road.txt", "config/image/sports_road.png",oc);
		break;
	case 17:
		map_grass.load("config/mesh/map_grass.txt", "config/image/sports_grass.png",oc);
		break;
	case 18:
		map_player.load("config/mesh/map_player.txt",oc);
		break;
	case 19:
		sports_lap.load("config/mesh/sports_lap.txt",oc);
		break;
	case 20:
		skyOutSide.load("config/mesh/skyOutSide.txt", "config/image/puresky.jpg", oc);
		break;
	case 21:
		sports2_mainbody.load("config/mesh/sports2_mainbody.txt", "config/image/sports2_mainbody.png",oc);
		break;
	case 22:
		sports2_left.load("config/mesh/sports2_left.txt", "config/image/sports2_left.png",oc);
		break;
	case 23:
		sports2_right.load("config/mesh/sports2_right.txt", "config/image/sports2_right.png",oc);
		break;
	case 24:
		sports2_plane.load("config/mesh/sports2_plane.txt", "config/image/sports2_plane.png",oc);
		break;
	case 25:
		sports2light.load("config/mesh/sports2light.txt", "config/image/sports2light.png",oc);
		break;
	case 26:
		sports_1st.load("config/mesh/sports_1st.txt",oc);
		break;
	case 27:
		sports_2nd.load("config/mesh/sports_2nd.txt",oc);
		break;
	case 28:
		sports_3rd.load("config/mesh/sports_3rd.txt",oc);
		break;
	case 29:
		sports_4th.load("config/mesh/sports_4th.txt",oc);
		break;
	case 30:
		text_go.load("config/mesh/go.txt",oc);
		break;
	case 31:
		sports3_mainbody.load("config/mesh/sports3_mainbody.txt","config/image/sports3_mainbody.png",oc);
		break;
	case 32:
		sports3_plane.load("config/mesh/sports3_plane.txt","config/image/sports3_plane.png",oc);
		break;
	case 33:
		sports3_Left.load("config/mesh/sports3_Left.txt","config/image/sports3_Left.png",oc);
		break;
	case 34:
		sports3_Right.load("config/mesh/sports3_Right.txt","config/image/sports3_Right.png",oc);
		break;
	case 35:
		sports3light.load("config/mesh/sports3light.txt","config/image/sports3light.png",oc);
		break;
	case 36:
		sports4_mainbody.load("config/mesh/sports4_mainbody.txt","config/image/sports4_mainbody.png",oc);
		break;
	case 37:
		sports4_plane.load("config/mesh/sports4_plane.txt","config/image/sports4_plane.png",oc);
		break;
	case 38:
		sports4_Left.load("config/mesh/sports4_Left.txt","config/image/sports4_Left.png",oc);
		break;
	case 39:
		sports4_Right.load("config/mesh/sports4_Right.txt","config/image/sports4_Right.png",oc);
		break;
	case 40:
		sports4light.load("config/mesh/sports4light.txt","config/image/sports4light.png",oc);
		break;
    case 41:
        roadAnimMesh(0, 28, "config/anim/anim_1st_1", "config/image/anim_1st.png", anim_1st_1);
        break;
    case 42:
        roadAnimMesh(0, 28, "config/anim/anim_1st_s", "config/image/anim_1st.png", anim_1st_s);
        break;
    case 43:
        roadAnimMesh(0, 28, "config/anim/anim_1st_t", "config/image/anim_1st.png", anim_1st_t);
        break;
    case 44:
        roadAnimMesh(0, 28, "config/anim/anim_2nd_2", "config/image/anim_2nd.png", anim_2nd_2);
        break;
    case 45:
        roadAnimMesh(0, 28, "config/anim/anim_2nd_n", "config/image/anim_2nd.png", anim_2nd_n);
        break;
    case 46:
        roadAnimMesh(0, 28, "config/anim/anim_2nd_d", "config/image/anim_2nd.png", anim_2nd_d);
        break;
    case 47:
        roadAnimMesh(0, 28, "config/anim/anim_3rd_3", "config/image/anim_3rd.png", anim_3rd_3);
        break;
    case 48:
        roadAnimMesh(0, 28, "config/anim/anim_3rd_r", "config/image/anim_3rd.png", anim_3rd_r);
        break;
    case 49:
        roadAnimMesh(0, 28, "config/anim/anim_3rd_d", "config/image/anim_3rd.png", anim_3rd_d);
        break;
    case 50:
        roadAnimMesh(0, 28, "config/anim/anim_4th_4", "config/image/anim_4th.png", anim_4th_4);
        break;
    case 51:
        roadAnimMesh(0, 28, "config/anim/anim_4th_t", "config/image/anim_4th.png", anim_4th_t);
        break;
    case 52:
        roadAnimMesh(0, 28, "config/anim/anim_4th_h", "config/image/anim_4th.png", anim_4th_h);
        break;
	default:
		game[1].stts = 6;
		if(checkGameStts(1,6) != game[1].p_NUM - 1)
		{
			glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			gluLookAt(0, 0, 0, 1, 0, 0, 0, 0, 1);

			glPushMatrix();
			glTranslatef(0.11, 0, 0);
			waitingforplayers.make(1.0f,1.0f,1.0f);
			glPopMatrix();
		}
		else
		{
			mainloopcount = 7;
			currentMeshNum = 0;
			Mix_PlayMusic(BGM_race_ingame, -1);

		}
		break;

	}
}

void loadTankGameMesh(int frame)
{
	int oc = 9;
	switch (frame)
	{
	case 0:
		tankUpper.load("config/mesh/tankUpper.txt", "config/image/tank.jpg",oc);
		break;
	case 1:
		tankBarrel.load("config/mesh/tankBarrel.txt", "config/image/tank.jpg",oc);
		break;
	case 2:
		canon.load("config/mesh/canon.txt", "config/image/canon.png",oc);
		break;
	case 3:
		explosion.load("config/mesh/explosion.txt", "config/image/explosion.jpg",oc);
		break;
	case 4:
		tankground.load("config/mesh/tankground.txt", "config/image/tank_grass.png",oc);
		break;
	case 5:
		tankmap.load("config/mesh/tankmap.txt", "config/image/tankmap.png",oc);
		break;
	case 6:
		dropPosition.load("config/mesh/dropPosition.txt",oc);
		break;
	case 7:
		skyOutSide.load("config/mesh/skyOutSide.txt", "config/image/puresky.jpg", oc);
		break;
	case 8:
		tankLower.load("config/mesh/tankLower.txt", "config/image/tank.jpg",oc);
		break;
    case 9:
        roadAnimMesh(0, 28, "config/anim/anim_1st_1", "config/image/anim_1st.png", anim_1st_1);
        break;
    case 10:
        roadAnimMesh(0, 28, "config/anim/anim_1st_s", "config/image/anim_1st.png", anim_1st_s);
        break;
    case 11:
        roadAnimMesh(0, 28, "config/anim/anim_1st_t", "config/image/anim_1st.png", anim_1st_t);
        break;
    case 12:
        roadAnimMesh(0, 28, "config/anim/anim_2nd_2", "config/image/anim_2nd.png", anim_2nd_2);
        break;
    case 13:
        roadAnimMesh(0, 28, "config/anim/anim_2nd_n", "config/image/anim_2nd.png", anim_2nd_n);
        break;
    case 14:
        roadAnimMesh(0, 28, "config/anim/anim_2nd_d", "config/image/anim_2nd.png", anim_2nd_d);
        break;
    case 15:
        roadAnimMesh(0, 28, "config/anim/anim_3rd_3", "config/image/anim_3rd.png", anim_3rd_3);
        break;
    case 16:
        roadAnimMesh(0, 28, "config/anim/anim_3rd_r", "config/image/anim_3rd.png", anim_3rd_r);
        break;
    case 17:
        roadAnimMesh(0, 28, "config/anim/anim_3rd_d", "config/image/anim_3rd.png", anim_3rd_d);
        break;
    case 18:
        roadAnimMesh(0, 28, "config/anim/anim_4th_4", "config/image/anim_4th.png", anim_4th_4);
        break;
    case 19:
        roadAnimMesh(0, 28, "config/anim/anim_4th_t", "config/image/anim_4th.png", anim_4th_t);
        break;
    case 20:
        roadAnimMesh(0, 28, "config/anim/anim_4th_h", "config/image/anim_4th.png", anim_4th_h);
        break;
	default:
		game[3].stts = 4;
		if(checkGameStts(3,4) != game[3].p_NUM - 1)
		{
			glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			gluLookAt(0, 0, 0, 1, 0, 0, 0, 0, 1);

			glPushMatrix();
			glTranslatef(0.11, 0, 0);
			waitingforplayers.make(1.0f,1.0f,1.0f);
			glPopMatrix();
		}
		else
		{
			mainloopcount = 7;
			currentMeshNum = 0;
			Mix_PlayMusic(BGM_tank_ingame, -1);

		}
		break;
	}
}

void loadShootingGameMesh(int frame)
{
	int oc = 26;
	switch (frame)
	{
	case 0:
		Reciever.load("config/mesh/Reciever.txt", "config/image/Reciever.png",oc);
		break;
	case 1:
		Foregrip.load("config/mesh/Foregrip.txt", "config/image/Foregrip.png",oc);
		break;
	case 2:
		Handguard.load("config/mesh/Handguard.txt", "config/image/Handguard.png",oc);
		break;
	case 3:
		Scope.load("config/mesh/Scope.txt", "config/image/Scope.png",oc);
		break;
	case 4:
		Silencer.load("config/mesh/Silencer.txt", "config/image/Silencer.png",oc);
		break;
	case 5:
		Stock.load("config/mesh/Stock.txt", "config/image/Stock.png",oc);
		break;
	case 6:
		Base.load("config/mesh/Base.txt", "config/image/Base.png",oc);
		break;
	case 7:
		Mount.load("config/mesh/Mount.txt", "config/image/Mount.png",oc);
		break;
	case 8:
		Charge.load("config/mesh/Charge.txt", "config/image/Charge.png",oc);
		break;
	case 9:
		Hand.load("config/mesh/Hand.txt", "config/image/Hand.png",oc);
		break;
	case 10:
		Ret.load("config/mesh/Ret.txt", "config/image/Ret.png",oc);
		break;
	case 11:
		base_ground.load("config/mesh/base_ground.txt", "config/image/base_ground.png",oc);
		break;
	case 12:
		inner_ground.load("config/mesh/inner_ground.txt", "config/image/inner_ground.png",oc);
		break;
	case 13:
		labslogo.load("config/mesh/labslogo.txt", "config/image/labslogo.png",oc);
		break;
	case 14:
		stair_flat.load("config/mesh/stair_flat.txt", "config/image/stair_flat.png",oc);
		break;
	case 15:
		stair_long.load("config/mesh/stair_long.txt", "config/image/stair_long.png",oc);
		break;
	case 16:
		stair_naname.load("config/mesh/stair_naname.txt", "config/image/stair_naname.png",oc);
		break;
	case 17:
		lightPM.load("config/mesh/lightPM.txt",oc);
		break;
	case 18:
		tarkov_fence.load("config/mesh/tarkov_fence.txt", "config/image/tarkov_fence.png",oc);
		break;
	case 19:
		rooms.load("config/mesh/rooms.txt", "config/image/rooms.png",oc);
		break;
	case 20:
		fireFlash.load("config/mesh/fireFlash.txt", "config/image/rooms.png",oc);
		break;
	case 21:
		item_case_1.load("config/mesh/item_case_1.txt", "config/image/item_case_1.png",oc);
		break;
	case 22:
		item_case_2.load("config/mesh/item_case_2.txt", "config/image/item_case_2.png",oc);
		break;
	case 23:
		tarkov_item_cat.load("config/mesh/tarkov_item_cat.txt", "config/image/tarkov_item_cat.png",oc);
		break;
	case 24:
		tarkov_item_egg.load("config/mesh/tarkov_item_egg.txt", "config/image/tarkov_item_egg.png",oc);
		break;
	case 25:
		tarkov_item_ledx.load("config/mesh/tarkov_item_ledx.txt", "config/image/tarkov_item_ledx.png",oc);
		break;
	case 26:
		escape1.load("config/mesh/escape1.txt",oc);
		break;
	case 27:
		escape2.load("config/mesh/escape2.txt",oc);
		break;
	case 28:
		escape3.load("config/mesh/escape3.txt",oc);
		break;
    case 29:
		getitem.load("config/mesh/getitem.txt",oc);
        break;
    case 30:
        roadAnimMesh(0, 28, "config/anim/anim_survived_u", "config/image/anim_survived.png", anim_survived_u);
        break;
    case 31:
        roadAnimMesh(0, 28, "config/anim/anim_survived_r", "config/image/anim_survived.png", anim_survived_r);
        break;
    case 32:
        roadAnimMesh(0, 28, "config/anim/anim_survived_v1", "config/image/anim_survived.png", anim_survived_v1);
        break;
    case 33:
        roadAnimMesh(0, 28, "config/anim/anim_survived_i", "config/image/anim_survived.png", anim_survived_i);
        break;
    case 34:
        roadAnimMesh(0, 28, "config/anim/anim_survived_v2", "config/image/anim_survived.png", anim_survived_v2);
        break;
    case 35:
        roadAnimMesh(0, 28, "config/anim/anim_survived_e", "config/image/anim_survived.png", anim_survived_e);
        break;
    case 36:
        roadAnimMesh(0, 28, "config/anim/anim_survived_d", "config/image/anim_survived.png", anim_survived_d);
        break;
	case 37:
        roadAnimMesh(0, 28, "config/anim/anim_survived_s", "config/image/anim_survived.png", anim_survived_s);
		break;
    case 38:
        roadAnimMesh(0, 28, "config/anim/L", "config/image/lose.png", text_l);
        break;
    case 39:
        roadAnimMesh(0, 28, "config/anim/O", "config/image/lose.png", text_o);
        break;
    case 40:
        roadAnimMesh(0, 28, "config/anim/S", "config/image/lose.png", text_s);
        break;
    case 41:
        roadAnimMesh(0, 28, "config/anim/E", "config/image/lose.png", text_e);
        break;
	default:
		game[2].stts = 4;
		if(checkGameStts(2,4) != game[2].p_NUM - 1)
		{
			glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			gluLookAt(0, 0, 0, 1, 0, 0, 0, 0, 1);

			glPushMatrix();
			glTranslatef(0.11, 0, 0);
			waitingforplayers.make(1.0f,1.0f,1.0f);
			glPopMatrix();
		}
		else
		{
			mainloopcount = 7;
			currentMeshNum = 0;
			Mix_PlayMusic(BGM_shooting_ingame, -1);

		}
		break;
	}
}

void loadChessGameMesh(int frame)
{

	int oc = 54;
	switch (frame)
	{
	case 0:
		chess_P.load("config/mesh/chess_P.txt",oc);
		break;
	case 1:
		chess_R.load("config/mesh/chess_R.txt",oc);
		break;
	case 2:
		chess_B.load("config/mesh/chess_B.txt",oc);
		break;
	case 3:
		chess_N.load("config/mesh/chess_N.txt",oc);
		break;
	case 4:
		chess_Q.load("config/mesh/chess_Q.txt",oc);
		break;
	case 5:
		chess_K.load("config/mesh/chess_K.txt",oc);
		break;
	case 6:
		chess_circle.load("config/mesh/chess_circle.txt",oc);
		break;
	case 7:
		chess_masu.load("config/mesh/masu.txt",oc);
		break;
	case 8:
		chess_chair.load("config/mesh/chess_chair.txt", "config/image/chess_chair.png", oc);
		break;
	case 9:
		chess_table.load("config/mesh/chess_table.txt", "config/image/chess_table.png", oc);
		break;
	case 10:
		chess_map.load("config/mesh/chess_map.txt", "config/image/chess_set_board.png", oc);
		break;
	case 11:
		chess_set_board.load("config/mesh/chess_set_board.txt", "config/image/chess_set_board.png", oc);
		break;
	case 12:
		chess_WB1.load("config/mesh/WB1.txt", "config/image/chess_set_white.png", oc);
		break;
	case 13:
		chess_WB2.load("config/mesh/WB2.txt", "config/image/chess_set_white.png", oc);
		break;
	case 14:
		chess_WR1.load("config/mesh/WR1.txt", "config/image/chess_set_white.png", oc);
		break;
	case 15:
		chess_WR2.load("config/mesh/WR2.txt", "config/image/chess_set_white.png", oc);
		break;
	case 16:
		chess_WK.load("config/mesh/WK.txt", "config/image/chess_set_white.png", oc);
		break;
	case 17:
		chess_WQ.load("config/mesh/WQ.txt", "config/image/chess_set_white.png", oc);
		break;
	case 18:
		chess_WN1.load("config/mesh/WN1.txt", "config/image/chess_set_white.png", oc);
		break;
	case 19:
		chess_WN2.load("config/mesh/WN2.txt", "config/image/chess_set_white.png", oc);
		break;
	case 20:
		chess_WP1.load("config/mesh/WP1.txt", "config/image/chess_set_white.png", oc);
		break;
	case 21:
		chess_WP2.load("config/mesh/WP2.txt", "config/image/chess_set_white.png", oc);
		break;
	case 22:
		chess_WP3.load("config/mesh/WP3.txt", "config/image/chess_set_white.png", oc);
		break;
	case 23:
		chess_WP4.load("config/mesh/WP4.txt", "config/image/chess_set_white.png", oc);
		break;
	case 24:
		chess_WP5.load("config/mesh/WP5.txt", "config/image/chess_set_white.png", oc);
		break;
	case 25:
		chess_WP6.load("config/mesh/WP6.txt", "config/image/chess_set_white.png", oc);
		break;
	case 26:
		chess_WP7.load("config/mesh/WP7.txt", "config/image/chess_set_white.png", oc);
		break;
	case 27:
		chess_WP8.load("config/mesh/WP8.txt", "config/image/chess_set_white.png", oc);
		break;
	case 28:
		chess_BB1.load("config/mesh/BB1.txt", "config/image/chess_set_black.png", oc);
		break;
	case 29:
		chess_BB2.load("config/mesh/BB2.txt", "config/image/chess_set_black.png", oc);
		break;
	case 30:
		chess_BK.load("config/mesh/BK.txt", "config/image/chess_set_black.png", oc);
		break;
	case 31:
		chess_BN1.load("config/mesh/BN1.txt", "config/image/chess_set_black.png", oc);
		break;
	case 32:
		chess_BN2.load("config/mesh/BN2.txt", "config/image/chess_set_black.png", oc);
		break;
	case 33:
		chess_BQ.load("config/mesh/BQ.txt", "config/image/chess_set_black.png", oc);
		break;
	case 34:
		chess_BR1.load("config/mesh/BR1.txt", "config/image/chess_set_black.png", oc);
		break;
	case 35:
		chess_BR2.load("config/mesh/BR2.txt", "config/image/chess_set_black.png", oc);
		break;
	case 36:
		chess_BP1.load("config/mesh/BP1.txt", "config/image/chess_set_black.png", oc);
		break;
	case 37:
		chess_BP2.load("config/mesh/BP2.txt", "config/image/chess_set_black.png", oc);
		break;
	case 38:
		chess_BP3.load("config/mesh/BP3.txt", "config/image/chess_set_black.png", oc);
		break;
	case 39:
		chess_BP4.load("config/mesh/BP4.txt", "config/image/chess_set_black.png", oc);
		break;
	case 40:
		chess_BP5.load("config/mesh/BP5.txt", "config/image/chess_set_black.png", oc);
		break;
	case 41:
		chess_BP6.load("config/mesh/BP6.txt", "config/image/chess_set_black.png", oc);
		break;
	case 42:
		chess_BP7.load("config/mesh/BP7.txt", "config/image/chess_set_black.png", oc);
		break;
	case 43:
		chess_BP8.load("config/mesh/BP8.txt", "config/image/chess_set_black.png", oc);
		break;
	case 44:
	    game2_chess_house_playing.load("config/mesh/game2_chess_house_playing.txt", "config/image/game2_chess_house.png", oc);
		break;
	case 45:
	    game2_chess_black_playing.load("config/mesh/game2_chess_black_playing.txt", "config/image/game2_chess_black.png", oc);
		break;
	case 46:
	    game2_Floor_playing.load("config/mesh/game2_Floor_playing.txt", "config/image/game2_Floor.png", oc);
		break;
	case 47:
		skyInSide.load("config/mesh/skyInSide.txt", "config/image/pureskyinside.jpg",oc);
		break;
	case 48:
		grass.load("config/mesh/grass.txt", "config/image/grass.jpg",oc);
		break;
	case 49:
		house_brick.load("config/mesh/house_brick.txt", "config/image/house_brick.jpg",oc);
		break;
	case 50:
		house_roof.load("config/mesh/house_roof.txt", "config/image/house_roof.jpg",oc);
		break;
	case 51:
		house_window.load("config/mesh/house_window.txt", "config/image/house_window.jpg",oc);
		break;
	case 52:
		house_white.load("config/mesh/house_white.txt",oc);
		break;
	case 53:
		house_door.load("config/mesh/house_door.txt", "config/image/house_door.jpg",oc);
		break;
    case 54:
        roadAnimMesh(0, 28, "config/anim/W", "config/image/win.png", text_w);
        break;
    case 55:
        roadAnimMesh(0, 28, "config/anim/I", "config/image/win.png", text_i);
        break;
    case 56:
        roadAnimMesh(0, 28, "config/anim/N", "config/image/win.png", text_n);
        break;
    case 57:
        roadAnimMesh(0, 28, "config/anim/L", "config/image/lose.png", text_l);
        break;
    case 58:
        roadAnimMesh(0, 28, "config/anim/O", "config/image/lose.png", text_o);
        break;
    case 59:
        roadAnimMesh(0, 28, "config/anim/S", "config/image/lose.png", text_s);
        break;
    case 60:
        roadAnimMesh(0, 28, "config/anim/E", "config/image/lose.png", text_e);
        break;
	default:
		mainloopcount = 7;
		currentMeshNum = 0;
		Mix_PlayMusic(BGM_chess, -1);

		break;
	}
}

void initChessPos()
{
	ci.bp1.pos[0] = 6;
	ci.bp1.pos[1] = 0;

	ci.bp2.pos[0] = 6;
	ci.bp2.pos[1] = 1;

	ci.bp3.pos[0] = 6;
	ci.bp3.pos[1] = 2;

	ci.bp4.pos[0] = 6;
	ci.bp4.pos[1] = 3;

	ci.bp5.pos[0] = 6;
	ci.bp5.pos[1] = 4;

	ci.bp6.pos[0] = 6;
	ci.bp6.pos[1] = 5;

	ci.bp7.pos[0] = 6;
	ci.bp7.pos[1] = 6;

	ci.bp8.pos[0] = 6;
	ci.bp8.pos[1] = 7;

	ci.bb1.pos[0] = 7;
	ci.bb1.pos[1] = 2;

	ci.bb2.pos[0] = 7;
	ci.bb2.pos[1] = 5;

	ci.br1.pos[0] = 7;
	ci.br1.pos[1] = 0;

	ci.br2.pos[0] = 7;
	ci.br2.pos[1] = 7;

	ci.bn1.pos[0] = 7;
	ci.bn1.pos[1] = 1;

	ci.bn2.pos[0] = 7;
	ci.bn2.pos[1] = 6;

	ci.bq.pos[0] = 7;
	ci.bq.pos[1] = 3;

	ci.bk.pos[0] = 7;
	ci.bk.pos[1] = 4;

	ci.wp1.pos[0] = 1;
	ci.wp1.pos[1] = 0;

	ci.wp2.pos[0] = 1;
	ci.wp2.pos[1] = 1;

	ci.wp3.pos[0] = 1;
	ci.wp3.pos[1] = 2;

	ci.wp4.pos[0] = 1;
	ci.wp4.pos[1] = 3;

	ci.wp5.pos[0] = 1;
	ci.wp5.pos[1] = 4;

	ci.wp6.pos[0] = 1;
	ci.wp6.pos[1] = 5;

	ci.wp7.pos[0] = 1;
	ci.wp7.pos[1] = 6;

	ci.wp8.pos[0] = 1;
	ci.wp8.pos[1] = 7;

	ci.wb1.pos[0] = 0;
	ci.wb1.pos[1] = 2;

	ci.wb2.pos[0] = 0;
	ci.wb2.pos[1] = 5;

	ci.wr1.pos[0] = 0;
	ci.wr1.pos[1] = 0;

	ci.wr2.pos[0] = 0;
	ci.wr2.pos[1] = 7;

	ci.wn1.pos[0] = 0;
	ci.wn1.pos[1] = 1;

	ci.wn2.pos[0] = 0;
	ci.wn2.pos[1] = 6;

	ci.wq.pos[0] = 0;
	ci.wq.pos[1] = 3;

	ci.wk.pos[0] = 0;
	ci.wk.pos[1] = 4;
}

void InitialProc()
{
	scene = scene_1;
	SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetEventFilter(ignore_key_repeat_event_filter, NULL);
	glEnable(GL_COLOR_MATERIAL);//�F��L����
	glEnable(GL_COLOR_MATERIAL_FACE);

	glViewport(0, 0, 1924, 1061);
	glMatrixMode(GL_PROJECTION);			// �ˉe�s��𑀍삷��
	glLoadIdentity();						// �s���������
	gluPerspective(80.0, 1924.0 / 1061.0, 0.1, 5000);
	glMatrixMode(GL_MODELVIEW);

	glEnableClientState(GL_VERTEX_ARRAY);//vertex_array�g�������Ȃ�����
	glEnableClientState(GL_NORMAL_ARRAY);

	glClearColor(0.1, 0.2, 0.3, 1.0);
	//�Ɩ��̐ݒ�
	float diffuse[] = { 0.5,0.5,0.5,1 };
	float specular[] = { 0.3,0.3,0.3,1 };
	float ambient[] = { 0.2,0.2,0.2,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightposMat);  // �����̈ʒu
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
	glMatrixMode(GL_MODELVIEW);

	myPosition.x = 0.0;
	myPosition.y = -13.0;
	myPosition.z = 2.5;
	myPosition.damage = 0;
	myPosition.dash = 0;

	tankPos.x = 0;
	tankPos.y = 0;
	tankPos.z = 0;
	tankPos.vecX = 0;
	tankPos.vecY = -1.0;
	sportsPos.x = 0;
	sportsPos.y = 0;
	sportsPos.z = 0.2;
	sportsPos.vecX = 0;
	sportsPos.vecY = -1.0;

	game1_chess_position = {-6.7727f,-62.126f};
	game2_tank_position = {48.783f,-25.644f};
	game3_race_position = {54.9654f,39.4242f};
	game4_shooting_position = {-3.008f,58.876f};

	explosionPos.c = false;

	CIN.thisTurn = 0;
	std::memcpy(CIN.cm,chessMap,sizeof(chessMap));
	for(int i =0;i<30;i++)
	{
		my_result[i] = 0;
	}

	initChessPos();
	CIN.ci = ci;
	lookingPosition.x = 4.5;
	lookingPosition.y = 4.5;
	lookingPosition.z = -0.7;
	jumpSpeed = g * (gTime / 2.0);
	jumpingHeight = 0.0;
	key1 = (rand() % 6) + 1;
	key2 = (rand() % 6) + 7;

	radius_aincrad = aincradRad;
	height_aincrad = aincradZ;

	std::vector<Point> EWpoints = { {162.900146484375,4.896299362182617}, {162.87840270996094,4.815141677856445}, {162.87840270996094,-4.847443580627441}, {162.900146484375,-4.92860221862793}, {162.9595489501953,-4.988014221191406}, {163.04071044921875,-5.009759902954102}, {223.37139892578125,-5.009757995605469}, {223.4525604248047,-4.988012790679932}, {223.511962890625,-4.928600311279297}, {223.53372192382812,-4.847442626953125}, {223.53372192382812,4.815134048461914}, {223.51197814941406,4.8962907791137695}, {223.45257568359375,4.955702781677246}, {223.3714141845703,4.977449417114258}, {163.04071044921875,4.977456092834473}, {162.9595489501953,4.955711364746094}, {162.900146484375,4.896299362182617} };
	entranceWall.push_back({ 1,EWpoints });

	std::vector<Point> pedes1 = { {143.77685546875,4.699215412139893}, {143.83139038085938,4.751978397369385}, {143.84262084960938,2.7405941486358643}, {143.77685546875,2.8042151927948}, {143.77685546875,2.8042151927948}, {143.77685546875,4.699215412139893}, {145.80691528320312,2.7405941486358643}, {143.84262084960938,2.7405941486358643}, {145.85585021972656,2.7879409790039062}, {145.80691528320312,2.7405941486358643}, {143.83139038085938,4.751978397369385}, {145.7937469482422,4.751978874206543}, {145.7937469482422,4.751978874206543}, {145.85585021972656,4.691887378692627}, {145.85585021972656,4.691887378692627}, {145.85585021972656,2.7879409790039062} };
	std::vector<Point> pedes2 = { {145.83242797851562,-5.062530517578125}, {145.7940216064453,-5.099686622619629}, {145.7940216064453,-5.099686622619629}, {143.84556579589844,-5.099686622619629}, {143.84556579589844,-5.099686622619629}, {143.80038452148438,-5.055976867675781}, {143.80038452148438,-5.055976867675781}, {143.80038452148438,-3.1787333488464355}, {143.80038452148438,-3.1787333488464355}, {143.84690856933594,-3.133716106414795}, {143.84690856933594,-3.133716106414795}, {145.78921508789062,-3.1337156295776367}, {145.78921508789062,-3.1337156295776367}, {145.83242797851562,-3.175525188446045}, {145.83242797851562,-3.175525188446045}, {145.83242797851562,-5.062530517578125} };
	std::vector<Point> lampCol[14];
	lampCol[0] = { {119.5662841796875,4.648244857788086}, {119.426513671875,4.635412216186523}, {119.426513671875,4.635412216186523}, {119.30257415771484,4.572858810424805}, {119.30257415771484,4.572858810424805}, {119.21369934082031,4.470582962036133}, {119.21369934082031,4.470582962036133}, {119.17293548583984,4.343877792358398}, {119.17293548583984,4.343877792358398}, {119.18645477294922,4.212251663208008}, {119.18645477294922,4.212251663208008}, {119.25215148925781,4.095464706420898}, {119.25215148925781,4.095464706420898}, {119.36042022705078,4.011037826538086}, {119.36042022705078,4.011037826538086}, {119.49481201171875,3.9722537994384766}, {119.49481201171875,3.9722537994384766}, {119.63465881347656,3.9851512908935547}, {119.63465881347656,3.9851512908935547}, {119.75838470458984,4.047582626342773}, {119.75838470458984,4.047582626342773}, {119.84740447998047,4.15001106262207}, {119.84740447998047,4.15001106262207}, {119.88812255859375,4.276594161987305}, {119.88812255859375,4.276594161987305}, {119.87458038330078,4.408327102661133}, {119.87458038330078,4.408327102661133}, {119.80884552001953,4.525117874145508}, {119.80884552001953,4.525117874145508}, {119.70055389404297,4.609518051147461}, {119.70055389404297,4.609518051147461}, {119.5662841796875,4.648244857788086} };
	lampCol[1] = { {119.5662841796875,-4.3134379386901855}, {119.42652130126953,-4.3262739181518555}, {119.42652130126953,-4.3262739181518555}, {119.30257415771484,-4.388823509216309}, {119.30257415771484,-4.388823509216309}, {119.21370697021484,-4.49110221862793}, {119.21370697021484,-4.49110221862793}, {119.17293548583984,-4.617804050445557}, {119.17293548583984,-4.617804050445557}, {119.18646240234375,-4.749432563781738}, {119.18646240234375,-4.749432563781738}, {119.25215911865234,-4.866218090057373}, {119.25215911865234,-4.866218090057373}, {119.36042785644531,-4.950645923614502}, {119.36042785644531,-4.950645923614502}, {119.49481201171875,-4.989431381225586}, {119.49481201171875,-4.989431381225586}, {119.6346664428711,-4.976537704467773}, {119.6346664428711,-4.976537704467773}, {119.75838470458984,-4.9141011238098145}, {119.75838470458984,-4.9141011238098145}, {119.84740447998047,-4.81167459487915}, {119.84740447998047,-4.81167459487915}, {119.88813018798828,-4.685091972351074}, {119.88813018798828,-4.685091972351074}, {119.87458801269531,-4.553356647491455}, {119.87458801269531,-4.553356647491455}, {119.80885314941406,-4.436568260192871}, {119.80885314941406,-4.436568260192871}, {119.70055389404297,-4.352168083190918}, {119.70055389404297,-4.352168083190918}, {119.5662841796875,-4.3134379386901855} };
	lampCol[2] = { {85.25505828857422,-4.57697868347168}, {85.11529541015625,-4.58981466293335}, {85.11529541015625,-4.58981466293335}, {84.99134826660156,-4.652364253997803}, {84.99134826660156,-4.652364253997803}, {84.90248107910156,-4.754642963409424}, {84.90248107910156,-4.754642963409424}, {84.86170959472656,-4.881344795227051}, {84.86170959472656,-4.881344795227051}, {84.87523651123047,-5.012973308563232}, {84.87523651123047,-5.012973308563232}, {84.94093322753906,-5.129758834838867}, {84.94093322753906,-5.129758834838867}, {85.04920196533203,-5.214186668395996}, {85.04920196533203,-5.214186668395996}, {85.18358612060547,-5.25297212600708}, {85.18358612060547,-5.25297212600708}, {85.32344055175781,-5.240078449249268}, {85.32344055175781,-5.240078449249268}, {85.44715881347656,-5.177641868591309}, {85.44715881347656,-5.177641868591309}, {85.53617858886719,-5.0752153396606445}, {85.53617858886719,-5.0752153396606445}, {85.576904296875,-4.948632717132568}, {85.576904296875,-4.948632717132568}, {85.56336212158203,-4.816897392272949}, {85.56336212158203,-4.816897392272949}, {85.49762725830078,-4.700109004974365}, {85.49762725830078,-4.700109004974365}, {85.38932800292969,-4.615708827972412}, {85.38932800292969,-4.615708827972412}, {85.25505828857422,-4.57697868347168} };
	lampCol[3] = { {85.25996398925781,4.900493144989014}, {85.12020111083984,4.887657165527344}, {85.12020111083984,4.887657165527344}, {84.99625396728516,4.825107574462891}, {84.99625396728516,4.825107574462891}, {84.90738677978516,4.7228288650512695}, {84.90738677978516,4.7228288650512695}, {84.86661529541016,4.596127033233643}, {84.86661529541016,4.596127033233643}, {84.88014221191406,4.464498519897461}, {84.88014221191406,4.464498519897461}, {84.94583892822266,4.347712993621826}, {84.94583892822266,4.347712993621826}, {85.05410766601562,4.263285160064697}, {85.05410766601562,4.263285160064697}, {85.18849182128906,4.224499702453613}, {85.18849182128906,4.224499702453613}, {85.3283462524414,4.237393379211426}, {85.3283462524414,4.237393379211426}, {85.45206451416016,4.299829959869385}, {85.45206451416016,4.299829959869385}, {85.54108428955078,4.402256488800049}, {85.54108428955078,4.402256488800049}, {85.5818099975586,4.528839111328125}, {85.5818099975586,4.528839111328125}, {85.56826782226562,4.660574436187744}, {85.56826782226562,4.660574436187744}, {85.50253295898438,4.777362823486328}, {85.50253295898438,4.777362823486328}, {85.39423370361328,4.861763000488281}, {85.39423370361328,4.861763000488281}, {85.25996398925781,4.900493144989014} };
	lampCol[4] = { {39.59074783325195,4.900493144989014}, {39.450984954833984,4.887657165527344}, {39.450984954833984,4.887657165527344}, {39.3270378112793,4.825107574462891}, {39.3270378112793,4.825107574462891}, {39.23816680908203,4.7228288650512695}, {39.23816680908203,4.7228288650512695}, {39.1973991394043,4.596127033233643}, {39.1973991394043,4.596127033233643}, {39.21092224121094,4.464498519897461}, {39.21092224121094,4.464498519897461}, {39.27661895751953,4.347712993621826}, {39.27661895751953,4.347712993621826}, {39.3848876953125,4.263285160064697}, {39.3848876953125,4.263285160064697}, {39.51927947998047,4.224499702453613}, {39.51927947998047,4.224499702453613}, {39.65912628173828,4.237393379211426}, {39.65912628173828,4.237393379211426}, {39.7828483581543,4.299829959869385}, {39.7828483581543,4.299829959869385}, {39.87187194824219,4.402256488800049}, {39.87187194824219,4.402256488800049}, {39.91259002685547,4.528839111328125}, {39.91259002685547,4.528839111328125}, {39.8990478515625,4.660574436187744}, {39.8990478515625,4.660574436187744}, {39.83331298828125,4.777362823486328}, {39.83331298828125,4.777362823486328}, {39.72502136230469,4.861763000488281}, {39.72502136230469,4.861763000488281}, {39.59074783325195,4.900493144989014} };
	lampCol[5] = { {39.59074783325195,-4.565845489501953}, {39.450984954833984,-4.578681468963623}, {39.450984954833984,-4.578681468963623}, {39.3270378112793,-4.641231060028076}, {39.3270378112793,-4.641231060028076}, {39.23816680908203,-4.743509769439697}, {39.23816680908203,-4.743509769439697}, {39.1973991394043,-4.870211601257324}, {39.1973991394043,-4.870211601257324}, {39.21092224121094,-5.001840114593506}, {39.21092224121094,-5.001840114593506}, {39.27661895751953,-5.118625640869141}, {39.27661895751953,-5.118625640869141}, {39.3848876953125,-5.2030534744262695}, {39.3848876953125,-5.2030534744262695}, {39.51927947998047,-5.2418389320373535}, {39.51927947998047,-5.2418389320373535}, {39.65912628173828,-5.228945255279541}, {39.65912628173828,-5.228945255279541}, {39.7828483581543,-5.166508674621582}, {39.7828483581543,-5.166508674621582}, {39.87187194824219,-5.064082145690918}, {39.87187194824219,-5.064082145690918}, {39.91259002685547,-4.937499523162842}, {39.91259002685547,-4.937499523162842}, {39.8990478515625,-4.805764198303223}, {39.8990478515625,-4.805764198303223}, {39.83331298828125,-4.688975811004639}, {39.83331298828125,-4.688975811004639}, {39.72502136230469,-4.6045756340026855}, {39.72502136230469,-4.6045756340026855}, {39.59074783325195,-4.565845489501953} };
	lampCol[6] = { {16.401649475097656,-6.4468278884887695}, {16.261882781982422,-6.4596638679504395}, {16.261882781982422,-6.4596638679504395}, {16.137937545776367,-6.522213459014893}, {16.137937545776367,-6.522213459014893}, {16.0490665435791,-6.624492168426514}, {16.0490665435791,-6.624492168426514}, {16.00830078125,-6.751194000244141}, {16.00830078125,-6.751194000244141}, {16.021821975708008,-6.882822513580322}, {16.021821975708008,-6.882822513580322}, {16.087520599365234,-6.999608039855957}, {16.087520599365234,-6.999608039855957}, {16.195789337158203,-7.084035873413086}, {16.195789337158203,-7.084035873413086}, {16.330177307128906,-7.12282133102417}, {16.330177307128906,-7.12282133102417}, {16.470027923583984,-7.109927654266357}, {16.470027923583984,-7.109927654266357}, {16.593746185302734,-7.047491073608398}, {16.593746185302734,-7.047491073608398}, {16.682769775390625,-6.945064544677734}, {16.682769775390625,-6.945064544677734}, {16.723491668701172,-6.818481922149658}, {16.723491668701172,-6.818481922149658}, {16.70994758605957,-6.686746597290039}, {16.70994758605957,-6.686746597290039}, {16.644214630126953,-6.569958209991455}, {16.644214630126953,-6.569958209991455}, {16.535921096801758,-6.485558032989502}, {16.535921096801758,-6.485558032989502}, {16.401649475097656,-6.4468278884887695} };
	lampCol[7] = { {6.09427547454834,-16.314105987548828}, {5.954509258270264,-16.326940536499023}, {5.954509258270264,-16.326940536499023}, {5.830564022064209,-16.389490127563477}, {5.830564022064209,-16.389490127563477}, {5.741693019866943,-16.491769790649414}, {5.741693019866943,-16.491769790649414}, {5.700926780700684,-16.618471145629883}, {5.700926780700684,-16.618471145629883}, {5.714448928833008,-16.750099182128906}, {5.714448928833008,-16.750099182128906}, {5.780147075653076,-16.866884231567383}, {5.780147075653076,-16.866884231567383}, {5.888415813446045,-16.951313018798828}, {5.888415813446045,-16.951313018798828}, {6.0228047370910645,-16.99009895324707}, {6.0228047370910645,-16.99009895324707}, {6.16265344619751,-16.977205276489258}, {6.16265344619751,-16.977205276489258}, {6.286373138427734,-16.91476821899414}, {6.286373138427734,-16.91476821899414}, {6.375396251678467,-16.812341690063477}, {6.375396251678467,-16.812341690063477}, {6.416117191314697,-16.685758590698242}, {6.416117191314697,-16.685758590698242}, {6.40257453918457,-16.55402374267578}, {6.40257453918457,-16.55402374267578}, {6.3368401527404785,-16.43723487854004}, {6.3368401527404785,-16.43723487854004}, {6.2285475730896,-16.352834701538086}, {6.2285475730896,-16.352834701538086}, {6.09427547454834,-16.314105987548828} };
	lampCol[8] = { {-6.710097312927246,-16.025609970092773}, {-6.849863529205322,-16.03844451904297}, {-6.849863529205322,-16.03844451904297}, {-6.973808765411377,-16.100994110107422}, {-6.973808765411377,-16.100994110107422}, {-7.062679767608643,-16.20327377319336}, {-7.062679767608643,-16.20327377319336}, {-7.103446006774902,-16.329975128173828}, {-7.103446006774902,-16.329975128173828}, {-7.089923858642578,-16.46160316467285}, {-7.089923858642578,-16.46160316467285}, {-7.02422571182251,-16.578388214111328}, {-7.02422571182251,-16.578388214111328}, {-6.915956974029541,-16.662817001342773}, {-6.915956974029541,-16.662817001342773}, {-6.7815680503845215,-16.701602935791016}, {-6.7815680503845215,-16.701602935791016}, {-6.641719341278076,-16.688709259033203}, {-6.641719341278076,-16.688709259033203}, {-6.517999649047852,-16.626272201538086}, {-6.517999649047852,-16.626272201538086}, {-6.428976535797119,-16.523845672607422}, {-6.428976535797119,-16.523845672607422}, {-6.388255596160889,-16.397262573242188}, {-6.388255596160889,-16.397262573242188}, {-6.401798248291016,-16.265527725219727}, {-6.401798248291016,-16.265527725219727}, {-6.467532634735107,-16.148738861083984}, {-6.467532634735107,-16.148738861083984}, {-6.575825214385986,-16.06433868408203}, {-6.575825214385986,-16.06433868408203}, {-6.710097312927246,-16.025609970092773} };
	lampCol[9] = { {-16.32021713256836,-6.464759349822998}, {-16.459983825683594,-6.477595329284668}, {-16.459983825683594,-6.477595329284668}, {-16.58392906188965,-6.540144920349121}, {-16.58392906188965,-6.540144920349121}, {-16.672800064086914,-6.642423629760742}, {-16.672800064086914,-6.642423629760742}, {-16.713565826416016,-6.769125461578369}, {-16.713565826416016,-6.769125461578369}, {-16.700044631958008,-6.900753974914551}, {-16.700044631958008,-6.900753974914551}, {-16.63434600830078,-7.0175395011901855}, {-16.63434600830078,-7.0175395011901855}, {-16.526077270507812,-7.1019673347473145}, {-16.526077270507812,-7.1019673347473145}, {-16.39168930053711,-7.140752792358398}, {-16.39168930053711,-7.140752792358398}, {-16.25183868408203,-7.127859115600586}, {-16.25183868408203,-7.127859115600586}, {-16.12812042236328,-7.065422534942627}, {-16.12812042236328,-7.065422534942627}, {-16.03909683227539,-6.962996006011963}, {-16.03909683227539,-6.962996006011963}, {-15.99837589263916,-6.836413383483887}, {-15.99837589263916,-6.836413383483887}, {-16.011919021606445,-6.704678058624268}, {-16.011919021606445,-6.704678058624268}, {-16.077651977539062,-6.587889671325684}, {-16.077651977539062,-6.587889671325684}, {-16.185945510864258,-6.5034894943237305}, {-16.185945510864258,-6.5034894943237305}, {-16.32021713256836,-6.464759349822998} };
	lampCol[10] = { {-16.321584701538086,7.111845016479492}, {-16.46135139465332,7.099009037017822}, {-16.46135139465332,7.099009037017822}, {-16.585296630859375,7.036459445953369}, {-16.585296630859375,7.036459445953369}, {-16.67416763305664,6.934180736541748}, {-16.67416763305664,6.934180736541748}, {-16.714933395385742,6.807478904724121}, {-16.714933395385742,6.807478904724121}, {-16.701412200927734,6.6758503913879395}, {-16.701412200927734,6.6758503913879395}, {-16.635713577270508,6.559064865112305}, {-16.635713577270508,6.559064865112305}, {-16.52744483947754,6.474637031555176}, {-16.52744483947754,6.474637031555176}, {-16.393056869506836,6.435851573944092}, {-16.393056869506836,6.435851573944092}, {-16.253206253051758,6.448745250701904}, {-16.253206253051758,6.448745250701904}, {-16.129487991333008,6.511181831359863}, {-16.129487991333008,6.511181831359863}, {-16.040464401245117,6.613608360290527}, {-16.040464401245117,6.613608360290527}, {-15.999743461608887,6.7401909828186035}, {-15.999743461608887,6.7401909828186035}, {-16.013286590576172,6.871926307678223}, {-16.013286590576172,6.871926307678223}, {-16.07901954650879,6.988714694976807}, {-16.07901954650879,6.988714694976807}, {-16.187313079833984,7.07311487197876}, {-16.187313079833984,7.07311487197876}, {-16.321584701538086,7.111845016479492} };
	lampCol[11] = { {-6.022785186767578,16.96158218383789}, {-6.162551403045654,16.948747634887695}, {-6.162551403045654,16.948747634887695}, {-6.286496639251709,16.886198043823242}, {-6.286496639251709,16.886198043823242}, {-6.375367641448975,16.783918380737305}, {-6.375367641448975,16.783918380737305}, {-6.416133880615234,16.657217025756836}, {-6.416133880615234,16.657217025756836}, {-6.40261173248291,16.525588989257812}, {-6.40261173248291,16.525588989257812}, {-6.336913585662842,16.408803939819336}, {-6.336913585662842,16.408803939819336}, {-6.228644847869873,16.32437515258789}, {-6.228644847869873,16.32437515258789}, {-6.0942559242248535,16.28558921813965}, {-6.0942559242248535,16.28558921813965}, {-5.954407215118408,16.29848289489746}, {-5.954407215118408,16.29848289489746}, {-5.830687522888184,16.360919952392578}, {-5.830687522888184,16.360919952392578}, {-5.741664409637451,16.463346481323242}, {-5.741664409637451,16.463346481323242}, {-5.700943470001221,16.589929580688477}, {-5.700943470001221,16.589929580688477}, {-5.714486122131348,16.721664428710938}, {-5.714486122131348,16.721664428710938}, {-5.7802205085754395,16.83845329284668}, {-5.7802205085754395,16.83845329284668}, {-5.888513088226318,16.922853469848633}, {-5.888513088226318,16.922853469848633}, {-6.022785186767578,16.96158218383789} };
	lampCol[12] = { {6.792219161987305,16.697832107543945}, {6.6524529457092285,16.68499755859375}, {6.6524529457092285,16.68499755859375}, {6.528507709503174,16.622447967529297}, {6.528507709503174,16.622447967529297}, {6.439636707305908,16.52016830444336}, {6.439636707305908,16.52016830444336}, {6.398870468139648,16.39346694946289}, {6.398870468139648,16.39346694946289}, {6.412392616271973,16.261838912963867}, {6.412392616271973,16.261838912963867}, {6.478090763092041,16.14505386352539}, {6.478090763092041,16.14505386352539}, {6.58635950088501,16.060625076293945}, {6.58635950088501,16.060625076293945}, {6.720748424530029,16.021839141845703}, {6.720748424530029,16.021839141845703}, {6.860597133636475,16.034732818603516}, {6.860597133636475,16.034732818603516}, {6.984316825866699,16.097169876098633}, {6.984316825866699,16.097169876098633}, {7.073339939117432,16.199596405029297}, {7.073339939117432,16.199596405029297}, {7.114060878753662,16.32617950439453}, {7.114060878753662,16.32617950439453}, {7.100518226623535,16.457914352416992}, {7.100518226623535,16.457914352416992}, {7.034783840179443,16.574703216552734}, {7.034783840179443,16.574703216552734}, {6.9264912605285645,16.659103393554688}, {6.9264912605285645,16.659103393554688}, {6.792219161987305,16.697832107543945} };
	lampCol[13] = { {16.38450813293457,7.119203567504883}, {16.244741439819336,7.106367588043213}, {16.244741439819336,7.106367588043213}, {16.12079620361328,7.04381799697876}, {16.12079620361328,7.04381799697876}, {16.031925201416016,6.941539287567139}, {16.031925201416016,6.941539287567139}, {15.991158485412598,6.814837455749512}, {15.991158485412598,6.814837455749512}, {16.004680633544922,6.68320894241333}, {16.004680633544922,6.68320894241333}, {16.07037925720215,6.566423416137695}, {16.07037925720215,6.566423416137695}, {16.178647994995117,6.481995582580566}, {16.178647994995117,6.481995582580566}, {16.31303596496582,6.443210124969482}, {16.31303596496582,6.443210124969482}, {16.4528865814209,6.456103801727295}, {16.4528865814209,6.456103801727295}, {16.57660484313965,6.518540382385254}, {16.57660484313965,6.518540382385254}, {16.66562843322754,6.620966911315918}, {16.66562843322754,6.620966911315918}, {16.706350326538086,6.747549533843994}, {16.706350326538086,6.747549533843994}, {16.692806243896484,6.879284858703613}, {16.692806243896484,6.879284858703613}, {16.627073287963867,6.996073246002197}, {16.627073287963867,6.996073246002197}, {16.518779754638672,7.08047342300415}, {16.518779754638672,7.08047342300415}, {16.38450813293457,7.119203567504883} };
	robyWall.push_back({ 0,pedes1 });
	robyWall.push_back({ 0,pedes2 });
	for (int i = 0; i < 14; i++)
		robyWall.push_back({ 0,lampCol[i] });
	std::vector<Point> mainObj = { {-0.3048030436038971,7.272381782531738}, {1.184884652616347e-07,7.2787652015686035}, {-0.6090713143348694,7.253237247467041}, {-0.3048030436038971,7.272381782531738}, {-0.9122712016105652,7.221370220184326}, {-0.6090713143348694,7.253237247467041}, {-1.2138704061508179,7.176833629608154}, {-0.9122712016105652,7.221370220184326}, {-1.5133405923843384,7.119707107543945}, {-1.2138704061508179,7.176833629608154}, {-1.8101555109024048,7.050090312957764}, {-1.5133405923843384,7.119707107543945}, {-2.1037943363189697,6.968104362487793}, {-1.8101555109024048,7.050090312957764}, {-2.3937430381774902,6.873893737792969}, {-2.1037943363189697,6.968104362487793}, {-2.6794919967651367,6.767624855041504}, {-2.3937430381774902,6.873893737792969}, {-2.960540533065796,6.6494832038879395}, {-2.6794919967651367,6.767624855041504}, {-3.2363946437835693,6.519675254821777}, {-2.960540533065796,6.6494832038879395}, {-3.5065717697143555,6.378430366516113}, {-3.2363946437835693,6.519675254821777}, {-3.770596981048584,6.225996017456055}, {-3.5065717697143555,6.378430366516113}, {-4.0280070304870605,6.062638282775879}, {-3.770596981048584,6.225996017456055}, {-4.278351306915283,5.888644695281982}, {-4.0280070304870605,6.062638282775879}, {-4.521189212799072,5.704320430755615}, {-4.278351306915283,5.888644695281982}, {-4.756094932556152,5.509989261627197}, {-4.521189212799072,5.704320430755615}, {-4.9826579093933105,5.3059916496276855}, {-4.756094932556152,5.509989261627197}, {-5.200479030609131,5.092685699462891}, {-4.9826579093933105,5.3059916496276855}, {-5.409176349639893,4.8704447746276855}, {-5.200479030609131,5.092685699462891}, {-5.60838508605957,4.639659881591797}, {-5.409176349639893,4.8704447746276855}, {-5.79775333404541,4.400735378265381}, {-5.60838508605957,4.639659881591797}, {-5.976952075958252,4.154090404510498}, {-5.79775333404541,4.400735378265381}, {-6.145664215087891,3.900157928466797}, {-5.976952075958252,4.154090404510498}, {-6.303595542907715,3.6393826007843018}, {-6.145664215087891,3.900157928466797}, {-6.450468063354492,3.372223138809204}, {-6.303595542907715,3.6393826007843018}, {-6.586023330688477,3.0991477966308594}, {-6.450468063354492,3.372223138809204}, {-6.710025787353516,2.820634603500366}, {-6.586023330688477,3.0991477966308594}, {-6.822255611419678,2.5371742248535156}, {-6.710025787353516,2.820634603500366}, {-6.9225172996521,2.2492620944976807}, {-6.822255611419678,2.5371742248535156}, {-7.010633945465088,1.957404375076294}, {-6.9225172996521,2.2492620944976807}, {-7.086452007293701,1.6621122360229492}, {-7.010633945465088,1.957404375076294}, {-7.149838447570801,1.363904595375061}, {-7.086452007293701,1.6621122360229492}, {-7.200681686401367,1.0633041858673096}, {-7.149838447570801,1.363904595375061}, {-7.238891124725342,0.7608382105827332}, {-7.200681686401367,1.0633041858673096}, {-7.264402866363525,0.45703741908073425}, {-7.238891124725342,0.7608382105827332}, {-7.277167797088623,0.15243497490882874}, {-7.264402866363525,0.45703741908073425}, {-7.277167797088623,-0.15243497490882874}, {-7.277167797088623,0.15243497490882874}, {-7.264402866363525,-0.4570375084877014}, {-7.277167797088623,-0.15243497490882874}, {-7.238891124725342,-0.7608382105827332}, {-7.264402866363525,-0.4570375084877014}, {-7.200681686401367,-1.0633041858673096}, {-7.238891124725342,-0.7608382105827332}, {-7.149838447570801,-1.363904595375061}, {-7.200681686401367,-1.0633041858673096}, {-7.086452007293701,-1.6621122360229492}, {-7.149838447570801,-1.363904595375061}, {-7.010633945465088,-1.957404375076294}, {-7.086452007293701,-1.6621122360229492}, {-6.9225172996521,-2.2492620944976807}, {-7.010633945465088,-1.957404375076294}, {-6.822255611419678,-2.5371742248535156}, {-6.9225172996521,-2.2492620944976807}, {-6.710025787353516,-2.820634603500366}, {-6.822255611419678,-2.5371742248535156}, {-6.586023330688477,-3.0991477966308594}, {-6.710025787353516,-2.820634603500366}, {-6.450468063354492,-3.372223138809204}, {-6.586023330688477,-3.0991477966308594}, {-6.303595542907715,-3.6393826007843018}, {-6.450468063354492,-3.372223138809204}, {-6.145664215087891,-3.900157928466797}, {-6.303595542907715,-3.6393826007843018}, {-5.976952075958252,-4.154090404510498}, {-6.145664215087891,-3.900157928466797}, {-5.79775333404541,-4.400735378265381}, {-5.976952075958252,-4.154090404510498}, {-5.60838508605957,-4.639659881591797}, {-5.79775333404541,-4.400735378265381}, {-5.409176349639893,-4.8704447746276855}, {-5.60838508605957,-4.639659881591797}, {-5.200479030609131,-5.092685699462891}, {-5.409176349639893,-4.8704447746276855}, {-4.9826579093933105,-5.3059916496276855}, {-5.200479030609131,-5.092685699462891}, {-4.756094932556152,-5.509989261627197}, {-4.9826579093933105,-5.3059916496276855}, {-4.521189212799072,-5.704320430755615}, {-4.756094932556152,-5.509989261627197}, {-4.278351306915283,-5.888644695281982}, {-4.521189212799072,-5.704320430755615}, {-4.0280070304870605,-6.062638282775879}, {-4.278351306915283,-5.888644695281982}, {-3.770596981048584,-6.225996017456055}, {-4.0280070304870605,-6.062638282775879}, {-3.5065717697143555,-6.378430366516113}, {-3.770596981048584,-6.225996017456055}, {-3.2363946437835693,-6.519675254821777}, {-3.5065717697143555,-6.378430366516113}, {-2.960540533065796,-6.6494832038879395}, {-3.2363946437835693,-6.519675254821777}, {-2.6794919967651367,-6.767624855041504}, {-2.960540533065796,-6.6494832038879395}, {-2.3937430381774902,-6.873893737792969}, {-2.6794919967651367,-6.767624855041504}, {-2.1037943363189697,-6.968104362487793}, {-2.3937430381774902,-6.873893737792969}, {-1.8101555109024048,-7.050090312957764}, {-2.1037943363189697,-6.968104362487793}, {-1.5133405923843384,-7.119707107543945}, {-1.8101555109024048,-7.050090312957764}, {-1.2138704061508179,-7.176833629608154}, {-1.5133405923843384,-7.119707107543945}, {-0.9122712016105652,-7.221370220184326}, {-1.2138704061508179,-7.176833629608154}, {-0.6090713143348694,-7.253237247467041}, {-0.9122712016105652,-7.221370220184326}, {-0.3048030436038971,-7.272381782531738}, {-0.6090713143348694,-7.253237247467041}, {1.184884652616347e-07,-7.2787652015686035}, {-0.3048030436038971,-7.272381782531738}, {0.30480313301086426,-7.272381782531738}, {1.184884652616347e-07,-7.2787652015686035}, {0.6090715527534485,-7.253237247467041}, {0.30480313301086426,-7.272381782531738}, {0.9122713208198547,-7.221370220184326}, {0.6090715527534485,-7.253237247467041}, {1.2138707637786865,-7.176833629608154}, {0.9122713208198547,-7.221370220184326}, {1.5133405923843384,-7.119707107543945}, {1.2138707637786865,-7.176833629608154}, {1.8101555109024048,-7.050090312957764}, {1.5133405923843384,-7.119707107543945}, {2.103795051574707,-6.968104362487793}, {1.8101555109024048,-7.050090312957764}, {2.3937435150146484,-6.873893737792969}, {2.103795051574707,-6.968104362487793}, {2.679492473602295,-6.767624855041504}, {2.3937435150146484,-6.873893737792969}, {2.960541248321533,-6.6494832038879395}, {2.679492473602295,-6.767624855041504}, {3.2363955974578857,-6.519675254821777}, {2.960541248321533,-6.6494832038879395}, {3.506572723388672,-6.378430366516113}, {3.2363955974578857,-6.519675254821777}, {3.770597457885742,-6.225996017456055}, {3.506572723388672,-6.378430366516113}, {4.028007507324219,-6.062638282775879}, {3.770597457885742,-6.225996017456055}, {4.278350830078125,-5.888644695281982}, {4.028007507324219,-6.062638282775879}, {4.521189212799072,-5.704320430755615}, {4.278350830078125,-5.888644695281982}, {4.7560954093933105,-5.509989261627197}, {4.521189212799072,-5.704320430755615}, {4.982658386230469,-5.3059916496276855}, {4.7560954093933105,-5.509989261627197}, {5.200479030609131,-5.092685699462891}, {4.982658386230469,-5.3059916496276855}, {5.409176349639893,-4.8704447746276855}, {5.200479030609131,-5.092685699462891}, {5.60838508605957,-4.639659881591797}, {5.409176349639893,-4.8704447746276855}, {5.797753810882568,-4.400735378265381}, {5.60838508605957,-4.639659881591797}, {5.976952075958252,-4.154090404510498}, {5.797753810882568,-4.400735378265381}, {6.145665168762207,-3.900157928466797}, {5.976952075958252,-4.154090404510498}, {6.303596019744873,-3.6393826007843018}, {6.145665168762207,-3.900157928466797}, {6.450468063354492,-3.372223138809204}, {6.303596019744873,-3.6393826007843018}, {6.586023330688477,-3.0991477966308594}, {6.450468063354492,-3.372223138809204}, {6.710025787353516,-2.820634603500366}, {6.586023330688477,-3.0991477966308594}, {6.822255611419678,-2.5371742248535156}, {6.710025787353516,-2.820634603500366}, {6.922517776489258,-2.2492620944976807}, {6.822255611419678,-2.5371742248535156}, {7.010633945465088,-1.957404375076294}, {6.922517776489258,-2.2492620944976807}, {7.086452007293701,-1.6621122360229492}, {7.010633945465088,-1.957404375076294}, {7.149838447570801,-1.363904595375061}, {7.086452007293701,-1.6621122360229492}, {7.200681686401367,-1.0633041858673096}, {7.149838447570801,-1.363904595375061}, {7.238891124725342,-0.7608382105827332}, {7.200681686401367,-1.0633041858673096}, {7.264402866363525,-0.4570375084877014}, {7.238891124725342,-0.7608382105827332}, {7.2771687507629395,-0.15243497490882874}, {7.264402866363525,-0.4570375084877014}, {7.2771687507629395,0.15243497490882874}, {7.2771687507629395,-0.15243497490882874}, {7.264402866363525,0.45703741908073425}, {7.2771687507629395,0.15243497490882874}, {7.238891124725342,0.7608382105827332}, {7.264402866363525,0.45703741908073425}, {7.200681686401367,1.0633041858673096}, {7.238891124725342,0.7608382105827332}, {7.149838447570801,1.363904595375061}, {7.200681686401367,1.0633041858673096}, {7.086452007293701,1.6621122360229492}, {7.149838447570801,1.363904595375061}, {7.010633945465088,1.957404375076294}, {7.086452007293701,1.6621122360229492}, {6.922517776489258,2.2492620944976807}, {7.010633945465088,1.957404375076294}, {6.822255611419678,2.5371742248535156}, {6.922517776489258,2.2492620944976807}, {6.710025787353516,2.820634603500366}, {6.822255611419678,2.5371742248535156}, {6.586023330688477,3.0991477966308594}, {6.710025787353516,2.820634603500366}, {6.450468063354492,3.372223138809204}, {6.586023330688477,3.0991477966308594}, {6.303596019744873,3.6393826007843018}, {6.450468063354492,3.372223138809204}, {6.145665168762207,3.900157928466797}, {6.303596019744873,3.6393826007843018}, {5.976952075958252,4.154090404510498}, {6.145665168762207,3.900157928466797}, {5.797753810882568,4.400735378265381}, {5.976952075958252,4.154090404510498}, {5.60838508605957,4.639659881591797}, {5.797753810882568,4.400735378265381}, {5.409176349639893,4.8704447746276855}, {5.60838508605957,4.639659881591797}, {5.200479030609131,5.092685699462891}, {5.409176349639893,4.8704447746276855}, {4.982658386230469,5.3059916496276855}, {5.200479030609131,5.092685699462891}, {4.7560954093933105,5.509989261627197}, {4.982658386230469,5.3059916496276855}, {4.521189212799072,5.704320430755615}, {4.7560954093933105,5.509989261627197}, {4.278350830078125,5.888644695281982}, {4.521189212799072,5.704320430755615}, {4.028007507324219,6.062638282775879}, {4.278350830078125,5.888644695281982}, {3.770597457885742,6.225996017456055}, {4.028007507324219,6.062638282775879}, {3.506572723388672,6.378430366516113}, {3.770597457885742,6.225996017456055}, {3.2363955974578857,6.519675254821777}, {3.506572723388672,6.378430366516113}, {2.960541248321533,6.6494832038879395}, {3.2363955974578857,6.519675254821777}, {2.679492473602295,6.767624855041504}, {2.960541248321533,6.6494832038879395}, {2.3937435150146484,6.873893737792969}, {2.679492473602295,6.767624855041504}, {2.103795051574707,6.968104362487793}, {2.3937435150146484,6.873893737792969}, {1.8101555109024048,7.050090312957764}, {2.103795051574707,6.968104362487793}, {1.5133405923843384,7.119707107543945}, {1.8101555109024048,7.050090312957764}, {1.2138707637786865,7.176833629608154}, {1.5133405923843384,7.119707107543945}, {0.9122713208198547,7.221370220184326}, {1.2138707637786865,7.176833629608154}, {0.6090715527534485,7.253237247467041}, {0.9122713208198547,7.221370220184326}, {0.30480313301086426,7.272381782531738}, {0.6090715527534485,7.253237247467041}, {1.184884652616347e-07,7.2787652015686035}, {0.30480313301086426,7.272381782531738} };
	robyWall.push_back({ 0,mainObj });
	std::vector<Point> inside_world = { {98.15967559814453,16.26300811767578}, {84.3594741821289,16.415218353271484}, {83.19254302978516,27.47567367553711}, {84.25800323486328,39.449378967285156}, {84.25800323486328,48.73406982421875}, {70.50853729248047,65.98432159423828}, {54.83110046386719,79.3786392211914}, {40.01617431640625,88.40965270996094}, {20.02618408203125,94.24429321289062}, {-0.217498779296875,96.12152862548828}, {-15.18463134765625,95.1068115234375}, {-35.02241516113281,89.17069244384766}, {-52.780029296875,79.7337875366211}, {-65.41329956054688,70.49983215332031}, {-78.45245361328125,54.61945343017578}, {-87.68641662597656,37.72434997558594}, {-93.52105712890625,22.5035400390625}, {-95.70269775390625,2.1076526641845703}, {-93.87620544433594,-18.28823471069336}, {-90.32467651367188,-32.2913818359375}, {-80.98924255371094,-51.46959686279297}, {-68.60964965820312,-66.89334869384766}, {-57.34625244140625,-77.29423522949219}, {-39.233489990234375,-87.54291534423828}, {-20.5626220703125,-93.783447265625}, {-5.4432830810546875,-95.76215362548828}, {15.815109252929688,-94.29080963134766}, {35.24700927734375,-89.52162170410156}, {48.79353332519531,-83.4840316772461}, {65.38421630859375,-71.25664520263672}, {80.30061340332031,-55.98509979248047}, {85.0190658569336,-39.19147491455078}, {84.96833038330078,-18.338960647583008}, {89.38236236572266,-16.86761474609375}, {115.81583404541016,-16.360254287719727}, {139.9661865234375,-16.208045959472656}, {147.82012939453125,-16.512462615966797}, {150.13368225097656,-21.93107032775879}, {160.60560607910156,-21.870187759399414}, {162.3712158203125,-6.101428985595703}, {162.51058959960938,-5.1957292556762695}, {223.5669708251953,-5.133362770080566}, {224.4251251220703,-5.702329635620117}, {162.95272827148438,-5.766788482666016}, {161.18568420410156,-22.449705123901367}, {149.69961547851562,-22.555404663085938}, {147.33897399902344,-17.164701461791992}, {128.91192626953125,-17.023767471313477}, {87.92533111572266,-18.33884620666504}, {85.73353576660156,-41.93718719482422}, {80.91158294677734,-58.08341979980469}, {66.95714569091797,-71.23419952392578}, {49.86112976074219,-84.31192016601562}, {36.18218231201172,-90.63923645019531}, {16.456008911132812,-95.53424835205078}, {-5.5350189208984375,-97.2146224975586}, {-21.535125732421875,-95.24200439453125}, {-40.30543518066406,-88.7457504272461}, {-58.278167724609375,-78.66348266601562}, {-69.19140625,-67.87342834472656}, {-82.4627685546875,-52.35113525390625}, {-91.82612609863281,-32.99317932128906}, {-95.92916870117188,-17.641809463500977}, {-97.61245727539062,2.2421746253967285}, {-94.86172485351562,23.340402603149414}, {-88.65455627441406,39.54216766357422}, {-79.39640808105469,55.112693786621094}, {-66.45603942871094,71.52487182617188}, {-53.83128356933594,81.20384979248047}, {-36.051422119140625,90.2515869140625}, {-15.430999755859375,96.14313507080078}, {0.1395263671875,97.8264389038086}, {21.391189575195312,95.93272399902344}, {39.907493591308594,90.46199798583984}, {55.79364013671875,81.20384216308594}, {71.46937561035156,67.42182159423828}, {86.30345916748047,48.905517578125}, {85.98783874511719,37.01720428466797}, {85.6722183227539,19.026933670043945}, {112.07899475097656,18.50090217590332}, {161.6844940185547,17.930477142333984}, {163.2674102783203,5.926845073699951}, {224.25189208984375,6.034613609313965}, {223.43125915527344,5.357703685760498}, {162.39114379882812,5.099059104919434}, {161.03988647460938,16.792694091796875}, {142.72418212890625,16.437541961669922}, {119.41807556152344,16.36448097229004}, {98.15967559814453,16.26300811767578} };
	std::vector<Point> col_chess_house = { {5.73764705657959,-48.00446319580078}, {5.450861930847168,-48.2492790222168}, {3.3676815032958984,-63.44190216064453}, {3.6635704040527344,-63.790008544921875}, {3.8550281524658203,-64.55583953857422}, {3.785407066345215,-65.25204467773438}, {3.5069236755371094,-65.80901336669922}, {3.0543880462646484,-66.29635620117188}, {2.3929896354675293,-66.54003143310547}, {1.714186191558838,-66.57484436035156}, {1.1098384857177734,-66.40562438964844}, {0.5538387298583984,-65.98258209228516}, {0.28792572021484375,-65.46284484863281}, {-14.668858528137207,-63.499534606933594}, {-15.021394729614258,-63.862144470214844}, {-15.615670204162598,-64.1240234375}, {-16.43153953552246,-64.19453430175781}, {-17.106395721435547,-63.94272232055664}, {-17.680524826049805,-63.388736724853516}, {-17.982698440551758,-62.764244079589844}, {-18.022987365722656,-62.079315185546875}, {-17.761104583740234,-61.364173889160156}, {-17.348133087158203,-60.87062072753906}, {-16.75385856628418,-60.52815628051758}, {-14.809211730957031,-45.91636276245117}, {-15.242327690124512,-45.54368209838867}, {-15.534429550170898,-45.00984191894531}, {-15.64522647857666,-44.4659309387207}, {-15.594863891601562,-43.81121826171875}, {-15.332980155944824,-43.257232666015625}, {-14.849501609802246,-42.75361251831055}, {-14.265298843383789,-42.461509704589844}, {-13.580371856689453,-42.40107727050781}, {-12.935733795166016,-42.60252380371094}, {-12.472400665283203,-42.93491744995117}, {-12.150081634521484,-43.33781433105469}, {-6.909383773803711,-44.122318267822266}, {-6.959982395172119,-44.537227630615234}, {-11.91040325164795,-43.87412643432617}, {-11.843254089355469,-44.33578109741211}, {-11.91879653930664,-44.889766693115234}, {-12.111852645874023,-45.34302520751953}, {-12.447601318359375,-45.78789520263672}, {-12.926043510437012,-46.08167266845703}, {-13.471634864807129,-46.249549865722656}, {-14.075983047485352,-46.241153717041016}, {-15.450377464294434,-56.861934661865234}, {-9.045970916748047,-57.52503967285156}, {-8.802553176879883,-59.20378112792969}, {-4.748386859893799,-59.73258972167969}, {-3.5648727416992188,-58.15456771850586}, {3.192070484161377,-59.136634826660156}, {4.5844879150390625,-48.67610168457031}, {4.007419586181641,-48.58866500854492}, {3.3778905868530273,-48.355506896972656}, {2.975691795349121,-48.040740966796875}, {2.620124340057373,-47.55693817138672}, {2.4569129943847656,-46.98569869995117}, {2.4510841369628906,-46.3736572265625}, {2.6784138679504395,-45.77327346801758}, {-1.8531627655029297,-45.17285919189453}, {-1.760061264038086,-44.658775329589844}, {3.0135765075683594,-45.38239669799805}, {3.3730297088623047,-45.12495040893555}, {3.785914897918701,-44.920936584472656}, {4.2862348556518555,-44.828643798828125}, {4.898276329040527,-44.89179229736328}, {5.373920440673828,-45.1086311340332}, {5.779616355895996,-45.465362548828125}, {6.017437934875488,-45.850074768066406}, {6.276244163513184,-46.50758361816406}, {6.2202863693237305,-47.09514236450195}, {6.045416831970215,-47.58477783203125}, {5.73764705657959,-48.00446319580078} };
	std::vector<Point> col_chess_sofa = { {-14.211329460144043,-53.8132438659668}, {-14.030024528503418,-54.20002746582031}, {-12.325763702392578,-54.47802734375}, {-11.987329483032227,-54.27254867553711}, {-11.17750358581543,-48.30159378051758}, {-11.31045913696289,-48.03567886352539}, {-13.050981521606445,-47.806026458740234}, {-13.413589477539062,-47.963157653808594}, {-14.211329460144043,-53.8132438659668} };
	std::vector<Point> col_chess_table = { {-9.279850959777832,-54.03080749511719}, {-8.639242172241211,-49.2443733215332}, {-8.772198677062988,-48.97846221923828}, {-10.29515552520752,-48.785072326660156}, {-10.657764434814453,-48.94219970703125}, {-11.298372268676758,-53.6682014465332}, {-11.11706829071045,-54.05498123168945}, {-9.6182861328125,-54.23628616333008}, {-9.279850959777832,-54.03080749511719} };
	std::vector<Point> col_chess_poll1 = { {-8.398322105407715,-39.8451042175293}, {-8.459726333618164,-39.98155975341797}, {-8.487017631530762,-40.13848114013672}, {-8.480195045471191,-40.31245803833008}, {-8.432435989379883,-40.46596908569336}, {-8.34032917022705,-40.61606979370117}, {-8.207286834716797,-40.7320556640625}, {-8.087889671325684,-40.8002815246582}, {-7.92073392868042,-40.837806701660156}, {-7.763812065124512,-40.844627380371094}, {-7.552308559417725,-40.80369186401367}, {-7.398797988891602,-40.71841049194336}, {-7.282812118530273,-40.57854461669922}, {-7.173649311065674,-40.39433288574219}, {-7.136124610900879,-40.18623733520508}, {-7.153181076049805,-40.02590560913086}, {-7.180471897125244,-39.92356491088867}, {-7.269166946411133,-39.773468017578125}, {-7.368095874786377,-39.65406799316406}, {-7.52842903137207,-39.551727294921875}, {-7.688762187957764,-39.51420593261719}, {-7.88662052154541,-39.51079177856445}, {-8.043542861938477,-39.548316955566406}, {-8.193641662597656,-39.61654281616211}, {-8.302804946899414,-39.7188835144043}, {-8.398322105407715,-39.8451042175293} };
	std::vector<Point> col_chess_poll2 = { {-0.059539973735809326,-41.067955017089844}, {-0.0875663161277771,-41.22910690307617}, {-0.08055979013442993,-41.40777587890625}, {-0.031513750553131104,-41.56542205810547}, {0.0630750060081482,-41.719566345214844}, {0.19970327615737915,-41.838680267333984}, {0.3223183751106262,-41.90874481201172}, {0.49397948384284973,-41.94728088378906}, {0.6551307439804077,-41.954288482666016}, {0.8723346590995789,-41.91224670410156}, {1.029982566833496,-41.82466506958008}, {1.1490944623947144,-41.6810302734375}, {1.261199712753296,-41.491851806640625}, {1.2997359037399292,-41.27815246582031}, {1.282219409942627,-41.11349868774414}, {1.2541931867599487,-41.008399963378906}, {1.1631077527999878,-40.85425567626953}, {1.0615123510360718,-40.73163986206055}, {0.8968577980995178,-40.62654113769531}, {0.7322032451629639,-40.58800506591797}, {0.5290124416351318,-40.584503173828125}, {0.36786121129989624,-40.62303924560547}, {0.2137165069580078,-40.6931037902832}, {0.10161125659942627,-40.79820251464844}, {0.0035192370414733887,-40.92782211303711}, {-0.059539973735809326,-41.067955017089844} };
	std::vector<Point> col_tank_canon = { {52.40139389038086,-20.03044319152832}, {52.03324508666992,-22.380924224853516}, {51.24031066894531,-23.07474136352539}, {46.70926284790039,-22.267648696899414}, {46.581825256347656,-21.0924072265625}, {43.653907775878906,-20.471694946289062}, {43.4080810546875,-20.041500091552734}, {43.58433532714844,-19.389156341552734}, {44.11012649536133,-19.204788208007812}, {46.780059814453125,-19.662296295166016}, {47.28980255126953,-18.614490509033203}, {51.97660827636719,-19.336626052856445}, {52.40139389038086,-20.03044319152832} };
	std::vector<Point> col_tank_tower = { {51.589683532714844,-31.429336547851562}, {50.91657638549805,-31.06955337524414}, {50.32659149169922,-30.58536720275879}, {49.8424072265625,-29.995384216308594}, {49.48262405395508,-29.32227897644043}, {49.261070251464844,-28.591915130615234}, {49.18626022338867,-27.83236312866211}, {49.261070251464844,-27.072811126708984}, {49.48262405395508,-26.34244728088379}, {49.8424072265625,-25.669342041015625}, {50.32659149169922,-25.07935905456543}, {50.91657638549805,-24.595172882080078}, {51.589683532714844,-24.235389709472656}, {52.320045471191406,-24.013835906982422}, {53.07959747314453,-23.93902587890625}, {53.839149475097656,-24.013835906982422}, {54.56951141357422,-24.235389709472656}, {55.242618560791016,-24.595172882080078}, {55.832603454589844,-25.07935905456543}, {56.31678771972656,-25.669342041015625}, {56.676570892333984,-26.34244728088379}, {56.89812469482422,-27.072811126708984}, {56.97293472290039,-27.83236312866211}, {56.89812469482422,-28.591915130615234}, {56.676570892333984,-29.32227897644043}, {56.31678771972656,-29.995384216308594}, {55.832603454589844,-30.58536720275879}, {55.242618560791016,-31.06955337524414}, {54.56951141357422,-31.429336547851562}, {53.839149475097656,-31.650890350341797}, {53.07959747314453,-31.72570037841797}, {52.320045471191406,-31.650890350341797}, {51.589683532714844,-31.429336547851562} };
	std::vector<Point> col_tank_wall = { {35.66817855834961,-23.336700439453125}, {35.32402038574219,-23.049903869628906}, {33.36561584472656,-19.829593658447266}, {33.087013244628906,-20.001672744750977}, {34.996253967285156,-22.984352111816406}, {34.74223709106445,-22.97615623474121}, {34.25058364868164,-23.05809783935547}, {33.955596923828125,-23.279340744018555}, {33.668800354003906,-23.60710906982422}, {33.57046890258789,-24.139728546142578}, {33.619632720947266,-24.565826416015625}, {33.84907150268555,-24.942758560180664}, {34.1276741027832,-25.139419555664062}, {34.570159912109375,-25.327884674072266}, {37.710174560546875,-34.01390838623047}, {37.497127532958984,-34.25153732299805}, {37.36602020263672,-34.56291580200195}, {37.33324432373047,-34.923458099365234}, {37.382408142089844,-35.25122833251953}, {37.50532150268555,-35.54621887207031}, {37.7839241027832,-35.82482147216797}, {38.0305061340332,-35.95285415649414}, {38.37667465209961,-36.0666618347168}, {38.798709869384766,-36.00975799560547}, {39.10219955444336,-35.89120864868164}, {39.34403991699219,-35.720497131347656}, {46.10521697998047,-39.130584716796875}, {46.093833923339844,-39.477699279785156}, {46.156429290771484,-39.78498077392578}, {46.3100700378418,-40.086570739746094}, {46.50923156738281,-40.285736083984375}, {46.799442291259766,-40.445068359375}, {47.175010681152344,-40.51904296875}, {47.49367141723633,-40.49627685546875}, {47.806644439697266,-40.39385223388672}, {48.06840133666992,-40.20606994628906}, {48.27894592285156,-39.91017150878906}, {48.387062072753906,-39.59150695800781}, {48.42689514160156,-39.36958312988281}, {57.942100524902344,-36.990779876708984}, {58.127830505371094,-37.15279769897461}, {58.35307312011719,-37.30296325683594}, {58.621788024902344,-37.4096565246582}, {58.94977569580078,-37.453125}, {59.305423736572266,-37.40175247192383}, {59.589942932128906,-37.235782623291016}, {59.83494567871094,-37.026344299316406}, {59.993011474609375,-36.73392105102539}, {60.087852478027344,-36.326900482177734}, {60.052284240722656,-35.97125244140625}, {59.90607452392578,-35.6156005859375}, {59.69663619995117,-35.41011428833008}, {63.09492492675781,-28.712657928466797}, {63.442039489746094,-28.67282485961914}, {63.90864944458008,-28.507801055908203}, {64.23300170898438,-28.217592239379883}, {64.43785858154297,-27.830646514892578}, {64.48907470703125,-27.346961975097656}, {64.36388397216797,-26.931562423706055}, {64.1135025024414,-26.612899780273438}, {63.74932098388672,-26.385284423828125}, {63.37944412231445,-26.294239044189453}, {59.53972625732422,-17.21684455871582}, {59.801483154296875,-17.000608444213867}, {59.95512390136719,-16.68194580078125}, {60.046173095703125,-16.32914161682129}, {60.04048156738281,-15.936504364013672}, {59.89253234863281,-15.578009605407715}, {59.63077163696289,-15.30487060546875}, {59.26658630371094,-15.082944869995117}, {58.817047119140625,-15.026041030883789}, {58.35612487792969,-15.179681777954102}, {58.08867645263672,-15.356083869934082}, {57.96348571777344,-15.424368858337402}, {51.29670715332031,-12.08508014678955}, {51.29670715332031,-11.753140449523926}, {51.216094970703125,-11.33110237121582}, {51.01218795776367,-10.951742172241211}, {50.703956604003906,-10.72886848449707}, {50.40521240234375,-10.605576515197754}, {49.96894836425781,-10.596092224121094}, {49.50897216796875,-10.747836112976074}, {49.20548629760742,-11.0181303024292}, {48.98735427856445,-11.383264541625977}, {48.91622543334961,-11.682010650634766}, {48.90673828125,-11.914368629455566}, {40.113670349121094,-14.533881187438965}, {39.749488830566406,-14.311955451965332}, {39.339778900146484,-14.164005279541016}, {38.82195281982422,-14.164005279541016}, {38.40086364746094,-14.385931015014648}, {38.122032165527344,-14.755806922912598}, {37.979774475097656,-15.228109359741211}, {38.036678314208984,-15.671960830688477}, {38.24153137207031,-16.064598083496094}, {38.50886535644531,-16.246292114257812}, {36.75859069824219,-19.69767951965332}, {37.052215576171875,-19.84107780456543}, {38.79074478149414,-16.38532066345215}, {38.97954177856445,-16.456119537353516}, {39.227333068847656,-16.479717254638672}, {39.498722076416016,-16.408920288085938}, {39.73471450805664,-16.302724838256836}, {39.95890808105469,-16.149330139160156}, {40.147701263427734,-15.913336753845215}, {40.24209976196289,-15.641945838928223}, {40.30109786987305,-15.323356628417969}, {40.312896728515625,-15.21716022491455}, {49.173744201660156,-12.537338256835938}, {49.37860107421875,-12.709415435791016}, {49.58345413208008,-12.840522766113281}, {49.84566879272461,-12.930658340454102}, {50.19801712036133,-12.947046279907227}, {50.46023178100586,-12.897881507873535}, {50.71424865722656,-12.807744979858398}, {50.951881408691406,-12.63566780090332}, {51.16493225097656,-12.67663860321045}, {57.736656188964844,-16.011667251586914}, {57.720848083496094,-16.232959747314453}, {57.74456024169922,-16.529335021972656}, {57.83940124511719,-16.75853157043457}, {57.99351501464844,-16.991680145263672}, {58.206905364990234,-17.181358337402344}, {58.44795608520508,-17.327571868896484}, {58.71666717529297,-17.406604766845703}, {58.9932861328125,-17.438217163085938}, {62.73139953613281,-26.426687240600586}, {62.494300842285156,-26.636125564575195}, {62.28486251831055,-26.91669273376465}, {62.16236114501953,-27.165647506713867}, {62.12284469604492,-27.46202278137207}, {62.15050506591797,-27.754446029663086}, {62.2572021484375,-28.03896713256836}, {62.43107604980469,-28.29582405090332}, {62.56938171386719,-28.46574592590332}, {59.21357727050781,-35.0782470703125}, {58.826629638671875,-35.112388610839844}, {58.43968200683594,-35.21481704711914}, {58.177921295166016,-35.39122009277344}, {57.97306823730469,-35.60176086425781}, {57.80235290527344,-35.94318389892578}, {57.71699905395508,-36.22770690917969}, {57.50645446777344,-36.46101379394531}, {48.28010559082031,-38.703880310058594}, {47.995582580566406,-38.4351692199707}, {47.66364288330078,-38.24549102783203}, {47.24871826171875,-38.17041015625}, {46.841697692871094,-38.241539001464844}, {46.53742218017578,-38.407508850097656}, {46.33588409423828,-38.58533477783203}, {39.62977600097656,-35.24211120605469}, {39.665340423583984,-34.831138610839844}, {39.55073928833008,-34.3450813293457}, {39.26622009277344,-33.98548126220703}, {38.82758712768555,-33.77604293823242}, {38.48774337768555,-33.7088623046875}, {38.32572555541992,-33.72467041015625}, {35.250274658203125,-25.245943069458008}, {35.52887725830078,-25.032894134521484}, {35.799285888671875,-24.72970962524414}, {35.930389404296875,-24.22986602783203}, {35.87303161621094,-23.680856704711914}, {35.66817855834961,-23.336700439453125} };
	std::vector<Point> col_tarkov_human = { {-2.463717460632324,58.493072509765625}, {-2.3406829833984375,58.8667106628418}, {-2.541480302810669,59.183677673339844}, {-2.9963221549987793,59.24648666381836}, {-3.3540146350860596,59.114994049072266}, {-3.472938060760498,58.802947998046875}, {-3.300413131713867,58.51114273071289}, {-2.8658735752105713,58.39078903198242}, {-2.463717460632324,58.493072509765625} };
	std::vector<Point> col_tarkov_poll1 = { {-16.309078216552734,51.83457565307617}, {-16.971227645874023,51.79525375366211}, {-16.931907653808594,51.13310241699219}, {-16.269756317138672,51.17242431640625}, {-16.309078216552734,51.83457565307617} };
	std::vector<Point> col_tarkov_poll2 = { {-16.716476440429688,46.65361022949219}, {-16.054325103759766,46.69293212890625}, {-16.093647003173828,47.35508346557617}, {-16.755796432495117,47.31576156616211}, {-16.716476440429688,46.65361022949219} };
	std::vector<Point> col_tarkov_poll3 = { {-16.31903076171875,40.33554458618164}, {-15.656880378723145,40.3748664855957}, {-15.69620132446289,41.037017822265625}, {-16.35835075378418,40.99769592285156}, {-16.31903076171875,40.33554458618164} };
	std::vector<Point> col_tarkov_poll4 = { {-9.971705436706543,41.39726257324219}, {-10.633855819702148,41.357940673828125}, {-10.594534873962402,40.6957893371582}, {-9.932384490966797,40.735111236572266}, {-9.971705436706543,41.39726257324219} };
	std::vector<Point> col_tarkov_poll5 = { {5.392230033874512,42.28575134277344}, {4.7300801277160645,42.246429443359375}, {4.7694010734558105,41.58427810668945}, {5.431550979614258,41.623600006103516}, {5.392230033874512,42.28575134277344} };
	std::vector<Point> col_tarkov_table = { {-5.836777687072754,57.05236053466797}, {0.7278921008110046,57.4320182800293}, {0.660912811756134,58.27537536621094}, {-5.904158115386963,57.90300750732422}, {-5.836777687072754,57.05236053466797} };
	std::vector<Point> col_tarkov_wall = { {4.730260848999023,41.55165100097656}, {4.488521575927734,45.84252166748047}, {4.864475250244141,47.20012664794922}, {3.8828201293945312,63.03191375732422}, {-12.533782005310059,62.17557907104492}, {-12.366691589355469,58.186302185058594}, {-10.841995239257812,58.20718765258789}, {-10.278066635131836,46.99126434326172}, {-11.050857543945312,46.94948959350586}, {-11.259720802307129,52.5470085144043}, {-16.376855850219727,52.567893981933594}, {-17.291698455810547,57.85263442993164}, {-13.030899047851562,58.128334045410156}, {-13.331661224365234,62.84027099609375}, {8.899679183959961,64.24382781982422}, {9.991085052490234,45.58598709106445}, {5.208131790161133,45.230918884277344}, {5.479652404785156,41.57582473754883}, {4.730260848999023,41.55165100097656} };
	std::vector<Point> col_race_car1 ={{38.602317810058594,28.38249397277832}, {39.87422180175781,29.8681640625}, {39.703208923339844,31.214887619018555}, {36.73316192626953,33.32176971435547}, {35.492027282714844,33.16144561767578}, {34.391136169433594,31.94169044494629}, {34.669029235839844,30.210189819335938}, {37.159400939941406,28.286298751831055}, {38.602317810058594,28.38249397277832}};
	std::vector<Point> col_race_car2 ={{59.32638931274414,30.346824645996094}, {59.95249557495117,30.695356369018555}, {60.41573715209961,32.404781341552734}, {60.13551330566406,32.97074508666992}, {55.48548126220703,34.10771942138672}, {54.88422393798828,33.716766357421875}, {54.506927490234375,31.844558715820312}, {55.02799987792969,31.343799591064453}, {59.32638931274414,30.346824645996094}};
	std::vector<Point> col_race_car3 ={{57.966670989990234,24.377460479736328}, {58.45310592651367,23.72719955444336}, {62.73758316040039,22.445117950439453}, {63.23417282104492,22.599599838256836}, {63.757205963134766,24.265329360961914}, {63.577789306640625,24.78641128540039}, {59.23683547973633,26.11589241027832}, {58.40593338012695,25.970863342285156}, {57.966670989990234,24.377460479736328}};
	std::vector<Point> col_race_car4 ={{62.49797439575195,17.8240909576416}, {61.73160171508789,17.5118408203125}, {61.46331787109375,16.183752059936523}, {62.00688552856445,15.535140991210938}, {66.40292358398438,14.659910202026367}, {67.03180694580078,14.866042137145996}, {67.29558563232422,16.595558166503906}, {66.99081420898438,17.076929092407227}, {62.49797439575195,17.8240909576416}};
	std::vector<Point> col_race_sofa1 ={{49.51861572265625,37.792057037353516}, {49.20046615600586,38.28078079223633}, {46.99159240722656,38.97249984741211}, {46.39594268798828,38.69828796386719}, {46.159244537353516,37.850563049316406}, {46.362064361572266,37.61094284057617}, {49.065101623535156,36.73760223388672}, {49.292789459228516,36.92072296142578}, {49.51861572265625,37.792057037353516}};
	std::vector<Point> col_race_sofa2 ={{43.21878433227539,35.13831329345703}, {43.4969482421875,34.54449462890625}, {44.34622573852539,34.31343460083008}, {44.584495544433594,34.517845153808594}, {45.43985366821289,37.22662353515625}, {45.25522232055664,37.453094482421875}, {44.382408142089844,37.67312240600586}, {43.895809173583984,37.35173034667969}, {43.21878433227539,35.13831329345703}};
	std::vector<Point> col_race_table ={{48.147254943847656,33.0036735534668}, {44.85447311401367,34.01239013671875}, {45.89651870727539,37.24823760986328}, {49.12731170654297,36.22014617919922}, {48.147254943847656,33.0036735534668}};
	std::vector<Point> col_race_tableandchair1 ={{38.13551712036133,23.38463020324707}, {35.1441650390625,22.208711624145508}, {34.53273010253906,23.618967056274414}, {37.4958610534668,24.757062911987305}, {38.13551712036133,23.38463020324707}};
	std::vector<Point> col_race_tableandchair2 ={{41.24103546142578,26.424434661865234}, {38.27790451049805,25.286338806152344}, {38.889339447021484,23.876083374023438}, {41.88069152832031,25.052001953125}, {41.24103546142578,26.424434661865234}};
	std::vector<Point> col_race_tableandchair3 ={{44.986209869384766,28.0789794921875}, {42.02307891845703,26.94088363647461}, {42.63451385498047,25.530628204345703}, {45.6258659362793,26.706546783447266}, {44.986209869384766,28.0789794921875}};
	std::vector<Point> col_race_tableandchair4 ={{58.02815628051758,21.48671531677246}, {55.03680419921875,20.3107967376709}, {54.42536926269531,21.721052169799805}, {57.38850021362305,22.859148025512695}, {58.02815628051758,21.48671531677246}};
	std::vector<Point> col_race_tableandchair5 ={{59.417633056640625,18.408491134643555}, {56.4262809753418,17.232572555541992}, {55.81484603881836,18.6428279876709}, {58.777976989746094,19.78092384338379}, {59.417633056640625,18.408491134643555}};
	std::vector<Point> col_race_tableandchair6 ={{60.80710983276367,15.255449295043945}, {57.815757751464844,14.079529762268066}, {57.204322814941406,15.489785194396973}, {60.16745376586914,16.627880096435547}, {60.80710983276367,15.255449295043945}};
	std::vector<Point> col_race_tableandchair7 ={{61.50349044799805,13.603096961975098}, {58.54035949707031,12.465002059936523}, {59.15179443359375,11.054746627807617}, {62.14314651489258,12.23066520690918}, {61.50349044799805,13.603096961975098}};
	std::vector<Point> col_race_tableandchair8 ={{63.4684944152832,9.430335998535156}, {60.477142333984375,8.254417419433594}, {59.86570739746094,9.6646728515625}, {62.82883834838867,10.802767753601074}, {63.4684944152832,9.430335998535156}};
	std::vector<Point> col_race_wall ={{51.12113952636719,37.27622604370117}, {51.781455993652344,37.01691436767578}, {58.67132568359375,40.11509323120117}, {71.26976776123047,11.522797584533691}, {60.70292282104492,6.792319297790527}, {53.167266845703125,23.734622955322266}, {49.27023696899414,22.0723819732666}, {47.88503646850586,22.589523315429688}, {47.58952713012695,23.30982780456543}, {43.94479751586914,21.733661651611328}, {44.12330627441406,21.345806121826172}, {47.31932830810547,22.74993324279785}, {47.54292678833008,22.198760986328125}, {49.277076721191406,21.525142669677734}, {52.83481979370117,23.069725036621094}, {60.2891960144043,6.016210556030273}, {71.98018646240234,11.25939655303955}, {56.517791748046875,46.083580017089844}, {27.671167373657227,33.25117111206055}, {33.43192672729492,20.25814437866211}, {46.65336608886719,26.202028274536133}, {46.523399353027344,26.52060317993164}, {33.66184616088867,20.909738540649414}, {28.23839569091797,32.946388244628906}, {49.021446228027344,42.03467559814453}, {51.12113952636719,37.27622604370117}};
	robyWall.push_back({ 0,inside_world });
	robyWall.push_back({ 0,col_chess_house });
	robyWall.push_back({ 0,col_chess_sofa });
	robyWall.push_back({ 0,col_chess_table });
	robyWall.push_back({ 0,col_chess_poll1 });
	robyWall.push_back({ 0,col_chess_poll2 });
	robyWall.push_back({ 0,col_tank_canon });
	robyWall.push_back({ 0,col_tank_tower });
	robyWall.push_back({ 0,col_tank_wall });
	robyWall.push_back({ 0,col_tarkov_human });
	robyWall.push_back({ 0,col_tarkov_poll1 });
	robyWall.push_back({ 0,col_tarkov_poll2 });
	robyWall.push_back({ 0,col_tarkov_poll3 });
	robyWall.push_back({ 0,col_tarkov_poll4 });
	robyWall.push_back({ 0,col_tarkov_poll5 });
	robyWall.push_back({ 0,col_tarkov_table });
	robyWall.push_back({ 0,col_tarkov_wall });
	robyWall.push_back({ 0,col_race_car1 });
	robyWall.push_back({ 0,col_race_car2 });
	robyWall.push_back({ 0,col_race_car3 });
	robyWall.push_back({ 0,col_race_car4 });
	robyWall.push_back({ 0,col_race_sofa1 });
	robyWall.push_back({ 0,col_race_sofa2 });
	robyWall.push_back({ 0,col_race_table });
	robyWall.push_back({ 0,col_race_tableandchair1 });
	robyWall.push_back({ 0,col_race_tableandchair2 });
	robyWall.push_back({ 0,col_race_tableandchair3 });
	robyWall.push_back({ 0,col_race_tableandchair4 });
	robyWall.push_back({ 0,col_race_tableandchair5 });
	robyWall.push_back({ 0,col_race_tableandchair6 });
	robyWall.push_back({ 0,col_race_tableandchair7 });
	robyWall.push_back({ 0,col_race_tableandchair8 });
	robyWall.push_back({ 0,col_race_wall });
	
	//sports
	std::vector<Point> sports_in = { {113.63177490234375,-51.55768966674805}, {104.56221008300781,-25.542381286621094}, {96.24769592285156,0.7869148254394531}, {90.30876159667969,26.126386642456055}, {89.91283416748047,47.30860137939453}, {91.49655151367188,76.60736846923828}, {99.88255310058594,112.62593078613281}, {108.68098449707031,142.04566955566406}, {109.78079223632812,155.793212890625}, {107.03128051757812,169.9531707763672}, {91.634033203125,181.5010986328125}, {72.11251831054688,185.76283264160156}, {52.17858123779297,179.1640167236328}, {40.76811981201172,161.56716918945312}, {38.01860809326172,143.1454620361328}, {38.98093795776367,82.93122863769531}, {40.656314849853516,1.0}, {40.656314849853516,-156.76544189453125}, {41.06874084472656,-156.76544189453125}, {41.48116683959961,-178.76150512695312}, {43.543296813964844,-200.20767211914062}, {47.94251251220703,-219.04180908203125}, {55.91608810424805,-238.28836059570312}, {62.37743377685547,-247.774169921875}, {69.93858337402344,-255.33531188964844}, {79.011962890625,-262.07159423828125}, {89.93960571289062,-267.060302734375}, {104.66817474365234,-270.6236572265625}, {118.59559631347656,-271.7285461425781}, {128.99110412597656,-270.6624755859375}, {142.25474548339844,-267.8909606933594}, {152.94482421875,-264.3276062011719}, {163.8328857421875,-257.99273681640625}, {172.14739990234375,-251.26193237304688}, {183.6293487548828,-241.75962829589844}, {195.37203979492188,-230.39881896972656}, {207.49661254882812,-216.84222412109375}, {233.15283203125,-184.53439331054688}, {502.8177185058594,154.35116577148438}, {596.6529541015625,272.4172668457031}, {606.6771850585938,289.5062255859375}, {608.8729858398438,297.62109375}, {608.1092529296875,304.2084655761719}, {603.3358154296875,312.03692626953125}, {595.31640625,313.9463195800781}, {587.0106201171875,313.75537109375}, {575.9362182617188,310.89129638671875}, {566.3893432617188,302.3945617675781}, {559.7064819335938,289.5062561035156}, {553.9783325195312,267.73931884765625}, {543.2858276367188,236.80735778808594}, {533.2615356445312,210.3624267578125}, {521.3279418945312,182.29452514648438}, {517.9865112304688,176.2799835205078}, {488.0091857910156,138.8561248779297}, {352.54437255859375,-30.474899291992188}, {342.4246520996094,-33.816314697265625}, {323.3308410644531,-42.21759033203125}, {297.93609619140625,-48.42307662963867}, {265.57208251953125,-41.7402458190918}, {233.30355834960938,-38.68523406982422}, {221.46539306640625,-48.51854705810547}, {218.31491088867188,-57.30169677734375}, {215.7290496826172,-90.45658874511719}, {210.14491271972656,-122.2771987915039}, {205.74569702148438,-162.5574951171875}, {203.5460968017578,-179.74192810058594}, {191.5857391357422,-214.3857421875}, {183.61216735839844,-238.8563690185547}, {169.5896759033203,-250.95420837402344}, {156.2545623779297,-260.5774841308594}, {141.54469299316406,-265.93902587890625}, {124.36026000976562,-269.5133972167969}, {110.3377685546875,-269.65087890625}, {91.5091552734375,-265.010009765625}, {69.10044860839844,-238.68972778320312}, {62.53695297241211,-213.76170349121094}, {64.39329528808594,-187.3751220703125}, {71.12959289550781,-167.5786590576172}, {91.4759521484375,-131.83505249023438}, {105.63592529296875,-108.4642333984375}, {113.19706726074219,-89.49263000488281}, {114.9842529296875,-71.2083969116211}, {113.63177490234375,-51.55768966674805} };
	std::vector<Point> sports_out = { {36.027008056640625,234.90223693847656}, {14.600418090820312,221.6193389892578}, {-0.6591033935546875,204.14599609375}, {-10.779403686523438,186.5935821533203}, {-17.499923706054688,162.00440979003906}, {-18.923095703125,144.1357421875}, {-16.701736450195312,1.1075458526611328}, {-16.701736450195312,-127.52362060546875}, {-15.752944946289062,-176.6703643798828}, {-14.424667358398438,-196.9742431640625}, {-12.337356567382812,-212.15469360351562}, {-7.8780975341796875,-231.509765625}, {-1.805908203125,-248.492919921875}, {5.87921142578125,-265.3811950683594}, {19.351852416992188,-284.0721435546875}, {33.48866271972656,-298.11407470703125}, {50.566680908203125,-310.4482116699219}, {68.40371704101562,-319.1769714355469}, {88.42294311523438,-325.343994140625}, {107.87290954589844,-328.28521728515625}, {128.55628967285156,-328.28521728515625}, {147.62673950195312,-325.53375244140625}, {166.41256713867188,-320.41033935546875}, {185.9573974609375,-312.0610656738281}, {203.2251739501953,-300.865478515625}, {220.49295043945312,-286.4440612792969}, {239.4077911376953,-269.2507629394531}, {258.85772705078125,-246.57493591308594}, {326.07684326171875,-162.1218719482422}, {393.29595947265625,-77.66880798339844}, {460.51507568359375,6.784255027770996}, {527.7341918945312,91.23731231689453}, {594.9533081054688,175.69036865234375}, {615.8123779296875,202.33209228515625}, {645.8570556640625,241.943603515625}, {655.6729125976562,254.593994140625}, {661.8400268554688,267.32342529296875}, {665.1463623046875,292.3033447265625}, {662.4581298828125,317.7622375488281}, {651.784423828125,339.74224853515625}, {632.7297973632812,359.8247375488281}, {607.11279296875,369.4706726074219}, {584.8955688476562,371.13104248046875}, {562.5992431640625,367.6521911621094}, {538.8006591796875,356.66217041015625}, {524.65771484375,341.93408203125}, {512.6267700195312,325.0005798339844}, {503.8764343261719,302.73992919921875}, {494.6334533691406,271.354736328125}, {472.7120666503906,214.68869018554688}, {460.7732849121094,188.8489227294922}, {452.6422424316406,177.52218627929688}, {412.1483459472656,126.08514404296875}, {363.9978332519531,66.4326171875}, {352.4172668457031,52.97750473022461}, {343.2828369140625,43.51460266113281}, {330.3161926269531,32.68271255493164}, {313.15911865234375,19.699703216552734}, {293.9775085449219,11.203631401062012}, {249.27468872070312,21.035287857055664}, {223.1832733154297,22.30032730102539}, {198.03102111816406,17.790035247802734}, {173.6790313720703,6.800016403198242}, {170.04205322265625,1.9770584106445312}, {167.4329071044922,-17.868228912353516}, {168.0654296875,-40.4017219543457}, {169.17233276367188,-59.061031341552734}, {168.3026123046875,-77.24595642089844}, {164.58656311035156,-98.67254638671875}, {159.52642822265625,-124.68490600585938}, {151.22459411621094,-151.8041534423828}, {144.66221618652344,-169.11936950683594}, {141.8158721923828,-175.68174743652344}, {138.49514770507812,-176.7095947265625}, {134.93722534179688,-174.89108276367188}, {134.77908325195312,-170.62158203125}, {139.28578186035156,-160.58033752441406}, {148.69451904296875,-134.7261199951172}, {156.5219268798828,-106.4208984375}, {160.39610290527344,-86.02215576171875}, {161.5820770263672,-64.67463684082031}, {161.34487915039062,-43.08991622924805}, {160.39608764648438,-21.109878540039062}, {160.8704833984375,-6.00848388671875}, {160.8811798095703,2.638460636138916}, {159.9217071533203,10.832337379455566}, {152.64773559570312,20.95264434814453}, {149.88046264648438,33.44489669799805}, {149.40606689453125,44.27678680419922}, {150.592041015625,68.54971313476562}, {154.3871612548828,87.36715698242188}, {161.6611328125,112.50978088378906}, {167.432861328125,132.90853881835938}, {169.2513427734375,155.4420166015625}, {166.24688720703125,176.31515502929688}, {156.75909423828125,200.8252716064453}, {141.57864379882812,218.377685546875}, {121.81241607666016,231.73963928222656}, {101.72992706298828,239.2508087158203}, {79.67083740234375,242.80874633789062}, {56.979217529296875,241.14837646484375}, {36.027008056640625,234.90223693847656} };

	sportsWall.push_back({ 1,sports_out });
	sportsWall.push_back({ 0,sports_in });

	//tank
	std::vector<Point> tank_col1 = {{-97.28660583496094,-79.29420471191406}, {-95.33956909179688,-81.6915512084961}, {-94.0785140991211,-85.50234985351562}, {-94.37449645996094,-89.49081420898438}, {-96.17425537109375,-93.0624008178711}, {-98.2960205078125,-95.03938293457031}, {-101.04116821289062,-96.48686218261719}, {-105.0220718383789,-96.9747314453125}, {-108.85612487792969,-95.91270446777344}, {-112.01667785644531,-93.4443130493164}, {-113.98644256591797,-89.9636001586914}, {-114.47189331054688,-85.99858093261719}, {-113.40586853027344,-82.13994598388672}, {-111.71056365966797,-79.78701782226562}, {-109.30054473876953,-77.8318099975586}, {-105.50242614746094,-76.57893371582031}, {-102.60417175292969,-76.68130493164062}, {-99.64824676513672,-77.59247589111328}, {-97.28660583496094,-79.29420471191406}};
	std::vector<Point> tank_col2 = {{182.27784729003906,-44.323822021484375}, {178.44271850585938,-44.793827056884766}, {174.7490692138672,-43.77069091796875}, {171.70423889160156,-41.39268493652344}, {169.80661010742188,-38.03943634033203}, {169.33892822265625,-34.2196044921875}, {170.3659210205078,-30.50226593017578}, {171.9991455078125,-28.235498428344727}, {174.32090759277344,-26.35188102722168}, {177.97994995117188,-25.14488410949707}, {180.77207946777344,-25.24350929260254}, {183.61976623535156,-26.121315002441406}, {185.89492797851562,-27.76072883605957}, {187.77066040039062,-30.07029151916504}, {188.9855499267578,-33.741539001464844}, {188.70040893554688,-37.58395767211914}, {186.966552734375,-41.02476119995117}, {184.9224853515625,-42.929351806640625}, {182.27784729003906,-44.323822021484375}};
	std::vector<Point> tank_col3 = {{23.225812911987305,49.139034271240234}, {17.183319091796875,48.39850997924805}, {11.363733291625977,50.010528564453125}, {6.566431999206543,53.757225036621094}, {3.5765795707702637,59.04048156738281}, {2.8397350311279297,65.05886840820312}, {4.457823276519775,70.91576385498047}, {7.031065940856934,74.48719787597656}, {10.689156532287598,77.4549560546875}, {16.454204559326172,79.35665893554688}, {20.853374481201172,79.2012710571289}, {25.340087890625,77.81822967529297}, {28.924747467041016,75.2352294921875}, {31.880088806152344,71.59636688232422}, {33.79420471191406,65.81208801269531}, {33.34495162963867,59.75811767578125}, {30.613147735595703,54.3369140625}, {27.39259147644043,51.33610916137695}, {23.225812911987305,49.139034271240234}};
	std::vector<Point> tank_col4 = {{-47.704315185546875,118.10320281982422}, {-51.382442474365234,117.65243530273438}, {-54.924888610839844,118.6336898803711}, {-57.84505844116211,120.91434478759766}, {-59.66501235961914,124.13031768798828}, {-60.1135368347168,127.79377746582031}, {-59.12858963012695,131.3589324951172}, {-57.56222915649414,133.53289794921875}, {-55.33551025390625,135.3394012451172}, {-51.826263427734375,136.4969940185547}, {-49.148441314697266,136.40240478515625}, {-46.41733169555664,135.56053161621094}, {-44.23530960083008,133.9882354736328}, {-42.436363220214844,131.77322387695312}, {-41.27122116088867,128.2522735595703}, {-41.54468536376953,124.56715393066406}, {-43.20756530761719,121.26720428466797}, {-45.16794967651367,119.44058990478516}, {-47.704315185546875,118.10320281982422}};
	std::vector<Point> tank_col5 = {{154.9004669189453,160.1885986328125}, {157.728271484375,160.08871459960938}, {160.6123504638672,159.19969177246094}, {162.9165802001953,157.53932189941406}, {164.8162841796875,155.20025634765625}, {166.04669189453125,151.48208618164062}, {165.75790405273438,147.590576171875}, {164.00189208984375,144.10580444335938}, {161.93170166015625,142.1768798828125}, {159.25328063964844,140.76458740234375}, {155.369140625,140.28857421875}, {151.6282958984375,141.3247833251953}, {148.54457092285156,143.73318481445312}, {146.6226806640625,147.1292724609375}, {146.14903259277344,150.9979248046875}, {147.18914794921875,154.76275634765625}, {148.84324645996094,157.05848693847656}, {151.19467163085938,158.96617126464844}, {154.9004669189453,160.1885986328125}};
	std::vector<Point> tank_col6 = {{91.4102554321289,240.24758911132812}, {92.35686492919922,243.67398071289062}, {93.86225128173828,245.76332092285156}, {96.0022964477539,247.49951171875}, {99.37494659423828,248.61203002929688}, {101.94853210449219,248.52113342285156}, {104.57333374023438,247.7120361328125}, {106.67041778564453,246.200927734375}, {108.39933776855469,244.0721435546875}, {109.51912689208984,240.688232421875}, {109.25630187988281,237.14657592773438}, {107.65815734863281,233.97508239746094}, {105.77407836914062,232.2195587158203}, {103.33644104003906,230.93423461914062}, {99.8014907836914,230.5010223388672}, {96.39693450927734,231.44407653808594}, {93.59043884277344,233.63595581054688}, {91.84132385253906,236.72674560546875}, {91.4102554321289,240.24758911132812}};
	std::vector<Point> tank_col7 = {{-139.40565490722656,218.71823120117188}, {-137.192138671875,220.5140380859375}, {-133.7036895751953,221.66476440429688}, {-131.041748046875,221.5707244873047}, {-128.32681274414062,220.73385620117188}, {-126.15773010253906,219.17086791992188}, {-124.36944580078125,216.96897888183594}, {-123.2112045288086,213.46890258789062}, {-123.48304748535156,209.8056182861328}, {-125.13607025146484,206.52523803710938}, {-127.0848388671875,204.70944213867188}, {-129.60617065429688,203.37998962402344}, {-133.2624969482422,202.931884765625}, {-136.78395080566406,203.90733337402344}, {-139.6868133544922,206.17446899414062}, {-141.49598693847656,209.3713836669922}, {-141.9418487548828,213.01312255859375}, {-140.96273803710938,216.55714416503906}, {-139.40565490722656,218.71823120117188}};
	std::vector<Point> tank_col8 = {{7.0341691970825195,21.504331588745117}, {-2.6555817127227783,31.141420364379883}, {-14.13582992553711,31.352069854736328}, {-13.819864273071289,46.3079833984375}, {-23.193645477294922,56.36636734008789}, {-41.04595184326172,56.57700729370117}, {-40.993289947509766,45.46540069580078}, {-24.24687385559082,45.36008071899414}, {-24.883872985839844,-27.217411041259766}, {-144.15609741210938,-27.027570724487305}, {-143.92153930664062,-10.68826675415039}, {-155.27293395996094,-10.613637924194336}, {-154.72691345214844,-28.777542114257812}, {-144.7262725830078,-38.350894927978516}, {-33.4538688659668,-38.38613510131836}, {-33.5185432434082,-89.88401794433594}, {-23.091529846191406,-89.6207046508789}, {-23.301435470581055,-38.200958251953125}, {-13.559019088745117,-28.458553314208984}, {-14.083171844482422,21.074249267578125}, {-3.90191912651062,20.679290771484375}, {-3.463066339492798,4.35417366027832}, {7.771427154541016,4.441941261291504}, {7.0341691970825195,21.504331588745117}};
	std::vector<Point> tank_col9 = {{-1.4940075874328613,125.2725601196289}, {-1.1906743049621582,108.51349639892578}, {-14.613086700439453,108.6651611328125}, {-24.77468490600586,98.65522003173828}, {-24.54718589782715,83.94366455078125}, {-41.837074279785156,83.64032745361328}, {-41.53374099731445,72.34124755859375}, {-23.3338623046875,72.64457702636719}, {-13.096430778503418,82.88201141357422}, {-13.551427841186523,97.7452392578125}, {0.022650837898254395,97.74523162841797}, {9.880921363830566,107.75517272949219}, {9.729251861572266,125.27255249023438}, {-1.4940075874328613,125.2725601196289}};
	std::vector<Point> tank_col11 = {{25.259845733642578,125.2229995727539}, {26.398649215698242,107.99007415771484}, {35.87043762207031,98.18915557861328}, {50.16954803466797,97.93315124511719}, {49.77922058105469,31.290660858154297}, {33.6015510559082,31.22746467590332}, {23.42731285095215,21.306005477905273}, {23.04814910888672,3.86445689201355}, {34.04391098022461,3.9908454418182373}, {34.48626708984375,20.484485626220703}, {50.411163330078125,20.48448371887207}, {60.20623779296875,30.405942916870117}, {59.953460693359375,41.338504791259766}, {62.923583984375,41.338504791259766}, {62.486785888671875,86.00100708007812}, {122.08338165283203,85.84375762939453}, {122.00755310058594,72.54267883300781}, {131.16015625,63.23209762573242}, {131.16015625,54.12162399291992}, {145.64212036132812,54.22694778442383}, {145.58946228027344,62.758148193359375}, {154.12066650390625,62.70549011230469}, {154.17332458496094,77.6087417602539}, {143.11436462402344,77.50341033935547}, {143.2196807861328,73.55379486083984}, {133.449462890625,73.54410552978516}, {133.35845947265625,86.64801025390625}, {123.05783081054688,96.69586181640625}, {60.5958366394043,96.25907135009766}, {60.49051284790039,98.94481658935547}, {50.695438385009766,108.89786529541016}, {36.89807891845703,108.79255676269531}, {36.950740814208984,125.22299194335938}, {25.259845733642578,125.2229995727539}};
	std::vector<Point> tank_col12 = {{122.41622924804688,20.627849578857422}, {122.78022766113281,-96.10425567626953}, {133.79115295410156,-96.01325225830078}, {133.26895141601562,19.96681785583496}, {145.22315979003906,20.177461624145508}, {145.0047607421875,39.614933013916016}, {131.1370086669922,39.2068977355957}, {131.38978576660156,29.159046173095703}, {122.41622924804688,20.627849578857422}};
	std::vector<Point> tank_col13 = {{77.72872161865234,199.77059936523438}, {-63.06822967529297,199.68528747558594}, {-115.0108642578125,148.33900451660156}, {-115.1146011352539,46.37146759033203}, {-103.96009063720703,46.07956314086914}, {-103.66761779785156,143.8467559814453}, {-58.96028137207031,188.70777893066406}, {77.99491119384766,187.97482299804688}, {77.72872161865234,199.77059936523438}};
	
	std::vector<Point> tank_col_outside = {{223.97811889648438,63.25165557861328}, {169.4544677734375,63.288673400878906}, {169.16506958007812,76.9866714477539}, {180.61416625976562,76.84925079345703}, {180.73626708984375,69.86907196044922}, {223.778076171875,70.15015411376953}, {224.24403381347656,264.8966979980469}, {210.30296325683594,279.47412109375}, {-181.35043334960938,279.4741516113281}, {-191.60736083984375,269.24822998046875}, {-192.50672912597656,-27.77163314819336}, {-182.57823181152344,-27.430864334106445}, {-182.18247985839844,-10.036474227905273}, {-170.69244384765625,-9.857565879821777}, {-170.97706604003906,-27.793508529663086}, {-181.35536193847656,-38.14177322387695}, {-192.67715454101562,-37.7972412109375}, {-191.7097930908203,-123.5895767211914}, {-179.7477569580078,-135.46238708496094}, {50.05998992919922,-136.33302307128906}, {50.2705078125,-65.76956939697266}, {60.87040710449219,-65.50932312011719}, {61.158592224121094,-136.59329223632812}, {210.59437561035156,-135.51425170898438}, {223.9781036376953,-122.03353118896484}, {223.97811889648438,63.25165557861328}};
	tankWall.push_back({1,tank_col_outside});
	tankWall.push_back({0, tank_col1});
	tankWall.push_back({0, tank_col2});
	tankWall.push_back({0, tank_col3});
	tankWall.push_back({0, tank_col4});
	tankWall.push_back({0, tank_col5});
	tankWall.push_back({0, tank_col6});
	tankWall.push_back({0, tank_col7});
	tankWall.push_back({0, tank_col8});
	tankWall.push_back({0, tank_col9});
	tankWall.push_back({0, tank_col11});
	tankWall.push_back({0, tank_col12});
	tankWall.push_back({0, tank_col13});

	//shooting
	std::vector<Point> F1_outside = { {40.92902755737305,34.151187896728516}, {40.98923873901367,19.449626922607422}, {41.00982666015625,19.400348663330078}, {41.059112548828125,19.379802703857422}, {59.166404724121094,19.319490432739258}, {59.21562957763672,19.298946380615234}, {59.23603057861328,19.249666213989258}, {59.257049560546875,-20.367883682250977}, {59.2366943359375,-20.417232513427734}, {59.18749237060547,-20.43796157836914}, {53.469154357910156,-20.477853775024414}, {53.419952392578125,-20.49858283996582}, {53.399559020996094,-20.547931671142578}, {53.399559020996094,-20.648630142211914}, {53.41992950439453,-20.69863510131836}, {53.46910095214844,-20.7209415435791}, {54.883583068847656,-20.776275634765625}, {54.93275451660156,-20.798582077026367}, {54.953125,-20.848587036132812}, {54.953125,-36.91436767578125}, {54.93273162841797,-36.96366882324219}, {54.88352966308594,-36.984283447265625}, {42.00189971923828,-37.044403076171875}, {41.952632904052734,-37.06501007080078}, {41.93210220336914,-37.11431884765625}, {41.87173080444336,-57.90666198730469}, {41.851200103759766,-57.95587921142578}, {41.801937103271484,-57.97625732421875}, {9.192187309265137,-57.97625732421875}, {9.142645835876465,-57.95587158203125}, {9.121466636657715,-57.90667724609375}, {9.093338966369629,-56.17341613769531}, {9.07215404510498,-56.12421417236328}, {9.022616386413574,-56.10382843017578}, {8.901522636413574,-56.10382843017578}, {8.8519868850708,-56.12421417236328}, {8.830817222595215,-56.17341613769531}, {8.802657127380371,-57.93235778808594}, {8.781487464904785,-57.98158264160156}, {8.731951713562012,-58.00199890136719}, {-29.02623748779297,-58.03227233886719}, {-29.050498962402344,-58.031837463378906}, {-29.0660343170166,-58.013214111328125}, {-29.07048225402832,-57.98335266113281}, {-29.07322883605957,-57.95146942138672}, {-29.202985763549805,-22.16629981994629}, {-29.22370147705078,-22.117095947265625}, {-29.273048400878906,-22.096710205078125}, {-43.24662780761719,-22.096710205078125}, {-43.29599380493164,-22.117095947265625}, {-43.31675338745117,-22.16629981994629}, {-43.37646484375,-29.981386184692383}, {-43.39722442626953,-30.030588150024414}, {-43.446590423583984,-30.050973892211914}, {-55.995609283447266,-30.050973892211914}, {-56.04481887817383,-30.03059196472168}, {-56.06520080566406,-29.981382369995117}, {-56.06520080566406,34.151187896728516}, {-56.04481887817383,34.20039749145508}, {-55.995609283447266,34.22077941894531}, {40.85914993286133,34.22077941894531}, {40.90843963623047,34.20039749145508}, {40.92902755737305,34.151187896728516} };
	std::vector<Point> center = { {-9.740642547607422,17.930543899536133}, {-10.730070114135742,17.44261360168457}, {-11.64734172821045,16.829710006713867}, {-12.476768493652344,16.102327346801758}, {-13.204155921936035,15.272896766662598}, {-13.817058563232422,14.355623245239258}, {-14.304987907409668,13.366199493408203}, {-14.659598350524902,12.321549415588379}, {-14.874822616577148,11.239553451538086}, {-14.946975708007812,10.13871955871582}, {-14.874822616577148,9.037885665893555}, {-14.659598350524902,7.955889701843262}, {-14.304987907409668,6.9112396240234375}, {-13.817058563232422,5.921813488006592}, {-13.204155921936035,5.004542350769043}, {-12.476768493652344,4.175114631652832}, {-11.64734172821045,3.4477286338806152}, {-10.730070114135742,2.834825038909912}, {-9.740642547607422,2.346895694732666}, {-8.69599437713623,1.992283821105957}, {-7.613996505737305,1.7770605087280273}, {-6.5131635665893555,1.7049083709716797}, {-5.412330150604248,1.7770605087280273}, {-4.330332279205322,1.992283821105957}, {-3.2856838703155518,2.346895694732666}, {-2.296257495880127,2.834825038909912}, {-1.3789844512939453,3.4477286338806152}, {-0.549558162689209,4.175114631652832}, {0.17782831192016602,5.004542350769043}, {0.7907309532165527,5.921813488006592}, {1.2786617279052734,6.9112396240234375}, {1.6332731246948242,7.955889701843262}, {1.8484954833984375,9.037885665893555}, {1.9206476211547852,10.13871955871582}, {1.8484954833984375,11.239553451538086}, {1.6332731246948242,12.321549415588379}, {1.2786617279052734,13.366199493408203}, {0.7907309532165527,14.355623245239258}, {0.17782831192016602,15.272896766662598}, {-0.549558162689209,16.102327346801758}, {-1.3789844512939453,16.829710006713867}, {-2.296257495880127,17.44261360168457}, {-3.2856838703155518,17.930543899536133}, {-4.330332279205322,18.28515625}, {-5.412330150604248,18.500377655029297}, {-6.5131635665893555,18.572532653808594}, {-7.613996505737305,18.500377655029297}, {-8.69599437713623,18.28515625}, {-9.740642547607422,17.930543899536133} };
	std::vector<Point> stairnaname1 = { {-53.26775360107422,-21.947656631469727}, {-56.18739318847656,-21.95584487915039}, {-56.34386444091797,-21.902080535888672}, {-56.40869140625,-21.771289825439453}, {-56.34386444091797,-21.64029312133789}, {-56.18739318847656,-21.58603286743164}, {-52.84172821044922,-21.58603286743164}, {-52.68524169921875,-21.64029312133789}, {-52.62042999267578,-21.771289825439453}, {-52.62042999267578,-26.473093032836914}, {-52.55561828613281,-26.60436248779297}, {-52.399131774902344,-26.65928077697754}, {-47.54126739501953,-26.679718017578125}, {-47.384796142578125,-26.734636306762695}, {-47.319969177246094,-26.86590576171875}, {-47.319969177246094,-27.005619049072266}, {-47.384796142578125,-27.136615753173828}, {-47.54126739501953,-27.190876007080078}, {-52.825157165527344,-27.190876007080078}, {-52.98164367675781,-27.136615753173828}, {-53.04645538330078,-27.005619049072266}, {-53.04645538330078,-22.132211685180664}, {-53.11126708984375,-22.001419067382812}, {-53.26775360107422,-21.947656631469727} };
	std::vector<Point> stairnaname2 = { {37.61503219604492,-20.00670051574707}, {37.558746337890625,-20.121545791625977}, {37.58268737792969,-25.186771392822266}, {37.526405334472656,-25.30161476135254}, {37.38943862915039,-25.349185943603516}, {32.596431732177734,-25.349185943603516}, {32.4592399597168,-25.396757125854492}, {32.40241241455078,-25.51160430908203}, {32.40241241455078,-25.595928192138672}, {32.4592399597168,-25.710773468017578}, {32.596431732177734,-25.758344650268555}, {37.75199890136719,-25.758344650268555}, {37.889190673828125,-25.710773468017578}, {37.946014404296875,-25.595928192138672}, {37.946014404296875,-20.121545791625977}, {37.889190673828125,-20.00670051574707}, {37.75199890136719,-19.959129333496094}, {37.61503219604492,-20.00670051574707} };
	std::vector<Point> stairwall1 = { {21.27896499633789,-0.22923994064331055}, {21.27896499633789,-9.451610565185547}, {21.328569412231445,-9.527350425720215}, {21.448320388793945,-9.558723449707031}, {25.12465476989746,-9.558723449707031}, {25.244264602661133,-9.527350425720215}, {25.29352378845215,-9.451610565185547}, {25.25188446044922,-0.2503070831298828}, {25.20193862915039,-0.17456531524658203}, {25.08204460144043,-0.14319324493408203}, {24.96229362487793,-0.17456531524658203}, {24.912691116333008,-0.2503070831298828}, {24.912691116333008,-9.248137474060059}, {24.863088607788086,-9.323878288269043}, {24.743335723876953,-9.35525131225586}, {21.808208465576172,-9.35525131225586}, {21.688457489013672,-9.323878288269043}, {21.63885498046875,-9.248137474060059}, {21.63885498046875,-0.22923994064331055}, {21.589252471923828,-0.15349817276000977}, {21.469499588012695,-0.12212610244750977}, {21.448320388793945,-0.12212610244750977}, {21.328569412231445,-0.15349817276000977}, {21.27896499633789,-0.22923994064331055} };
	std::vector<Point> stairwall2 = { {25.112560272216797,14.462875366210938}, {25.094741821289062,14.46236801147461}, {24.96864891052246,14.491836547851562}, {24.916419982910156,14.570178985595703}, {24.916419982910156,23.811853408813477}, {24.864139556884766,23.89168357849121}, {24.737918853759766,23.92474937438965}, {21.808731079101562,23.92474937438965}, {21.682510375976562,23.89168357849121}, {21.63022804260254,23.811853408813477}, {21.63022804260254,14.59813117980957}, {21.57794761657715,14.51829719543457}, {21.45172691345215,14.485231399536133}, {21.32550621032715,14.51829719543457}, {21.273223876953125,14.59813117980957}, {21.273223876953125,24.086740493774414}, {21.32550621032715,24.166574478149414}, {21.45172691345215,24.19964027404785}, {25.11237907409668,24.19964027404785}, {25.238595962524414,24.166574478149414}, {25.29088020324707,24.086740493774414}, {25.29088020324707,14.580865859985352}, {25.238649368286133,14.499540328979492}, {25.112560272216797,14.462875366210938} };
	std::vector<Point> stairwall3 = { {-37.71170425415039,15.130216598510742}, {-37.71170425415039,24.56198501586914}, {-37.763458251953125,24.64101219177246}, {-37.888404846191406,24.67374610900879}, {-41.553897857666016,24.67374610900879}, {-41.6788444519043,24.64101219177246}, {-41.73059844970703,24.56198501586914}, {-41.73059844970703,15.138262748718262}, {-41.6788444519043,15.059235572814941}, {-41.553897857666016,15.026501655578613}, {-41.5234375,15.026501655578613}, {-41.39849090576172,15.059235572814941}, {-41.34673309326172,15.138262748718262}, {-41.34673309326172,24.358722686767578}, {-41.294979095458984,24.4377498626709}, {-41.1700325012207,24.470483779907227}, {-38.24140548706055,24.470483779907227}, {-38.116458892822266,24.4377498626709}, {-38.06470489501953,24.358722686767578}, {-38.06470489501953,15.119531631469727}, {-38.01300811767578,15.042069435119629}, {-37.88820266723633,15.013113021850586}, {-37.763397216796875,15.049625396728516}, {-37.71170425415039,15.130216598510742} };
	std::vector<Point> stairwall4 = { {-38.076683044433594,0.040430545806884766}, {-38.076683044433594,-9.204456329345703}, {-38.13414764404297,-9.292197227478027}, {-38.27287292480469,-9.328540802001953}, {-41.14544677734375,-9.328540802001953}, {-41.28417205810547,-9.292197227478027}, {-41.34163284301758,-9.204456329345703}, {-41.34163284301758,0.014968395233154297}, {-41.39909362792969,0.10270977020263672}, {-41.537818908691406,0.1390533447265625}, {-41.58293151855469,0.1390533447265625}, {-41.721656799316406,0.10270977020263672}, {-41.77912139892578,0.014968395233154297}, {-41.77912139892578,-9.435785293579102}, {-41.721656799316406,-9.523526191711426}, {-41.58293151855469,-9.559869766235352}, {-37.837890625,-9.559869766235352}, {-37.69932174682617,-9.523527145385742}, {-37.64224624633789,-9.435785293579102}, {-37.68376541137695,0.04043102264404297}, {-37.74161148071289,0.12817096710205078}, {-37.880496978759766,0.16451501846313477}, {-38.019222259521484,0.1281719207763672}, {-38.076683044433594,0.040430545806884766} };
	std::vector<Point> stairwall5 = { {-29.216588973999023,-22.217424392700195}, {-26.020307540893555,-22.217424392700195}, {-25.907869338989258,-22.24688720703125}, {-25.861330032348633,-22.318012237548828}, {-25.866716384887695,-31.467039108276367}, {-25.82017707824707,-31.538166046142578}, {-25.707738876342773,-31.567626953125}, {-25.59528160095215,-31.538164138793945}, {-25.548702239990234,-31.467037200927734}, {-25.548702239990234,-22.091075897216797}, {-25.59528160095215,-22.01995086669922}, {-25.707738876342773,-21.99048614501953}, {-29.216585159301758,-21.99048614501953}, {-29.329042434692383,-22.01995086669922}, {-29.37562370300293,-22.091075897216797}, {-29.37562370300293,-22.116836547851562}, {-29.32904624938965,-22.18796157836914}, {-29.216588973999023,-22.217424392700195} };
	std::vector<Point> stairwall6 = { {32.74445343017578,-22.00218391418457}, {32.84437942504883,-22.02835464477539}, {32.885765075683594,-22.091552734375}, {32.885765075683594,-28.655258178710938}, {32.927154541015625,-28.71861457824707}, {33.027076721191406,-28.74517059326172}, {41.180999755859375,-28.77589988708496}, {41.280921936035156,-28.750097274780273}, {41.32231140136719,-28.687053680419922}, {41.32231140136719,-20.801769256591797}, {41.36370086669922,-20.738569259643555}, {41.463623046875,-20.712390899658203}, {50.28561019897461,-20.712390899658203}, {50.385536193847656,-20.68621253967285}, {50.42692184448242,-20.62301254272461}, {50.42692184448242,-20.563274383544922}, {50.385536193847656,-20.500076293945312}, {50.28561019897461,-20.473896026611328}, {41.22624206542969,-20.473896026611328}, {41.126319885253906,-20.500076293945312}, {41.08492660522461,-20.563274383544922}, {41.08492660522461,-28.4138126373291}, {41.04353332519531,-28.477012634277344}, {40.94361114501953,-28.503189086914062}, {33.215457916259766,-28.503189086914062}, {33.11553955078125,-28.477012634277344}, {33.07414245605469,-28.4138126373291}, {33.07414245605469,-21.838184356689453}, {33.032752990722656,-21.77498435974121}, {32.932830810546875,-21.74880599975586}, {5.324227333068848,-21.74880599975586}, {5.224480628967285,-21.77498435974121}, {5.183515548706055,-21.838184356689453}, {5.246555328369141,-31.458696365356445}, {5.288370132446289,-31.521896362304688}, {5.388469696044922,-31.548072814941406}, {5.4883928298950195,-31.521894454956055}, {5.529783248901367,-31.458694458007812}, {5.529783248901367,-22.093624114990234}, {5.571172714233398,-22.030420303344727}, {5.671095848083496,-22.004234313964844}, {32.74445343017578,-22.00218391418457} };
	std::vector<Point> stairwall7 = { {8.793684005737305,-50.21733093261719}, {8.793684005737305,-22.34910011291504}, {8.819158554077148,-22.31035614013672}, {8.880668640136719,-22.29461669921875}, {8.942169189453125,-22.31110382080078}, {8.967643737792969,-22.350160598754883}, {8.967643737792969,-50.21733093261719}, {8.942168235778809,-50.256229400634766}, {8.880664825439453,-50.27234649658203}, {8.819160461425781,-50.256229400634766}, {8.793684005737305,-50.21733093261719} };
	std::vector<Point> stairwall8 = { {8.864524841308594,-52.704986572265625}, {8.851061820983887,-52.68442916870117}, {8.851061820983887,-50.26509094238281}, {8.864524841308594,-50.24454116821289}, {8.897029876708984,-50.236053466796875}, {35.10143280029297,-50.257484436035156}, {35.133949279785156,-50.248992919921875}, {35.147430419921875,-50.22844696044922}, {35.167335510253906,-29.298715591430664}, {35.180816650390625,-29.278156280517578}, {35.21333312988281,-29.26963996887207}, {48.362388610839844,-29.26963996887207}, {48.394893646240234,-29.261125564575195}, {48.408355712890625,-29.24056625366211}, {48.408355712890625,-20.64694595336914}, {48.42182159423828,-20.626386642456055}, {48.45432662963867,-20.61787223815918}, {48.4868278503418,-20.626386642456055}, {48.50029373168945,-20.64694595336914}, {48.50029373168945,-29.366355895996094}, {48.4868278503418,-29.38691520690918}, {48.45432662963867,-29.395429611206055}, {35.3032341003418,-29.395429611206055}, {35.270729064941406,-29.403945922851562}, {35.25726318359375,-29.424503326416016}, {35.25726318359375,-50.33083724975586}, {35.24380111694336,-50.35139846801758}, {35.21129608154297,-50.35990905761719}, {9.072480201721191,-50.35990905761719}, {9.0399751663208,-50.36842727661133}, {9.026512145996094,-50.38898468017578}, {9.026512145996094,-52.68442916870117}, {9.01304817199707,-52.704986572265625}, {8.98054313659668,-52.7135009765625}, {8.897029876708984,-52.7135009765625}, {8.864524841308594,-52.704986572265625} };
	std::vector<Point> stairwall9 = { {37.74722671508789,25.740570068359375}, {37.6441764831543,25.77623748779297}, {37.60111618041992,25.862342834472656}, {37.57638931274414,30.562063217163086}, {37.533329010009766,30.648168563842773}, {37.43028259277344,30.683835983276367}, {32.72444534301758,30.683835983276367}, {32.621585845947266,30.719501495361328}, {32.5789794921875,30.80560874938965}, {32.5789794921875,34.32488250732422}, {32.621585845947266,34.410987854003906}, {32.72444534301758,34.4466552734375}, {32.827308654785156,34.410987854003906}, {32.86991500854492,34.32488250732422}, {32.86991500854492,31.203155517578125}, {32.91252136230469,31.117048263549805}, {33.015380859375,31.08138084411621}, {37.77235794067383,31.08138084411621}, {37.87521743774414,31.04571533203125}, {37.917823791503906,30.95960807800293}, {37.917823791503906,25.862342834472656}, {37.87521743774414,25.77623748779297}, {37.77235794067383,25.740570068359375}, {37.74722671508789,25.740570068359375} };

	tarkovWall.push_back({ 1,F1_outside });
	tarkovWall.push_back({ 0,center });
	tarkovWall.push_back({ 0,stairnaname1 });
	tarkovWall.push_back({ 0,stairnaname2 });
	tarkovWall.push_back({ 0,stairwall1 });
	tarkovWall.push_back({ 0,stairwall2 });
	tarkovWall.push_back({ 0,stairwall3 });
	tarkovWall.push_back({ 0,stairwall4 });
	tarkovWall.push_back({ 0,stairwall5 });
	tarkovWall.push_back({ 0,stairwall6 });
	tarkovWall.push_back({ 0,stairwall7 });
	tarkovWall.push_back({ 0,stairwall8 });
	tarkovWall.push_back({ 0,stairwall9 });

	std::vector<Point> col2_1 = { {4.875383377075195,-21.693742752075195}, {-25.269935607910156,-21.693742752075195}, {-25.52477264404297,-21.76050567626953}, {-25.630327224731445,-21.92168426513672}, {-25.52477264404297,-22.08286476135254}, {-25.269935607910156,-22.149625778198242}, {4.875383377075195,-22.149625778198242}, {5.130219459533691,-22.08286476135254}, {5.235774993896484,-21.92168426513672}, {5.130219459533691,-21.76050567626953}, {4.875383377075195,-21.693742752075195} };
	std::vector<Point> col2_2 = { {-47.931053161621094,-22.606834411621094}, {-48.07634353637695,-22.647415161132812}, {-48.13652038574219,-22.74037742614746}, {-48.13652038574219,-57.29969024658203}, {-48.076316833496094,-57.39161682128906}, {-47.930973052978516,-57.42969512939453}, {-29.54947280883789,-57.42969512939453}, {-29.404132843017578,-57.39161682128906}, {-29.34392738342285,-57.29969024658203}, {-29.34392738342285,-22.625885009765625}, {-29.404132843017578,-22.533992767333984}, {-29.54947280883789,-22.495994567871094}, {-37.526268005371094,-22.500301361083984}, {-37.671607971191406,-22.462303161621094}, {-37.731815338134766,-22.370410919189453}, {-37.731815338134766,-22.000024795532227}, {-37.671607971191406,-21.908098220825195}, {-37.526268005371094,-21.87002182006836}, {-29.37285041809082,-21.87002182006836}, {-29.227508544921875,-21.908098220825195}, {-29.16730499267578,-22.000024795532227}, {-29.16730499267578,-57.47734832763672}, {-29.227508544921875,-57.56927490234375}, {-29.37285041809082,-57.60735321044922}, {-48.156105041503906,-57.60735321044922}, {-48.30139923095703,-57.56927490234375}, {-48.361488342285156,-57.47734832763672}, {-48.31782531738281,-22.27962875366211}, {-48.37791442871094,-22.18770408630371}, {-48.52320861816406,-22.149625778198242}, {-52.723819732666016,-22.149625778198242}, {-52.86915969848633,-22.111549377441406}, {-52.92936325073242,-22.019622802734375}, {-52.86915969848633,-21.927696228027344}, {-52.723819732666016,-21.889617919921875}, {-39.656803131103516,-21.889617919921875}, {-39.5114631652832,-21.927696228027344}, {-39.45125961303711,-22.019622802734375}, {-39.45125961303711,-22.330778121948242}, {-39.511444091796875,-22.42374038696289}, {-39.6567268371582,-22.46432113647461}, {-47.931053161621094,-22.606834411621094} };
	std::vector<Point> col2_3 = { {-41.4379768371582,-8.67891788482666}, {-41.424537658691406,23.82257843017578}, {-41.56587219238281,24.363723754882812}, {-41.90752410888672,24.589502334594727}, {-42.896297454833984,24.59519386291504}, {-43.23741149902344,24.37335205078125}, {-43.377437591552734,23.833843231201172}, {-43.290714263916016,-6.852461814880371}, {-43.191490173339844,-7.554747581481934}, {-42.95499801635742,-8.169569969177246}, {-42.587039947509766,-8.641032218933105}, {-42.17042922973633,-8.99720287322998}, {-41.88930130004883,-9.168402671813965}, {-41.57029724121094,-9.138800621032715}, {-41.4379768371582,-8.67891788482666} };
	std::vector<Point> col2_4 = { {-55.87944793701172,33.86640167236328}, {32.80353927612305,33.86640167236328}, {32.93362808227539,33.95332717895508}, {32.98185348510742,34.16318130493164}, {32.91997146606445,34.37303161621094}, {32.78422927856445,34.4599609375}, {-56.335330963134766,34.4599609375}, {-56.46823501586914,34.372920989990234}, {-56.52328872680664,34.16278839111328}, {-56.523284912109375,-21.86623764038086}, {-56.46823501586914,-22.07636833190918}, {-56.335330963134766,-22.163408279418945}, {-56.2553596496582,-22.163408279418945}, {-56.12245178222656,-22.07636833190918}, {-56.06740188598633,-21.86623764038086}, {-56.06740188598633,33.56923294067383}, {-56.012351989746094,33.77936553955078}, {-55.87944793701172,33.86640167236328} };
	std::vector<Point> col2_5 = { {33.04555892944336,23.973691940307617}, {33.12116241455078,24.023204803466797}, {33.15248107910156,24.14274024963379}, {33.15248107910156,26.92562484741211}, {33.18379592895508,27.045162200927734}, {33.2593994140625,27.094675064086914}, {40.911338806152344,27.094675064086914}, {40.986942291259766,27.045162200927734}, {41.01826095581055,26.92562484741211}, {41.01826095581055,14.84864616394043}, {40.986942291259766,14.729109764099121}, {40.911338806152344,14.679596900939941}, {33.25478744506836,14.679596900939941}, {33.17918395996094,14.729110717773438}, {33.14786911010742,14.84864616394043}, {33.14786911010742,22.240270614624023}, {33.11655044555664,22.35980796813965}, {33.04094696044922,22.409320831298828}, {32.93974304199219,22.409320831298828}, {32.864139556884766,22.359806060791016}, {32.832820892333984,22.240270614624023}, {32.832820892333984,-17.285274505615234}, {32.864139556884766,-17.404808044433594}, {32.93974304199219,-17.454322814941406}, {33.002803802490234,-17.454322814941406}, {33.07841110229492,-17.40480613708496}, {33.10972595214844,-17.2852725982666}, {33.10972595214844,-9.654587745666504}, {33.14104080200195,-9.535050392150879}, {33.21664810180664,-9.4855375289917}, {40.93995666503906,-9.4855375289917}, {41.01556396484375,-9.535050392150879}, {41.046878814697266,-9.654587745666504}, {41.046878814697266,-21.770383834838867}, {41.01556396484375,-21.889917373657227}, {40.93995666503906,-21.93943214416504}, {33.151302337646484,-21.93943214416504}, {33.0756950378418,-21.889917373657227}, {33.04438018798828,-21.770383834838867}, {33.04438018798828,-19.29034996032715}, {33.013065338134766,-19.170820236206055}, {32.93745803833008,-19.12130355834961}, {32.861854553222656,-19.170822143554688}, {32.83053970336914,-19.29035186767578}, {32.83053970336914,-25.487258911132812}, {32.861854553222656,-25.606792449951172}, {32.93745803833008,-25.656307220458984}, {32.94548416137695,-25.656307220458984}, {33.021087646484375,-25.60679054260254}, {33.052406311035156,-25.48725700378418}, {33.052406311035156,-22.194795608520508}, {33.08372116088867,-22.075258255004883}, {33.159324645996094,-22.025747299194336}, {41.05097961425781,-22.025747299194336}, {41.126583099365234,-21.976240158081055}, {41.157901763916016,-21.85670280456543}, {41.157901763916016,-9.486990928649902}, {41.126583099365234,-9.367457389831543}, {41.05097961425781,-9.317940711975098}, {33.313899993896484,-9.317940711975098}, {33.23822784423828,-9.268425941467285}, {33.20674133300781,-9.148892402648926}, {33.17342758178711,14.335434913635254}, {33.20457458496094,14.454970359802246}, {33.28010559082031,14.504484176635742}, {41.101566314697266,14.504484176635742}, {41.17716979980469,14.553997039794922}, {41.20848846435547,14.67353343963623}, {41.20848846435547,27.17092514038086}, {41.17716979980469,27.29046058654785}, {41.101566314697266,27.339975357055664}, {33.2593994140625,27.339975357055664}, {33.18379592895508,27.389488220214844}, {33.1524772644043,27.509023666381836}, {33.1524772644043,30.9055118560791}, {33.12116241455078,31.025049209594727}, {33.04555892944336,31.074562072753906}, {32.942928314208984,31.074562072753906}, {32.86732482910156,31.025049209594727}, {32.83600616455078,30.9055118560791}, {32.83600997924805,24.14274024963379}, {32.86732482910156,24.023202896118164}, {32.942928314208984,23.973690032958984}, {33.04555892944336,23.973691940307617} };
	std::vector<Point> col2_6 = { {20.899274826049805,23.906028747558594}, {21.091699600219727,23.89626693725586}, {21.159658432006836,23.715991973876953}, {21.063335418701172,23.470802307128906}, {0.08400237560272217,-5.269041538238525}, {-0.04211972653865814,-5.545369625091553}, {-0.04610520601272583,-5.800826549530029}, {1.127506971359253,-9.229976654052734}, {1.260833501815796,-9.400084495544434}, {1.4662094116210938,-9.470365524291992}, {21.299335479736328,-9.446582794189453}, {21.48058319091797,-9.531946182250977}, {21.555660247802734,-9.738472938537598}, {21.555662155151367,-11.021649360656738}, {21.48061752319336,-11.228262901306152}, {21.299448013305664,-11.313846588134766}, {1.5227429866790771,-11.313846588134766}, {1.3037755489349365,-11.255558967590332}, {1.1374824047088623,-11.114834785461426}, {-0.3401191234588623,-8.8361234664917}, {-0.44188833236694336,-8.615455627441406}, {-0.5050805807113647,-8.364168167114258}, {-0.6423737406730652,-7.320740699768066}, {-0.659176766872406,-7.038593292236328}, {-0.648950457572937,-6.743422985076904}, {-0.5403280258178711,-5.616476535797119}, {-0.45735064148902893,-5.315994739532471}, {-0.2985115647315979,-5.0210113525390625}, {20.695100784301758,23.739553451538086}, {20.899274826049805,23.906028747558594} };
	std::vector<Point> col2_7 = { {14.9456787109375,28.596576690673828}, {9.004447937011719,18.288291931152344}, {8.895208358764648,18.143692016601562}, {8.75560188293457,18.009950637817383}, {8.57530403137207,17.898677825927734}, {8.367816925048828,17.808320999145508}, {8.274967193603516,17.77737045288086}, {8.039621353149414,17.722972869873047}, {7.792049407958984,17.698516845703125}, {7.758207321166992,17.698081970214844}, {7.514900207519531,17.722389221191406}, {7.289850234985352,17.785717010498047}, {7.174882888793945,17.834989547729492}, {6.982522964477539,17.9384765625}, {6.818143844604492,18.05972671508789}, {4.021354675292969,20.648130416870117}, {3.8643112182617188,20.77519416809082}, {3.689666748046875,20.89270782470703}, {-1.9870729446411133,24.253337860107422}, {-2.193552017211914,24.338882446289062}, {-2.4274463653564453,24.388765335083008}, {-8.879457473754883,25.017135620117188}, {-9.122598648071289,25.009822845458984}, {-9.351404190063477,24.95728874206543}, {-15.364356994628906,22.633333206176758}, {-15.559718132019043,22.533700942993164}, {-15.722116470336914,22.412689208984375}, {-20.56302261352539,17.674781799316406}, {-20.73575210571289,17.584896087646484}, {-20.9560546875,17.56041717529297}, {-21.295299530029297,17.589492797851562}, {-21.540538787841797,17.627872467041016}, {-21.77346420288086,17.689739227294922}, {-22.051132202148438,17.786922454833984}, {-22.249801635742188,17.882537841796875}, {-22.412336349487305,18.002384185791016}, {-22.7918701171875,18.38191795349121}, {-22.922855377197266,18.52106475830078}, {-23.04535675048828,18.663265228271484}, {-23.369035720825195,19.064342498779297}, {-23.482553482055664,19.209617614746094}, {-23.59185028076172,19.356182098388672}, {-30.62171745300293,29.10805892944336}, {-30.697803497314453,29.259809494018555}, {-30.731143951416016,29.417604446411133}, {-30.737014770507812,29.722761154174805}, {-30.714025497436523,29.882081985473633}, {-30.65412139892578,30.037511825561523}, {-30.582807540893555,30.164100646972656}, {-30.48390007019043,30.312969207763672}, {-30.366762161254883,30.45644760131836}, {-30.300081253051758,30.5280704498291}, {-30.159744262695312,30.66312026977539}, {-30.004840850830078,30.791641235351562}, {-29.947994232177734,30.83427619934082}, {-29.756118774414062,30.921884536743164}, {-29.52652359008789,30.958160400390625}, {13.852733612060547,30.95494270324707}, {14.098352432250977,30.930557250976562}, {14.328910827636719,30.871713638305664}, {14.40733528137207,30.842041015625}, {14.601940155029297,30.742679595947266}, {14.760747909545898,30.6204776763916}, {14.878938674926758,30.497987747192383}, {14.982856750488281,30.353069305419922}, {15.044952392578125,30.198863983154297}, {15.105981826782227,29.897106170654297}, {15.130239486694336,29.735958099365234}, {15.142818450927734,29.574275970458984}, {15.148181915283203,29.373140335083008}, {15.139167785644531,29.21169090270996}, {15.111297607421875,29.05110740661621}, {15.074649810791016,28.908830642700195}, {15.019807815551758,28.751110076904297}, {14.9456787109375,28.596576690673828} };
	std::vector<Point> col2_8 = { {-12.499674797058105,-7.723263740539551}, {-12.555079460144043,-7.952356338500977}, {-12.642580032348633,-8.177409172058105}, {-13.308048248291016,-9.519250869750977}, {-13.445948600769043,-9.733049392700195}, {-13.623031616210938,-9.934971809387207}, {-14.915815353393555,-11.156644821166992}, {-15.168461799621582,-11.293572425842285}, {-15.488788604736328,-11.35046100616455}, {-35.18267059326172,-11.366059303283691}, {-35.522708892822266,-11.32031536102295}, {-35.82294464111328,-11.209466934204102}, {-36.61362075805664,-10.753571510314941}, {-36.86216354370117,-10.584404945373535}, {-37.07740783691406,-10.397871017456055}, {-37.80808639526367,-9.640070915222168}, {-37.83579635620117,-9.499263763427734}, {-37.63159942626953,-9.440492630004883}, {-15.908317565917969,-9.395554542541504}, {-15.59830093383789,-9.334476470947266}, {-15.370546340942383,-9.188096046447754}, {-12.98111343383789,-6.275819778442383}, {-12.910919189453125,-6.069139003753662}, {-12.981282234191895,-5.862481594085693}, {-37.823970794677734,24.377986907958984}, {-37.84663391113281,24.553417205810547}, {-37.661277770996094,24.684703826904297}, {-37.37685012817383,24.694820404052734}, {-37.16035079956055,24.577716827392578}, {-12.642769813537598,-5.555296421051025}, {-12.517112731933594,-5.769791126251221}, {-12.452007293701172,-5.994800090789795}, {-12.394930839538574,-6.590034008026123}, {-12.388751029968262,-6.822332382202148}, {-12.405352592468262,-7.054426670074463}, {-12.499674797058105,-7.723263740539551} };
	std::vector<Point> col2_9 = { {12.173002243041992,-22.070106506347656}, {9.062066078186035,-22.070106506347656}, {8.9542818069458,-22.098344802856445}, {8.909636497497559,-22.16651725769043}, {8.909636497497559,-58.112823486328125}, {8.9542818069458,-58.180992126464844}, {9.062066078186035,-58.209232330322266}, {24.859437942504883,-58.209232330322266}, {24.96735382080078,-58.180992126464844}, {25.012317657470703,-58.112823486328125}, {25.14748764038086,-29.18215560913086}, {25.192453384399414,-29.113985061645508}, {25.300369262695312,-29.08574676513672}, {32.870094299316406,-29.08574676513672}, {32.97787857055664,-29.057510375976562}, {33.022525787353516,-28.989337921142578}, {33.022525787353516,-28.851747512817383}, {32.97787857055664,-28.7835750579834}, {32.870094299316406,-28.75533676147461}, {25.300552368164062,-28.75533676147461}, {25.192768096923828,-28.727100372314453}, {25.148120880126953,-28.65892791748047}, {25.148120880126953,-22.159902572631836}, {25.103477478027344,-22.091732025146484}, {24.99569320678711,-22.063493728637695}, {14.149686813354492,-22.063493728637695}, {14.041902542114258,-22.091732025146484}, {13.9972562789917,-22.159902572631836}, {13.9972562789917,-22.195117950439453}, {14.041902542114258,-22.263290405273438}, {14.149686813354492,-22.291526794433594}, {24.765262603759766,-22.291526794433594}, {24.873044967651367,-22.319766998291016}, {24.917692184448242,-22.387937545776367}, {24.917692184448242,-57.888275146484375}, {24.873044967651367,-57.95644760131836}, {24.765262603759766,-57.98468780517578}, {9.216407775878906,-57.98468780517578}, {9.108624458312988,-57.95644760131836}, {9.063977241516113,-57.888275146484375}, {9.063977241516113,-22.35933494567871}, {9.108624458312988,-22.291162490844727}, {9.216407775878906,-22.26292610168457}, {12.173002243041992,-22.26292610168457}, {12.280786514282227,-22.23468780517578}, {12.325432777404785,-22.16651725769043}, {12.280786514282227,-22.098344802856445}, {12.173002243041992,-22.070106506347656} };
	std::vector<Point> col2_10 = { {24.963499069213867,23.344053268432617}, {25.02920913696289,-9.234025001525879}, {25.430177688598633,-9.173644065856934}, {25.83708953857422,-9.000195503234863}, {26.206087112426758,-8.798022270202637}, {26.49587059020996,-8.527739524841309}, {26.706668853759766,-8.251425743103027}, {26.88564682006836,-7.982068061828613}, {26.916399002075195,23.33279037475586}, {26.775066375732422,23.87393569946289}, {26.433412551879883,24.099714279174805}, {25.444643020629883,24.105405807495117}, {25.10352897644043,23.883563995361328}, {24.963499069213867,23.344053268432617} };

	tarkovWall2.push_back({ 0,col2_1 });
	tarkovWall2.push_back({ 0,col2_2 });
	tarkovWall2.push_back({ 0,col2_3 });
	tarkovWall2.push_back({ 0,col2_4 });
	tarkovWall2.push_back({ 0,col2_5 });
	tarkovWall2.push_back({ 0,col2_6 });
	tarkovWall2.push_back({ 0,col2_7 });
	tarkovWall2.push_back({ 0,col2_8 });
	tarkovWall2.push_back({ 0,col2_9 });
	tarkovWall2.push_back({ 0,col2_10 });

	stair1 = { {-29.2292f,-30.8009f,0.163281f}, {-25.7989f,-30.8009f,0.163281f}, {-29.2292f,-22.8176f,5.88035f}, {-25.7989f,-22.8176f,5.88035f} };
	stair2 = { {5.47152f,-30.8009f,0.163281f}, {8.90186f,-30.8009f,0.163281f}, {5.47152f,-22.8176f,5.88035f}, {8.90186f,-22.8176f,5.88035f} };
	stair3 = { {21.5594f,-0.79951f,0.163281f}, {24.9898f,-0.79951f,0.163281f}, {21.5594f,-8.78282f,5.88035f}, {24.9898f,-8.78282f,5.88035f} };
	stair4 = { {21.5594f,15.2446f,0.163281f}, {24.9898f,15.2446f,0.163281f}, {21.5594f,23.2279f,5.88035f}, {24.9898f,23.2279f,5.88035f} };
	stair5 = { {-41.4201f,15.9372f,0.163281f}, {-37.9897f,15.9372f,0.163281f}, {-41.4201f,23.9205f,5.88035f}, {-37.9897f,23.9205f,5.88035f} };
	stair6 = { {-41.4201f,-0.799512f,0.163281f}, {-37.9897f,-0.799512f,0.163281f}, {-41.4201f,-8.78282f,5.88035f}, {-37.9897f,-8.78282f,5.88035f} };

	stair7 = { {-56.1938f,-26.7988f,3.03658f}, {-52.7634f,-26.7988f,3.03658f}, {-56.1935f,-22.8072f,5.89512f}, {-52.7632f,-22.8072f,5.89512f} };
	stair8 = { {37.6469f,-20.7913f,0.168282f}, {41.0772f,-20.7913f,0.168282f}, {37.6469f,-24.783f,3.02682}, {41.0772f,-24.783f,3.02682} };
	stair9 = { {37.6469f,26.1051f,0.163281f}, {41.0772f,26.1051f,0.163281f}, {37.6469f,30.0968f,3.02682f}, {41.0772f,30.0968f,3.02682f} };

	stairXMinus1 = { {37.6571f,30.7549f,3.03658f}, {37.6571f,34.1852f,3.03658f}, {33.6654f,30.7549f,5.89512f}, {33.6654f,34.1852f,5.89512f} };
	stairXMinus2 = { {37.6571f,-28.881f,3.03658f}, {37.6571f,-25.4506f,3.03658f}, {33.6654f,-28.881f,5.89512f}, {33.6654f,-25.4506f,5.89512f} };
	stairXMinus3 = { {-48.1042f,-30.2194f,0.168282f}, {-48.1042f,-26.7891f,0.168282f}, {-52.0959f,-30.2194f,3.02682f}, {-25.7989f,-26.7891f,3.02682f} };
}


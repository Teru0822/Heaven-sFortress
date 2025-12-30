#include "func.h"

extern Scene scene;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_GLContext glContext;

extern chess_stts cs;
extern chess_info ci;
extern chess_kind_piece cp;
extern Position myPosition;
extern Position lookingPosition;
extern Position canonPos;
extern vihicle tankPos;
extern vihicle sportsPos;
extern Game game[4];
extern chessInfoNet CIN;
extern u_int8_t can_get;
extern int cmap[8][8];
extern int chessMap[8][8];
extern int chessMyColor;
extern int jumpingTime;
extern int canonCoolTime;
extern int onFire_frame_count;
extern int weapon_aiming_torigger;
extern int mouseDisplayX;
extern int mouseDisplayY;
extern int chess_having;
extern int chess_get_point[2];
extern int original_turn;
extern int mainloopcount;
extern int fin;
extern int key1;
extern int key2;
extern int my_id;
extern Mix_Music* BGM_park; // 広場

extern bool pressA;
extern bool pressS;
extern bool pressD;
extern bool pressW;
extern bool doorAIM;
extern bool doorANIM;
extern bool chess_hukan;
extern bool pressSPACE;
extern bool pressSHIFT_L;
extern bool pressCTRL_L;
extern bool shotCanon;
extern bool flyingCanon;
extern bool onFire;
extern bool join;
extern bool found1;
extern bool found2;

extern float weapon_moving_anim;
extern float h1;
extern float angle;
extern float alpha;
extern float sita;

void keyDown(unsigned char key, int x, int y)
{
	if (key == 0x1b)
	{
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		glDisable(GL_COLOR_MATERIAL_FACE);
		glDisable(GL_COLOR_MATERIAL);
		exit(0);
	}
	if(key == '1')
	{
		if(scene == scene_7)
		{
			sportsPos.type = 0;
		}
		if(scene == scene_4)
		{
			if(game[1].stts == 4)
			{
				sportsPos.type = 0;
				game[1].stts = 5;
			}
		}
	}
	if(key == '2')
	{
		if(scene == scene_7)
		{
			sportsPos.type = 1;
		}
		if(scene == scene_4)
		{
			if(game[1].stts == 2)
			{
				game[1].p_NUM = 2;
				game[1].stts = 3;
			}
			if(game[1].stts == 4)
			{
				sportsPos.type = 1;
				game[1].stts = 5;
			}

			if(game[2].stts == 2)
			{
				game[2].p_NUM = 2;
				game[2].stts = 3;
			}
			if(game[3].stts == 2)
			{
				game[3].p_NUM = 2;
				game[3].stts = 3;				
			}
			
		}
	}
	if(key == '3')
	{
		if(scene == scene_4)
		{
			if(game[1].stts == 2)
			{
				game[1].p_NUM = 3;
				game[1].stts = 3;
			}
			if(game[1].stts == 4)
			{
				sportsPos.type = 2;
				game[1].stts = 5;
			}

			if(game[2].stts == 2)
			{
				game[2].p_NUM = 3;
				game[2].stts = 3;
			}
			if(game[3].stts == 2)
			{
				game[3].p_NUM = 3;
				game[3].stts = 3;
			}
		}
	}
	if(key == '4')
	{
		if(scene == scene_4)
		{
			if(game[1].stts == 2)
			{
				game[1].p_NUM = 4;
				game[1].stts = 3;
			}
			if(game[1].stts == 4)
			{
				sportsPos.type = 3;
				game[1].stts = 5;
			}
			if(game[2].stts == 2)
			{
				game[2].p_NUM = 4;
				game[2].stts = 3;
			}
			if(game[3].stts == 2)
			{
				game[3].p_NUM = 4;
				game[3].stts = 3;
			}
		}
	}

	if (key == 'w' || key == 'W' || key == 23)
	{
		if (pressA == false && pressD == false && pressW == false && pressS == false)
		{
			weapon_moving_anim = 0;
		}
		pressW = true;
	}
	if (key == 's' || key == 'S' || key == 19)
	{
		if (pressA == false && pressD == false && pressW == false && pressS == false)
		{
			weapon_moving_anim = 0;
		}
		pressS = true;
	}
	if (key == 'a' || key == 'A' || key == 1)
	{
		if (pressA == false && pressD == false && pressW == false && pressS == false)
		{
			weapon_moving_anim = 0;
		}
		pressA = true;
	}
	if (key == 'd' || key == 'D' || key == 4)
	{
		if (pressA == false && pressD == false && pressW == false && pressS == false)
		{
			weapon_moving_anim = 0;
		}
		pressD = true;
	}
	if (key == 'r' )
	{
		if (scene == scene_7)
		{
			sportsPos.x = 0;
			sportsPos.y = 0;
			sportsPos.z = 0.2;
			sportsPos.vecX = 0;
			sportsPos.vecY = -1.0;
		}
		else if(scene == scene_5)
		{
			if (chessMyColor == 0)
			{
				chessMyColor = 1;
			}
			else
			{
				chessMyColor = 0;
			}
			int k = 0;
			for (int i = 0; i < 8; i++)
			{
				int l = 0;
				for (int j = 0; j < 8; j++)
				{
					cmap[k][l] = chessMap[7 - i][7 - j];
					l++;
				}
				k++;
			}
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					chessMap[i][j] = cmap[i][j];
				}
			}
		}

	}
	if (key == 'n')
	{
		switch (scene)
		{
		case scene_1:
			scene = scene_2;
			break;
		case scene_2:
			break;
		case scene_3:
			//scene = scene_4;
			break;
		case scene_4://�L��
			// //戦車のロード
			// mainloopcount = 6;
			// //チェスのアンロード
			// UnloadChessMesh();
			// scene = scene_6;
			// myPosition.x = 0;
			// myPosition.y = 25;
			// myPosition.z = 12;
			// game[0].stts = 0;

			// lookingPosition.x = 9.0;
			// lookingPosition.y = 0;
			// lookingPosition.z = 0;

			// SDL_ShowCursor(SDL_DISABLE);
			break;
		case scene_5://�`�F�X
			// //戦車のロード
			// mainloopcount = 6;
			// //チェスのアンロード
			// UnloadChessMesh();
			// scene = scene_6;
			// myPosition.x = 0;
			// myPosition.y = 25;
			// myPosition.z = 12;
			// game[0].stts = 0;
			
			// lookingPosition.x = 9.0;
			// lookingPosition.y = 0;
			// lookingPosition.z = 0;
			// SDL_ShowCursor(SDL_DISABLE);
			break;
		case scene_6://���
			// //カーレースのロード
			// mainloopcount = 3;
			// //戦車のアンロード
			// UnloadTankMesh();
			// scene = scene_7;
			// myPosition.z = 2.7;
			break;
		case scene_7://�J�[���[�X
			// //シューティングのロード
			// mainloopcount = 5;
			// //カーレースのアンロード
			// UnloadRaceMesh();
			// scene = scene_8;
			// glViewport(0, 0, 1924, 1061);
			// glMatrixMode(GL_PROJECTION);			// �ˉe�s��𑀍삷��
			// glLoadIdentity();						// �s���������
			// gluPerspective(80.0, 1924.0 / 1061.0, 0.001, 5000);
			// glMatrixMode(GL_MODELVIEW);
			// myPosition.z = 2.5;

			break;
		default:
			break;
		}

	}
	if (key == 'y')
	{
		switch (scene)
		{
		case scene_1:
			break;
		case scene_2:
			break;
		case scene_3:
			break;
		case scene_4:
			break;
		case scene_5://チェス
			//広場のロード
			mainloopcount = 2;
			//チェスのアンロード
			UnloadChessMesh();
			game[0].stts = 0;

			SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
			SDL_ShowCursor(SDL_DISABLE);
			myPosition.z = 2.5;
			scene = scene_4;
			break;
		case scene_6://戦車
			//広場のロード
			mainloopcount = 2;
			//戦車のアンロード
			UnloadTankMesh();
			game[3].stts = 0;

			SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
			SDL_ShowCursor(SDL_DISABLE);
			myPosition.z = 2.5;
			scene = scene_4;
			break;
		case scene_7://カーレース
			//広場のロード
			mainloopcount = 2;
			//カーレースのアンロード
			UnloadRaceMesh();
			game[1].stts = 0;

			SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
			SDL_ShowCursor(SDL_DISABLE);
			myPosition.z = 2.5;
			scene = scene_4;
			break;
		case scene_8:
			//広場のロード
			mainloopcount = 2;
			//シューティングのアンロード
			UnloadShootingMesh();
			game[2].stts = 0;
			SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
			SDL_ShowCursor(SDL_DISABLE);
			myPosition.z = 2.5;
			scene = scene_4;
			glViewport(0, 0, 1924, 1061);
			glMatrixMode(GL_PROJECTION);			// 射影行列を操作する
			glLoadIdentity();						// 行列を初期化
			gluPerspective(80.0, 1924.0 / 1061.0, 0.1, 5000);
			glMatrixMode(GL_MODELVIEW);

			break;
		default:
			break;
		}
	}
	if (key == 'f')
	{
		if(scene == scene_8 && can_get != 0)
		{
			game[2].havingItems[my_id] += can_get;
		}
		if (doorAIM == true && scene == scene_3)
		{
			doorANIM = true;
			scene = scene_4;
			Mix_PlayMusic(BGM_park, -1);
		}
		if(game[0].stts == 1)
		{
			game[0].stts = 2;
		}
		if(game[1].stts == 1)
		{
			game[1].stts = 2;
		}
		if(game[2].stts == 1)
		{
			game[2].stts = 2;
		}
		if(game[3].stts == 1)
		{
			game[3].stts = 2;
		}		

		if(game[1].stts == 10)
		{
			game[1].stts = 3;
		}
		if(game[2].stts == 10)
		{
			game[2].stts = 3;
		}
		if(game[3].stts == 10)
		{
			game[3].stts = 3;
		}
		if(join == true)
		{
			game[0].stts = 3;
		}
	}
	if (scene == scene_5 && chess_hukan == false && key == 'm')
	{
		chess_hukan = true;
	}
	if (key == 32)
	{
		if (pressSPACE == false)
		{
			pressSPACE = true;
			jumpingTime = 0;
			h1 = myPosition.z;
			myPosition.dash = anim_jump;
		}
	}
	if (key == 225)
	{
		pressSHIFT_L = true;
	}
	if (key == 224)
	{
		pressCTRL_L = true;
	}
}

void keyUp(unsigned char key, int x, int y)
{
	if (key == 'w' || key == 'W' || key == 23)
	{
		pressW = false;
	}
	if (key == 's' || key == 'S' || key == 19)
	{
		pressS = false;
	}
	if (key == 'a' || key == 'A' || key == 1)
	{
		pressA = false;
	}
	if (key == 'd' || key == 'D' || key == 4)
	{
		pressD = false;
	}
	if (key == 225)
	{
		pressSHIFT_L = false;	
	}
	if (scene == scene_5 && chess_hukan == true && key == 'm')
	{
		chess_hukan = false;
	}
}

void clicking(int x, int y)
{
	//SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
	//lookingPosition.x -= (x - 900) / 100.0;//dx
	//lookingPosition.z -= (y - 500) / 140.0;//dy
	//if (lookingPosition.z * 20.0 >= 89.0)
	//{
	//	lookingPosition.z = 4.4;
	//}
	//else if (lookingPosition.z * 20.0 <= -89.0)
	//{
	//	lookingPosition.z = -4.4;
	//}
}

void clicked_down(int x, int y, int button)
{
	switch (scene)
	{
	case scene_1:
		scene = scene_2;
		break;
	case scene_2:
		break;
	case scene_3:
		break;
	case scene_4:
		break;
	case scene_5:
		//printf("clicked  x :  %d  y  :  %d\n",x,y);
		break;
	case scene_6:
		if (canonCoolTime > 300 && fin == 0)
		{
			shotCanon = true;
			canonCoolTime = 0;
			canonPos.x = tankPos.x;
			canonPos.y = tankPos.y;
			canonPos.z = tankPos.z;
			canonPos.alpha = alpha;
			canonPos.sita = sita;
			flyingCanon = true;
		}
		break;
	case scene_7:
		break;
	case scene_8:
		if (button == SDL_BUTTON_LEFT)
		{
			onFire = true;
			onFire_frame_count = 0;
		}
		else if (button == SDL_BUTTON_RIGHT)
		{
			if (weapon_aiming_torigger == normalPos)
			{
				weapon_aiming_torigger = goingLeft;
			}
			else if (weapon_aiming_torigger == goingLeft)
			{
				weapon_aiming_torigger = goingRight;
			}
			else if (weapon_aiming_torigger == aimingPos)
			{
				weapon_aiming_torigger = goingRight;
			}
			else if (weapon_aiming_torigger == goingRight)
			{
				weapon_aiming_torigger = goingLeft;
			}
		}
		break;
	default:
		break;
	}
}

void clicked_up(int x, int y, int button)
{
	int tate = 10;
	int yoko = 10;
	int xx;
	int yy;
	bool set = false;
	switch (scene)
	{
	case scene_1:
		break;
	case scene_2:
		break;
	case scene_3:
		break;
	case scene_4:
		for(int i = 0;i < 8;i++)
		{
			for(int j=0;j < 8;j++)
			{
				printf("%d ",chessMap[i][j]);
			}
			printf("\n");
		}
		printf("\n");
		break;
	case scene_5:
		//x 1154 y 160
		//width 38 height 28.125
		printf("turn : %d\n",original_turn);
		if((original_turn % 2 == 0 && chessMyColor ==1) || (original_turn % 2 == 1 && chessMyColor ==0) || found1 == false || found2 == false)
		{
			break;
		}
		mouseDisplayX = x;
		mouseDisplayY = y;

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (x > DCX + (DCW * i) && x < (DCX + DCW) + (DCW * i) && y > DCY + (DCH * j) && y < (DCY + DCH) + (DCH * j))
				{
					tate = j;
					yoko = i;
					break;
				}
			}
		}
		if (tate != 10 && yoko != 10 )
		{
			switch (cs)
			{
			case get_piece:
				if (chessMap[tate][yoko] >= 7 && chessMap[tate][yoko] <= 12 && chessMyColor == 0)//��
				{
					switch (chessMap[tate][yoko])
					{
					case 7://�|�[��
						chess_having = chessMap[tate][yoko] - 6;
						cs = set_piece;
						chess_get_point[0] = tate;
						chess_get_point[1] = yoko;
						if (tate == 7 - ci.wp1.pos[0] && yoko == ci.wp1.pos[1])
							cp = wp1;
						else if (tate == 7 - ci.wp2.pos[0] && yoko == ci.wp2.pos[1])
							cp = wp2;
						else if (tate == 7 - ci.wp3.pos[0] && yoko == ci.wp3.pos[1])
							cp = wp3;
						else if (tate == 7 - ci.wp4.pos[0] && yoko == ci.wp4.pos[1])
							cp = wp4;
						else if (tate == 7 - ci.wp5.pos[0] && yoko == ci.wp5.pos[1])
							cp = wp5;
						else if (tate == 7 - ci.wp6.pos[0] && yoko == ci.wp6.pos[1])
							cp = wp6;
						else if (tate == 7 - ci.wp7.pos[0] && yoko == ci.wp7.pos[1])
							cp = wp7;
						else if (tate == 7 - ci.wp8.pos[0] && yoko == ci.wp8.pos[1])
							cp = wp8;
						break;
					case 8://���[�N
						chess_having = chessMap[tate][yoko] - 6;
						cs = set_piece;
						chess_get_point[0] = tate;
						chess_get_point[1] = yoko;
						if (tate == 7 - ci.wr1.pos[0] && yoko == ci.wr1.pos[1])
							cp = wr1;
						else if (tate == 7 - ci.wr2.pos[0] && yoko == ci.wr2.pos[1])
							cp = wr2;
						break;
					case 9://�i�C�g
						chess_having = chessMap[tate][yoko] - 6;
						cs = set_piece;
						chess_get_point[0] = tate;
						chess_get_point[1] = yoko;
						if (tate == 7 - ci.wn1.pos[0] && yoko == ci.wn1.pos[1])
							cp = wn1;
						else if (tate == 7 - ci.wn2.pos[0] && yoko == ci.wn2.pos[1])
							cp = wn2;
						break;
					case 10://�r�V���b�v
						chess_having = chessMap[tate][yoko] - 6;
						cs = set_piece;
						chess_get_point[0] = tate;
						chess_get_point[1] = yoko;
						if (tate == 7 - ci.wb1.pos[0] && yoko == ci.wb1.pos[1])
							cp = wb1;
						else if (tate == 7 - ci.wb2.pos[0] && yoko == ci.wb2.pos[1])
							cp = wb2;

						break;
					case 11://�L���O
						chess_having = chessMap[tate][yoko] - 6;
						cs = set_piece;
						chess_get_point[0] = tate;
						chess_get_point[1] = yoko;
						cp = wk;

						break;
					case 12://�N�C�[��
						chess_having = chessMap[tate][yoko] - 6;
						cs = set_piece;
						chess_get_point[0] = tate;
						chess_get_point[1] = yoko;
						cp = wq;
						break;
					default:
						chess_having = 0;
						break;
					}
				}
				else if (chessMap[tate][yoko] >= 1 && chessMap[tate][yoko] <= 6 && chessMyColor == 1) //��
				{
					switch (chessMap[tate][yoko])
					{
					case 1:
						chess_having = chessMap[tate][yoko];
						cs = set_piece;
						chess_get_point[0] = tate;
						chess_get_point[1] = yoko;
						if (tate == ci.bp1.pos[0] && yoko == ci.bp1.pos[1])
							cp = bp1;
						else if (tate == ci.bp2.pos[0] && yoko == ci.bp2.pos[1])
							cp = bp2;
						else if (tate == ci.bp3.pos[0] && yoko == ci.bp3.pos[1])
							cp = bp3;
						else if (tate == ci.bp4.pos[0] && yoko == ci.bp4.pos[1])
							cp = bp4;
						else if (tate == ci.bp5.pos[0] && yoko == ci.bp5.pos[1])
							cp = bp5;
						else if (tate == ci.bp6.pos[0] && yoko == ci.bp6.pos[1])
							cp = bp6;
						else if (tate == ci.bp7.pos[0] && yoko == ci.bp7.pos[1])
							cp = bp7;
						else if (tate == ci.bp8.pos[0] && yoko == ci.bp8.pos[1])
							cp = bp8;

						break;
					case 2:
						chess_having = chessMap[tate][yoko];
						cs = set_piece;
						chess_get_point[0] = tate;
						chess_get_point[1] = yoko;
						if (tate == ci.br1.pos[0] && yoko == ci.br1.pos[1])
							cp = br1;
						else if (tate == ci.br2.pos[0] && yoko == ci.br2.pos[1])
							cp = br2;

						break;
					case 3:
						chess_having = chessMap[tate][yoko];
						cs = set_piece;
						chess_get_point[0] = tate;
						chess_get_point[1] = yoko;
						if (tate == ci.bn1.pos[0] && yoko == ci.bn1.pos[1])
							cp = bn1;
						else if (tate == ci.bn2.pos[0] && yoko == ci.bn2.pos[1])
							cp = bn2;

						break;
					case 4:
						chess_having = chessMap[tate][yoko];
						cs = set_piece;
						chess_get_point[0] = tate;
						chess_get_point[1] = yoko;
						if (tate == ci.bb1.pos[0] && yoko == ci.bb1.pos[1])
							cp = bb1;
						else if (tate == ci.bb2.pos[0] && yoko == ci.bb2.pos[1])
							cp = bb2;

						break;
					case 5:
						chess_having = chessMap[tate][yoko];
						cs = set_piece;
						chess_get_point[0] = tate;
						chess_get_point[1] = yoko;
						cp = bk;

						break;
					case 6:
						chess_having = chessMap[tate][yoko];
						cs = set_piece;
						chess_get_point[0] = tate;
						chess_get_point[1] = yoko;
						cp = bq;

						break;
					default:
						chess_having = 0;
						break;
					}

				}
				angle = 0;
				break;
			case set_piece:
				if (tate == chess_get_point[0] && yoko == chess_get_point[1])
				{
					cs = get_piece;
					break;
				}
				if(button == SDL_BUTTON_RIGHT)
				{
					cs = get_piece;
					break;					
				}
				if (chessMap[tate][yoko] == 0 || (chessMyColor == 0 && chessMap[tate][yoko] < 7) || (chessMyColor == 1 && chessMap[tate][yoko] > 6))//�����F���U���ł��Ȃ��悤�ɂ��Ă���
				{
					int p;
					switch (chess_having)
					{
					case 1://�|�[��
						if (tate == chess_get_point[0] - 1 && yoko == chess_get_point[1] && chessMap[tate][yoko] == 0)//�����̑O�ړ�
						{
							switch (cp)
							{
							case bp1:
								cs = get_piece;
								ci.bp1.pos[0]--;
								break;
							case bp2:
								cs = get_piece;
								ci.bp2.pos[0]--;
								break;
							case bp3:
								cs = get_piece;
								ci.bp3.pos[0]--;
								break;
							case bp4:
								cs = get_piece;
								ci.bp4.pos[0]--;
								break;
							case bp5:
								cs = get_piece;
								ci.bp5.pos[0]--;
								break;
							case bp6:
								cs = get_piece;
								ci.bp6.pos[0]--;
								break;
							case bp7:
								cs = get_piece;
								ci.bp7.pos[0]--;
								break;
							case bp8:
								cs = get_piece;
								ci.bp8.pos[0]--;
								break;
							case wp1:
								cs = get_piece;
								ci.wp1.pos[0]++;
								break;
							case wp2:
								cs = get_piece;
								ci.wp2.pos[0]++;
								break;
							case wp3:
								cs = get_piece;
								ci.wp3.pos[0]++;
								break;
							case wp4:
								cs = get_piece;
								ci.wp4.pos[0]++;
								break;
							case wp5:
								cs = get_piece;
								ci.wp5.pos[0]++;
								break;
							case wp6:
								cs = get_piece;
								ci.wp6.pos[0]++;
								break;
							case wp7:
								cs = get_piece;
								ci.wp7.pos[0]++;
								break;
							case wp8:
								cs = get_piece;
								ci.wp8.pos[0]++;
								break;
							default:
								break;
							}
							p = chessMap[chess_get_point[0]][chess_get_point[1]];
							chessMap[chess_get_point[0]][chess_get_point[1]] = chessMap[tate][yoko];
							chessMap[tate][yoko] = p;
						}
						else if (tate == chess_get_point[0] - 1 && yoko == chess_get_point[1] && chessMap[tate][yoko] != 0)//���ʂɉ����̋�����
						{
							cs = get_piece;
						}
						else if (tate == chess_get_point[0] - 1 && (yoko == chess_get_point[1] - 1 || yoko == chess_get_point[1] + 1) && chessMap[tate][yoko] != 0)//�U���ł��鎞
						{
							switch (cp)
							{
							case bp1:
								cs = get_piece;
								ci.bp1.pos[0]--;
								ci.bp1.pos[1] += yoko - chess_get_point[1];
								break;
							case bp2:
								cs = get_piece;
								ci.bp2.pos[0]--;
								ci.bp2.pos[1] += yoko - chess_get_point[1];
								break;
							case bp3:
								cs = get_piece;
								ci.bp3.pos[0]--;
								ci.bp3.pos[1] += yoko - chess_get_point[1];
								break;
							case bp4:
								cs = get_piece;
								ci.bp4.pos[0]--;
								ci.bp4.pos[1] += yoko - chess_get_point[1];
								break;
							case bp5:
								cs = get_piece;
								ci.bp5.pos[0]--;
								ci.bp5.pos[1] += yoko - chess_get_point[1];
								break;
							case bp6:
								cs = get_piece;
								ci.bp6.pos[0]--;
								ci.bp6.pos[1] += yoko - chess_get_point[1];
								break;
							case bp7:
								cs = get_piece;
								ci.bp7.pos[0]--;
								ci.bp7.pos[1] += yoko - chess_get_point[1];
								break;
							case bp8:
								cs = get_piece;
								ci.bp8.pos[0]--;
								ci.bp8.pos[1] += yoko - chess_get_point[1];
								break;
							case wp1:
								cs = get_piece;
								ci.wp1.pos[0]++;
								ci.wp1.pos[1] += yoko - chess_get_point[1];
								break;
							case wp2:
								cs = get_piece;
								ci.wp2.pos[0]++;
								ci.wp2.pos[1] += yoko - chess_get_point[1];
								break;
							case wp3:
								cs = get_piece;
								ci.wp3.pos[0]++;
								ci.wp3.pos[1] += yoko - chess_get_point[1];
								break;
							case wp4:
								cs = get_piece;
								ci.wp4.pos[0]++;
								ci.wp4.pos[1] += yoko - chess_get_point[1];
								break;
							case wp5:
								cs = get_piece;
								ci.wp5.pos[0]++;
								ci.wp5.pos[1] += yoko - chess_get_point[1];
								break;
							case wp6:
								cs = get_piece;
								ci.wp6.pos[0]++;
								ci.wp6.pos[1] += yoko - chess_get_point[1];
								break;
							case wp7:
								cs = get_piece;
								ci.wp7.pos[0]++;
								ci.wp7.pos[1] += yoko - chess_get_point[1];
								break;
							case wp8:
								cs = get_piece;
								ci.wp8.pos[0]++;
								ci.wp8.pos[1] += yoko - chess_get_point[1];
								break;
							default:
								break;
							}
							chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
							chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
							set = true;
						}
						else if (chess_get_point[0] == 6)//�����ʒu����2�}�X�������
						{
							if (tate == chess_get_point[0] - 2 && yoko == chess_get_point[1])
							{
								switch (cp)
								{
								case bp1:
									cs = get_piece;
									ci.bp1.pos[0] -= 2;
									break;
								case bp2:
									cs = get_piece;
									ci.bp2.pos[0] -= 2;
									break;
								case bp3:
									cs = get_piece;
									ci.bp3.pos[0] -= 2;
									break;
								case bp4:
									cs = get_piece;
									ci.bp4.pos[0] -= 2;
									break;
								case bp5:
									cs = get_piece;
									ci.bp5.pos[0] -= 2;
									break;
								case bp6:
									cs = get_piece;
									ci.bp6.pos[0] -= 2;
									break;
								case bp7:
									cs = get_piece;
									ci.bp7.pos[0] -= 2;
									break;
								case bp8:
									cs = get_piece;
									ci.bp8.pos[0] -= 2;
									break;
								case wp1:
									cs = get_piece;
									ci.wp1.pos[0] += 2;
									break;
								case wp2:
									cs = get_piece;
									ci.wp2.pos[0] += 2;
									break;
								case wp3:
									cs = get_piece;
									ci.wp3.pos[0] += 2;
									break;
								case wp4:
									cs = get_piece;
									ci.wp4.pos[0] += 2;
									break;
								case wp5:
									cs = get_piece;
									ci.wp5.pos[0] += 2;
									break;
								case wp6:
									cs = get_piece;
									ci.wp6.pos[0] += 2;
									break;
								case wp7:
									cs = get_piece;
									ci.wp7.pos[0] += 2;
									break;
								case wp8:
									cs = get_piece;
									ci.wp8.pos[0] += 2;
									break;
								default:
									break;
								}
								p = chessMap[chess_get_point[0]][chess_get_point[1]];
								chessMap[chess_get_point[0]][chess_get_point[1]] = chessMap[tate][yoko];
								chessMap[tate][yoko] = p;
								set = true;
							}
						}
						break;
					case 2://���[�N
						if (tate == chess_get_point[0] && yoko == chess_get_point[1])//�����ꏊ�N���b�N
						{
							cs = get_piece;
						}
						else if (tate == chess_get_point[0])//���ړ�
						{
							bool conti = true;
							if (chess_get_point[1] < yoko)//�E
							{
								for (int k = chess_get_point[1] + 1; k < yoko; k++)
								{
									if (chessMap[tate][k] != 0)
									{
										conti = false;
										break;
									}
								}
							}
							else//��
							{
								for (int k = yoko + 1; k < chess_get_point[1]; k++)
								{
									if (chessMap[tate][k] != 0)
									{
										conti = false;
										break;
									}
								}
							}
							if (conti == true)
							{
								switch (cp)
								{
								case br1:
									ci.br1.pos[1] += yoko - chess_get_point[1];
									break;
								case br2:
									ci.br2.pos[1] += yoko - chess_get_point[1];
									break;
								case wr1:
									ci.wr1.pos[1] += yoko - chess_get_point[1];
									break;
								case wr2:
									ci.wr2.pos[1] += yoko - chess_get_point[1];
									break;
								default:
									break;
								}
								cs = get_piece;
								chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
								chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
								set = true;
							}
						}
						else if (yoko == chess_get_point[1])//�c�ړ�
						{
							bool conti = true;
							if (chess_get_point[0] < tate)//��
							{
								for (int k = chess_get_point[0] + 1; k < tate; k++)
								{
									if (chessMap[k][yoko] != 0)
									{
										conti = false;
										break;
									}
								}
							}
							else//��
							{
								for (int k = tate + 1; k < chess_get_point[0]; k++)
								{
									if (chessMap[k][yoko] != 0)
									{
										conti = false;
										break;
									}
								}
							}
							if (conti == true)
							{
								switch (cp)
								{
								case br1:
									ci.br1.pos[0] += tate - chess_get_point[0];
									break;
								case br2:
									ci.br2.pos[0] += tate - chess_get_point[0];
									break;
								case wr1:
									ci.wr1.pos[0] -= tate - chess_get_point[0];
									break;
								case wr2:
									ci.wr2.pos[0] -= tate - chess_get_point[0];
									break;
								default:
									break;
								}
								cs = get_piece;
								chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
								chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
								set = true;
							}
						}
						else
						{
							cs = get_piece;
						}
						break;
					case 3://�i�C�g
						if (tate == chess_get_point[0] - 2 && yoko == chess_get_point[1] - 1)
						{
							switch (cp)
							{
							case bn1:
								ci.bn1.pos[0] += tate - chess_get_point[0];
								ci.bn1.pos[1] += yoko - chess_get_point[1];
								break;
							case bn2:
								ci.bn2.pos[0] += tate - chess_get_point[0];
								ci.bn2.pos[1] += yoko - chess_get_point[1];
								break;
							case wn1:
								ci.wn1.pos[0] -= tate - chess_get_point[0];
								ci.wn1.pos[1] += yoko - chess_get_point[1];
								break;
							case wn2:
								ci.wn2.pos[0] -= tate - chess_get_point[0];
								ci.wn2.pos[1] += yoko - chess_get_point[1];
								break;
							default:
								break;
							}
							chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
							chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
							set = true;
						}
						else if (tate == chess_get_point[0] - 2 && yoko == chess_get_point[1] + 1)
						{
							switch (cp)
							{
							case bn1:
								ci.bn1.pos[0] += tate - chess_get_point[0];
								ci.bn1.pos[1] += yoko - chess_get_point[1];
								break;
							case bn2:
								ci.bn2.pos[0] += tate - chess_get_point[0];
								ci.bn2.pos[1] += yoko - chess_get_point[1];
								break;
							case wn1:
								ci.wn1.pos[0] -= tate - chess_get_point[0];
								ci.wn1.pos[1] += yoko - chess_get_point[1];
								break;
							case wn2:
								ci.wn2.pos[0] -= tate - chess_get_point[0];
								ci.wn2.pos[1] += yoko - chess_get_point[1];
								break;
							default:
								break;
							}
							chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
							chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
							set = true;
						}
						else if (tate == chess_get_point[0] - 1 && yoko == chess_get_point[1] - 2)
						{
							switch (cp)
							{
							case bn1:
								ci.bn1.pos[0] += tate - chess_get_point[0];
								ci.bn1.pos[1] += yoko - chess_get_point[1];
								break;
							case bn2:
								ci.bn2.pos[0] += tate - chess_get_point[0];
								ci.bn2.pos[1] += yoko - chess_get_point[1];
								break;
							case wn1:
								ci.wn1.pos[0] -= tate - chess_get_point[0];
								ci.wn1.pos[1] += yoko - chess_get_point[1];
								break;
							case wn2:
								ci.wn2.pos[0] -= tate - chess_get_point[0];
								ci.wn2.pos[1] += yoko - chess_get_point[1];
								break;
							default:
								break;
							}
							chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
							chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
							set = true;
						}
						else if (tate == chess_get_point[0] - 1 && yoko == chess_get_point[1] + 2)
						{
							switch (cp)
							{
							case bn1:
								ci.bn1.pos[0] += tate - chess_get_point[0];
								ci.bn1.pos[1] += yoko - chess_get_point[1];
								break;
							case bn2:
								ci.bn2.pos[0] += tate - chess_get_point[0];
								ci.bn2.pos[1] += yoko - chess_get_point[1];
								break;
							case wn1:
								ci.wn1.pos[0] -= tate - chess_get_point[0];
								ci.wn1.pos[1] += yoko - chess_get_point[1];
								break;
							case wn2:
								ci.wn2.pos[0] -= tate - chess_get_point[0];
								ci.wn2.pos[1] += yoko - chess_get_point[1];
								break;
							default:
								break;
							}
							chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
							chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
							set = true;
						}
						else if (tate == chess_get_point[0] + 2 && yoko == chess_get_point[1] - 1)
						{
							switch (cp)
							{
							case bn1:
								ci.bn1.pos[0] += tate - chess_get_point[0];
								ci.bn1.pos[1] += yoko - chess_get_point[1];
								break;
							case bn2:
								ci.bn2.pos[0] += tate - chess_get_point[0];
								ci.bn2.pos[1] += yoko - chess_get_point[1];
								break;
							case wn1:
								ci.wn1.pos[0] -= tate - chess_get_point[0];
								ci.wn1.pos[1] += yoko - chess_get_point[1];
								break;
							case wn2:
								ci.wn2.pos[0] -= tate - chess_get_point[0];
								ci.wn2.pos[1] += yoko - chess_get_point[1];
								break;
							default:
								break;
							}
							chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
							chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
							set = true;
						}
						else if (tate == chess_get_point[0] + 2 && yoko == chess_get_point[1] + 1)
						{
							switch (cp)
							{
							case bn1:
								ci.bn1.pos[0] += tate - chess_get_point[0];
								ci.bn1.pos[1] += yoko - chess_get_point[1];
								break;
							case bn2:
								ci.bn2.pos[0] += tate - chess_get_point[0];
								ci.bn2.pos[1] += yoko - chess_get_point[1];
								break;
							case wn1:
								ci.wn1.pos[0] -= tate - chess_get_point[0];
								ci.wn1.pos[1] += yoko - chess_get_point[1];
								break;
							case wn2:
								ci.wn2.pos[0] -= tate - chess_get_point[0];
								ci.wn2.pos[1] += yoko - chess_get_point[1];
								break;
							default:
								break;
							}
							chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
							chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
							set = true;
						}
						else if (tate == chess_get_point[0] + 1 && yoko == chess_get_point[1] - 2)
						{
							switch (cp)
							{
							case bn1:
								ci.bn1.pos[0] += tate - chess_get_point[0];
								ci.bn1.pos[1] += yoko - chess_get_point[1];
								break;
							case bn2:
								ci.bn2.pos[0] += tate - chess_get_point[0];
								ci.bn2.pos[1] += yoko - chess_get_point[1];
								break;
							case wn1:
								ci.wn1.pos[0] -= tate - chess_get_point[0];
								ci.wn1.pos[1] += yoko - chess_get_point[1];
								break;
							case wn2:
								ci.wn2.pos[0] -= tate - chess_get_point[0];
								ci.wn2.pos[1] += yoko - chess_get_point[1];
								break;
							default:
								break;
							}
							chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
							chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
							set = true;
						}
						else if (tate == chess_get_point[0] + 1 && yoko == chess_get_point[1] + 2)
						{
							switch (cp)
							{
							case bn1:
								ci.bn1.pos[0] += tate - chess_get_point[0];
								ci.bn1.pos[1] += yoko - chess_get_point[1];
								break;
							case bn2:
								ci.bn2.pos[0] += tate - chess_get_point[0];
								ci.bn2.pos[1] += yoko - chess_get_point[1];
								break;
							case wn1:
								ci.wn1.pos[0] -= tate - chess_get_point[0];
								ci.wn1.pos[1] += yoko - chess_get_point[1];
								break;
							case wn2:
								ci.wn2.pos[0] -= tate - chess_get_point[0];
								ci.wn2.pos[1] += yoko - chess_get_point[1];
								break;
							default:
								break;
							}
							chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
							chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
							set = true;
						}
						cs = get_piece;
						break;
					case 4://�r�V���b�v
						xx = std::abs(tate - chess_get_point[0]);
						yy = std::abs(yoko - chess_get_point[1]);
						if (tate != chess_get_point[0] && yoko != chess_get_point[1] && xx == yy)
						{
							bool conti = true;
							if (tate > chess_get_point[0])
							{
								if (yoko > chess_get_point[1])//�E��
								{
									for (int k = 1; k < tate - chess_get_point[0]; k++)
									{
										if (chessMap[chess_get_point[0] + k][chess_get_point[1] + k] != 0)
										{
											conti = false;
											break;
										}
									}
								}
								else//����
								{
									for (int k = 1; k < tate - chess_get_point[0]; k++)
									{
										if (chessMap[chess_get_point[0] + k][chess_get_point[1] - k] != 0)
										{
											conti = false;
											break;
										}
									}
								}
							}
							else
							{
								if (yoko > chess_get_point[1])//�E��
								{
									for (int k = 1; k < chess_get_point[0] - tate; k++)
									{
										if (chessMap[chess_get_point[0] - k][chess_get_point[1] + k] != 0)
										{
											conti = false;
											break;
										}
									}
								}
								else//����
								{
									for (int k = 1; k < chess_get_point[0] - tate; k++)
									{
										if (chessMap[chess_get_point[0] - k][chess_get_point[1] - k] != 0)
										{
											conti = false;
											break;
										}
									}
								}
							}
							if (conti == true)
							{
								switch (cp)
								{
								case bb1:
									ci.bb1.pos[0] += tate - chess_get_point[0];
									ci.bb1.pos[1] += yoko - chess_get_point[1];
									break;
								case bb2:
									ci.bb2.pos[0] += tate - chess_get_point[0];
									ci.bb2.pos[1] += yoko - chess_get_point[1];
									break;
								case wb1:
									ci.wb1.pos[0] -= tate - chess_get_point[0];
									ci.wb1.pos[1] += yoko - chess_get_point[1];
									break;
								case wb2:
									ci.wb2.pos[0] -= tate - chess_get_point[0];
									ci.wb2.pos[1] += yoko - chess_get_point[1];
									break;
								default:
									break;
								}
								chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
								chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
								set = true;
							}
						}
						cs = get_piece;
						break;
					case 5://�L���O
						xx = std::abs(tate - chess_get_point[0]);
						yy = std::abs(yoko - chess_get_point[1]);
						if (xx <= 1 && yy <= 1 && (tate != chess_get_point[0] || yoko != chess_get_point[1]))
						{
							switch (cp)
							{
							case bk:
								ci.bk.pos[0] += tate - chess_get_point[0];
								ci.bk.pos[1] += yoko - chess_get_point[1];
								break;
							case wk:
								ci.wk.pos[0] -= tate - chess_get_point[0];
								ci.wk.pos[1] -= yoko - chess_get_point[1];
								break;
							default:
								break;
							}
							chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
							chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
							set = true;
						}
						cs = get_piece;
						break;
					case 6://�N�C�[��
						if (tate == chess_get_point[0])//���ړ�
						{
							bool conti = true;
							if (chess_get_point[1] < yoko)//�E
							{
								for (int k = chess_get_point[1] + 1; k < yoko; k++)
								{
									if (chessMap[tate][k] != 0)
									{
										conti = false;
										break;
									}
								}
							}
							else//��
							{
								for (int k = yoko + 1; k < chess_get_point[1]; k++)
								{
									if (chessMap[tate][k] != 0)
									{
										conti = false;
										break;
									}
								}
							}
							if (conti == true)
							{
								switch (cp)
								{
								case bq:
									ci.bq.pos[1] += yoko - chess_get_point[1];
									break;
								case wq:
									ci.wq.pos[1] -= yoko - chess_get_point[1];
									break;
								default:
									break;
								}
								cs = get_piece;
								chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
								chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
								set = true;
							}
						}
						else if (yoko == chess_get_point[1])//�c�ړ�
						{
							bool conti = true;
							if (chess_get_point[0] < tate)//��
							{
								for (int k = chess_get_point[0] + 1; k < tate; k++)
								{
									if (chessMap[k][yoko] != 0)
									{
										conti = false;
										break;
									}
								}
							}
							else//��
							{
								for (int k = tate + 1; k < chess_get_point[0]; k++)
								{
									if (chessMap[k][yoko] != 0)
									{
										conti = false;
										break;
									}
								}
							}
							if (conti == true)
							{
								switch (cp)
								{
								case bq:
									ci.bq.pos[0] += tate - chess_get_point[0];
									break;
								case wq:
									ci.wq.pos[0] -= tate - chess_get_point[0];
									break;
								default:
									break;
								}
								cs = get_piece;
								chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
								chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
								set = true;
							}
						}
						xx = std::abs(tate - chess_get_point[0]);
						yy = std::abs(yoko - chess_get_point[1]);
						if (tate != chess_get_point[0] && yoko != chess_get_point[1] && xx == yy)
						{
							bool conti = true;
							if (tate > chess_get_point[0])
							{
								if (yoko > chess_get_point[1])//�E��
								{
									for (int k = 1; k < tate - chess_get_point[0]; k++)
									{
										if (chessMap[chess_get_point[0] + k][chess_get_point[1] + k] != 0)
										{
											conti = false;
											break;
										}
									}
								}
								else//����
								{
									for (int k = 1; k < tate - chess_get_point[0]; k++)
									{
										if (chessMap[chess_get_point[0] + k][chess_get_point[1] - k] != 0)
										{
											conti = false;
											break;
										}
									}
								}
							}
							else
							{
								if (yoko > chess_get_point[1])//�E��
								{
									for (int k = 1; k < chess_get_point[0] - tate; k++)
									{
										if (chessMap[chess_get_point[0] - k][chess_get_point[1] + k] != 0)
										{
											conti = false;
											break;
										}
									}
								}
								else//����
								{
									for (int k = 1; k < chess_get_point[0] - tate; k++)
									{
										if (chessMap[chess_get_point[0] - k][chess_get_point[1] - k] != 0)
										{
											conti = false;
											break;
										}
									}
								}
							}
							if (conti == true)
							{
								switch (cp)
								{
								case bq:
									ci.bq.pos[0] += tate - chess_get_point[0];
									ci.bq.pos[1] += yoko - chess_get_point[1];
									break;
								case wq:
									ci.wq.pos[0] -= tate - chess_get_point[0];
									ci.wq.pos[1] -= yoko - chess_get_point[1];
									break;
								default:
									break;
								}
								chessMap[tate][yoko] = chessMap[chess_get_point[0]][chess_get_point[1]];
								chessMap[chess_get_point[0]][chess_get_point[1]] = 0;
								set = true;
							}
						}
						cs = get_piece;
						break;
					default:
						break;
					}
					CIN.ci = ci;
					std::memcpy(CIN.cm,chessMap,sizeof(chessMap));
					found1= false;
					found2= false;
					int f1 = 0;
					int f2 = 0;

					for(int m = 0;m<8;m++)
					{
						for(int n=0;n<8;n++)
						{
							printf("%d ",chessMap[m][n]);
							if(chessMap[m][n] == key1)
								f1++;
							if(chessMap[m][n] == key2)
								f2++;

						}
						printf("\n");
					}
					switch(key1)
					{
						case 1:
							if(f1 == 8)
								found1 = true;
							break;
						case 2:
							if(f1 == 2)
								found1 = true;						
							break;
						case 3:
							if(f1 == 2)
								found1 = true;						
							break;
						case 4:
							if(f1 == 2)
								found1 = true;						
							break;
						case 5:
							if(f1 == 1)
								found1 = true;						
							break;
						case 6:
							if(f1 == 1)
								found1 = true;						
							break;
					}
					switch(key2)
					{
						case 7:
							if(f2 == 8)
								found2 = true;	
							break;
						case 8:
							if(f2 == 2)
								found2 = true;							
							break;
						case 9:
							if(f2 == 2)
								found2 = true;							
							break;
						case 10:
							if(f2 == 2)
								found2 = true;							
							break;
						case 11:
							if(f2 == 1)
								found2 = true;							
							break;
						case 12:
							if(f2 == 1)
								found2 = true;							
							break;
					}
					if(found1 == false)
						CIN.f = 1;
					if(found2 == false)
					    CIN.f = 2;
					original_turn++;
					// if(chessMyColor == 0)
					// 	CIN.thisTurn = 1;
					// else
					// 	CIN.thisTurn = 0;
				}
				break;
			default:
				break;
			}
		}
		break;
	case scene_6:
		break;
	case scene_7:
		break;
	case scene_8:
		if (button == SDL_BUTTON_LEFT)
		{
			onFire = false;
		}
		break;
	default:
		break;
	}

}


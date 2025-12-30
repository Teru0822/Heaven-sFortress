#include "func.h"
#define TARMINATE_ANIM_SPEED 6

extern float angle;
extern float piece_width;
extern bool chess_hukan;
extern bool found1;
extern bool found2;
extern int chessMyColor;
extern int mouseDisplayX;
extern int mouseDisplayY;
extern int chessMap[8][8];
extern int chess_get_point[2];
extern int original_turn;
extern int mainloopcount;
extern uint8_t my_result[30];
int terminate_anim_count = 0;
extern chess_stts cs;
extern chess_info ci;
extern chess_kind_piece cp;
extern SDL_Window* window;
extern Position myPosition;
extern Scene scene;
extern Game game[4];

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
extern obj game2_chess_house_playing;
extern obj game2_chess_black_playing;
extern obj game2_Floor_playing;
extern obj skyInSide;
extern obj grass;
extern obj inside_road;
extern obj house_brick;
extern obj house_roof;
extern obj house_window;
extern obj house_white;
extern obj house_door;
extern obj yourturn;
extern obj enemyturn;

extern obj text_w[29];
extern obj text_i[29];
extern obj text_n[29];
extern obj text_l[29];
extern obj text_o[29];
extern obj text_s[29];
extern obj text_e[29];


extern chessInfoNet CIN;

//�R�����g����
void scene5(int x, int y, int w, int h)
{
	angle += 1;

	glViewport(x, y, w, h);
	if (chess_hukan == false)
	{
		//white
		if (chessMyColor == 0)
		{
			gluLookAt(-chessMyPosX, -chessMyPosY, chessMyPosZ,
				-chessAimX, -chessAimY, chessAimZ,
				0, 0, 1);

			glPushMatrix();
			glTranslatef(-chessMyPosX + ((-chessAimX + chessMyPosX) * 0.11), -chessMyPosY + ((-chessAimY + chessMyPosY) * 0.11), chessMyPosZ + ((chessAimZ - chessMyPosZ) * 0.11));
			glRotatef(-1.0 * chessAlpha / PI * 180.0, 0, 0, 1);
			glRotatef(chessSita / PI * 180.0, 0, -1, 0);
			if((original_turn % 2 == 0 && chessMyColor ==1) || (original_turn % 2 == 1 && chessMyColor ==0) || found1 == false || found2 == false)
				enemyturn.make(0,0,1);
			else
				yourturn.make(1,0,0);
			if((found1 ==false && chessMyColor == 0) || (found2 == false && chessMyColor == 1))
			{
				makeAnim(1, 1, 1, text_w, text_w[0].textureID, terminate_anim_count / TARMINATE_ANIM_SPEED, 29);
				makeAnim(1, 1, 1, text_i, text_i[0].textureID, terminate_anim_count / TARMINATE_ANIM_SPEED, 29);
				makeAnim(1, 1, 1, text_n, text_n[0].textureID, terminate_anim_count / TARMINATE_ANIM_SPEED, 29);
				terminate_anim_count++;
			}
			else if((found1 ==false && chessMyColor == 1) || (found2 == false && chessMyColor == 0))
			{
				makeAnim(1, 1, 1, text_l, text_l[0].textureID, terminate_anim_count / TARMINATE_ANIM_SPEED, 29);
				makeAnim(1, 1, 1, text_o, text_o[0].textureID, terminate_anim_count / TARMINATE_ANIM_SPEED, 29);
				makeAnim(1, 1, 1, text_s, text_s[0].textureID, terminate_anim_count / TARMINATE_ANIM_SPEED, 29);
				makeAnim(1, 1, 1, text_e, text_e[0].textureID, terminate_anim_count / TARMINATE_ANIM_SPEED, 29);
				terminate_anim_count++;
			}			
			chess_map.makeWithTex(1, 1, 1);
			makeChess_2D_icon(chessMap, cs, chess_get_point[0], chess_get_point[1], chessMyColor, mouseDisplayX, mouseDisplayY, DCX, DCY, DCW, angle, CIN.ci, cp);
			glPopMatrix();

		}
		else
		{
			gluLookAt(chessMyPosX, chessMyPosY, chessMyPosZ,
				chessAimX, chessAimY, chessAimZ,
				0, 0, 1);

			glPushMatrix();
			glTranslatef(chessMyPosX + ((chessAimX - chessMyPosX) * 0.11), chessMyPosY + ((chessAimY - chessMyPosY) * 0.11), chessMyPosZ + ((chessAimZ - chessMyPosZ) * 0.11));
			glRotatef(chessAlpha / PI * 180.0, 0, 0, 1);
			glRotatef(chessSita / PI * 180.0, 0, -1, 0);
			if((original_turn % 2 == 0 && chessMyColor ==1) || (original_turn % 2 == 1 && chessMyColor ==0) || found1 == false || found2 == false)
				enemyturn.make(0,0,1);
			else
				yourturn.make(1,0,0);
			if((found1 ==false && chessMyColor == 0) || (found2 == false && chessMyColor == 1))
			{
				makeAnim(1, 1, 1, text_w, text_w[0].textureID, terminate_anim_count / TARMINATE_ANIM_SPEED, 29);
				makeAnim(1, 1, 1, text_i, text_i[0].textureID, terminate_anim_count / TARMINATE_ANIM_SPEED, 29);
				makeAnim(1, 1, 1, text_n, text_n[0].textureID, terminate_anim_count / TARMINATE_ANIM_SPEED, 29);
				terminate_anim_count++;
			}
			else if((found1 ==false && chessMyColor == 1) || (found2 == false && chessMyColor == 0))
			{
				makeAnim(1, 1, 1, text_l, text_l[0].textureID, terminate_anim_count / TARMINATE_ANIM_SPEED, 29);
				makeAnim(1, 1, 1, text_o, text_o[0].textureID, terminate_anim_count / TARMINATE_ANIM_SPEED, 29);
				makeAnim(1, 1, 1, text_s, text_s[0].textureID, terminate_anim_count / TARMINATE_ANIM_SPEED, 29);
				makeAnim(1, 1, 1, text_e, text_e[0].textureID, terminate_anim_count / TARMINATE_ANIM_SPEED, 29);
				terminate_anim_count++;
			}		
			chess_map.makeWithTex(1, 1, 1);
			makeChess_2D_icon(chessMap, cs, chess_get_point[0], chess_get_point[1], chessMyColor, mouseDisplayX, mouseDisplayY, DCX, DCY, DCW, angle, CIN.ci, cp);
			glPopMatrix();
		}
	}
	else
	{
		gluLookAt(0, -0.1, 5, 0, 0, 3, 0, 0, 1);
	}
	chess_chair.makeWithTex(1, 1, 1);
	chess_set_board.makeWithTex(1, 1, 1);
	chess_table.makeWithTex(1, 1, 1);
	game2_chess_house_playing.makeWithTex(1, 1, 1);
	game2_chess_black_playing.makeWithTex(1, 1, 1);
	game2_Floor_playing.makeWithTex(1, 1, 1);
	skyInSide.makeWithTex(1, 1, 1);
	grass.makeWithTex(1, 1, 1);
	inside_road.makeWithTex(1, 1, 1);
	house_brick.makeWithTex(1, 1, 1);
	house_roof.makeWithTex(1, 1, 1);
	house_window.makeWithTex(1, 1, 1);
	house_white.make(1, 1, 1);
	house_door.makeWithTex(1, 1, 1);

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.bb1.pos[0]][7 - CIN.ci.bb1.pos[1]] == 4)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bb1.pos[1] - 2) * piece_width, (CIN.ci.bb1.pos[0] - 7) * -piece_width, 0);
			chess_BB1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.bb1.pos[0]][CIN.ci.bb1.pos[1]] == 4)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bb1.pos[1] - 2) * piece_width, (CIN.ci.bb1.pos[0] - 7) * -piece_width, 0);
			chess_BB1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.bb2.pos[0]][7 - CIN.ci.bb2.pos[1]] == 4)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bb2.pos[1] - 5) * piece_width, (CIN.ci.bb2.pos[0] - 7) * -piece_width, 0);
			chess_BB2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.bb2.pos[0]][CIN.ci.bb2.pos[1]] == 4)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bb2.pos[1] - 5) * piece_width, (CIN.ci.bb2.pos[0] - 7) * -piece_width, 0);
			chess_BB2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.bk.pos[0]][7 - CIN.ci.bk.pos[1]] == 5)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bk.pos[1] - 4) * piece_width, (CIN.ci.bk.pos[0] - 7) * -piece_width, 0);
			chess_BK.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.bk.pos[0]][CIN.ci.bk.pos[1]] == 5)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bk.pos[1] - 4) * piece_width, (CIN.ci.bk.pos[0] - 7) * -piece_width, 0);
			chess_BK.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.bn1.pos[0]][7 - CIN.ci.bn1.pos[1]] == 3)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bn1.pos[1] - 1) * piece_width, (CIN.ci.bn1.pos[0] - 7) * -piece_width, 0);
			chess_BN1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.bn1.pos[0]][CIN.ci.bn1.pos[1]] == 3)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bn1.pos[1] - 1) * piece_width, (CIN.ci.bn1.pos[0] - 7) * -piece_width, 0);
			chess_BN1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.bn2.pos[0]][7 - CIN.ci.bn2.pos[1]] == 3)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bn2.pos[1] - 6) * piece_width, (CIN.ci.bn2.pos[0] - 7) * -piece_width, 0);
			chess_BN2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.bn2.pos[0]][CIN.ci.bn2.pos[1]] == 3)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bn2.pos[1] - 6) * piece_width, (CIN.ci.bn2.pos[0] - 7) * -piece_width, 0);
			chess_BN2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.bp1.pos[0]][7 - CIN.ci.bp1.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef(CIN.ci.bp1.pos[1] * piece_width, (6 - CIN.ci.bp1.pos[0]) * piece_width, 0);
			chess_BP1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.bp1.pos[0]][CIN.ci.bp1.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef(CIN.ci.bp1.pos[1] * piece_width, (6 - CIN.ci.bp1.pos[0]) * piece_width, 0);
			chess_BP1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.bp2.pos[0]][7 - CIN.ci.bp2.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp2.pos[1] - 1) * piece_width, (6 - CIN.ci.bp2.pos[0]) * piece_width, 0);
			chess_BP2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.bp2.pos[0]][CIN.ci.bp2.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp2.pos[1] - 1) * piece_width, (6 - CIN.ci.bp2.pos[0]) * piece_width, 0);
			chess_BP2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.bp3.pos[0]][7 - CIN.ci.bp3.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp3.pos[1] - 2) * piece_width, (6 - CIN.ci.bp3.pos[0]) * piece_width, 0);
			chess_BP3.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.bp3.pos[0]][CIN.ci.bp3.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp3.pos[1] - 2) * piece_width, (6 - CIN.ci.bp3.pos[0]) * piece_width, 0);
			chess_BP3.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.bp4.pos[0]][7 - CIN.ci.bp4.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp4.pos[1] - 3) * piece_width, (6 - CIN.ci.bp4.pos[0]) * piece_width, 0);
			chess_BP4.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.bp4.pos[0]][CIN.ci.bp4.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp4.pos[1] - 3) * piece_width, (6 - CIN.ci.bp4.pos[0]) * piece_width, 0);
			chess_BP4.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.bp5.pos[0]][7 - CIN.ci.bp5.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp5.pos[1] - 4) * piece_width, (6 - CIN.ci.bp5.pos[0]) * piece_width, 0);
			chess_BP5.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.bp5.pos[0]][CIN.ci.bp5.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp5.pos[1] - 4) * piece_width, (6 - CIN.ci.bp5.pos[0]) * piece_width, 0);
			chess_BP5.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.bp6.pos[0]][7 - CIN.ci.bp6.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp6.pos[1] - 5) * piece_width, (6 - CIN.ci.bp6.pos[0]) * piece_width, 0);
			chess_BP6.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.bp6.pos[0]][CIN.ci.bp6.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp6.pos[1] - 5) * piece_width, (6 - CIN.ci.bp6.pos[0]) * piece_width, 0);
			chess_BP6.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.bp7.pos[0]][7 - CIN.ci.bp7.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp7.pos[1] - 6) * piece_width, (6 - CIN.ci.bp7.pos[0]) * piece_width, 0);
			chess_BP7.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.bp7.pos[0]][CIN.ci.bp7.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp7.pos[1] - 6) * piece_width, (6 - CIN.ci.bp7.pos[0]) * piece_width, 0);
			chess_BP7.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.bp8.pos[0]][7 - CIN.ci.bp8.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp8.pos[1] - 7) * piece_width, (6 - CIN.ci.bp8.pos[0]) * piece_width, 0);
			chess_BP8.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.bp8.pos[0]][CIN.ci.bp8.pos[1]] == 1)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bp8.pos[1] - 7) * piece_width, (6 - CIN.ci.bp8.pos[0]) * piece_width, 0);
			chess_BP8.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.bq.pos[0]][7 - CIN.ci.bq.pos[1]] == 6)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bq.pos[1] - 3) * piece_width, (CIN.ci.bq.pos[0] - 7) * -piece_width, 0);
			chess_BQ.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.bq.pos[0]][CIN.ci.bq.pos[1]] == 6)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.bq.pos[1] - 3) * piece_width, (CIN.ci.bq.pos[0] - 7) * -piece_width, 0);
			chess_BQ.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.br1.pos[0]][7 - CIN.ci.br1.pos[1]] == 2)
		{
			glPushMatrix();
			glTranslatef(CIN.ci.br1.pos[1] * piece_width, (CIN.ci.br1.pos[0] - 7) * -piece_width, 0);
			chess_BR1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.br1.pos[0]][CIN.ci.br1.pos[1]] == 2)
		{
			glPushMatrix();
			glTranslatef(CIN.ci.br1.pos[1] * piece_width, (CIN.ci.br1.pos[0] - 7) * -piece_width, 0);
			chess_BR1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.br2.pos[0]][7 - CIN.ci.br2.pos[1]] == 2)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.br2.pos[1] - 7) * piece_width, (CIN.ci.br2.pos[0] - 7) * -piece_width, 0);
			chess_BR2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.br2.pos[0]][CIN.ci.br2.pos[1]] == 2)
		{
			glPushMatrix();
			glTranslatef((CIN.ci.br2.pos[1] - 7) * piece_width, (CIN.ci.br2.pos[0] - 7) * -piece_width, 0);
			chess_BR2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	//������
	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wb1.pos[0]][CIN.ci.wb1.pos[1]] == 10)
		{
			glPushMatrix();
			glTranslatef((2 - CIN.ci.wb1.pos[1]) * piece_width, CIN.ci.wb1.pos[0] * -piece_width, 0);
			chess_WB1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wb1.pos[0]][7 - CIN.ci.wb1.pos[1]] == 10)
		{
			glPushMatrix();
			glTranslatef((2 - CIN.ci.wb1.pos[1]) * piece_width, CIN.ci.wb1.pos[0] * -piece_width, 0);
			chess_WB1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wb2.pos[0]][CIN.ci.wb2.pos[1]] == 10)
		{
			glPushMatrix();
			glTranslatef((5 - CIN.ci.wb2.pos[1]) * piece_width, CIN.ci.wb2.pos[0] * -piece_width, 0);
			chess_WB2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wb2.pos[0]][7 - CIN.ci.wb2.pos[1]] == 10)
		{
			glPushMatrix();
			glTranslatef((5 - CIN.ci.wb2.pos[1]) * piece_width, CIN.ci.wb2.pos[0] * -piece_width, 0);
			chess_WB2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wk.pos[0]][7 - CIN.ci.wk.pos[1]] == 11)
		{
			glPushMatrix();
			glTranslatef((4 - CIN.ci.wk.pos[1]) * -piece_width, CIN.ci.wk.pos[0] * -piece_width, 0);
			chess_WK.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wk.pos[0]][CIN.ci.wk.pos[1]] == 11)
		{
			glPushMatrix();
			glTranslatef((4 - CIN.ci.wk.pos[1]) * -piece_width, CIN.ci.wk.pos[0] * -piece_width, 0);
			chess_WK.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wq.pos[0]][7 - CIN.ci.wq.pos[1]] == 12)
		{
			glPushMatrix();
			glTranslatef((3 - CIN.ci.wq.pos[1]) * -piece_width, CIN.ci.wq.pos[0] * -piece_width, 0);
			chess_WQ.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wq.pos[0]][CIN.ci.wq.pos[1]] == 12)
		{
			glPushMatrix();
			glTranslatef((3 - CIN.ci.wq.pos[1]) * -piece_width, CIN.ci.wq.pos[0] * -piece_width, 0);
			chess_WQ.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wn1.pos[0]][CIN.ci.wn1.pos[1]] == 9)
		{
			glPushMatrix();
			glTranslatef((1 - CIN.ci.wn1.pos[1]) * piece_width, CIN.ci.wn1.pos[0] * -piece_width, 0);
			chess_WN1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wn1.pos[0]][7 - CIN.ci.wn1.pos[1]] == 9)
		{
			glPushMatrix();
			glTranslatef((1 - CIN.ci.wn1.pos[1]) * piece_width, CIN.ci.wn1.pos[0] * -piece_width, 0);
			chess_WN1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wn2.pos[0]][CIN.ci.wn2.pos[1]] == 9)
		{
			glPushMatrix();
			glTranslatef((6 - CIN.ci.wn2.pos[1]) * piece_width, CIN.ci.wn2.pos[0] * -piece_width, 0);
			chess_WN2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wn2.pos[0]][7 - CIN.ci.wn2.pos[1]] == 9)
		{
			glPushMatrix();
			glTranslatef((6 - CIN.ci.wn2.pos[1]) * piece_width, CIN.ci.wn2.pos[0] * -piece_width, 0);
			chess_WN2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wr1.pos[0]][CIN.ci.wr1.pos[1]] == 8)
		{
			glPushMatrix();
			glTranslatef(-CIN.ci.wr1.pos[1] * piece_width, -CIN.ci.wr1.pos[0] * piece_width, 0);
			chess_WR1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wr1.pos[0]][7 - CIN.ci.wr1.pos[1]] == 8)
		{
			glPushMatrix();
			glTranslatef(-CIN.ci.wr1.pos[1] * piece_width, CIN.ci.wr1.pos[0] * -piece_width, 0);
			chess_WR1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wr2.pos[0]][CIN.ci.wr2.pos[1]] == 8)
		{
			glPushMatrix();
			glTranslatef((7 - CIN.ci.wr2.pos[1]) * piece_width, -CIN.ci.wr2.pos[0] * piece_width, 0);
			chess_WR2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wr2.pos[0]][7 - CIN.ci.wr2.pos[1]] == 8)
		{
			glPushMatrix();
			glTranslatef((7 - CIN.ci.wr2.pos[1]) * piece_width, CIN.ci.wr2.pos[0] * -piece_width, 0);
			chess_WR2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wp1.pos[0]][CIN.ci.wp1.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef(-CIN.ci.wp1.pos[1] * piece_width, (CIN.ci.wp1.pos[0] - 1) * -piece_width, 0);
			chess_WP1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wp1.pos[0]][7 - CIN.ci.wp1.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef(CIN.ci.wp1.pos[1] * -piece_width, (CIN.ci.wp1.pos[0] - 1) * -piece_width, 0);
			chess_WP1.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wp2.pos[0]][CIN.ci.wp2.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((1 - CIN.ci.wp2.pos[1]) * piece_width, (CIN.ci.wp2.pos[0] - 1) * -piece_width, 0);
			chess_WP2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wp2.pos[0]][7 - CIN.ci.wp2.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((1 - CIN.ci.wp2.pos[1]) * piece_width, (CIN.ci.wp2.pos[0] - 1) * -piece_width, 0);
			chess_WP2.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wp3.pos[0]][CIN.ci.wp3.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((2 - CIN.ci.wp3.pos[1]) * piece_width, (CIN.ci.wp3.pos[0] - 1) * -piece_width, 0);
			chess_WP3.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wp3.pos[0]][7 - CIN.ci.wp3.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((2 - CIN.ci.wp3.pos[1]) * piece_width, (CIN.ci.wp3.pos[0] - 1) * -piece_width, 0);
			chess_WP3.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wp4.pos[0]][CIN.ci.wp4.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((3 - CIN.ci.wp4.pos[1]) * piece_width, (CIN.ci.wp4.pos[0] - 1) * -piece_width, 0);
			chess_WP4.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wp4.pos[0]][7 - CIN.ci.wp4.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((3 - CIN.ci.wp4.pos[1]) * piece_width, (CIN.ci.wp4.pos[0] - 1) * -piece_width, 0);
			chess_WP4.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wp5.pos[0]][CIN.ci.wp5.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((4 - CIN.ci.wp5.pos[1]) * piece_width, (CIN.ci.wp5.pos[0] - 1) * -piece_width, 0);
			chess_WP5.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wp5.pos[0]][7 - CIN.ci.wp5.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((4 - CIN.ci.wp5.pos[1]) * piece_width, (CIN.ci.wp5.pos[0] - 1) * -piece_width, 0);
			chess_WP5.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wp6.pos[0]][CIN.ci.wp6.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((5 - CIN.ci.wp6.pos[1]) * piece_width, (CIN.ci.wp6.pos[0] - 1) * -piece_width, 0);
			chess_WP6.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wp6.pos[0]][7 - CIN.ci.wp6.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((5 - CIN.ci.wp6.pos[1]) * piece_width, (CIN.ci.wp6.pos[0] - 1) * -piece_width, 0);
			chess_WP6.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wp7.pos[0]][CIN.ci.wp7.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((6 - CIN.ci.wp7.pos[1]) * piece_width, (CIN.ci.wp7.pos[0] - 1) * -piece_width, 0);
			chess_WP7.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wp7.pos[0]][7 - CIN.ci.wp7.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((6 - CIN.ci.wp7.pos[1]) * piece_width, (CIN.ci.wp7.pos[0] - 1) * -piece_width, 0);
			chess_WP7.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}

	if (chessMyColor == 0)
	{
		if (chessMap[7 - CIN.ci.wp8.pos[0]][CIN.ci.wp8.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((7 - CIN.ci.wp8.pos[1]) * piece_width, (CIN.ci.wp8.pos[0] - 1) * -piece_width, 0);
			chess_WP8.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		if (chessMap[CIN.ci.wp8.pos[0]][7 - CIN.ci.wp8.pos[1]] == 7)
		{
			glPushMatrix();
			glTranslatef((7 - CIN.ci.wp8.pos[1]) * piece_width, (CIN.ci.wp8.pos[0] - 1) * -piece_width, 0);
			chess_WP8.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
	}


	if (chessMyColor == 0)
	{
		if((found1 ==false && chessMyColor == 0) || (found2 == false && chessMyColor == 1))
		{
			if(terminate_anim_count > (TARMINATE_ANIM_SPEED * 29) - 1)
			{
				game[0].stts = 5;

				mainloopcount = 2;
				UnloadChessMesh();

				printf("chess in game\n");
				scene = scene_4;			
				SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
				SDL_ShowCursor(SDL_DISABLE);
				myPosition.z = 2.5;		
				initChessPos();
				found1 = true;
				found2 = true;
				original_turn = 0;
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
				for(int i = 0;i< 30;i++)
				{
					if(my_result[i] == 0)
					{
						my_result[i] = chess_win;
						break;
					}
				}
			}
		}
		else if((found1 ==false && chessMyColor == 1) || (found2 == false && chessMyColor == 0))
		{
			if(terminate_anim_count > (TARMINATE_ANIM_SPEED * 29) - 1)
			{
				game[0].stts = 5;

				mainloopcount = 2;
				UnloadChessMesh();

				printf("chess in game\n");
				scene = scene_4;			
				SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
				SDL_ShowCursor(SDL_DISABLE);
				myPosition.z = 2.5;		
				initChessPos();
				found1 = true;
				found2 = true;
				original_turn = 0;
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
				for(int i = 0;i< 30;i++)
				{
					if(my_result[i] == 0)
					{
						my_result[i] = chess_lose;
						break;
					}
				}
			}
		}
	}
	else
	{
		if((found1 ==false && chessMyColor == 0) || (found2 == false && chessMyColor == 1))
		{
			if(terminate_anim_count > (TARMINATE_ANIM_SPEED * 29) - 1)
			{
				game[0].stts = 5;

				mainloopcount = 2;
				UnloadChessMesh();
				scene = scene_4;			
				SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
				SDL_ShowCursor(SDL_DISABLE);
				myPosition.z = 2.5;		
				found1 = true;
				found2 = true;
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
				for(int i = 0;i< 30;i++)
				{
					if(my_result[i] == 0)
					{
						my_result[i] = chess_win;
						break;
					}
				}
			}
		}
		else if((found1 ==false && chessMyColor == 1) || (found2 == false && chessMyColor == 0))
		{
			if(terminate_anim_count > (TARMINATE_ANIM_SPEED * 29) - 1)
			{
				game[0].stts = 5;

				mainloopcount = 2;
				UnloadChessMesh();
				scene = scene_4;			
				SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
				SDL_ShowCursor(SDL_DISABLE);
				found1 = true;
				found2 = true;
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
				myPosition.z = 2.5;					
				for(int i = 0;i< 30;i++)
				{
					if(my_result[i] == 0)
					{
						my_result[i] = chess_lose;
						break;
					}
				}
			}
		}
	}


}

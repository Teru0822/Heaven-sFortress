#include "func.h"


extern float sita;
extern float alpha;
extern float sports_wheelR;
extern float sports_body_vec;
extern float sports_vec;
extern int my_id;
extern int torque;
extern int animFrame;
extern int mainloopcount;
extern uint8_t my_result[30];
extern int fin;
extern int tarminalTime;

extern Position lookingPosition;
extern Position AIMPos;
extern Position myPosition;
extern Scene scene;
extern vihicle sportsPos;
extern Game game[4];
extern obj sports_mainBody;
extern obj sports_plane;
extern obj sports_wheel_right;
extern obj sports_wheel_left;
extern obj sports_road;
extern obj sports_back;
extern obj sports_speedtext;
extern obj sports_speedtext_red;
extern obj sports_stick;
extern obj sports_grass;
extern obj sports_dirt;
extern obj sports_tire;
extern obj sports_wall;
extern obj skyOutSide;
extern obj skyOutSide;
extern obj skyOutSide;
extern obj map_wall;
extern obj map_tire;
extern obj map_road;
extern obj map_grass;
extern obj map_player;
extern obj sports_lap;
extern obj sports2_mainbody;
extern obj sports2_plane;
extern obj sports2_right;
extern obj sports2_left;
extern obj anim_1st_1[29];
extern obj anim_1st_s[29];
extern obj anim_1st_t[29];
extern obj anim_2nd_2[29];
extern obj anim_2nd_n[29];
extern obj anim_2nd_d[29];
extern obj anim_3rd_3[29];
extern obj anim_3rd_r[29];
extern obj anim_3rd_d[29];
extern obj anim_4th_4[29];
extern obj anim_4th_t[29];
extern obj anim_4th_h[29];
extern obj sports_1st;
extern obj sports_2nd;
extern obj sports_3rd;
extern obj sports_4th;
extern obj text_go;
extern obj sports3_Right;
extern obj sports3_Left;
extern obj sports3_mainbody;
extern obj sports3_plane;
extern obj sports4_Right;
extern obj sports4_Left;
extern obj sports4_mainbody;
extern obj sports4_plane;
extern obj waitingforplayers;

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

extern void makeEnemySportsCar();

std::pair<double, double> W2D(float x,float y)
{
	std::pair<double, double> pair_d;
	pair_d.first = -0.07744715362787247 - (0.0920522138476372 * (x + 43.298828125) / 742.7169189453125);
	pair_d.second = -0.000623 + (0.092053 * (y + 350.27423095703125) / 742.7166137695312);

	return pair_d;
}

void scene7(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);
	if(fin == false)
	{
		if(animFrame > 280)
			sportsMotionController();
	}
	animFrame++;
	CollisionController();
	unsigned int angleZ = sin(lookingPosition.z * 20.0 / 180.0 * PI);

	AIMPos.x = sportsPos.x - (sin(lookingPosition.x * 20.0 / 180.0 * PI) * (1.0 - angleZ));
	AIMPos.y = sportsPos.y + (cos(lookingPosition.x * 20.0 / 180.0 * PI) * (1.0 - angleZ));
	AIMPos.z = (sin(lookingPosition.z * 20.0 / 180.0 * PI) * 2.0);

	sita = atan2(AIMPos.z, 1);

	float aa = (alpha * 180.0f / PI) + 90.0f;
	float bb = -sports_body_vec;
	if (aa - bb > 0.0f)
	{
		alpha -= (aa - bb) * 0.1f * PI / 180.0f;
	}
	else if (aa - bb < 0.0f)
	{
		alpha -= (aa - bb) * 0.1f * PI / 180.0f;
	}

	double aimX = sportsPos.x + (cosf(sita) * cosf(alpha)) * 10;
	double aimY = sportsPos.y + (cosf(sita) * sinf(alpha)) * 10;
	double aimZ = sinf(sita);

	double lpx = sportsPos.x - (aimX - sportsPos.x);
	double lpy = sportsPos.y - (aimY - sportsPos.y);

	gluLookAt(lpx, lpy, (-aimZ * 15) + 5,
		aimX, aimY, aimZ,
		0, 0, 1);

	double radian = sportsPos.vecX * 180.0 / PI;
	double angle_tank = (radian * 180.0 / PI);

	double l = sqrt((aimX - lpx) * (aimX - lpx) + (aimY - lpy) * (aimY - lpy) + (aimZ - (-aimZ * 15.0) - 5.0) * (aimZ - (-aimZ * 15.0) - 5.0));
	double xyl = sqrt((aimX - lpx) * (aimX - lpx) + (aimY - lpy) * (aimY - lpy));
	double ls = atan2((aimZ - (-aimZ * 15.0) - 5.0), xyl);


	//everyone fin
	if(checkGameStts(1,7) == game[1].p_NUM - 1 && game[1].stts == 7)
	{
		if(tarminalTime < 180)
		{
			tarminalTime++;
		}
		else
		{
			//load inside park
			mainloopcount = 2;
			
			UnloadRaceMesh();

			myPosition.z = 2.5;
			scene = scene_4;
			sportsPos.x = 0;
			sportsPos.y = 0;
			sportsPos.z = 0.2;
			sportsPos.vecX = 0;
			sportsPos.vecY = -1.0;
			sportsPos.lap = 0;
			tarminalTime = 0;
			torque = 0;			
			switch (fin)
			{
			case 1:
				for(int i = 0;i< 30;i++)
				{
					if(my_result[i] == 0)
					{
						my_result[i] = race_1st;
						break;
					}
				}
				break;
			case 2:
				for(int i = 0;i< 30;i++)
				{
					if(my_result[i] == 0)
					{
						my_result[i] = race_2nd;
						break;
					}
				}
				break;
			case 3:
				for(int i = 0;i< 30;i++)
				{
					if(my_result[i] == 0)
					{
						my_result[i] = race_3rd;
						break;
					}
				}
				break;
			case 4:
				for(int i = 0;i< 30;i++)
				{
					if(my_result[i] == 0)
					{
						my_result[i] = race_4th;
						break;
					}
				}
				break;			
			}
			fin = 0;
		}
	}

	glPushMatrix();
	glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
	glRotatef(alpha / PI * 180.0, 0, 0, 1);
	glRotatef(ls / PI * 180.0, 0, -1, 0);
	glTranslatef(0, -0.118429534137248994, -0.06189822033047676);
	sports_speedtext.make(1.0f,1.0f,1.0f);
	sports_speedtext_red.make(1.0f,0.0f,0.0f);
	sports_back.make(0.0f,0.0f,0.0f);
	glRotatef(torque / speedLev * 237.56 / 210.0, 1, 0, 0);
	sports_stick.make(1, 0, 0);
	glPopMatrix();

	std::pair<double, double> dd = W2D(sportsPos.x, sportsPos.y);
	glPushMatrix();
	glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
	glRotatef(alpha / PI * 180.0, 0, 0, 1);
	glRotatef(ls / PI * 180.0, 0, -1, 0);
	map_wall.makeWithTex(1.0f, 1.0f, 1.0f);
	map_grass.makeWithTex(1.0f, 1.0f, 1.0f);
	map_road.makeWithTex(1.0f, 1.0f, 1.0f);
	map_tire.makeWithTex(1.0f, 1.0f, 1.0f);
	sports_lap.make(1.0f, 1.0f, 1.0f);

	if(animFrame < 340)
	{
		if(animFrame < 160 && animFrame > 100)
		{
			num_3.make(1.0f,1.0f,1.0f);
		}
		else if(animFrame <= 220 && animFrame > 160)
		{
			num_2.make(1.0f,1.0f,1.0f);
		}
		else if(animFrame <= 280 && animFrame > 220)
		{
			num_1.make(1.0f,1.0f,1.0f);
		}
		else if(animFrame <= 340 && animFrame > 280)
		{
			text_go.make(1.0f,1.0f,1.0f);
		}
	}

	if(fin == 1)
	{
		makeAnim(1.0f,1.0f,1.0f,anim_1st_1,anim_1st_1[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_1st_s,anim_1st_s[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_1st_t,anim_1st_t[0].textureID,animFrame / 3,29);
	}
	else if (fin == 2)
	{
		makeAnim(1.0f,1.0f,1.0f,anim_2nd_2,anim_2nd_2[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_2nd_n,anim_2nd_n[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_2nd_d,anim_2nd_d[0].textureID,animFrame / 3,29);
	}
	else if(fin == 3)
	{
		makeAnim(1.0f,1.0f,1.0f,anim_3rd_3,anim_3rd_3[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_3rd_r,anim_3rd_r[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_3rd_d,anim_3rd_d[0].textureID,animFrame / 3,29);
	}
	else if(fin == 4)
	{
		makeAnim(1.0f,1.0f,1.0f,anim_4th_4,anim_4th_4[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_4th_t,anim_4th_t[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_4th_h,anim_4th_h[0].textureID,animFrame / 3,29);
	}

	switch (game[1].gameLap)
	{
	case 2:
		glPushMatrix();
		glTranslatef(0, 0.095528, -0.061803);
		num_2.make(1, 1, 1);
		glPopMatrix();
		break;
	case 3:
		glPushMatrix();
		glTranslatef(0, 0.095528, -0.061803);
		num_3.make(1, 1, 1);
		glPopMatrix();
		break;
	case 4:
		glPushMatrix();
		glTranslatef(0, 0.095528, -0.061803);
		num_4.make(1, 1, 1);
		glPopMatrix();
		break;
	}
	switch (sportsPos.lap)
	{
	case 0:
		glPushMatrix();
		glTranslatef(0, 0.111901, -0.061803);
		num_0.make(1, 1, 1);
		glPopMatrix();
		break;
	case 1:
		glPushMatrix();
		glTranslatef(0, 0.111901, -0.061803);
		num_1.make(1, 1, 1);
		glPopMatrix();
		break;
	case 2:
		glPushMatrix();
		glTranslatef(0, 0.111901, -0.061803);
		num_2.make(1, 1, 1);
		glPopMatrix();
		break;
	case 3:
		if(fin > 0)
		{
			glPushMatrix();
			glTranslatef(0, 0.111901, -0.061803);
			num_2.make(1, 1, 1);
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glTranslatef(0, 0.111901, -0.061803);
			num_3.make(1, 1, 1);
			glPopMatrix();
		}
		break;
	case 4:
		if(fin > 0)
		{
			glPushMatrix();
			glTranslatef(0, 0.111901, -0.061803);
			num_3.make(1, 1, 1);
			glPopMatrix();
		}
		else
		{
			glPushMatrix();
			glTranslatef(0, 0.111901, -0.061803);
			num_4.make(1, 1, 1);
			glPopMatrix();
		}
		break;
	case 5:
		if(fin > 0)
		{
			glPushMatrix();
			glTranslatef(0, 0.111901, -0.061803);
			num_4.make(1, 1, 1);
			glPopMatrix();			
		}
		break;
	}

	glPushMatrix();
	glTranslatef(-0.000099,dd.first, dd.second);
	glRotatef(sports_body_vec, 1, 0, 0);
	switch (my_id)
	{
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

	makeEnemySportsCarIcon();

	glPopMatrix();

	sportsPos.angle = -sports_body_vec;
	int sp = torque / speedLev;

	if (sp < 10)
	{
		switch (sp)
		{
		case 0:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1204, -0.061803);
			num_0.make(1, 1, 1);
			glPopMatrix();
			break;
		case 1:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1204, -0.061803);
			num_1.make(1, 1, 1);
			glPopMatrix();
			break;
		case 2:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1204, -0.061803);
			num_2.make(1, 1, 1);
			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1204, -0.061803);
			num_3.make(1, 1, 1);
			glPopMatrix();
			break;
		case 4:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1204, -0.061803);
			num_4.make(1, 1, 1);
			glPopMatrix();
			break;
		case 5:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1204, -0.061803);
			num_5.make(1, 1, 1);
			glPopMatrix();
			break;
		case 6:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1204, -0.061803);
			num_6.make(1, 1, 1);
			glPopMatrix();
			break;
		case 7:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1204, -0.061803);
			num_7.make(1, 1, 1);
			glPopMatrix();
			break;
		case 8:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1204, -0.061803);
			num_8.make(1, 1, 1);
			glPopMatrix();
			break;
		case 9:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1204, -0.061803);
			num_9.make(1, 1, 1);
			glPopMatrix();
			break;
		default:
			break;
		}
	}
	else if (sp >= 10 && sp < 100)
	{
		int s1 = sp % 10;
		switch (s1)
		{
		case 0:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.123835, -0.061803);
			num_0.make(1, 1, 1);
			glPopMatrix();
			break;
		case 1:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.123835, -0.061803);
			num_1.make(1, 1, 1);
			glPopMatrix();
			break;
		case 2:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.123835, -0.061803);
			num_2.make(1, 1, 1);
			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.123835, -0.061803);
			num_3.make(1, 1, 1);
			glPopMatrix();
			break;
		case 4:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.123835, -0.061803);
			num_4.make(1, 1, 1);
			glPopMatrix();
			break;
		case 5:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.123835, -0.061803);
			num_5.make(1, 1, 1);
			glPopMatrix();
			break;
		case 6:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.123835, -0.061803);
			num_6.make(1, 1, 1);
			glPopMatrix();
			break;
		case 7:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.123835, -0.061803);
			num_7.make(1, 1, 1);
			glPopMatrix();
			break;
		case 8:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.123835, -0.061803);
			num_8.make(1, 1, 1);
			glPopMatrix();
			break;
		case 9:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.123835, -0.061803);
			num_9.make(1, 1, 1);
			glPopMatrix();
			break;
		default:
			break;
		}

		int s2 = sp / 10;
		switch (s2)
		{
		case 1:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.115798, -0.061803);
			num_1.make(1, 1, 1);
			glPopMatrix();
			break;
		case 2:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.115798, -0.061803);
			num_2.make(1, 1, 1);
			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.115798, -0.061803);
			num_3.make(1, 1, 1);
			glPopMatrix();
			break;
		case 4:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.115798, -0.061803);
			num_4.make(1, 1, 1);
			glPopMatrix();
			break;
		case 5:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.115798, -0.061803);
			num_5.make(1, 1, 1);
			glPopMatrix();
			break;
		case 6:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.115798, -0.061803);
			num_6.make(1, 1, 1);
			glPopMatrix();
			break;
		case 7:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.115798, -0.061803);
			num_7.make(1, 1, 1);
			glPopMatrix();
			break;
		case 8:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.115798, -0.061803);
			num_8.make(1, 1, 1);
			glPopMatrix();
			break;
		case 9:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.115798, -0.061803);
			num_9.make(1, 1, 1);
			glPopMatrix();
			break;
		default:
			break;
		}

	}
	else if (sp >= 100)
	{
		int s1 = sp % 10;
		switch (s1)
		{
		case 0:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.126184, -0.061803);
			num_0.make(1, 1, 1);
			glPopMatrix();
			break;
		case 1:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.126184, -0.061803);
			num_1.make(1, 1, 1);
			glPopMatrix();
			break;
		case 2:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.126184, -0.061803);
			num_2.make(1, 1, 1);
			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.126184, -0.061803);
			num_3.make(1, 1, 1);
			glPopMatrix();
			break;
		case 4:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.126184, -0.061803);
			num_4.make(1, 1, 1);
			glPopMatrix();
			break;
		case 5:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.126184, -0.061803);
			num_5.make(1, 1, 1);
			glPopMatrix();
			break;
		case 6:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.126184, -0.061803);
			num_6.make(1, 1, 1);
			glPopMatrix();
			break;
		case 7:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.126184, -0.061803);
			num_7.make(1, 1, 1);
			glPopMatrix();
			break;
		case 8:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.126184, -0.061803);
			num_8.make(1, 1, 1);
			glPopMatrix();
			break;
		case 9:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.126184, -0.061803);
			num_9.make(1, 1, 1);
			glPopMatrix();
			break;
		default:
			break;
		}

		int s2 = sp / 10;
		int s22 = s2 % 10;
		switch (s22)
		{
		case 0:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1184, -0.061803);
			num_0.make(1, 1, 1);
			glPopMatrix();
			break;
		case 1:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1184, -0.061803);
			num_1.make(1, 1, 1);
			glPopMatrix();
			break;
		case 2:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1184, -0.061803);
			num_2.make(1, 1, 1);
			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1184, -0.061803);
			num_3.make(1, 1, 1);
			glPopMatrix();
			break;
		case 4:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1184, -0.061803);
			num_4.make(1, 1, 1);
			glPopMatrix();
			break;
		case 5:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1184, -0.061803);
			num_5.make(1, 1, 1);
			glPopMatrix();
			break;
		case 6:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1184, -0.061803);
			num_6.make(1, 1, 1);
			glPopMatrix();
			break;
		case 7:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1184, -0.061803);
			num_7.make(1, 1, 1);
			glPopMatrix();
			break;
		case 8:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1184, -0.061803);
			num_8.make(1, 1, 1);
			glPopMatrix();
			break;
		case 9:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.1184, -0.061803);
			num_9.make(1, 1, 1);
			glPopMatrix();
			break;
		default:
			break;
		}

		int s3 = sp / 100;
		switch (s3)
		{
		case 1:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.110213, -0.061803);
			num_1.make(1, 1, 1);
			glPopMatrix();
			break;
		case 2:
			glPushMatrix();
			glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), (-aimZ * 15) + 5 + 0.12 * ((aimZ - (-aimZ * 15.0) - 5.0) / l));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(ls / PI * 180.0, 0, -1, 0);
			glTranslatef(0, -0.110213, -0.061803);
			num_2.make(1, 1, 1);
			glPopMatrix();
			break;
		}
	}


	sports_wheelR += torque / speedLev;

	if(sportsPos.type == 0)
	{
		switch (my_id) {
		case 0:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports_mainBody.makeWithTex_Color(0.6, 0, 0);
			sports_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		case 1:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports_mainBody.makeWithTex_Color(0, 0.6, 0);
			sports_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		case 2:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports_mainBody.makeWithTex_Color(0, 0, 0.6);
			sports_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports_mainBody.makeWithTex_Color(0.6, 0.6, 0.0);
			sports_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		default:
			break;
		}
		//右前
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(-1.79055, -2.9316, 0.718507);
		glRotatef(sports_vec, 0, 0, -1);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports_wheel_right.makeWithTex(1, 1, 1);
		glPopMatrix();
		//左前
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(1.79055, -2.9316, 0.718507);
		glRotatef(sports_vec, 0, 0, -1);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports_wheel_left.makeWithTex(1, 1, 1);
		glPopMatrix();
		//右後
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(-1.78345, 3.11515, 0.718507);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports_wheel_right.makeWithTex(1, 1, 1);
		glPopMatrix();
		//左後
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(1.78345, 3.11515, 0.718507);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports_wheel_left.makeWithTex(1, 1, 1);
		glPopMatrix();
	}
	else if(sportsPos.type == 1)
	{
		switch (my_id) {
		case 0:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports2_mainbody.makeWithTex_Color(0.6, 0, 0);
			sports2_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		case 1:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports2_mainbody.makeWithTex_Color(0, 0.6, 0);
			sports2_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		case 2:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports2_mainbody.makeWithTex_Color(0, 0, 0.6);
			sports2_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports2_mainbody.makeWithTex_Color(0.6, 0.6, 0.0);
			sports2_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		default:
			break;
		}
		//右前
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(-1.78683f, -3.24491f, 0.688572f);
		glRotatef(sports_vec, 0, 0, -1);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports2_right.makeWithTex(1, 1, 1);
		glPopMatrix();
		//左前
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(1.79631f, -3.24491f, 0.688572f);
		glRotatef(sports_vec, 0, 0, -1);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports2_left.makeWithTex(1, 1, 1);
		glPopMatrix();
		//右後
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(-1.78683f, 3.12798f, 0.688572f);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports2_right.makeWithTex(1, 1, 1);
		glPopMatrix();
		//左後
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(1.79631f, 3.12798f, 0.688572f);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports2_left.makeWithTex(1, 1, 1);
		glPopMatrix();
	}
	else if(sportsPos.type == 2)
	{
		switch (my_id) {
		case 0:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports3_mainbody.makeWithTex_Color(0.6, 0, 0);
			sports3_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		case 1:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports3_mainbody.makeWithTex_Color(0, 0.6, 0);
			sports3_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		case 2:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports3_mainbody.makeWithTex_Color(0, 0, 0.6);
			sports3_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports3_mainbody.makeWithTex_Color(0.6, 0.6, 0.0);
			sports3_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		default:
			break;
		}
		//右前
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(-1.6384f, -4.49f, 0.97888f);
		glRotatef(sports_vec, 0, 0, -1);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports3_Right.makeWithTex(1, 1, 1);
		glPopMatrix();
		//左前
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(2.0119f, -4.49f, 0.97888f);
		glRotatef(sports_vec, 0, 0, -1);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports3_Left.makeWithTex(1, 1, 1);
		glPopMatrix();
		//右後
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(-1.783f, 3.02f, 1.0067f);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports3_Right.makeWithTex(1, 1, 1);
		glPopMatrix();
		//左後
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(2.1437f, 3.02f, 1.0067f);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports3_Left.makeWithTex(1, 1, 1);
		glPopMatrix();
	}
	else if(sportsPos.type == 3)
	{
		switch (my_id) {
		case 0:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports4_mainbody.makeWithTex_Color(0.6, 0, 0);
			sports4_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		case 1:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports4_mainbody.makeWithTex_Color(0, 0.6, 0);
			sports4_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		case 2:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports4_mainbody.makeWithTex_Color(0, 0, 0.6);
			sports4_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
			glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
			glRotatef(-sports_body_vec, 0, 0, 1);
			sports4_mainbody.makeWithTex_Color(0.6, 0.6, 0.0);
			sports4_plane.makeWithTex_Color(1.0f,1.0f,1.0f);
			glPopMatrix();
			break;
		default:
			break;
		}
		//右前
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(-1.6383f, -2.271f, 0.93348f);
		glRotatef(sports_vec, 0, 0, -1);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports4_Right.makeWithTex(1, 1, 1);
		glPopMatrix();
		//左前
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(2.291f, -2.271f, 0.93348f);
		glRotatef(sports_vec, 0, 0, -1);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports4_Left.makeWithTex(1, 1, 1);
		glPopMatrix();
		//右後
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(-1.6383f, 1.8535f, 0.93348f);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports4_Right.makeWithTex(1, 1, 1);
		glPopMatrix();
		//左後
		glPushMatrix();
		glTranslatef(sportsPos.x, sportsPos.y, sportsPos.z);
		glRotatef(-sports_body_vec, 0, 0, 1);
		glTranslatef(2.291f, 1.8535f, 0.93348f);
		glRotatef(sports_wheelR, 1, 0, 0);
		sports4_Left.makeWithTex(1, 1, 1);
		glPopMatrix();		
	}

	makeEnemySportsCar();

	sports_dirt.makeWithTex(1, 1, 1);
	sports_grass.makeWithTex(1, 1, 1);
	sports_tire.makeWithTex(1, 1, 1);
	sports_wall.makeWithTex(1, 1, 1);
	sports_road.makeWithTex(1, 1, 1);
	skyOutSide.makeWithTex(1, 1, 1);

}

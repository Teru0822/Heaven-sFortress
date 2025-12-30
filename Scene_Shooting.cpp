#include "func.h"

extern SDL_Window* window;
extern Scene scene;
extern Game game[4];
extern Position lookingPosition;
extern Position AIMPos;
extern Position myPosition;
extern uint8_t my_result[30];
extern bool onFire;
extern bool pressA;
extern bool pressD;
extern bool pressS;
extern bool pressW;
u_int8_t can_get = 0;
extern int onFire_frame_count;
extern int weapon_aiming_torigger;
extern int fin;
extern int animFrame;
extern int mainloopcount;
extern int tarminalTime;
extern int my_kill_count;
extern int my_id;
extern float sita;
extern float alpha;
extern float  weapon_aiming;
extern float weapon_moving_anim;

extern obj Reciever;
extern obj Foregrip;
extern obj Handguard;
extern obj Scope;
extern obj Silencer;
extern obj Stock;
extern obj Base;
extern obj Mount;
extern obj Charge;
extern obj Hand;
extern obj Ret;
extern obj base_ground;
extern obj inner_ground;
extern obj labslogo;
extern obj stair_flat;
extern obj stair_long;
extern obj stair_naname;
extern obj lightPM;
extern obj tarkov_fence;
extern obj rooms;
extern obj fireFlash;
extern obj ui_key;
extern obj ui_ammo;
extern obj item_case_1;
extern obj item_case_2;
extern obj tarkov_item_egg;
extern obj tarkov_item_cat;
extern obj tarkov_item_ledx;
extern obj getitem;
extern obj escape1;
extern obj escape2;
extern obj escape3;
extern cheapObj num_1;
extern cheapObj num_2;
extern cheapObj num_3;
extern obj text_go;
extern obj text_l[29];
extern obj text_o[29];
extern obj text_s[29];
extern obj text_e[29];
extern obj anim_survived_s[29];
extern obj anim_survived_u[29];
extern obj anim_survived_r[29];
extern obj anim_survived_v1[29];
extern obj anim_survived_i[29];
extern obj anim_survived_v2[29];
extern obj anim_survived_e[29];
extern obj anim_survived_d[29];

extern void make_MYHP();

bool coltype = false;
bool firing;
int rotate_angle = 0;
int escape_count = 0;

extern void makeEnemyPeople_T(int);

bool search_item_cheap()
{
	for(int i = 0;i < 4; i++)
	{
		if(game[2].havingItems[i] == 1 || game[2].havingItems[i] == 4 || game[2].havingItems[i] == 6 || game[2].havingItems[i] == 9)
		{
			return false;
		}
	}
	return true;
}

bool search_item_normal()
{
	for(int i = 0;i < 4; i++)
	{
		if(game[2].havingItems[i] == 3 || game[2].havingItems[i] == 4 || game[2].havingItems[i] == 8 || game[2].havingItems[i] == 9)
		{
			return false;
		}
	}
	return true;
}

bool search_item_expensive()
{
	for(int i = 0;i < 4; i++)
	{
		if(game[2].havingItems[i] == 5 || game[2].havingItems[i] == 6 || game[2].havingItems[i] == 8 || game[2].havingItems[i] == 9)
		{
			return false;
		}
	}
	return true;
}

void scene8(int x, int y, int w, int h)
{
	glViewport(x, y, w, h);
	CollisionController();
	//printf("myZ : %f\n",myPosition.z);
	if(fin == 0)
	{
		if(animFrame > 280)
			motionController_T();
	}
	unsigned int angleZ = sin(lookingPosition.z * 20.0 / 180.0 * PI);
	firing = false;
	if (onFire == true)
	{
		onFire_frame_count++;
		if (onFire_frame_count % 6 == 0)
		{
			int r = rand() % 3;
			if (r == 0)
			{
				lookingPosition.x += 0.01;
				lookingPosition.z += 0.01;
			}
			else if (r == 1)
			{
				lookingPosition.x -= 0.01;
				lookingPosition.z += 0.015;
			}
			else if (r == 2)
			{
				lookingPosition.x -= 0.005;
				lookingPosition.z += 0.02;
			}
			firing = true;
		}
	}

	AIMPos.x = myPosition.x - (sin(lookingPosition.x * 20.0 / 180.0 * PI) * (1.0 - angleZ));
	AIMPos.y = myPosition.y + (cos(lookingPosition.x * 20.0 / 180.0 * PI) * (1.0 - angleZ));
	AIMPos.z = 0.5 + (sin(lookingPosition.z * 20.0 / 180.0 * PI) * 2.0);

	sita = atan2(AIMPos.z, 1);
	alpha = atan2(AIMPos.y - myPosition.y, AIMPos.x - myPosition.x);


	double aimX = myPosition.x + (cosf(sita) * cosf(alpha));
	double aimY = myPosition.y + (cosf(sita) * sinf(alpha));
	double aimZ = myPosition.z + sinf(sita);
	gluLookAt(myPosition.x, myPosition.y, myPosition.z,
		aimX, aimY, aimZ,
		0, 0, 1);

	glPushMatrix();
	glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11), myPosition.y + ((aimY - myPosition.y) * 0.11), myPosition.z + ((aimZ - myPosition.z) * 0.11));
	glRotatef(alpha / PI * 180.0, 0, 0, 1);
	glRotatef(sita / PI * 180.0, 0, -1, 0);
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
	if(myPosition.x > 55.525f && myPosition.x < 59.525f && myPosition.y > 15.631f && myPosition.y < 19.631f)
	{
		escape_count++;
		if(escape_count > 0 && escape_count < 60)
		{
			num_3.make(1.0f,1.0f,1.0f);
		} 
		else if(escape_count >= 60 && escape_count < 120)
		{
			num_2.make(1.0f,1.0f,1.0f);
		}
		else if(escape_count >= 120 && escape_count < 180)
		{
			num_1.make(1.0f,1.0f,1.0f);
		}
		else if(escape_count >= 180)
		{
			game[2].stts = 5;
			fin = 4;
		}
	}
	else if(myPosition.x > 37.063f && myPosition.x < 41.063f && myPosition.y > -13.428f && myPosition.y < -9.4279f && myPosition.z > 6.5f)
	{
		escape_count++;
		if(escape_count > 0 && escape_count < 60)
		{
			num_3.make(1.0f,1.0f,1.0f);
		} 
		else if(escape_count >= 60 && escape_count < 120)
		{
			num_2.make(1.0f,1.0f,1.0f);
		}
		else if(escape_count >= 120 && escape_count < 180)
		{
			num_1.make(1.0f,1.0f,1.0f);
		}
		else if(escape_count >= 180)
		{
			game[2].stts = 5;
			fin = 4;
		}
	}
	else if(myPosition.x > -56.187f && myPosition.x < -52.187f && myPosition.y > 30.432f && myPosition.y < 34.432f && myPosition.z > 6.5f)
	{
		escape_count++;
		if(escape_count > 0 && escape_count < 60)
		{
			num_3.make(1.0f,1.0f,1.0f);
		} 
		else if(escape_count >= 60 && escape_count < 120)
		{
			num_2.make(1.0f,1.0f,1.0f);
		}
		else if(escape_count >= 120 && escape_count < 180)
		{
			num_1.make(1.0f,1.0f,1.0f);
		}
		else if(escape_count >= 180)
		{
			game[2].stts = 5;
			fin = 4;
		}
	}
	else
	{
		escape_count = 0;
	}
	ui_key.make(1,1,1);
	ui_ammo.make(1,1,1);
	make_MYHP();
	if(fin == 1)
	{
		makeAnim(1.0f,1.0f,1.0f,text_l,text_l[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,text_o,text_o[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,text_s,text_s[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,text_e,text_e[0].textureID,animFrame / 3,29);
	}
	else if (fin == 2)
	{
		makeAnim(1.0f,1.0f,1.0f,text_l,text_l[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,text_o,text_o[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,text_s,text_s[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,text_e,text_e[0].textureID,animFrame / 3,29);
	}
	else if(fin == 3)
	{
		makeAnim(1.0f,1.0f,1.0f,text_l,text_l[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,text_o,text_o[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,text_s,text_s[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,text_e,text_e[0].textureID,animFrame / 3,29);
	}
	else if(fin == 4)
	{
		makeAnim(1.0f,1.0f,1.0f,anim_survived_s,anim_survived_s[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_survived_u,anim_survived_u[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_survived_r,anim_survived_r[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_survived_v1,anim_survived_v1[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_survived_i,anim_survived_i[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_survived_v2,anim_survived_v2[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_survived_e,anim_survived_e[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_survived_d,anim_survived_d[0].textureID,animFrame / 3,29);
	}
	glPopMatrix();

	
	if(checkGameStts(2,5) == game[2].p_NUM -1 && fin == 0)
	{
		game[2].stts = 5;
		fin = 4;
	}
	//everyone fin
	if(checkGameStts(2,5) == game[2].p_NUM - 1 && game[2].stts == 5)
	{
		if(tarminalTime < 180)
		{
			tarminalTime++;
		}
		else
		{
			//広場のロード
			mainloopcount = 2;
			//シューティングのアンロード
			UnloadShootingMesh();			
			SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
			SDL_ShowCursor(SDL_DISABLE);
			myPosition.z = 2.5;
			scene = scene_4;
			glViewport(0, 0, 1924, 1061);
			glMatrixMode(GL_PROJECTION);			// 射影行列を操作する
			glLoadIdentity();						// 行列を初期化
			gluPerspective(80.0, 1924.0 / 1061.0, 0.1, 5000);
			glMatrixMode(GL_MODELVIEW);
			switch (fin)
			{
			case 1:
			case 2:
			case 3:
				printf("my score : %d\n",game[2].havingItems[my_id]);
				for(int i = 0;i< 30;i++)
				{
					if(my_result[i] == 0)
					{
						for(int j = 0; j < my_kill_count;j++)
						{
							my_result[i+j] = shooting_kill;
						}
						if(game[2].havingItems[my_id] == 1)
						{
							my_result[i+my_kill_count] = get_item_cheap;
						}
						else if(game[2].havingItems[my_id] == 3)
						{
							my_result[i+my_kill_count] = get_item_normal;
						}
						else if(game[2].havingItems[my_id] == 5)
						{
							my_result[i+my_kill_count] = get_item_expensive;
						}
						else if(game[2].havingItems[my_id] == 4)
						{
							my_result[i+my_kill_count] = get_item_cheap;
							my_result[i+my_kill_count+1] = get_item_normal;
						}	
						else if(game[2].havingItems[my_id] == 6)
						{
							my_result[i+my_kill_count] = get_item_cheap;
							my_result[i+my_kill_count+1] = get_item_expensive;
						}
						else if(game[2].havingItems[my_id] == 8)
						{
							my_result[i+my_kill_count] = get_item_normal;
							my_result[i+my_kill_count+1] = get_item_expensive;							
						}	
						else if(game[2].havingItems[my_id] == 9)
						{
							my_result[i+my_kill_count] = get_item_cheap;
							my_result[i+my_kill_count+1] = get_item_normal;
							my_result[i+my_kill_count+2] = get_item_expensive;							
						}																
						break;
					}
				}
				break;
			case 4:
				printf("my score : %d\n",game[2].havingItems[my_id]);
				for(int i = 0;i< 30;i++)
				{
					if(my_result[i] == 0)
					{
						my_result[i] = shooting_survived;
						for(int j = 0; j < my_kill_count;j++)
						{
							my_result[i+j+1] = shooting_kill;
						}
						if(game[2].havingItems[my_id] == 1)
						{
							my_result[i+my_kill_count+1] = get_item_cheap;
						}
						else if(game[2].havingItems[my_id] == 3)
						{
							my_result[i+my_kill_count+1] = get_item_normal;
						}
						else if(game[2].havingItems[my_id] == 5)
						{
							my_result[i+my_kill_count+1] = get_item_expensive;
						}
						else if(game[2].havingItems[my_id] == 4)
						{
							my_result[i+my_kill_count+1] = get_item_cheap;
							my_result[i+my_kill_count+2] = get_item_normal;
						}	
						else if(game[2].havingItems[my_id] == 6)
						{
							my_result[i+my_kill_count+1] = get_item_cheap;
							my_result[i+my_kill_count+2] = get_item_expensive;							
						}
						else if(game[2].havingItems[my_id] == 8)
						{
							my_result[i+my_kill_count+1] = get_item_normal;
							my_result[i+my_kill_count+2] = get_item_expensive;							
						}	
						else if(game[2].havingItems[my_id] == 9)
						{
							my_result[i+my_kill_count+1] = get_item_cheap;
							my_result[i+my_kill_count+2] = get_item_normal;
							my_result[i+my_kill_count+3] = get_item_expensive;							
						}
						break;
					}
				}
				break;			
			}
			fin = 0;
		}
	}
	double s = 0.0;
	double a = 0.0;
	if (weapon_aiming_torigger == normalPos)
	{
		glPointSize(4);
		glBegin(GL_POINTS);
		glColor3f(1, 1, 1);
		glVertex3f(myPosition.x + ((aimX - myPosition.x) * 0.11), myPosition.y + ((aimY - myPosition.y) * 0.11), myPosition.z + ((aimZ - myPosition.z) * 0.11));
		glEnd();
		if (pressA == false && pressD == false && pressW == false && pressS == false)
		{
			weapon_moving_anim += 1.0;
			s = sinf(weapon_moving_anim * M_PI / 180.0) * 0.001;
			if (s < 0)
			{
				weapon_moving_anim += 1.0;
				s = sinf(weapon_moving_anim * M_PI / 180.0) * 0.0006;
			}
		}
		else
		{
			s = sinf(weapon_moving_anim * M_PI / 180.0) * 0.005;
			if (s < 0)
			{
				weapon_moving_anim += 1.0;
				s = sinf(weapon_moving_anim * M_PI / 180.0) * 0.003;
			}
		}
	}
	else
	{
		if (weapon_aiming_torigger == goingRight)
		{
			weapon_aiming -= 3.0;
		}
		else if (weapon_aiming_torigger == goingLeft)
		{
			weapon_aiming += 3.0;
		}
		else if (weapon_aiming_torigger == aimingPos)
		{
			weapon_moving_anim += 1.0;
			s = sinf(weapon_moving_anim * M_PI / 180.0) * 0.0007;
			if (s < 0)
			{
				weapon_moving_anim += 1.0;
				s = sinf(weapon_moving_anim * M_PI / 180.0) * 0.0004;
			}
		}
	}
	if (weapon_aiming <= 0.0)
	{
		weapon_aiming_torigger = normalPos;
	}
	else if (weapon_aiming >= 90.0)
	{
		weapon_aiming_torigger = aimingPos;
	}
	a = sinf(weapon_aiming * M_PI / 180.0) * 0.071757;

	myPosition.alpha = alpha;
	myPosition.sita = sita;	

	glPushMatrix();
	glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.28), myPosition.y + ((aimY - myPosition.y) * 0.28), myPosition.z + ((aimZ - myPosition.z) * 0.28));
	glRotatef((alpha / PI * 180.0) + 90.0, 0, 0, 1);
	glRotatef(sita / PI * 180.0, -1, 0, 0);
	glTranslatef(0, 0, s);
	glTranslatef(a, a * 0.6, a * 0.1);
	if (firing == true)
	{
		fireFlash.make(1, 1, 1);
	}
	Reciever.makeWithTex(0.8, 0.8, 0.8);
	Foregrip.makeWithTex(0.8, 0.8, 0.8);
	Handguard.makeWithTex(0.8, 0.8, 0.8);
	Scope.makeWithTex(0.8, 0.8, 0.8);
	Silencer.makeWithTex(0.8, 0.8, 0.8);
	Stock.makeWithTex(0.8, 0.8, 0.8);
	Base.makeWithTex(0.8, 0.8, 0.8);
	Mount.makeWithTex(0.8, 0.8, 0.8);
	Charge.makeWithTex(0.8, 0.8, 0.8);
	Hand.makeWithTex(0.8, 0.8, 0.8);
	Ret.makeWithTex(1, 1, 1);
	glPopMatrix();

	base_ground.makeWithTex(1, 1, 1);
	inner_ground.makeWithTex(1, 1, 1);
	stair_flat.makeWithTex(1, 1, 1);
	stair_naname.makeWithTex(1, 1, 1);
	stair_long.makeWithTex(1, 1, 1);
	labslogo.makeWithTex(1, 1, 1);
	rooms.makeWithTex(1, 1, 1);
	lightPM.make(1, 1, 1);
	tarkov_fence.makeWithTex(1, 1, 1);
	item_case_1.makeWithTex(1, 1, 1);
	item_case_2.makeWithTex(1, 1, 1);

	glPushMatrix();
	glTranslatef(0,0,(rotate_angle % 100) * 0.005f);
	escape1.make(0.164149f,0.800339f,0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,(rotate_angle % 100) * 0.005f);
	escape2.make(0.164149f,0.800339f,0.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0,(rotate_angle % 100) * 0.005f);
	escape3.make(0.164149f,0.800339f,0.0f);
	glPopMatrix();

	bool near = false;

	if(search_item_cheap() == true)
	{
		float dis = sqrt((-39.0272f - myPosition.x) * (-39.0272f - myPosition.x) + (-39.9068f - myPosition.y) * (-39.9068f - myPosition.y) + (7.13109f - myPosition.z) * (7.13109f - myPosition.z));
		if(dis < 3.0f)
		{
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11), myPosition.y + ((aimY - myPosition.y) * 0.11), myPosition.z + ((aimZ - myPosition.z) * 0.11));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(sita / PI * 180.0, 0, -1, 0);
			getitem.make(1,1,1);
			glPopMatrix();

			can_get = 1;
			near = true;
		}
		glPushMatrix();
		glTranslatef(-39.0272f,-39.9068f,7.13109f);
		glTranslatef(0, 0,sinf(rotate_angle * PI / 180.0f) * 0.1f);
		glRotatef(rotate_angle / 3.0f, 0, 0,1);
		tarkov_item_cat.makeWithTex(1, 1, 1);
		glPopMatrix();
	}

    if(search_item_expensive() == true)
	{
		float dis = sqrt((37.366f - myPosition.x) * (37.366f - myPosition.x) + (20.9312f - myPosition.y) * (20.9312f - myPosition.y) + (7.40035f - myPosition.z) * (7.40035f - myPosition.z));
		if(dis < 3.0f)
		{
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11), myPosition.y + ((aimY - myPosition.y) * 0.11), myPosition.z + ((aimZ - myPosition.z) * 0.11));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(sita / PI * 180.0, 0, -1, 0);
			getitem.make(1,1,1);
			glPopMatrix();

			can_get = 5;
			near = true;
		}
		glPushMatrix();
		glTranslatef(37.366f,20.9312f,7.40035f);
		glTranslatef(0, 0,sinf(rotate_angle * PI / 180.0f) * 0.1f);
		glRotatef(rotate_angle / 3.0f, 0, 0,1);
		tarkov_item_ledx.makeWithTex(1, 1,1);
		glPopMatrix();
	}

	if (search_item_normal() == true)
	{
		float dis = sqrt((16.8945f - myPosition.x) * (16.8945f - myPosition.x) + (-39.9005f - myPosition.y) * (-39.9005f - myPosition.y) + (7.44169f - myPosition.z) * (7.44169f - myPosition.z));
		if(dis < 3.0f)
		{
			glPushMatrix();
			glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11), myPosition.y + ((aimY - myPosition.y) * 0.11), myPosition.z + ((aimZ - myPosition.z) * 0.11));
			glRotatef(alpha / PI * 180.0, 0, 0, 1);
			glRotatef(sita / PI * 180.0, 0, -1, 0);
			getitem.make(1,1,1);
			glPopMatrix();

			can_get = 3;
			near = true;
		}

		glPushMatrix();
		glTranslatef(16.8945f,-39.9005f,7.44169f);
		glTranslatef(0, 0,sinf(rotate_angle * PI / 180.0f) * 0.1f);
		glRotatef(rotate_angle / 3.0f, 0, 0,1);
		tarkov_item_egg.makeWithTex(1, 1,1);
		glPopMatrix();
	}

	if(near == false)
	{
		can_get = 0;
	}

	animFrame++;
	makeEnemyPeople_T(animFrame);
	rotate_angle++;

}

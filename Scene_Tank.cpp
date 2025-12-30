#include "func.h"
#define g 0.0098f

extern SDL_Window* window;
extern Scene scene;
extern Game game[4];
extern float angle;
extern float sita;
extern float alpha;
extern bool shotCanon;
extern bool flyingCanon;
extern int canonCoolTime;
extern int explosionTime;
extern int animFrame;
extern int mainloopcount;
extern int tarminalTime;
extern int fin;
extern Position lookingPosition;
extern Position AIMPos;
extern Position canonPos;
extern Position myPosition;
Position tradePos;
extern explodePos explosionPos;
extern vihicle tankPos;
extern uint8_t my_result[30];
extern obj tankLower;
extern obj tankUpper;
extern obj tankBarrel;
extern obj canon;
extern obj explosion;
extern obj tankground;
extern obj tankmap;
extern obj dropPosition;
extern obj skyOutSide;
extern cheapObj num_1;
extern cheapObj num_2;
extern cheapObj num_3;
extern obj text_go;
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
extern std::vector<std::pair<int, std::vector<Point>>> tankWall;

extern void makeEnemyTank();
extern void makeHP(uint8_t);

void scene6(int x, int y, int w, int h)
{
	canonCoolTime++;

	glViewport(x, y, w, h);
	if(fin == 0)
	{
		if(animFrame > 280)
			tankMotionController();
	}
	animFrame++;
	CollisionController();
	unsigned int angleZ = sin(lookingPosition.z * 10.0 / 180.0 * PI);

	AIMPos.x = tankPos.x - (sin(lookingPosition.x * 20.0 / 180.0 * PI) * (1.0 - angleZ));
	AIMPos.y = tankPos.y + (cos(lookingPosition.x * 20.0 / 180.0 * PI) * (1.0 - angleZ));
	AIMPos.z = (sin(lookingPosition.z * 10.0 / 180.0 * PI) * 2.0);

	sita = atan2(AIMPos.z, 1);
	alpha = atan2(AIMPos.y - tankPos.y, AIMPos.x - tankPos.x);

	double aimX = tankPos.x + (cosf(sita) * cosf(alpha)) * 25;
	double aimY = tankPos.y + (cosf(sita) * sinf(alpha)) * 25;
	double aimZ = sinf(sita);

	double lpx = tankPos.x - (aimX - tankPos.x) * 0.7;
	double lpy = tankPos.y - (aimY - tankPos.y) * 0.7;

	gluLookAt(lpx, lpy, 13,
		aimX, aimY, aimZ,
		0, 0, 1);

	double radian = tankPos.vecX * 180.0 / PI;
	//double angle_tank = (radian * 180.0 / PI);

	double l = sqrt((aimX - lpx) * (aimX - lpx) + (aimY - lpy) * (aimY - lpy) + (aimZ - 13) * (aimZ - 13));
	double xyl = sqrt((aimX - lpx) * (aimX - lpx) + (aimY - lpy) * (aimY - lpy));
	double ls = atan2(aimZ - 13, xyl);

	glPushMatrix();
	glTranslatef(lpx + 0.12 * ((aimX - lpx) / l), lpy + 0.12 * ((aimY - lpy) / l), 13 + 0.12 * ((aimZ - 13) / l));
	glRotatef(alpha / PI * 180.0, 0, 0, 1);
	glRotatef(ls / PI * 180.0, 0, -1, 0);
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
	makeHP(tankPos.damage);
	if(fin == 1)
	{
		makeAnim(1.0f,1.0f,1.0f,anim_4th_4,anim_4th_4[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_4th_t,anim_4th_t[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_4th_h,anim_4th_h[0].textureID,animFrame / 3,29);
	}
	else if (fin == 2)
	{
		makeAnim(1.0f,1.0f,1.0f,anim_3rd_3,anim_3rd_3[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_3rd_r,anim_3rd_r[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_3rd_d,anim_3rd_d[0].textureID,animFrame / 3,29);
	}
	else if(fin == 3)
	{
		makeAnim(1.0f,1.0f,1.0f,anim_2nd_2,anim_2nd_2[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_2nd_n,anim_2nd_n[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_2nd_d,anim_2nd_d[0].textureID,animFrame / 3,29);
	}
	else if(fin == 4)
	{
		makeAnim(1.0f,1.0f,1.0f,anim_1st_1,anim_1st_1[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_1st_s,anim_1st_s[0].textureID,animFrame / 3,29);
		makeAnim(1.0f,1.0f,1.0f,anim_1st_t,anim_1st_t[0].textureID,animFrame / 3,29);

	}
	glPopMatrix();
	tankPos.angle = -radian;
	tankPos.alpha = (alpha * 180.0 / PI) + 90;
	if(checkGameStts(3,5) == game[3].p_NUM -1 && fin == 0)
	{
		game[3].stts = 5;
		fin = 4;
	}
	if(tankPos.damage > 95 && fin == 0)
	{
		switch(checkGameStts(3,5))
		{
			case 0:
				game[3].stts = 5;
				fin = 1;
				break;
			case 1:
				game[3].stts = 5;
				fin = 2;
				break;
			case 2:
				game[3].stts = 5;
				fin = 3;
				break;
		}
	}

		//everyone fin
	if(checkGameStts(3,5) == game[3].p_NUM - 1 && game[3].stts == 5)
	{
		if(tarminalTime < 180)
		{
			tarminalTime++;
		}
		else
		{
			//広場のロード
			mainloopcount = 2;
			//戦車のアンロード
			UnloadTankMesh();
			
			SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
			SDL_ShowCursor(SDL_DISABLE);
			myPosition.z = 2.5;
			scene = scene_4;	
			switch (fin)
			{
			case 1:
				for(int i = 0;i< 30;i++)
				{
					if(my_result[i] == 0)
					{
						my_result[i] = tank_4th;
						break;
					}
				}
				break;
			case 2:
				for(int i = 0;i< 30;i++)
				{
					if(my_result[i] == 0)
					{
						my_result[i] = tank_3rd;
						break;
					}
				}
				break;
			case 3:
				for(int i = 0;i< 30;i++)
				{
					if(my_result[i] == 0)
					{
						my_result[i] = tank_2nd;
						break;
					}
				}
				break;
			case 4:
				for(int i = 0;i< 30;i++)
				{
					if(my_result[i] == 0)
					{
						my_result[i] = tank_1st;
						break;
					}
				}
				break;			
			}
			fin = 0;
		}
	}

	//�o�����\��
	if (shotCanon == false)
	{
		glPushMatrix();
		glTranslatef(tankPos.x, tankPos.y, tankPos.z);
		glRotatef((alpha * 180.0 / PI) + 90, 0, 0, 1);
		glRotatef(-(sita * 180.0 / PI) / 3.0, 1, 0, 0);
		tankBarrel.makeWithTex(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(tankPos.x, tankPos.y, tankPos.z);
		glRotatef((alpha * 180.0 / PI) + 90, 0, 0, 1);
		tankUpper.makeWithTex(1, 1, 1);
		glPopMatrix();

	}
	else
	{
		glPushMatrix();
		glTranslatef(tankPos.x, tankPos.y, tankPos.z);
		glRotatef((alpha * 180.0 / PI) + 90, 0, 0, 1);
		glRotatef(-(sita * 180.0 / PI) / 3.0, 1, 0, 0);
		glTranslatef(0, sinf(canonCoolTime / 90.0 * PI), 0);
		tankBarrel.makeWithTex(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(tankPos.x, tankPos.y, tankPos.z);
		glRotatef((alpha * 180.0 / PI) + 90, 0, 0, 1);
		glTranslatef(0, sinf(canonCoolTime / 90.0 * PI), 0);
		tankUpper.makeWithTex(1, 1, 1);
		glPopMatrix();

	}
	if (canonCoolTime > 180)
		shotCanon = false;

	//�����\��
	glPushMatrix();
	glTranslatef(tankPos.x, tankPos.y, tankPos.z);
	glRotatef(-radian, 0, 0, 1);
	tankLower.makeWithTex(1, 1, 1);
	glPopMatrix();

	//�L���m���\��
	if (flyingCanon == false)
	{
		float t = 0.0f;
		float dt = 1.0f;
		float x1, y1, z1;

		while (true) {
			x1 = tankPos.x + cosf(alpha) * canonFirstSpeed * (t / 4.0f);
			y1 = tankPos.y + sinf(alpha) * canonFirstSpeed * (t / 4.0f);
			z1 = canonFirstSpeed * (t / 2.0f) * sinf(sita) - (g * t * t / 2.0f);

			if (z1 <= -3.395f)
				break;
			t += dt;
		}
		if(canonCoolTime > 300)
		{
			glPushMatrix();
			glTranslatef(x1, y1, 0);
			dropPosition.make(1, 1, 1);
			glPopMatrix();
		}
	}
	else
	{
		canonPos.z = canonFirstSpeed * (canonCoolTime / 2.0f) * sinf(canonPos.sita) - (g * canonCoolTime * canonCoolTime / 2.0f);
		glPushMatrix();
		glTranslatef(canonPos.x + cosf(canonPos.alpha) * canonFirstSpeed * (canonCoolTime / 4.0), canonPos.y + sinf(canonPos.alpha) * canonFirstSpeed * (canonCoolTime / 4.0), canonPos.z);
		glRotatef((alpha * 180.0 / PI) + 90.0, 0, 0, 1);
		glRotatef(-(sita * 180.0 / PI) / 3.0, 1, 0, 0);
		canon.makeWithTex(1, 1, 1);
		glPopMatrix();
		if (canonPos.z <= -3.0f || Collision_C() == true)
		{
			flyingCanon = false;
			explosionPos.x = canonPos.x + cosf(canonPos.alpha) * canonFirstSpeed * (canonCoolTime / 4.0);
			explosionPos.y = canonPos.y + sinf(canonPos.alpha) * canonFirstSpeed * (canonCoolTime / 4.0);
			explosionPos.z = canonPos.z + 3.0f;
			explosionPos.c = true;
		}
	}

	//���j�\��
	if (explosionPos.c == true)
	{
		explosionTime++;
		float a = atan2f(explosionPos.y - tankPos.y, explosionPos.x - tankPos.x);
		if (explosionTime < 100)
		{
			glPushMatrix();
			glTranslatef(explosionPos.x, explosionPos.y, explosionPos.z);
			glRotatef((a * 180.0 / PI) + 90.0, 0, 0, 1);
			glTranslatef(0,-15,0);
			explosion.makeWithTex(1, 1, 1);
			glPopMatrix();
		}
		else
		{
			explosionPos.c = false;
			explosionTime = 0;
		}
		tradePos.x = explosionPos.x;
		tradePos.y = explosionPos.y;
		tradePos.z = explosionPos.z;
		tradePos.canonCoolTime = canonCoolTime;
		tradePos.kind = true;
		if(explosionTime == 1)
			tradePos.damage = 100;
		else
			tradePos.damage = 0;
	}
	else
	{
		tradePos.x = canonPos.x;
		tradePos.y = canonPos.y;
		tradePos.z = canonPos.z;
		tradePos.damage = 0;
		tradePos.canonCoolTime = canonCoolTime;
		tradePos.kind = false;
	}


	makeEnemyTank();

	glPushMatrix();
	tankground.makeWithTex(1, 1, 1);
	tankmap.makeWithTex(1, 1, 1);
	skyOutSide.makeWithTex(1, 1, 1);
	glPopMatrix();
}

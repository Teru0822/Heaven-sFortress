#include "func.h"

extern void motionController();
extern void CollisionController();
extern void makeEnemyPeople(int );

extern Position lookingPosition;
extern Position AIMPos;
extern Position myPosition;
extern FireWorksPos fireCenterPos[20];

extern float sita;
extern float alpha;

extern bool doorAIM;

extern int animFrame;

extern obj skyOutSide;
extern obj aincrad_top;
extern obj aincrad_bot;
extern obj aincrad_lower;
extern obj aincrad_sword;
extern obj aincrad_road;
extern obj door_left;
extern obj door_right;
extern obj door_frame;
extern obj fence;
extern obj text_w[29];
extern obj text_i[29];
extern obj text_n[29];
extern cheapObj open;


void scene3(int x, int y, int w, int h)
{
	//����

	glViewport(x, y, w, h);
	motionController();
	CollisionController();

	unsigned int angleZ = sin(lookingPosition.z * 20.0 / 180.0 * PI);

	AIMPos.x = myPosition.x - (sin(lookingPosition.x * 20.0 / 180.0 * PI) * (1.0 - angleZ));
	AIMPos.y = myPosition.y + (cos(lookingPosition.x * 20.0 / 180.0 * PI) * (1.0 - angleZ));
	AIMPos.z = 0.5 + (sin(lookingPosition.z * 20.0 / 180.0 * PI) * 2.0);

	sita = atan2(AIMPos.z, 1);
	alpha = atan2(AIMPos.y - myPosition.y, AIMPos.x - myPosition.x);
	myPosition.sita = sita;	
	myPosition.alpha = alpha;

	double aimX = myPosition.x + (cosf(sita) * cosf(alpha));
	double aimY = myPosition.y + (cosf(sita) * sinf(alpha));
	double aimZ = myPosition.z + sinf(sita);
	gluLookAt(myPosition.x, myPosition.y, myPosition.z,
		aimX, aimY, aimZ,
		0, 0, 1);

	doorAIM = false;
	if (myPosition.x < 168.2 && myPosition.x - aimX > 0.0)
	{
		doorAIM = true;
		glPushMatrix();
		glTranslatef(myPosition.x + ((aimX - myPosition.x) * 0.11), myPosition.y + ((aimY - myPosition.y) * 0.11), myPosition.z + ((aimZ - myPosition.z) * 0.11));
		glRotatef(alpha / PI * 180.0, 0, 0, 1);
		glRotatef(sita / PI * 180.0, 0, -1, 0);
		open.make(1, 1, 1);
		glPopMatrix();
	}
#pragma omp parallel for
	for (int i = 0; i < 20; i++)
	{
		int r = rand() % 72;
		int rr = rand() % 80;
		if (fireCenterPos[i].random == false && rr == 0)
		{
			fireCenterPos[i].x = cosf(r * 5 * M_PI / 180.0) * 663.0;
			fireCenterPos[i].y = sinf(r * 5 * M_PI / 180.0) * 663.0;
			fireCenterPos[i].z = sinf((rand() % 36) * 10 * M_PI / 180.0) * 300.0;
			fireCenterPos[i].random = true;
			fireCenterPos[i].FireWorkCount = 0;
		}
	}
	FireWork(fireCenterPos);
#pragma omp parallel for
	for (int i = 0; i < 20; i++)
	{
		if (fireCenterPos[i].FireWorkCount > 2000)
		{
			fireCenterPos[i].FireWorkCount = 0;
			fireCenterPos[i].random = false;
		}
	}
	animFrame++;

	glPointSize(4);
	glBegin(GL_POINTS);
	glColor3f(1, 1, 1);
	glVertex3f(myPosition.x + ((aimX - myPosition.x) * 0.11), myPosition.y + ((aimY - myPosition.y) * 0.11), myPosition.z + ((aimZ - myPosition.z) * 0.11));
	glEnd();

	skyOutSide.makeWithTex(1, 1, 1);
	aincrad_top.makeWithTex(0.4, 0.4, 0.4);
	aincrad_bot.makeWithTex(1, 1, 1);
	aincrad_lower.makeWithTex(0.4, 0.4, 0.4);
	aincrad_sword.makeWithTex(0.4, 0.4, 0.4);
	aincrad_road.makeWithTex(0.4, 0.4, 0.4);
	fence.make(0, 0, 0);
	door_frame.makeWithTex(0.4, 0.4, 0.4);
	glPushMatrix();
	glTranslatef(162.86, 4.8468, 0.0);
	door_right.makeWithTex(0.4, 0.4, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(162.86, -4.8959, 0.0);
	door_left.makeWithTex(0.4, 0.4, 0.4);
	glPopMatrix();

	makeEnemyPeople(animFrame);

}

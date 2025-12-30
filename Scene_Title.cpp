#include "func.h"
#define g 0.0098f

extern float angle;
extern float alpha;
extern FireWorksPos fireCenterPos[20];
extern obj skyOutSide;
extern obj FireWorks;
extern obj title;
extern obj titleShield;
extern obj titleFrame;
extern obj aincrad_bot;
extern obj aincrad_top;
extern obj aincrad_sword;
extern obj aincrad_lower;
extern obj aincrad_road;
extern obj aincrad_house;
extern obj fence;
extern obj door_frame;
extern obj door_left;
extern obj door_right;


void scene1(int x, int y, int w, int h)
{
	//�^�C�g�����
	glViewport(x, y, w, h);
	angle += 0.03;
	double lpx = aincradRad * cosf(angle * PI / 180.0);
	double lpy = aincradRad * sinf(angle * PI / 180.0);
	gluLookAt(lpx, lpy, aincradZ, 0, 0, 0, 0, 0, 1);
	//skyOutSide.makeWithTex(1, 1, 1);
	skyOutSide.makeWithTex(1.0f, 1.0f, 1.0f);
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


	double l = sqrt((lpx * lpx) + (lpy * lpy) + (aincradZ * aincradZ));
	double xyl = sqrt((lpx * lpx) + (lpy * lpy));
	double ls = atan2(aincradZ, xyl);
	alpha = atan2(-lpy, -lpx);

	glPushMatrix();
	glTranslatef(lpx - (0.12 * lpx / l), lpy - (0.12 * lpy / l), aincradZ - (0.12 * aincradZ / l));
	glRotatef(alpha / PI * 180.0, 0, 0, 1);
	glRotatef(ls / PI * 180.0, 0, 1, 0);
	title.makeWithTex(0.6f, 0.6f, 0.6f);
	titleFrame.make(0.0f, 0.0f, 0.0f);
	titleShield.make(0.4f, 0.0f, 0.0f);
	glPopMatrix();

	aincrad_top.makeWithTex(0.4f, 0.4f, 0.4f);
	aincrad_house.makeWithTex(0.4f, 0.4f, 0.4f);
	aincrad_bot.makeWithTex(1.0f, 1.0f, 1.0f);
	aincrad_lower.makeWithTex(0.4f, 0.4f, 0.4f);
	aincrad_sword.makeWithTex(0.4f, 0.4f, 0.4f);
	aincrad_road.makeWithTex(0.4f, 0.4f, 0.4f);
	fence.make(0.0f, 0.0f, 0.0f);
	door_frame.makeWithTex(0.4f, 0.4f, 0.4f);

	glPushMatrix();
	glTranslatef(162.86f, 4.8468f, 0.0f);
	door_right.makeWithTex(0.4f, 0.4f, 0.4f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(162.86f, -4.8959f, 0.0f);
	door_left.makeWithTex(0.4f, 0.4f, 0.4f);
	glPopMatrix();

}

void FireWork(FireWorksPos* centerPoints)
{
	for (int t = 0; t < 20; t++)
	{
		if (centerPoints[t].random == true)
		{
			for (int i = 0; i < 18; i++)
			{
				//�^��
				glPushMatrix();
				glTranslatef(cosf(((i * 20) + 10) * M_PI / 180.0) * centerPoints[t].FireWorkCount / 8.5, sinf(i * 20 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 8.5, (0.27 * centerPoints[t].FireWorkCount) - (g * centerPoints[t].FireWorkCount * centerPoints[t].FireWorkCount / 40.0));
				glTranslatef(centerPoints[t].x, centerPoints[t].y, centerPoints[t].z);
				FireWorks.make(sinf(i * 20 * M_PI / 180.0), cosf(i * 20 * M_PI / 180.0), 1);
				glPopMatrix();
				//�O�ԏ�
				glPushMatrix();
				glTranslatef(cosf(i * 20 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 9.5, sinf(i * 20 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 9.5, (0.3 * centerPoints[t].FireWorkCount) - (g * centerPoints[t].FireWorkCount * centerPoints[t].FireWorkCount / 40.0));
				glTranslatef(centerPoints[t].x, centerPoints[t].y, centerPoints[t].z);
				FireWorks.make(cosf(i * 20 * M_PI / 180.0), 1, sinf(i * 20 * M_PI / 180.0));
				glPopMatrix();
				//��ԏ�
				glPushMatrix();
				glTranslatef(cosf(((i * 20) + 10) * M_PI / 180.0) * centerPoints[t].FireWorkCount / 13.0, sinf(i * 20 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 13.0, (0.325 * centerPoints[t].FireWorkCount) - (g * centerPoints[t].FireWorkCount * centerPoints[t].FireWorkCount / 40.0));
				glTranslatef(centerPoints[t].x, centerPoints[t].y, centerPoints[t].z);
				FireWorks.make(sinf(i * 20 * M_PI / 180.0), 1, cosf(i * 20 * M_PI / 180.0));
				glPopMatrix();
				//��ԏ�
				glPushMatrix();
				glTranslatef(cosf(i * 20 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 29.0, sinf(i * 20 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 29.0, (0.34 * centerPoints[t].FireWorkCount) - (g * centerPoints[t].FireWorkCount * centerPoints[t].FireWorkCount / 40.0));
				glTranslatef(centerPoints[t].x, centerPoints[t].y, centerPoints[t].z);
				FireWorks.make(cosf(i * 20 * M_PI / 180.0), cosf(i * 20 * M_PI / 180.0), 1);
				glPopMatrix();
				//�O�ԉ�
				glPushMatrix();
				glTranslatef(cosf(i * 20 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 8.5, sinf(i * 20 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 8.5, (0.25 * centerPoints[t].FireWorkCount) - (g * centerPoints[t].FireWorkCount * centerPoints[t].FireWorkCount / 40.0));
				glTranslatef(centerPoints[t].x, centerPoints[t].y, centerPoints[t].z);
				FireWorks.make(cosf(i * 20 * M_PI / 180.0), cosf(i * 20 * M_PI / 180.0), 1);
				glPopMatrix();
				//��ԉ�
				glPushMatrix();
				glTranslatef(cosf(((i * 20) + 10) * M_PI / 180.0) * centerPoints[t].FireWorkCount / 10.0, sinf(i * 20 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 10.0, (0.23 * centerPoints[t].FireWorkCount) - (g * centerPoints[t].FireWorkCount * centerPoints[t].FireWorkCount / 40.0));
				glTranslatef(centerPoints[t].x, centerPoints[t].y, centerPoints[t].z);
				FireWorks.make(cosf(i * 20 * M_PI / 180.0), 1, sinf(i * 20 * M_PI / 180.0));
				glPopMatrix();
				//��ԉ�
				glPushMatrix();
				glTranslatef(cosf(i * 20 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 14.0, sinf(i * 20 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 14.0, (0.21 * centerPoints[t].FireWorkCount) - (g * centerPoints[t].FireWorkCount * centerPoints[t].FireWorkCount / 40.0));
				glTranslatef(centerPoints[t].x, centerPoints[t].y, centerPoints[t].z);
				FireWorks.make(sinf(i * 20 * M_PI / 180.0), 1, cosf(i * 20 * M_PI / 180.0));
				glPopMatrix();
			}
			centerPoints[t].FireWorkCount += 5;
		}
	}
}

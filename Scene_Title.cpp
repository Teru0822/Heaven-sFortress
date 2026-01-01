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
	//タイトル画面
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
	static int frameSkip = 0;
	frameSkip++;
	
	for (int t = 0; t < 20; t++)
	{
		if (centerPoints[t].random == true)
		{
			// パーティクル数を18から9に削減（40度間隔）
			// 種類を7から3に削減
			for (int i = 0; i < 9; i++)
			{
				// 赤丸
				glPushMatrix();
				glTranslatef(cosf(i * 40 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 8.5, 
				             sinf(i * 40 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 8.5, 
				             (0.27 * centerPoints[t].FireWorkCount) - (g * centerPoints[t].FireWorkCount * centerPoints[t].FireWorkCount / 40.0));
				glTranslatef(centerPoints[t].x, centerPoints[t].y, centerPoints[t].z);
				FireWorks.make(sinf(i * 40 * M_PI / 180.0), cosf(i * 40 * M_PI / 180.0), 1);
				glPopMatrix();
				
				// 緑丸（2フレームに1回のみ描画）
				if (frameSkip % 2 == 0) {
					glPushMatrix();
					glTranslatef(cosf(i * 40 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 9.5, 
					             sinf(i * 40 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 9.5, 
					             (0.3 * centerPoints[t].FireWorkCount) - (g * centerPoints[t].FireWorkCount * centerPoints[t].FireWorkCount / 40.0));
					glTranslatef(centerPoints[t].x, centerPoints[t].y, centerPoints[t].z);
					FireWorks.make(cosf(i * 40 * M_PI / 180.0), 1, sinf(i * 40 * M_PI / 180.0));
					glPopMatrix();
				}
				
				// 青丸（2フレームに1回のみ描画）
				if (frameSkip % 2 == 1) {
					glPushMatrix();
					glTranslatef(cosf(i * 40 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 13.0, 
					             sinf(i * 40 * M_PI / 180.0) * centerPoints[t].FireWorkCount / 13.0, 
					             (0.325 * centerPoints[t].FireWorkCount) - (g * centerPoints[t].FireWorkCount * centerPoints[t].FireWorkCount / 40.0));
					glTranslatef(centerPoints[t].x, centerPoints[t].y, centerPoints[t].z);
					FireWorks.make(sinf(i * 40 * M_PI / 180.0), 1, cosf(i * 40 * M_PI / 180.0));
					glPopMatrix();
				}
			}
			centerPoints[t].FireWorkCount += 5;
		}
	}
}

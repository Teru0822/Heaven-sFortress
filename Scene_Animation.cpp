#include "func.h"

extern Scene scene;
extern Position myPosition;
extern SDL_Window* window;
extern FireWorksPos fireCenterPos[20];

extern bool flagAnim;
extern int currentRadius;
extern int currentFrame;
extern int my_id;
extern float angle;
extern float radius_aincrad;
extern float height_aincrad;

extern obj skyOutSide;
extern obj aincrad_top;
extern obj aincrad_bot;
extern obj aincrad_lower;
extern obj aincrad_sword;
extern obj aincrad_road;
extern obj aincrad_house;
extern obj door_left;
extern obj door_right;
extern obj door_frame;
extern obj fence;

void scene2(int x, int y, int w, int h)
{
	//�^�C�g����ʂ�������܂ł̃A�j���[�V����

	glViewport(x, y, w, h);
	int angleINT = angle;
	if (flagAnim == false)
	{
		currentRadius++;
		if (angleINT % 360 != 180 && angleINT % 360 != 179 && angleINT % 360 != 181)
		{
			currentFrame++;
			angle = angle + (0.005 * currentFrame);
		}
		else
		{
			flagAnim = true;
			radius_aincrad = currentRadius;
		}
		gluLookAt(currentRadius * cosf(angle * PI / 180.0), currentRadius * sinf(angle * PI / 180.0), aincradZ, 0, 0, 0, 0, 0, 1);
	}
	else//400�t���[����180�x��]
	{
		switch (my_id)
		{
		case 0:
			angle += (180.0 / 400.0);
		    break;
		case 1:
			angle += (181.0 / 400.0);
		    break;
		case 2:
		    angle += (179.0 / 400.0);	
		    break;
		case 3:
		    angle += (182.0 / 400.0);
		    break;
		}
		radius_aincrad -= (currentRadius - 200.0) / 400.0;
		height_aincrad -= ((aincradZ - 3.5) / 400.0);
		if (radius_aincrad <= 200.0)
		{
			scene = scene_3;
			myPosition.x = 200;
			switch (my_id)
			{
			case 0:
				myPosition.y = 0.0f;
				break;
			case 1:
				myPosition.y = 2.0f;
				break;
			case 2:
				myPosition.y = -2.0f;
				break;
			case 3:
				myPosition.y = 4.0f;
				break;
			}
			myPosition.z = 2.5;
			SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);

		}
		gluLookAt(radius_aincrad * cosf(angle * PI / 180.0), radius_aincrad * sinf(angle * PI / 180.0), height_aincrad, 0, 0, 0, 0, 0, 1);

	}
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

	aincrad_house.makeWithTex(0.4f, 0.4f, 0.4f);
	aincrad_top.makeWithTex(0.4f, 0.4f, 0.4f);
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

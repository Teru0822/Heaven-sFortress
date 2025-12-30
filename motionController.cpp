#include "func.h"
#define g 0.0098f

extern Scene scene;
extern SDL_Window* window;
extern Position lookingPosition;
extern Position myPosition;
extern vihicle tankPos;
extern vihicle sportsPos;
extern Game game[4];
extern bool pressCTRL_L;
extern bool pressW;
extern bool pressS;
extern bool pressA;
extern bool pressD;
extern bool pressSHIFT_L;
extern bool pressSPACE;
extern bool coltype;
extern int mouseDisplayX;
extern int mouseDisplayY;
extern int jumpingTime;
extern int torque;
extern int gear;
extern int fin;
extern float movingStraight;
extern float movingRight;
extern float jumpingHeight;
extern float jumpSpeed;
extern float movingUp;
extern float topHeight;
extern float myAngle;
extern float sports_vec;
extern float sports_body_vec;
extern float h1;
extern float weapon_moving_anim;

extern stair stair1;
extern stair stair2;
extern stair stair3;
extern stair stair4;
extern stair stair5;
extern stair stair6;
extern stair stair7;
extern stair stair8;
extern stair stair9;

extern stair stairXMinus1;
extern stair stairXMinus2;
extern stair stairXMinus3;

int checkingSportsGoal(float x1,float y1,float x2,float y2)
{
	if (x1 < 41.5275 && x1 > -19.9242 && x2 < 41.5275 && x2 > -19.9242 && y1 >= -9.55032 && y2 <= -9.55032)//順方向
		return 1;
	else if (x1 < 41.5275 && x1 > -19.9242 && x2 < 41.5275 && x2 > -19.9242 && y1 <= -9.55032 && y2 >= -9.55032)//逆方向
		return 2;
	else
		return 0;
}

void stairUP()
{
	if (myPosition.x >= stair1.seg11.x && myPosition.x <= stair1.seg12.x && myPosition.y >= stair1.seg11.y && myPosition.y <= stair1.seg21.y)
	{
		myPosition.z = 1.8553f + (stair1.seg21.z - stair1.seg11.z) * ((myPosition.y - stair1.seg11.y) / (stair1.seg21.y - stair1.seg11.y));
	}
	if (myPosition.x >= stair2.seg11.x && myPosition.x <= stair2.seg12.x && myPosition.y >= stair2.seg11.y && myPosition.y <= stair2.seg21.y)
	{
		myPosition.z = 1.8553f + (stair2.seg21.z - stair2.seg11.z) * ((myPosition.y - stair2.seg11.y) / (stair2.seg21.y - stair2.seg11.y));
	}
	if (myPosition.x >= stair3.seg11.x && myPosition.x <= stair3.seg12.x && myPosition.y <= stair3.seg11.y && myPosition.y >= stair3.seg21.y)
	{
		myPosition.z = 1.8553f + (stair3.seg21.z - stair3.seg11.z) * (1.0f - (myPosition.y - stair3.seg21.y) / (stair3.seg11.y - stair3.seg21.y));
	}
	if (myPosition.x >= stair4.seg11.x && myPosition.x <= stair4.seg12.x && myPosition.y >= stair4.seg11.y && myPosition.y <= stair4.seg21.y)
	{
		myPosition.z = 1.8553f + (stair4.seg21.z - stair4.seg11.z) * ((myPosition.y - stair4.seg11.y) / (stair4.seg21.y - stair4.seg11.y));
	}
	if (myPosition.x >= stair5.seg11.x && myPosition.x <= stair5.seg12.x && myPosition.y >= stair5.seg11.y && myPosition.y <= stair5.seg21.y)
	{
		myPosition.z = 1.8553f + (stair5.seg21.z - stair5.seg11.z) * ((myPosition.y - stair5.seg11.y) / (stair5.seg21.y - stair5.seg11.y));
	}
	if (myPosition.x >= stair6.seg11.x && myPosition.x <= stair6.seg12.x && myPosition.y <= stair6.seg11.y && myPosition.y >= stair6.seg21.y)
	{
		myPosition.z = 1.8553f + (stair6.seg21.z - stair6.seg11.z) * (1.0f - (myPosition.y - stair6.seg21.y) / (stair6.seg11.y - stair6.seg21.y));
	}
	if (myPosition.x >= stair7.seg11.x && myPosition.x <= stair7.seg12.x && myPosition.y >= stair7.seg11.y && myPosition.y <= stair7.seg21.y)
	{
		myPosition.z = 4.71197f + (stair7.seg21.z - stair7.seg11.z) * ((myPosition.y - stair7.seg11.y) / (stair7.seg21.y - stair7.seg11.y));
	}
	if (myPosition.x >= stair8.seg11.x && myPosition.x <= stair8.seg12.x && myPosition.y <= stair8.seg11.y && myPosition.y >= stair8.seg21.y)
	{
		myPosition.z = 1.8553f + (stair8.seg21.z - stair8.seg11.z) * (1.0f - (myPosition.y - stair8.seg21.y) / (stair8.seg11.y - stair8.seg21.y));
	}
	if (myPosition.x >= stair9.seg11.x && myPosition.x <= stair9.seg12.x && myPosition.y >= stair9.seg11.y && myPosition.y <= stair9.seg21.y)
	{
		myPosition.z = 1.8553f + (stair9.seg21.z - stair9.seg11.z) * ((myPosition.y - stair9.seg11.y) / (stair9.seg21.y - stair9.seg11.y));
	}

	if (myPosition.y >= stairXMinus1.seg11.y && myPosition.y <= stairXMinus1.seg12.y && myPosition.x >= stairXMinus1.seg21.x && myPosition.x <= stairXMinus1.seg11.x)
	{
		myPosition.z = 4.71197f + (stairXMinus1.seg21.z - stairXMinus1.seg11.z) * (1.0f - (myPosition.x - stairXMinus1.seg21.x) / (stairXMinus1.seg11.x - stairXMinus1.seg21.x));
	}
	if (myPosition.y >= stairXMinus2.seg11.y && myPosition.y <= stairXMinus2.seg12.y && myPosition.x >= stairXMinus2.seg21.x && myPosition.x <= stairXMinus2.seg11.x)
	{
		myPosition.z = 4.71197f + (stairXMinus2.seg21.z - stairXMinus2.seg11.z) * (1.0f - (myPosition.x - stairXMinus2.seg21.x) / (stairXMinus2.seg11.x - stairXMinus2.seg21.x));
	}
	if (myPosition.y >= stairXMinus3.seg11.y && myPosition.y <= stairXMinus3.seg12.y && myPosition.x >= stairXMinus3.seg21.x && myPosition.x <= stairXMinus3.seg11.x)
	{
		myPosition.z = 1.8553f + (stairXMinus3.seg21.z - stairXMinus3.seg11.z) * (1.0f - (myPosition.x - stairXMinus3.seg21.x) / (stairXMinus3.seg11.x - stairXMinus3.seg21.x));
	}
}

void passiveMotion(int x, int y)
{

	if (scene == scene_3 || scene == scene_4)
	{
		SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
		lookingPosition.x -= (x - 900) / 100.0;//dx
		lookingPosition.z -= (y - 500) / 140.0;//dy
		if (pressCTRL_L == true)
		{
			if (lookingPosition.z > 4.099994)
				lookingPosition.z = 4.099994;
			else if (lookingPosition.z < -1.228571)
				lookingPosition.z = -1.228571;
		}
		else
		{
			if (lookingPosition.z > 2.28570819)
				lookingPosition.z = 2.28570819;
			else if (lookingPosition.z < -3.87857175)
				lookingPosition.z = -3.87857175;
		}
	}
	else if (scene == scene_5)
	{
		mouseDisplayX = x;
		mouseDisplayY = y;
	}
	else if (scene == scene_6)
	{
		SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
		lookingPosition.x -= (x - 900) / 100.0;//dx
		lookingPosition.z -= (y - 500) / 140.0;//dy
		if (lookingPosition.z > 0.5285)
			lookingPosition.z = 0.5285;
		else if (lookingPosition.z < 0.0357142873)
			lookingPosition.z = 0.0357142873;

	}
	else if (scene == scene_7)
	{
		SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
		lookingPosition.x -= (x - 900) / 100.0;//dx
		lookingPosition.z -= (y - 500) / 140.0;//dy
		if (lookingPosition.z > 0.5285)
			lookingPosition.z = 0.5285;
		else if (lookingPosition.z < 0.0357142873)
			lookingPosition.z = 0.0357142873;

	}
	else if (scene == scene_8)
	{
		SDL_WarpMouseInWindow(window, WARP_WIDTH, WARP_HEIGHT);
		lookingPosition.x -= (x - 900) / 100.0;//dx
		lookingPosition.z -= (y - 500) / 140.0;//dy
		if (pressCTRL_L == true)
		{
			if (lookingPosition.z > 4.099994)
				lookingPosition.z = 4.099994;
			else if (lookingPosition.z < -1.228571)
				lookingPosition.z = -1.228571;
		}
		else
		{
			if (lookingPosition.z > 2.28570819)
				lookingPosition.z = 2.28570819;
			else if (lookingPosition.z < -3.87857175)
				lookingPosition.z = -3.87857175;
		}
	}
}

void motionController()
{
	movingStraight = 0;
	movingRight = 0;
	myPosition.dash = anim_idle;
	if (pressW == true)
	{
		if(pressSPACE == false)
			myPosition.dash = anim_forward;
		if (pressSHIFT_L == true)
		{
			if(pressSPACE == false)
				myPosition.dash = anim_dash;
			movingStraight = movingSpeed * 2.0;
			weapon_moving_anim += 5.0;
		}
		else
		{
			movingStraight = movingSpeed;
			weapon_moving_anim += 3.0;
		}
	}
	if (pressS == true)
	{
		myPosition.dash = anim_back;
		movingStraight = -movingSpeed;
		weapon_moving_anim += 3.0;
	}
	if (pressA == true)
	{
		myPosition.dash = anim_left;
		movingRight = -movingSpeed;
		weapon_moving_anim += 3.0;
	}
	if (pressD == true)
	{
		myPosition.dash = anim_right;
		movingRight = movingSpeed;
		weapon_moving_anim += 3.0;
	}
	if ((pressW == true && pressA == true) || (pressW == true && pressD == true) || (pressS == true && pressA == true) || (pressS == true && pressD == true))
	{
		weapon_moving_anim -= 3.0;

	}
	if (pressSPACE == true)
	{
		jumpingTime++;
		float h;
		int time;
		myPosition.dash = anim_jump;
		if (jumpingTime < (gTime / 2) + 1)//jumpingTime 1~50
		{
			jumpingHeight = (jumpSpeed * jumpingTime) - (g * jumpingTime * jumpingTime / 2.0);
			h = h1 + jumpingHeight;
			movingUp = h;
			if (jumpingTime == gTime / 2)
				topHeight = h;
		}
		else if (jumpingTime > (gTime / 2) && jumpingTime <= gTime)//51~100
		{
			time = jumpingTime - (gTime / 2);//1,2,3,4...
			h = topHeight - (g * (time * time) / 2.0);
			jumpingHeight = h - h1;
			movingUp = h;
		}
		else if (jumpingTime > gTime)
		{
			pressSPACE = false;
			myPosition.dash = anim_idle;
		}
		myPosition.z = movingUp;
	}
	myAngle = lookingPosition.x * 20.0;//�����Ă���p�x
	double radian = myAngle / 180.0 * PI;

	myPosition.x -= sin(radian) * movingStraight;
	myPosition.y += cos(radian) * movingStraight;
	myPosition.x += cos(radian) * movingRight;
	myPosition.y -= -sin(radian) * movingRight;
}

void motionController_T()
{
	movingStraight = 0;
	movingRight = 0;
	myPosition.dash = anim_idle;
	if (pressW == true)
	{
		if(pressSPACE == false)
			myPosition.dash = anim_forward;
		if (pressSHIFT_L == true)
		{
			if(pressSPACE == false)
				myPosition.dash = anim_dash;
			movingStraight = movingSpeed * 2.0;
			weapon_moving_anim += 5.0;
		}
		else
		{
			movingStraight = movingSpeed;
			weapon_moving_anim += 3.0;
		}
	}
	if (pressS == true)
	{
		myPosition.dash = anim_back;
		movingStraight = -movingSpeed;
		weapon_moving_anim += 3.0;
	}
	if (pressA == true)
	{
		myPosition.dash = anim_left;
		movingRight = -movingSpeed;
		weapon_moving_anim += 3.0;
	}
	if (pressD == true)
	{
		myPosition.dash = anim_right;
		movingRight = movingSpeed;
		weapon_moving_anim += 3.0;
	}
	if ((pressW == true && pressA == true) || (pressW == true && pressD == true) || (pressS == true && pressA == true) || (pressS == true && pressD == true))
	{
		weapon_moving_anim -= 3.0;

	}
	if (pressSPACE == true)
	{
		jumpingTime++;
		float h;
		int time;
		myPosition.dash = anim_jump;
		if (jumpingTime < (gTime / 2) + 1)//jumpingTime 1~50
		{
			jumpingHeight = (jumpSpeed * jumpingTime) - (g * jumpingTime * jumpingTime / 2.0);
			h = h1 + jumpingHeight;
			movingUp = h;
			if (jumpingTime == gTime / 2)
				topHeight = h;
		}
		else if (jumpingTime > (gTime / 2) && jumpingTime <= gTime)//51~100
		{
			time = jumpingTime - (gTime / 2);//1,2,3,4...
			h = topHeight - (g * (time * time) / 2.0);
			jumpingHeight = h - h1;
			movingUp = h;
		}
		else if (jumpingTime > gTime)
		{
			pressSPACE = false;
			myPosition.dash = anim_idle;
		}
		myPosition.z = movingUp;
	}
	myAngle = lookingPosition.x * 20.0;//�����Ă���p�x
	double radian = myAngle / 180.0 * PI;

	float movedX = myPosition.x - sin(radian) * movingStraight + cos(radian) * movingRight;
	float movedY = myPosition.y + cos(radian) * movingStraight + sin(radian) * movingRight;


	
	if (myPosition.x >= 5.46844 && myPosition.x <= 8.90964 && myPosition.y <= -22.2543 && movedY >= -22.2543)//1から2   1
		coltype = true;
	else if(myPosition.x >= 5.46844 && myPosition.x <= 8.90964 && myPosition.y >= -22.2543 && movedY <= -22.2543)//2から1
		coltype = false;
	if (myPosition.y >= -28.765 && myPosition.y <= -25.5601 && myPosition.x >= 33.354 && movedX <= 33.354)//1から2    2
		coltype = true;
	else if (myPosition.y >= -28.765 && myPosition.y <= -25.5601 && myPosition.x <= 33.354 && movedX >= 33.354)//2から1
		coltype = false;
	if (myPosition.y >= 30.9423 && myPosition.y <= 34.1632 && myPosition.x >= 33.2063 && movedX <= 33.2063)//1から2     3
		coltype = true;
	else if (myPosition.y >= 30.9423 && myPosition.y <= 34.1632 && myPosition.x <= 33.2063 && movedX >= 33.2063)//2から1
		coltype = false;
	if (myPosition.x >= 21.5367 && myPosition.x <= 25.0037 && myPosition.y <= 23.8073 && movedY >= 23.8073)//1から2     4
		coltype = true;
	else if (myPosition.x >= 21.5367 && myPosition.x <= 25.0037 && myPosition.y >= 23.8073 && movedY <= 23.8073)//2から1
		coltype = false;	
	if (myPosition.x >= 21.5268 && myPosition.x <= 25.003 && myPosition.y >= -9.24732 && movedY <= -9.24732)//1から2    5
		coltype = true;
	else if (myPosition.x >= 21.5268 && myPosition.x <= 25.003 && myPosition.y <= -9.24732 && movedY >= -9.24732)//2から1
		coltype = false;
	if (myPosition.x >= -41.4201 && myPosition.x <= -37.8664 && myPosition.y <= 24.4569 && movedY >= 24.4569)//1から2   6
		coltype = true;
	else if (myPosition.x >= -41.4201 && myPosition.x <= -37.8664 && myPosition.y >= 24.4569 && movedY <= 24.4569)//2から1
		coltype = false;
	if (myPosition.x >= -41.5521 && myPosition.x <= -37.96 && myPosition.y >= -9.37157 && movedY <= -9.37157)//1から2   7
		coltype = true;
	else if (myPosition.x >= -41.5521 && myPosition.x <= -37.96 && myPosition.y <= -9.37157 && movedY >= -9.37157)//2から1
		coltype = false;
	if (myPosition.x >= -56.1935 && myPosition.x <= -52.7631 && myPosition.y <= -22.2862 && movedY >= -22.2862)//1から2 8
		coltype = true;
	else if (myPosition.x >= -56.1935 && myPosition.x <= -52.7631 && myPosition.y >= -22.2862 && movedY <= -22.2862)//2から1
		coltype = false;
	if (myPosition.x >= -29.2292 && myPosition.x <= -25.7989 && myPosition.y <= -22.2543 && movedY >= -22.2543)//1から2 8
		coltype = true;
	else if (myPosition.x >= -29.2292 && myPosition.x <= -25.7989 && myPosition.y >= -22.2543 && movedY <= -22.2543)//2から1
		coltype = false;


	myPosition.x = movedX;
	myPosition.y = movedY;

	stairUP();

}

void tankMotionController()
{
	movingStraight = 0;
	movingRight = 0;

	if (pressW == true)
		movingStraight = tankMovingSpeed;
	if (pressS == true)
		movingStraight = -tankMovingSpeed;
	if (pressA == true)
		tankPos.vecX -= tankMovingSpeed / 4.0;
	if (pressD == true)
		tankPos.vecX += tankMovingSpeed / 4.0;
	if (pressSPACE == true)
	{

	}
	//double radian = tankPos.vecX * 180.0 / PI;

	float s = sin(tankPos.vecX);
	float c = cos(tankPos.vecX);


	tankPos.x -= s * movingStraight;
	tankPos.y -= c * movingStraight;
}

void sportsMotionController()
{
	movingStraight = 0;
	movingRight = 0;

	if (torque > 0)
	{
		//torque -= (1 * sinf(torque / 9000 * PI));
		switch (gear)
		{
		case 1:
			torque -= 1;
			break;
		case 2:
			torque -= 2;
			break;
		case 3:
			torque -= 3;
			break;
		case 4:
			torque -= 4;
			break;
		case 5:
			torque -= 5;
			break;
		case 6:
			torque -= 6;
			break;
		default:
			torque += 2;
			break;
		}
	}
	else if (torque == 0.0)
	{
		torque = 0.0;
	}
	else if( torque < 0)
	{
		torque += 2;
		if(torque < -180.0)
			torque = -180.0;

	}

	if (pressW == true)
	{
		//torque += (1 * cosf(torque / 18000 * PI));
		torque += 8;
	}
	if (pressS == true)
	{
		torque -= 8;
	}
	if (pressA == true)
	{
		sports_vec -= cos(sports_vec * 3 * PI / 180.0);
	}
	if (pressD == true)
	{
		sports_vec += cos(sports_vec * 3 * PI / 180.0);
	}
	if (sports_vec != 0.0 && pressA == false && pressD == false)
	{
		if (sports_vec > 0)
		{
			sports_vec -= sin(sports_vec * 3 * PI / 180.0);
		}
		else
		{
			sports_vec -= sin(sports_vec * 3 * PI / 180.0);
		}
	}

	if (torque < 0.0)
	{
		gear = -1;
	}
	else if (torque < speedLev * 20)
	{
		gear = 1;
	}
	else if (torque < speedLev * 50)
	{
		gear = 2;
	}
	else if (torque < speedLev * 90)
	{
		gear = 3;
	}
	else if (torque < speedLev * 120)
	{
		gear = 4;
	}
	else if (torque < speedLev * 160)
	{
		gear = 5;
	}
	else
	{
		gear = 6;
	}

	//前進するときに曲がるようにするけど、スピードが出すぎているときは曲がりにくくしたい
	sports_body_vec += sports_vec * (torque / speedLev) * cosf(torque / speedLev * PI / 540.0) / 1000.0;

	float s = sin(sports_body_vec * PI / 180.0);
	float c = cos(sports_body_vec * PI / 180.0);

	float c1x, c1y, c2x, c2y;
	c1x = sportsPos.x;
	c1y = sportsPos.y;

	sportsPos.x -= s * torque / speedLev / 100.0;
	sportsPos.y -= c * torque / speedLev / 100.0;

	c2x = sportsPos.x;
	c2y = sportsPos.y;

	int t = checkingSportsGoal(c1x, c1y, c2x, c2y);
	if (t == 1)
		sportsPos.lap++;
	else if(t == 2)
		sportsPos.lap--;

	if(sportsPos.lap == game[1].gameLap + 1)
	{
		fin = checkGameStts(1,7) + 1;
		game[1].stts = 7;
	}
}

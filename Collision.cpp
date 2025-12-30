#include "func.h"

extern float movingStraight;
extern float movingRight;
extern float myAngle;
extern Scene scene;
extern Position myPosition;
extern Position canonPos;
extern std::vector<std::pair<int, std::vector<Point>>> entranceWall;
extern std::vector<std::pair<int, std::vector<Point>>> robyWall;
extern std::vector<std::pair<int, std::vector<Point>>> tarkovWall;
extern std::vector<std::pair<int, std::vector<Point>>> tarkovWall2;
extern std::vector<std::pair<int, std::vector<Point>>> sportsWall;
extern std::vector<std::pair<int, std::vector<Point>>> tankWall;
extern vihicle sportsPos;
extern vihicle tankPos;
extern int torque;
extern int canonCoolTime;
extern float sports_vec;
extern float sports_body_vec;
extern bool coltype;

double pointToSegmentDistance(const Position& p, const Point& p1, const Point& p2) {
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;

	if (dx == 0 && dy == 0) {
		return std::sqrt((p.x - p1.x) * (p.x - p1.x) + (p.y - p1.y) * (p.y - p1.y));
	}

	double t = ((p.x - p1.x) * dx + (p.y - p1.y) * dy) / (dx * dx + dy * dy);
	t = std::max(0.0, std::min(1.0, t));

	double closestX = p1.x + t * dx;
	double closestY = p1.y + t * dy;

	return std::sqrt((p.x - closestX) * (p.x - closestX) + (p.y - closestY) * (p.y - closestY));
}

double pointToSegmentDistance(const vihicle& p, const Point& p1, const Point& p2) {
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;

	if (dx == 0 && dy == 0) {
		return std::sqrt((p.x - p1.x) * (p.x - p1.x) + (p.y - p1.y) * (p.y - p1.y));
	}

	double t = ((p.x - p1.x) * dx + (p.y - p1.y) * dy) / (dx * dx + dy * dy);
	t = std::max(0.0, std::min(1.0, t));

	double closestX = p1.x + t * dx;
	double closestY = p1.y + t * dy;

	return std::sqrt((p.x - closestX) * (p.x - closestX) + (p.y - closestY) * (p.y - closestY));
}

std::pair<Point, Point> getNearestSegment(const std::vector<Point>& polygon, const Position& playerPos) {
	double minDistance = std::numeric_limits<double>::infinity();
	std::pair<Point, Point> nearestSegment;

	for (size_t i = 0; i < polygon.size(); ++i) {
		Point p1 = polygon[i];
		Point p2 = polygon[(i + 1) % polygon.size()]; 

		double distance = pointToSegmentDistance(playerPos, p1, p2);

		if (distance < minDistance) {
			minDistance = distance;
			nearestSegment = { p1, p2 };
		}
	}
	return nearestSegment;
}

std::pair<Point, Point> getNearestSegment(const std::vector<Point>& polygon, const vihicle& playerPos) {
	double minDistance = std::numeric_limits<double>::infinity();
	std::pair<Point, Point> nearestSegment;

	for (size_t i = 0; i < polygon.size(); ++i) {
		Point p1 = polygon[i];
		Point p2 = polygon[(i + 1) % polygon.size()];

		double distance = pointToSegmentDistance(playerPos, p1, p2);

		if (distance < minDistance) {
			minDistance = distance;
			nearestSegment = { p1, p2 };
		}
	}
	return nearestSegment;
}

bool isIntersecting(const Point& p1, const Point& p2, const Position& p)
{
	if (p1.y > p.y != p2.y > p.y)
	{
		double intersectX = (p2.x - p1.x) * (p.y - p1.y) / (p2.y - p1.y) + p1.x;
		return p.x < intersectX;
	}
	return false;
}

bool isIntersecting(const Point& p1, const Point& p2, const vihicle& p)
{
	if (p1.y > p.y != p2.y > p.y)
	{
		double intersectX = (p2.x - p1.x) * (p.y - p1.y) / (p2.y - p1.y) + p1.x;
		return p.x < intersectX;
	}
	return false;
}

Point normalize(const Point& v) {
	float length = std::sqrt(v.x * v.x + v.y * v.y);
    if (length == 0.0f)
        return {0.0f, 0.0f};
	return { v.x / length,v.y / length };
}

Point calculateSymmetricPoint(Point c1, Point c2, float px,float py) {
	// 直線C1C2の傾きを計算
	double dx = c2.x - c1.x;
	double dy = c2.y - c1.y;
	double m = dy / dx;

	// 点Pから直線C1C2に垂直に交わる点Iを求める
	double x_i = (m * (py - c1.y) + m * m * c1.x + px) / (1 + m * m);
	double y_i = m * (x_i - c1.x) + c1.y;

	// 点Iを基準にPの線対称な点Qを計算
	Point q;
	q.x = 2 * x_i - px;
	q.y = 2 * y_i - py;

	return q;
}

void Collision_S(const std::vector<std::pair<int, std::vector<Point>>>& AllWall)
{
	float remainX = sportsPos.x;
	float remainY = sportsPos.y;
	for (auto Wall : AllWall)
	{
		int intersectionCount = 0;
		for (size_t i = 0; i < Wall.second.size(); ++i)
		{
			Point p1 = Wall.second[i];
			Point p2 = Wall.second[(i + 1) % Wall.second.size()];
			if (isIntersecting(p1, p2, sportsPos))
			{
				intersectionCount++;
			}
		}
		if ((Wall.first == 1 && intersectionCount % 2 == 0) || (Wall.first == 0 && intersectionCount % 2 == 1))
		{

			double radian = (90.0 - sports_body_vec) * PI / 180.0f;

			double s = sin(radian);
			double c = cos(radian);

			double length = torque / speedLev / 100.0;


			sportsPos.x += c * length;
			sportsPos.y += s * length;

			std::pair<Point, Point> nearestSegment = getNearestSegment(Wall.second, sportsPos);

			Point WallSegmentVector = normalize({ nearestSegment.first.x - nearestSegment.second.x,nearestSegment.first.y - nearestSegment.second.y });
			double wallsegX = double(WallSegmentVector.x);
			double wallsegY = double(WallSegmentVector.y);

			//とりあえず内積を出す
			double dotVec = c * wallsegX + s * wallsegY;
			double createVecX;
			double createVecY;

			//内積が負の場合壁のベクトルを逆向きにする
			if (dotVec < 0.0)
			{
				dotVec *= -1.0;
				//壁の逆ベクトルx移動ベクトルの大きさx内積の大きさ
				createVecX = wallsegX * -1.0 * length * dotVec; 
				createVecY = wallsegY * -1.0 * length * dotVec;
			}
			else
			{
				//壁のベクトルx移動ベクトルの大きさx内積の大きさ
				createVecX = wallsegX * length * dotVec;
				createVecY = wallsegY * length * dotVec;
			}
			sportsPos.x -= createVecX;
			sportsPos.y -= createVecY;

			intersectionCount = 0;
			for (size_t i = 0; i < Wall.second.size(); ++i)
			{
				Point p1 = Wall.second[i];
				Point p2 = Wall.second[(i + 1) % Wall.second.size()];
				if (isIntersecting(p1, p2, sportsPos))
				{
					intersectionCount++;
				}
			}
			if ((Wall.first == 1 && intersectionCount % 2 == 0) || (Wall.first == 0 && intersectionCount % 2 == 1))
			{
				std::pair<Point, Point> nearestSegment = getNearestSegment(Wall.second, sportsPos);

				Point q = calculateSymmetricPoint(nearestSegment.first,nearestSegment.second, sportsPos.x,sportsPos.y);

				sportsPos.x = q.x;
				sportsPos.y = q.y;
			}
			if (std::isnan(sportsPos.x) || std::isnan(sportsPos.y)) {
				sportsPos.x = remainX;
                sportsPos.y = remainY;
                break;
			}

			if(torque > 0)
				torque -= 20 * (1.0 - dotVec);//垂直に当たれば-10でほぼ水平なら-0

		}
	}
}

void Collision_T(const std::vector<std::pair<int, std::vector<Point>>>& AllWall)
{
	for (auto Wall : AllWall)
	{
		int intersectionCount = 0;
		for (size_t i = 0; i < Wall.second.size(); ++i)
		{
			Point p1 = Wall.second[i];
			Point p2 = Wall.second[(i + 1) % Wall.second.size()];
			if (isIntersecting(p1, p2, tankPos))
			{
				intersectionCount++;
			}
		}
		if ((Wall.first == 1 && intersectionCount % 2 == 0) || (Wall.first == 0 && intersectionCount % 2 == 1))
		{

			double radian = tankPos.vecX * 180.0 / PI;

			float s = sin(tankPos.vecX);
			float c = cos(tankPos.vecX);

			tankPos.x += s * movingStraight;
			tankPos.y += c * movingStraight;

			std::pair<Point, Point> nearestSegment = getNearestSegment(Wall.second, tankPos);

			Point WallSegmentVector = normalize({ nearestSegment.first.x - nearestSegment.second.x,nearestSegment.first.y - nearestSegment.second.y });
			double wallsegX = double(WallSegmentVector.x);
			double wallsegY = double(WallSegmentVector.y);

			//とりあえず内積を出す
			double dotVec = s * wallsegX + c * wallsegY;
			double createVecX;
			double createVecY;

			//内積が負の場合壁のベクトルを逆向きにする
			if (dotVec < 0.0)
			{
				dotVec *= -1.0;
				//壁の逆ベクトルx移動ベクトルの大きさx内積の大きさ
				createVecX = wallsegX * -1.0 * movingStraight * dotVec; 
				createVecY = wallsegY * -1.0 * movingStraight * dotVec;
			}
			else
			{
				//壁のベクトルx移動ベクトルの大きさx内積の大きさ
				createVecX = wallsegX * movingStraight * dotVec;
				createVecY = wallsegY * movingStraight * dotVec;
			}
			tankPos.x -= createVecX;
			tankPos.y -= createVecY;

			intersectionCount = 0;
			for (size_t i = 0; i < Wall.second.size(); ++i)
			{
				Point p1 = Wall.second[i];
				Point p2 = Wall.second[(i + 1) % Wall.second.size()];
				if (isIntersecting(p1, p2, tankPos))
				{
					intersectionCount++;
				}
			}
			if ((Wall.first == 1 && intersectionCount % 2 == 0) || (Wall.first == 0 && intersectionCount % 2 == 1))
			{
				std::pair<Point, Point> nearestSegment = getNearestSegment(Wall.second, tankPos);

				Point q = calculateSymmetricPoint(nearestSegment.first,nearestSegment.second, tankPos.x,tankPos.y);

				tankPos.x = q.x;
				tankPos.y = q.y;
			}
		}
	}
}

bool Collision_C()
{
	for (auto Wall : tankWall)
	{
		int intersectionCount = 0;
		for (size_t i = 0; i < Wall.second.size(); ++i)
		{
			Point p1 = Wall.second[i];
			Point p2 = Wall.second[(i + 1) % Wall.second.size()];
			Position toCheckPos;
			toCheckPos.x = canonPos.x + cosf(canonPos.alpha) * canonFirstSpeed * (canonCoolTime / 4.0);
			toCheckPos.y = canonPos.y + sinf(canonPos.alpha) * canonFirstSpeed * (canonCoolTime / 4.0);			
			if (isIntersecting(p1, p2, toCheckPos))
			{
				intersectionCount++;
			}
		}
		if ((Wall.first == 1 && intersectionCount % 2 == 0) || (Wall.first == 0 && intersectionCount % 2 == 1))
		{
			//z <= 11.899f
			if(canonPos.z <= 11.899f)
			{
				return true;
			}
		}
	}
	return false;
}

void Collision(const std::vector<std::pair<int, std::vector<Point>>>& AllWall)
{
	float remainX = myPosition.x;
	float remainY = myPosition.y;
	for (auto Wall : AllWall)
	{
		int intersectionCount = 0;
		for (size_t i = 0; i < Wall.second.size(); ++i)
		{
			Point p1 = Wall.second[i];
			Point p2 = Wall.second[(i + 1) % Wall.second.size()];
			if (isIntersecting(p1, p2, myPosition))
			{
				intersectionCount++;
			}
		}
		if ((Wall.first == 1 && intersectionCount % 2 == 0) || (Wall.first == 0 && intersectionCount % 2 == 1))
		{
			float radian = myAngle / 180.0f * PI;

			float sr = -sin(radian);
			float sr1 = -sin(radian - PI / 2.0f);
			float cr = cos(radian);
			float cr1 = cos(radian - PI / 2.0f);

			myPosition.x += sin(radian) * movingStraight;
			myPosition.y -= cos(radian) * movingStraight;
			myPosition.x -= cos(radian) * movingRight;
			myPosition.y += -sin(radian) * movingRight;

			std::pair<Point, Point> nearestSegment = getNearestSegment(Wall.second, myPosition);

			Point WallSegmentVector = normalize({ nearestSegment.first.x - nearestSegment.second.x,nearestSegment.first.y - nearestSegment.second.y });

			float dotVec = sr * WallSegmentVector.x + cr * WallSegmentVector.y ;
			float dotVec1 = sr1 * WallSegmentVector.x + cr1 * WallSegmentVector.y ;

			Point createVec1;
			Point createVec2;

			if (dotVec < 0.0)
			{
				dotVec *= -1.0;
				createVec1 = { WallSegmentVector.x * -1.0f * movingStraight * dotVec,WallSegmentVector.y * -1.0f * movingStraight * dotVec };
			}
			else
				createVec1 = { WallSegmentVector.x * movingStraight * dotVec ,WallSegmentVector.y * movingStraight * dotVec };
			if (dotVec1 < 0.0)
			{
				dotVec1 *= -1.0;
				createVec2 = { WallSegmentVector.x * -1.0f * movingRight * dotVec1,WallSegmentVector.y * -1.0f * movingRight * dotVec1 };
			}
			else
				createVec2 = { WallSegmentVector.x * movingRight * dotVec1,WallSegmentVector.y * movingRight * dotVec1 };
			//slide
			myPosition.x += createVec1.x + createVec2.x;
			myPosition.y += createVec1.y + createVec2.y;


			intersectionCount = 0;
			for (size_t i = 0; i < Wall.second.size(); ++i)
			{
				Point p1 = Wall.second[i];
				Point p2 = Wall.second[(i + 1) % Wall.second.size()];
				if (isIntersecting(p1, p2, myPosition))
				{
					intersectionCount++;
				}
			}
			if ((Wall.first == 1 && intersectionCount % 2 == 0) || (Wall.first == 0 && intersectionCount % 2 == 1))
			{
				std::pair<Point, Point> nearestSegment = getNearestSegment(Wall.second, myPosition);

				Point q = calculateSymmetricPoint(nearestSegment.first, nearestSegment.second, myPosition.x, myPosition.y);

				myPosition.x = q.x;
				myPosition.y = q.y;
			}
			if (std::isnan(myPosition.x) || std::isnan(myPosition.y)) {
				myPosition.x = remainX;
                myPosition.y = remainY;
                break;
			}
		}
	}
}

void CollisionController()
{
	int intersectionCount = 0;
	switch (scene)
	{
	case scene_3:
		Collision(entranceWall);
		break;
	case scene_4:
		Collision(robyWall);
		break;
	case scene_5://chess
		break;
	case scene_6://tank
		Collision_T(tankWall);
		break;
	case scene_7://sports
		Collision_S(sportsWall);
		break;
	case scene_8:
		if(coltype == false)
			Collision(tarkovWall);
		else
			Collision(tarkovWall2);
		break;
	default:
		break;
	}
}
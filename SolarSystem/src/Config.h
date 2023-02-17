#pragma once
const int WindowXPos = 50;
const int WindowYPos = 50;
const int WindowWidth = 1200;
const int WindowHeight = 1200;

const float  PI = 3.14159265358979323846f;

const int StarsNum = 10;

const int TimePast = 1;			//默认一天绘制一次
const float SelfRotate = 3.0;		//自转速度
const int REST = 700;
const int REST_Y = -REST;
const int REST_Z = REST;
const int OFFSET = 20;

enum STARS
{
	Sun,
	Mercury,
	Venus,
	Earth,
	Moon,
	Mars,
	Jupiter,
	Saturn,
	Uranus,
	Neptune
};

#define SET_VALUE_3(name, value0, value1, value2) \
                   ((name)[0])=(value0), ((name)[1])=(value1), ((name)[2])=(value2)

#define SUN_RADIUS 48.74
#define MER_RADIUS  7.32
#define VEN_RADIUS 18.15
#define EAR_RADIUS 19.13
#define MOO_RADIUS  6.15
#define MAR_RADIUS 10.19
#define JUP_RADIUS 42.90
#define SAT_RADIUS 36.16
#define URA_RADIUS 25.56
#define NEP_RADIUS 24.78

#define MER_DIS   62.06
#define VEN_DIS  115.56
#define EAR_DIS  168.00
#define MOO_DIS   26.01
#define MAR_DIS  228.00
#define JUP_DIS  333.40
#define SAT_DIS  428.10
#define URA_DIS 848.00
#define NEP_DIS 949.10

#define MER_SPEED   87.0
#define VEN_SPEED  225.0
#define EAR_SPEED  365.0
#define MOO_SPEED   30.0
#define MAR_SPEED  687.0
#define JUP_SPEED 1298.4
#define SAT_SPEED 3225.6
#define URA_SPEED 3066.4
#define NEP_SPEED 6014.8


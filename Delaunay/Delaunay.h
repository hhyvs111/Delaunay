#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Delaunay.h"
#include <Qpainter.h>


#define Type double

// 最大定点数目上限和最大三角形数目上限
#define MAX_VERTEX   500
#define MAX_TRIANGLE 1000
#define MAX_CIRCLE 1000
#define MAX_NUM 1000

// 定义结构VERTEX表达一个点的坐标
typedef   struct   tagVERTEX
{
	long   x;  // x坐标
	long   y;  // y坐标
	long   z;  // z坐标
}VERTEX;

// 定义结构TRIANGLE表达一个三角形
typedef   struct   tagTRIANGLE
{
	int     vv0;
	int     vv1;
	int     vv2;
}TRIANGLE;

typedef   struct tagCIRCLE
{
	double xc;     //圆心
	double yc;
	double r;		//半径
}CIRCLE;

class Delaunay : public QMainWindow
{
	Q_OBJECT

private:
	Ui::DelaunayClass ui;
	int tPoints;  //定义点？
	int HowMany;		//有多少个三角形
	TRIANGLE Triangle[501];		//三角数组
	VERTEX Vertex[501];			//点的个数
	CIRCLE Circle[501];			//外接圆的个数

protected:
	void paintEvent(QPaintEvent *);   //要放在这里啊兄弟！

public:
	Delaunay(QWidget *parent = Q_NULLPTR);
	int FvsTrianglate(int nvert);
	//判断哪条边？
	int FvsTriangleWhichSide(double xp, double yp, double x1, double y1, double x2, double y2);
	//判断三角形是否在圆内

	CIRCLE FvsCenter(double x1, double y1, double x2, double y2, double x3, double y3);

	bool FvsTriangleInCircle(double xp, double yp, double x1, double y1, double x2, double y2, double x3, double y3, double *xc, double *yc, double* r);
	//Delaunay();
	virtual ~Delaunay();
};

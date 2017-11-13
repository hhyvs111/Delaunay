#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Delaunay.h"
#include <Qpainter.h>


#define Type double

// ��󶨵���Ŀ���޺������������Ŀ����
#define MAX_VERTEX   500
#define MAX_TRIANGLE 1000
#define MAX_CIRCLE 1000
#define MAX_NUM 1000

// ����ṹVERTEX���һ���������
typedef   struct   tagVERTEX
{
	long   x;  // x����
	long   y;  // y����
	long   z;  // z����
}VERTEX;

// ����ṹTRIANGLE���һ��������
typedef   struct   tagTRIANGLE
{
	int     vv0;
	int     vv1;
	int     vv2;
}TRIANGLE;

typedef   struct tagCIRCLE
{
	double xc;     //Բ��
	double yc;
	double r;		//�뾶
}CIRCLE;

class Delaunay : public QMainWindow
{
	Q_OBJECT

private:
	Ui::DelaunayClass ui;
	int tPoints;  //����㣿
	int HowMany;		//�ж��ٸ�������
	TRIANGLE Triangle[501];		//��������
	VERTEX Vertex[501];			//��ĸ���
	CIRCLE Circle[501];			//���Բ�ĸ���

protected:
	void paintEvent(QPaintEvent *);   //Ҫ�������ﰡ�ֵܣ�

public:
	Delaunay(QWidget *parent = Q_NULLPTR);
	int FvsTrianglate(int nvert);
	//�ж������ߣ�
	int FvsTriangleWhichSide(double xp, double yp, double x1, double y1, double x2, double y2);
	//�ж��������Ƿ���Բ��

	CIRCLE FvsCenter(double x1, double y1, double x2, double y2, double x3, double y3);

	bool FvsTriangleInCircle(double xp, double yp, double x1, double y1, double x2, double y2, double x3, double y3, double *xc, double *yc, double* r);
	//Delaunay();
	virtual ~Delaunay();
};

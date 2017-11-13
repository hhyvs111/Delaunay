#include "Delaunay.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define max(a, b)  (((a) > (b)) ? (a) : (b))

#define random(a,b) rand() / (float)30

Delaunay::Delaunay(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

Delaunay::~Delaunay()
{
	//��������
}


void Delaunay::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	int n = 100;
	for (int i = 1;i <= n;i++)
	{
		Vertex[i].x = random(100, 500);
		Vertex[i].y = random(100, 500);
		cout << "X :" << Vertex[i].x << endl;
		cout << "Y :" << Vertex[i].y << endl;

	}
	 HowMany = FvsTrianglate(n);
	
	for(int i = 1;i <= HowMany;i++)
	{
		painter.drawLine(QPointF(Vertex[Triangle[i].vv0].x, Vertex[Triangle[i].vv0].y),
						QPointF(Vertex[Triangle[i].vv1].x, Vertex[Triangle[i].vv1].y));
		painter.drawLine(QPointF(Vertex[Triangle[i].vv1].x, Vertex[Triangle[i].vv1].y),
						QPointF(Vertex[Triangle[i].vv2].x, Vertex[Triangle[i].vv2].y));
		painter.drawLine(QPointF(Vertex[Triangle[i].vv2].x, Vertex[Triangle[i].vv2].y),
					QPointF(Vertex[Triangle[i].vv0].x, Vertex[Triangle[i].vv0].y));
	}
	

}

CIRCLE Delaunay::FvsCenter(double x1, double y1, double x2, double y2, double x3, double y3)
{
	CIRCLE Circle;
	double eps;   //һ����Сֵ��epsilon�����������ʶ�����С���㸡�������ײ���ũ
	double m1;
	double m2;
	double mx1;
	double mx2;
	double my1;
	double my2;
	double dx;
	double dy;
	double rsqr;
	double drsqr;
	double xc, yc, r;
	eps = 0.000001;

	if (fabs(y2 - y1) < eps)   //���y2��y1��ͬһֱ����
	{
		m2 = -(x3 - x2) / (y3 - y2);	//m2��p2��p3���ߵ�б��
		mx2 = (x2 + x3) / 2;			//mx2��my2����p2��p3�������ߵ��е����ꡣ
		my2 = (y2 + y3) / 2;

		xc = (x2 + x1) / 2;			//Բ�ĵ�x���꣬��Ϊy2��y1��ͬһֱ���ϣ���Բ�ĵ�x�������p1��p2���е��ϡ�    
		yc = m2 * (xc - mx2) + my2;   //Բ�ĵ�y���꣬��б�ʹ�ʽ�ı��Σ���Ϊ���ߵ�б����ԭ����-1/m2
	}
	else if (fabs(y3 - y2) < eps)		//ͬ��
	{
		m1 = -(x2 - x1) / (y2 - y1);
		mx1 = (x1 + x2) / 2;
		my1 = (y1 + y2) / 2;
		xc = (x3 + x2) / 2;
		yc = m1 * ((xc)-mx1) + my1;
	}
	else                                   //����Ļ��Ͳ��������������������
	{
		m1 = -(x2 - x1) / (y2 - y1);		//�ֱ�����ֱ�ߵ�б��
		m2 = -(x3 - x2) / (y3 - y2);
		mx1 = (x1 + x2) / 2;				//����ֱ�ߵ��е�����
		mx2 = (x2 + x3) / 2;
		my1 = (y1 + y2) / 2;
		my2 = (y2 + y3) / 2;
		xc = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);		//
		yc = m1 * ((xc)-mx1) + my1;
	}

	dx = x2 - (xc);			//����㵽Բ�ĵľ��붼��һ����
	dy = y2 - (yc);
	rsqr = dx * dx + dy * dy;	//Բ�İ뾶��ƽ��
	r = sqrt(rsqr);
	Circle.r = r;
	Circle.xc = xc;
	Circle.yc = yc;
	return Circle;
}
//�ж�һ�����Ƿ���Բ�ڣ�����ȷ��һ��Բ��x1,x2,x3�������ε������㣬xp,yp�������㡣
bool Delaunay::FvsTriangleInCircle(double xp, double yp, double x1, double y1, double x2, double y2, double x3, double y3, double *xc, double *yc, double *r)
{
	bool  Ret;

	double eps;   //һ����Сֵ��epsilon�����������ʶ�����С���㸡�������ײ���ũ
	double m1;
	double m2;
	double mx1;
	double mx2;
	double my1;
	double my2;
	double dx;
	double dy;
	double rsqr;
	double drsqr;

	eps = 0.000001;
	Ret = false;
	//fabs�󸡵����ľ���ֵ
	if (fabs(y1 - y2) < eps && fabs(y2 - y3) < eps)	//���y1��y2��y3��ͬһֱ���ϣ�����false
	{
		printf("INCIRCUM - F - Points are coincident !\n");
		return Ret;
	}

	if (fabs(y2 - y1) < eps)   //���y2��y1��ͬһֱ����
	{
		m2 = -(x3 - x2) / (y3 - y2);	//m2��p2��p3���ߵ�б��
		mx2 = (x2 + x3) / 2;			//mx2��my2����p2��p3�������ߵ��е����ꡣ
		my2 = (y2 + y3) / 2;

		*xc = (x2 + x1) / 2;			//Բ�ĵ�x���꣬��Ϊy2��y1��ͬһֱ���ϣ���Բ�ĵ�x�������p1��p2���е��ϡ�    
		*yc = m2 * (*xc - mx2) + my2;   //Բ�ĵ�y���꣬��б�ʹ�ʽ�ı��Σ���Ϊ���ߵ�б����ԭ����-1/m2
	}
	else if (fabs(y3 - y2) < eps)		//ͬ��
	{
		m1 = -(x2 - x1) / (y2 - y1);
		mx1 = (x1 + x2) / 2;
		my1 = (y1 + y2) / 2;
		*xc = (x3 + x2) / 2;
		*yc = m1 * ((*xc) - mx1) + my1;
	}
	else                                   //����Ļ��Ͳ��������������������
	{
		m1 = -(x2 - x1) / (y2 - y1);		//�ֱ�����ֱ�ߵ�б��
		m2 = -(x3 - x2) / (y3 - y2);
		mx1 = (x1 + x2) / 2;				//����ֱ�ߵ��е�����
		mx2 = (x2 + x3) / 2;
		my1 = (y1 + y2) / 2;
		my2 = (y2 + y3) / 2;
		*xc = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);		//ĳ���߼���ʽ��X�����꣬
		*yc = m1 * ((*xc) - mx1) + my1;
	}

	dx = x2 - (*xc);			//����㵽Բ�ĵľ��붼��һ����
	dy = y2 - (*yc);
	rsqr = dx * dx + dy * dy;	//Բ�İ뾶��ƽ��
	*r = sqrt(rsqr);
	dx = xp - (*xc);			//p�㵽Բ�ĵľ���
	dy = yp - (*yc);
	drsqr = dx * dx + dy * dy;

	/*    if ( drsqr <= rsqr )
	TRACE("true\n");
	else
	TRACE("false\n");
	*/
	if (drsqr <= rsqr)	//����㵽Բ�ĵľ���С�ڰ뾶�򷵻��棬˵������Բ�ڡ�
		return true;
	else
		return false;
}


//�ж������Ƿ���
int Delaunay::FvsTriangleWhichSide(double xp, double yp, double x1, double y1, double x2, double y2)
{
	//equation ��ȡ�
	double equation;
	/*
	(y2 - y1)   (y3 - y2)
	--------- = --------- ,
	(x2 - x1)   (x3 - x2)*/

	//������ÿ���ĳ˻�����0���ߡ�
	equation = ((yp - y1) * (x2 - x1)) - ((y2 - y1) * (xp - x1));

	if (equation > 0)
		return -1;
	else if (equation == 0)
		return 0;
	else
		return 1;

}


int Delaunay::FvsTrianglate(int nvert)  //nvert������
{
	//	bool         Complete[MAX_TRIANGLE]; �����������Σ�
	bool         Complete[MAX_TRIANGLE + 1];
	//    long          Edges[2][3000]; /// ?
	long          Edges[3][3001]; //   �ߵĸ�����Edges[1]����ߵ���㣬Edges[2]����ߵ��յ�
	long          Nedge; //   �ߵĸ���

						 // For Super Triangle������һ�����������Ρ�
	long   xmin;	//x����С����ֵ����ͬ
	long   xmax;
	long   ymin;
	long   ymax;

	long   xmid;	//�����ʱ��֪
	long   ymid;

	double dx;		//����xmax-xmin����ͬ
	double dy;
	double dmax;	//math.max(dx,dy)
					// General Variables
	int   i;
	int   j;
	int   k;
	int   ntri;
	double   xc;	//Բ�ĺͰ뾶
	double   yc;
	double   r;
	bool  inc;

	/// ? ��Ӳ��������ĳ�ʼ�����̣�������������ȫ����ʼ��Ϊfalse
	for (i = 1; i <= MAX_TRIANGLE; i++)
		Complete[i] = false;

	// Find the maximum and minimum vertex bounds.  �ҵ������С�ı߽�
	// This is to allow calculation of the bounding triangle
	xmin = Vertex[1].x;
	
	ymin = Vertex[1].y;
	xmax = xmin;
	ymax = ymin;
	for (i = 2; i <= nvert; i++)     //�ҵ���ǰ��������С��XY����
	{
		cout << "X :" << Vertex[i].x << endl;
		if (Vertex[i].x < xmin)      xmin = Vertex[i].x;
		if (Vertex[i].x > xmax)      xmax = Vertex[i].x;
		if (Vertex[i].y < ymin)      ymin = Vertex[i].y;
		if (Vertex[i].y > ymax)      ymax = Vertex[i].y;
	}

	dx = xmax - xmin;
	dy = ymax - ymin;
	if (dx > dy)
		dmax = dx;
	else
		dmax = dy;
	xmid = (xmax + xmin) / 2;      //super�����ε��е㡣
	ymid = (ymax + ymin) / 2;

	// Set up the supertriangle
	// This is a triangle which encompasses all the sample points.
	// The supertriangle coordinates are added to the end of the
	// vertex list. The supertriangle is the first triangle in
	// the triangle list.
	//����һ�����������Σ�������������еĵ㡣���������εĵ���ӵ�������
	//��ĺ��棬�����������������б���ĵ�һ��������


	//��Щ���ǳ������ǵĶ��㣬ע����nvert��+1�����Գ������ǵĶ�����ڶ����б�ĺ���
	Vertex[nvert + 1].x = xmid - 2 * (long)dmax;		//�⼸���㹹��һ�����������Σ�һ����ƽ����X�ᡣ
	Vertex[nvert + 1].y = ymid - (long)dmax;
	Vertex[nvert + 2].x = xmid;
	Vertex[nvert + 2].y = ymid + 2 * (long)dmax;
	Vertex[nvert + 3].x = xmid + 2 * (long)dmax;
	Vertex[nvert + 3].y = ymid - (long)dmax;
	Triangle[1].vv0 = nvert + 1;			//����Ϊʲô�Ƕ�����+1��
	Triangle[1].vv1 = nvert + 2;			//��Ϊ���Ǿ���һЩ������ɣ���Vertex[nvert]�����ҵ���Ӧ���������ֵ������ֱ���ö���������±�ֵ����ʾ
	Triangle[1].vv2 = nvert + 3;
	Complete[1] = false;
	ntri = 1;			//���ǵ�����

	// Include each point one at a time into the existing mesh
	for (i = 1; i <= nvert; i++)        //ѭ��N�����
	{
		Nedge = 0;			//�ߵ�����
							/* Set up the edge buffer.    �߻������������Ų��������εı�
							'If the point (Vertex(i).x,Vertex(i).y) lies inside the circumcircle then the  ���������������Բ����ô�����ǵ����߶��ŵ��߻�������ȥ��
							'three edges of that triangle are added to the edge buffer.
							*/
		j = 0;
		do
		{
			j = j + 1;
			if (Complete[j] != true)					//���j�����β���Delaunay��������������ж�
			{
				inc = FvsTriangleInCircle(Vertex[i].x, Vertex[i].y,		//i���j���ǵ�ƥ�����
					Vertex[Triangle[j].vv0].x,
					Vertex[Triangle[j].vv0].y,
					Vertex[Triangle[j].vv1].x,
					Vertex[Triangle[j].vv1].y,
					Vertex[Triangle[j].vv2].x,
					Vertex[Triangle[j].vv2].y,
					&xc, &yc, &r);				//Բ������Ϊ��ַ���ã�������ֵ���ڸú������ص�ָ��ֵ

												//'Include this if points are sorted by X
												//'If (xc + r) < Vertex(i).x Then
												//    'complete(j) = True
												//'Else


				if (inc == true)	//�������Բ�ڣ��������μ���һ���������������ε����߼���߼���buffer edges����
				{
					Edges[1][Nedge + 1] = Triangle[j].vv0;				//Edges��1��2�ֱ�����߶ε������յ㣬�Լ�����
					Edges[2][Nedge + 1] = Triangle[j].vv1;
					Edges[1][Nedge + 2] = Triangle[j].vv1;
					Edges[2][Nedge + 2] = Triangle[j].vv2;
					Edges[1][Nedge + 3] = Triangle[j].vv2;
					Edges[2][Nedge + 3] = Triangle[j].vv0;
					Nedge = Nedge + 3;									//��Ϊ���Ǳ���֣��������3
					Triangle[j].vv0 = Triangle[ntri].vv0;
					Triangle[j].vv1 = Triangle[ntri].vv1;
					Triangle[j].vv2 = Triangle[ntri].vv2;

					Complete[j] = Complete[ntri];    //����j������״̬
					//TRACE("j = %d, ntri = %d \n", j, ntri);
					j = j - 1;
					ntri = ntri - 1;			//����һ������-1
				}
				//}
			}
		} while (j < ntri);	//��������С������

							//'Tag multiple edges			��Ƕ����Ե
							//'Note: if all triangles are specified anticlockwise then all
							//'interior edges are opposite pointing in direction.
							//���������������ʱ���ʷ֣���ô�����ڲ��߶����෴��
							//��ѭ���������������ظ���
		for (j = 1; j <= Nedge - 1; j++)
		{
			// �����ʽ�ж��������ʱ���ȴ�����������������Ŵ���Ƚ��������Ȼ���ٴ����߼�������� /// ?
			// If Not Edges(1, j) = 0 And Not Edges(2, j) = 0 Then
			if (!(Edges[1][j] == 0) && !(Edges[2][j] == 0))			//����ñߴ��ڣ���ô
			{
				//TRACE("enter then. ij=%ld-%ld\n", i, j);

				for (k = j + 1; k <= Nedge; k++)				//j���ڱ�
				{
					if (!(Edges[1][k] == 0) && !(Edges[2][k] == 0))		//���j���ڱ�KҲ����
					{
						if (Edges[1][j] == Edges[2][k])				//���J�ߵ�����K�ߵ��յ����
						{
							if (Edges[2][j] == Edges[1][k])			//���J�ߵ��յ��K�ߵ�������
							{
								Edges[1][j] = 0;					//�����������ߣ�
								Edges[2][j] = 0;
								Edges[1][k] = 0;
								Edges[2][k] = 0;
							}
						}
					}
				}
			}
		}

		//'Form new triangles for the current point  ���������������εĵ�
		//'Skipping over any tagged edges.		�������б���ǹ��ı�
		//'All edges are arranged in clockwise order.		���б߶���˳ʱ������


		//�����еĵ��볬�����������ɵĵ�����������
		for (j = 1; j <= Nedge; j++)
		{
			if (!(Edges[1][j] == 0) && !(Edges[2][j] == 0))			//�����û�б���ǵı�
			{
				ntri = ntri + 1;						//����+1��
				Triangle[ntri].vv0 = Edges[1][j];		//��û��ǵı���������
				Triangle[ntri].vv1 = Edges[2][j];
				Triangle[ntri].vv2 = i;					//���i��ʲô��  ѭ����һ��ʼ
				Complete[ntri] = false;

			}
		}
	}

	//'Remove triangles with supertriangle vertices   �Ƴ��������Ƕ���
	//'These are triangles which have a vertex number greater than NVERT		  ��Щ���ǵĶ���������NVERT

	i = 0;
	do
	{
		//TRACE("nvert:%d ", nvert);
		i = i + 1;
		if (Triangle[i].vv0 > nvert ||					//����nvert�ĵ�Ҫ
			Triangle[i].vv1 > nvert ||
			Triangle[i].vv2 > nvert)
		{

			Triangle[i].vv0 = Triangle[ntri].vv0;				//ɾ��
			Triangle[i].vv1 = Triangle[ntri].vv1;
			Triangle[i].vv2 = Triangle[ntri].vv2;
			i = i - 1;
			ntri = ntri - 1;

		}
	} while (i < ntri);

	return ntri;						//�������ǵ�����

}




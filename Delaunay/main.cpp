#include "Delaunay.h"
#include <ui_Delaunay.h>
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Delaunay w;
	w.show();
	return a.exec();
}

/********************************************************************************
** Form generated from reading UI file 'Delaunay.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELAUNAY_H
#define UI_DELAUNAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DelaunayClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DelaunayClass)
    {
        if (DelaunayClass->objectName().isEmpty())
            DelaunayClass->setObjectName(QStringLiteral("DelaunayClass"));
        DelaunayClass->resize(600, 400);
        menuBar = new QMenuBar(DelaunayClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        DelaunayClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DelaunayClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DelaunayClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(DelaunayClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        DelaunayClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(DelaunayClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DelaunayClass->setStatusBar(statusBar);

        retranslateUi(DelaunayClass);

        QMetaObject::connectSlotsByName(DelaunayClass);
    } // setupUi

    void retranslateUi(QMainWindow *DelaunayClass)
    {
        DelaunayClass->setWindowTitle(QApplication::translate("DelaunayClass", "Delaunay", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DelaunayClass: public Ui_DelaunayClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELAUNAY_H

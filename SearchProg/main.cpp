#include "mainwindow.h"
#include "searchfolder.h"

#include <QApplication>
#include <QDebug>
#include <QElapsedTimer>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow   w;
    w.show();

    SearchFolder finder;
    // Good Case :
    finder.setStartDirectory("D:/www/QT");
    finder.setFilters("*.jpg,*.png");


    QElapsedTimer myTimer;
    myTimer.start();

    // finder.start();


    if (finder.results().size() == 15)
        qDebug() << "Result size is OK";
    else
        qDebug() << "Result size is KO, size is: " << finder.results().size();
    qDebug() << finder.results();

    int current = finder.currentProgress();
    int max     = finder.maxProgress();
    qDebug() << current;
    qDebug() << max;
    finder.stop();
    qDebug() << "Elapsed Time :" << myTimer.elapsed();

    // Bad Case :
    /*finder.setStartDirectory("C:/Toto");
    finder.setFilters(",,,");*/

    return a.exec();
}

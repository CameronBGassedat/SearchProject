#include "mainwindow.h"
#include "../LibrarySearchingProject/librarysearchingproject.h"

#include <QApplication>
#include <QDebug>
#include <QElapsedTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //PROCESS
    LibrarySearchingProject finder;

    //Démarrage du timer
    QElapsedTimer myTimer;
    myTimer.start();

    finder.setStartDirectory("C:/Users/alexi/Documents/Projets Qt/SearchProject/TPSearchProject/TestData");
    finder.setFilters("*.jpg,*.png");

    finder.start();

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


    return a.exec();
}

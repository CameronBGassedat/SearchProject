#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDirIterator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnSearch_clicked()
{
    ui->btnSearch->setDisabled(true);

    int elapsedTime = executeFinder();

    //Affichage des résultats à l'utilisateur
    displayResults(elapsedTime);
}

void MainWindow::on_btnCancel_clicked()
{
    ui->btnSearch->setEnabled(true);

    clearFinder();

}

void MainWindow::clearFinder()
{
    ui->startDirectory->setText("");
    ui->filters->setText("");
    ui->result->setText("");
    finder.cleanresults();
}

int MainWindow::executeFinder()
{
    QString directoryFinder = ui->startDirectory->text();
    QString s_filters = ui->filters->text();

    directoryFinder.replace("\'","/'");


    finder.setStartDirectory(directoryFinder);
    finder.setFilters(s_filters);

    //Démarrage du timer
    QElapsedTimer myTimer;
    myTimer.start();
    finder.start();
    finder.stop();
    return myTimer.elapsed();
}

void MainWindow::displayResults(int elapsedTime)
{
    QString s_display;
    s_display = "Nombre d'éléments trouvés : " + QString::number(finder.results().size()) + '\n';
    s_display = s_display + "Temps écoulée : " + QString::number(elapsedTime) + " ms" + '\n';

    for (int i = 0; i < finder.results().size(); i++)
        s_display = s_display + finder.results()[i] + '\n';

    ui->result->setText(s_display);
}




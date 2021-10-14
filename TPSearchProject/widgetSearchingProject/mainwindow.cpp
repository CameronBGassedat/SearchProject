#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    //Affichage des résultats à l'utilisateur
    displayResults();
}

void MainWindow::displayResults()
{
    QString s_display;

    s_display = "Nombre d'éléments trouvés : " + QString::number(finder.results().size());

    ui->result->setText(s_display);
}

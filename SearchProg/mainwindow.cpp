#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), search(new SearchFolder()) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
    delete search;
}


void MainWindow::on_startDirectory_textChanged(const QString &arg1) {
    qDebug() << __FUNCTION__ << __LINE__ << arg1;
    search->setStartDirectory(arg1);
}

void MainWindow::on_filters_textChanged(const QString &arg1) {
    search->setFilters(arg1);
}

void MainWindow::on_btnSearch_clicked() {
    search->start();
}

void MainWindow::on_btnCancel_clicked() {
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../LibrarySearchingProject/librarysearchingproject.h"
#include <QMainWindow>
#include <QDebug>
#include<QElapsedTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    LibrarySearchingProject finder;
    MainWindow(QWidget *parent = nullptr);
    int executeFinder();
    void clearFinder();
    void displayResults(int);
    ~MainWindow();

private slots:
    void on_btnSearch_clicked();

    void on_btnCancel_clicked();

    void on_btnBrowse_clicked();

private:
    Ui::MainWindow *ui;
    QString s_directoryFinder;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myythread.h"

#include <QMainWindow>
#include <QStringListModel>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    QTimer *          _timer;
    int               _count  = 0;
    MyYThread *       _th1    = nullptr;
    QStringListModel *m_model = nullptr;
    QStringList       m_dirs;
    int               m_results_count  = 0;
    qint64            m_full_elaped    = 0;
    int               m_rate           = 0;
    QString           m_current_dir    = "";
    QString           m_selected_entry = "";

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void searchStarted();
    void searchFinished();
    void searchLocked(bool is_locked = true);
    void updateStatusBar();

  private:
    Ui::MainWindow *ui;
  public slots:
    void onValueChanged(int i);
    void onDirsAdded(const QStringList &);
    void onSearchStats(int dirs_size, qint64 full_elaped, int rate);
    void onExploringDir(QString dir);
  private slots:
    void on_pushButton_clicked();
    void on_pushButton_stop_clicked();
    void on_buttonBrowse_clicked();
    void on_filters_textChanged(const QString &arg1);
    void on_start_path_textChanged(const QString &arg1);
    void on_pushButton_reset_clicked();
    void on_listView_clicked(const QModelIndex &index);
    void on_listView_doubleClicked(const QModelIndex &index);
    void onOpenFolder();
    void onLaunchFile();
};
#endif // MAINWINDOW_H

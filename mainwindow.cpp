#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDebug>
#include <QDesktopServices>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _timer(new QTimer), _th1(new MyYThread), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // timer
    _timer->setInterval(100);
    connect(_timer, &QTimer::timeout, [&]() { this->ui->label->setText(QString::number(this->_count++)); });
    _timer->start();

    // listview
    m_model = new QStringListModel(this);
    ui->listView->setUniformItemSizes(true);
    ui->listView->setModel(m_model);

    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listView, &QListView::customContextMenuRequested, [this](QPoint pos) {
        QModelIndex index = ui->listView->indexAt(pos);
        m_selected_entry  = index.data(Qt::DisplayRole).toString();
        QMenu *  menu     = new QMenu(this);
        QAction *explore  = new QAction("Open folder", this);
        explore->setStatusTip(QString("Open the folder containg %1 in explorer ").arg(m_selected_entry));
        connect(explore, &QAction::triggered, this, &MainWindow::onOpenFolder);
        menu->addAction(explore);

        QAction *launch = new QAction("Launch file with default application", this);
        launch->setStatusTip(QString("Launch %1 with default application").arg(m_selected_entry));
        connect(launch, &QAction::triggered, this, &MainWindow::onLaunchFile);
        menu->addAction(launch);

        menu->popup(ui->listView->viewport()->mapToGlobal(pos));
    });

    // push
    ui->pushButton_stop->hide();

    // signal & slots
    connect(_th1, &MyYThread::started, this, &MainWindow::searchStarted);
    connect(_th1, &MyYThread::finished, this, &MainWindow::searchFinished);
    connect(_th1, &MyYThread::valueChanged, this, &MainWindow::onValueChanged);
    connect(_th1, &MyYThread::stats, this, &MainWindow::onSearchStats);
    connect(_th1, &MyYThread::dirsAdded, this, &MainWindow::onDirsAdded);
    connect(_th1, &MyYThread::exploringDir, this, &MainWindow::onExploringDir);
}


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::searchStarted() {
    qDebug() << __FUNCTION__ << __LINE__;
    ui->pushButton_stop->show();
    ui->pushButton->hide();
    m_dirs.clear();
    searchLocked();
}

void MainWindow::searchFinished() {
    qDebug() << __FUNCTION__ << __LINE__;
    ui->pushButton_stop->hide();
    ui->pushButton->show();
    searchLocked(false);
    ui->statusbar->showMessage(QString("%1 results found in %2 s (%3 result/s)")
                                   .arg(m_results_count)
                                   .arg(QTime::fromMSecsSinceStartOfDay((int)m_full_elaped).toString())
                                   .arg(m_rate));
}

void MainWindow::searchLocked(bool is_locked) {
    qDebug() << __FUNCTION__ << __LINE__ << is_locked;
    ui->pushButton_reset->setDisabled(is_locked);
    ui->filters->setDisabled(is_locked);
    ui->start_path->setDisabled(is_locked);
    ui->buttonBrowse->setDisabled(is_locked);
}

void MainWindow::updateStatusBar() {
    ui->statusbar->showMessage(QString("%1 results in %2 s (%3 result/s), exploring %4")
                                   .arg(m_results_count)
                                   .arg(QTime::fromMSecsSinceStartOfDay((int)m_full_elaped).toString())
                                   .arg(m_rate)
                                   .arg(m_current_dir));
}

void MainWindow::onValueChanged(int i) {
    qDebug() << __FUNCTION__ << __LINE__;
    ui->label_2->setText(QString::number(i));
}

void MainWindow::onDirsAdded(const QStringList &list) {
    qDebug() << __FUNCTION__ << __LINE__ << list.size() << m_dirs.size();
    m_dirs << list;
    m_model->setStringList(m_dirs);
    ui->listView->scrollToBottom();
    updateStatusBar();
}

void MainWindow::onSearchStats(int dirs_size, qint64 full_elaped, int rate) {
    qDebug() << __FUNCTION__ << __LINE__ << m_dirs.size();
    m_results_count = m_dirs.size(); // dirs_size;
    m_full_elaped   = full_elaped;
    m_rate          = rate;
}

void MainWindow::onExploringDir(QString dir) {
    m_current_dir = dir;
}

void MainWindow::on_pushButton_clicked() {
    qDebug() << __FUNCTION__ << __LINE__;

    if (ui->filters->text().isEmpty()) {
        ui->filters->setText("*.*");
    }
    if (ui->start_path->text().isEmpty()) {
        ui->start_path->setText(QDir::currentPath());
    }
    m_dirs.clear();
    _th1->start();
}

void MainWindow::on_pushButton_stop_clicked() {
    qDebug() << __FUNCTION__ << __LINE__;
    _th1->stop();
}

void MainWindow::on_buttonBrowse_clicked() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QString(),
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->start_path->setText(dir);
    _th1->setStart_path(dir);
}

void MainWindow::on_filters_textChanged(const QString &arg1) {
    qDebug() << __FUNCTION__ << arg1;
    _th1->setFilters(arg1);
}

void MainWindow::on_start_path_textChanged(const QString &arg1) {
    qDebug() << __FUNCTION__ << arg1;
    _th1->setStart_path(arg1);
}

void MainWindow::on_pushButton_reset_clicked() {
    m_dirs.clear();
}

void MainWindow::on_listView_clicked(const QModelIndex &index) {
    qDebug() << __FUNCTION__ << __LINE__;
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index) {
    qDebug() << __FUNCTION__ << __LINE__;
}
void MainWindow::onOpenFolder() {
    qDebug() << __FUNCTION__ << __LINE__ << m_selected_entry;

    QFileInfo fi(m_selected_entry);
    qDebug() << fi.absolutePath() << " fn=" << fi.fileName();
    QDesktopServices::openUrl(QUrl::fromLocalFile(fi.absolutePath()));
}

void MainWindow::onLaunchFile() {
    qDebug() << __FUNCTION__ << __LINE__ << m_selected_entry;
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_selected_entry));
}

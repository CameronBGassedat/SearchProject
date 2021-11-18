#ifndef MYYTHREAD_H
#define MYYTHREAD_H

#include <QThread>
#include <QDebug>

#include "database.h"

class MyYThread : public QThread {
    Q_OBJECT
    QStringList m_entries;
    QString     m_start_path = "";
    QStringList m_filters;
    bool        m_exitAsked = false;

    Database *_db;
    void finalize();
    bool fileMatch(QString entry);
    void prepareToSendDB(QString &entry, QStringList &m_filters);

public:
    MyYThread();
    void run() override;

    void setStart_path(const QString &start_path);

    void setFilters(const QString &filters);

  signals:
    void valueChanged(int val);
    void dirsAdded(const QStringList &);
    void searchCancel();
    void searchDone();
    void stats(int dirs_size, qint64 full_elaped, int rate);
    void exploringDir(QString);

  public slots:
    void stop();
};

#endif // MYYTHREAD_H

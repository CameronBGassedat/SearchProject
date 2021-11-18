#include "myythread.h"
#include <QDebug>
#include <QDirIterator>
#include <QElapsedTimer>


MyYThread::MyYThread() {
}

void MyYThread::setStart_path(const QString &start_path) {
    m_start_path = start_path;
}

void MyYThread::setFilters(const QString &filters) {
    m_filters.clear();
    for (auto &f : filters.split(QRegExp(",|;"))) {
        if (f.isEmpty())
            continue;
        m_filters << f;
    }
    qDebug() << __FUNCTION__ << __LINE__ << m_filters;
}

void MyYThread::finalize() {
    m_exitAsked = false;
    emit valueChanged(m_entries.size());
    emit dirsAdded(m_entries);
    m_entries.clear();
}

bool MyYThread::fileMatch(QString entry) {
    QRegExp rx;
    rx.setPatternSyntax(QRegExp::Wildcard);

    for (auto &f : m_filters) {
        rx.setPattern(f);
        if (rx.exactMatch(entry))
            return true;
    }
    return false;
}

void MyYThread::prepareToSendDB(QString &entry, QStringList &m_filters)
{
    QString filters = nullptr;
    QString name = nullptr;
    QString directory = nullptr;

    for (int i = 0; i < m_filters.size(); i++) {
        filters.append(m_filters[i]+ ",");
    }
    filters[filters.size()] = '\0';
    //cut entry to get the path to directory and the file name
    _db->addRow(entry, filters, "dirTest");
}

void MyYThread::run() {
    _db = new Database;
    emit dirsAdded(m_entries);
    if (m_start_path.isEmpty() || m_filters.isEmpty()) {
        emit searchDone();
        finalize();
        return;
    }
    qDebug() << __FUNCTION__ << m_start_path << m_filters;
    QElapsedTimer timer, timer_full;

    timer.start();
    timer_full.start();
    int    i           = 0;
    int    oDirs_size  = 0;
    int    dirs_size   = 0;
    qint64 full_elaped = 0;
    int    rate        = 0;

    QDirIterator it(m_start_path, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        i++;

        QString entry = it.next();
        if (it.fileInfo().isDir()) {
            emit exploringDir(entry);
            continue;
        }
        if (!fileMatch(entry))
            continue;

        m_entries << entry;
        prepareToSendDB(entry, m_filters);


        if (m_exitAsked) {
            qDebug() << __FUNCTION__ << __LINE__ << "Exit asked!!";

            emit searchCancel();
            finalize();
            break;
        }
        dirs_size = i;
        if (timer.elapsed() > 1000) {
            timer.restart();


            int dt      = dirs_size - oDirs_size;
            full_elaped = timer_full.elapsed();
            rate        = dirs_size / (full_elaped / 1000);
            oDirs_size  = dirs_size;
            emit valueChanged(dirs_size);
            emit dirsAdded(m_entries);
            emit stats(dirs_size, full_elaped, rate);
            qDebug() << __FUNCTION__ << "UPD" << i << full_elaped << dt << rate << m_entries.last();
            m_entries.clear();
        }
    }


    finalize();
    emit stats(dirs_size, full_elaped, rate);
    emit searchDone();
    qDebug() << __FUNCTION__ << __LINE__ << "Job Done!!" << dirs_size;
}

void MyYThread::stop() {
    m_exitAsked = true;
}

#include "searchfolder.h"

#include <QDebug>
#include <QDirIterator>

SearchFolder::SearchFolder() : _currentProgress(0), _maxProgress(0) {
}

int SearchFolder::maxProgress() const {
    return _maxProgress;
}

int SearchFolder::currentProgress() const {
    return _currentProgress;
}

QStringList SearchFolder::results() const {
    return m_results;
}

void SearchFolder::setFilters(const QString &filters) {
    m_filters = filters;
}

void SearchFolder::setStartDirectory(const QString &startDirectory) {
    m_startDirectory = startDirectory;
}

bool SearchFolder::isAvaiable() const {
    return _isAvaiable;
}

void SearchFolder::start() {
    qDebug() << __FUNCTION__ << __LINE__ << "Name of top directory: " << m_startDirectory << m_filters;

    QDirIterator it(m_startDirectory, m_filters.split(","), QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        // qDebug() << it.next();
        m_results << it.next();
        _currentProgress++;
    }
}

void SearchFolder::stop() {
}

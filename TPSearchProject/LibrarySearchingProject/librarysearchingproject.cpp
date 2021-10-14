#include "librarysearchingproject.h"

#include <QDebug>
#include <QDirIterator>

LibrarySearchingProject::LibrarySearchingProject() : _currentProgress(0), _maxProgress(0)
{
}

int LibrarySearchingProject::maxProgress() const {
    return _maxProgress;
}

int LibrarySearchingProject::currentProgress() const {
    return _currentProgress;
}

QStringList LibrarySearchingProject::results() const {
    return m_results;
}

void LibrarySearchingProject::setFilters(const QString &filters) {
    m_filters = filters;
}

void LibrarySearchingProject::setStartDirectory(const QString &startDirectory) {
    m_startDirectory = startDirectory;
}

bool LibrarySearchingProject::isAvaiable() const {
    return _isAvaiable;
}

void LibrarySearchingProject::start() {
    qDebug() << __FUNCTION__ << __LINE__ << "Name of top directory: " << m_startDirectory << m_filters;

    QDirIterator it(m_startDirectory, m_filters.split(","), QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        // qDebug() << it.next();
        m_results << it.next();
        _currentProgress++;
    }
}

void LibrarySearchingProject::stop() {
}

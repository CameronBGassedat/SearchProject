#ifndef LIBRARYSEARCHINGPROJECT_H
#define LIBRARYSEARCHINGPROJECT_H

#include "LibrarySearchingProject_global.h"
#include <QString>
#include <QStringList>

class LIBRARYSEARCHINGPROJECT_EXPORT LibrarySearchingProject
{
    QString     m_startDirectory;
    QString     m_filters;
    QStringList m_results;
    int         _currentProgress;
    int         _maxProgress;
    bool        _isAvaiable;

public:
    LibrarySearchingProject();
    void        start();
    void        stop();
    int         maxProgress() const;
    int         currentProgress() const;
    QStringList results();
    void        cleanresults();
    void        setFilters(const QString &filters);
    void        setStartDirectory(const QString &startDirectory);
    bool        isAvaiable() const;

};

#endif // LIBRARYSEARCHINGPROJECT_H

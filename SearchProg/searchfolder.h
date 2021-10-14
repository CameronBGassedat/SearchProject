#ifndef SEARCHFOLDER_H
#define SEARCHFOLDER_H

#include <QString>
#include <QStringList>


//#include "mainwindow.h"

class SearchFolder {
    QString     m_startDirectory;
    QString     m_filters;
    QStringList m_results;
    int         _currentProgress;
    int         _maxProgress;
    bool        _isAvaiable;

  public:
    SearchFolder();
    void        start();
    void        stop();
    int         maxProgress() const;
    int         currentProgress() const;
    QStringList results() const;
    void        setFilters(const QString &filters);
    void        setStartDirectory(const QString &startDirectory);
    bool        isAvaiable() const;
};

#endif // SEARCHFOLDER_H

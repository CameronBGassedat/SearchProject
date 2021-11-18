#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QStringList>

class Database
{
    QSqlDatabase _Database;
public:
    Database();
    void addRow(const QString& fileName, const QString& extension, const QString& folder);
    QStringList getFromName(QString& filename);
    QStringList getFromExt(QString& fileextension);
    QStringList transformQueryToStringList(QSqlQuery query);
};

#endif // DATABASE_H

#include "database.h"

Database::Database()
{
    _Database = QSqlDatabase::addDatabase("QSQLITE");
    _Database.setDatabaseName("C:\\SQLiteStudio\\sqlite\\databases\\TPSearchProg.db");
    if (!_Database.open())
     {
        qDebug() << "Error: connection with database failed";
     }
     else
     {
        qDebug() << "Database: connection ok";
     }
}

void Database::addRow(const QString& name, const QString& extension, const QString& dir)
{
   QSqlQuery query;


   query.prepare("INSERT INTO files(file_name, file_extension, directory) VALUES(?, ?, ?)");
   query.bindValue(0, name);
   query.bindValue(1, extension);
   query.bindValue(2, dir);

   if(query.exec())
   {
       qDebug() << "success";
   }
   else
   {
        qDebug() << "Error:" << query.lastError();
   }
}

QStringList Database::getFromName(QString &filename)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM files WHERE file_name = "+filename);

    if(query.exec())
    {
        qDebug() << "success";
    }
    else
    {
         qDebug() << "Error:" << query.lastError();
    }
    return (transformQueryToStringList(query));
}

QStringList Database::getFromExt(QString &fileextension)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM files WHERE file_extension = "+fileextension);

    if(query.exec())
    {
        qDebug() << "success";
    }
    else
    {
         qDebug() << "Error:" << query.lastError();
    }
    return (transformQueryToStringList(query));
}

QStringList Database::transformQueryToStringList(QSqlQuery query)
{
    QStringList list;

    for (int i = 0; i < query.size(); i++) {
        list.append(query.value(0).toString());
    }
}

/********************************************************************************
** log.cpp
** Definitions of the functions presented in log.h
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished
**
**
********************************************************************************/

#include "log.h"

QString getLog()
{
    QFile f("log.txt");
    if(!f.open(QIODevice::ReadOnly))
    {
        f.close();
        qDebug() << "Error reading file";
        return NULL;
    }

    QTextStream ts(&f);
    QString log = ts.readAll();
    f.close();
    return log;
}

void addLogEntry(QString texte)
{
    QFile f("log.txt");
    try{
        f.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(&f);
        ts << texte;
        f.close();
    }catch(std::exception e)
    {
        qDebug() << "pb";
    }
    f.close();
}

void addLogEntry(const char * texte)
{
    QFile f("log.txt");
    try{
        f.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(&f);
        ts << texte;
        f.close();
    }catch(std::exception e)
    {
        qDebug() << "pb";
    }
    f.close();
}

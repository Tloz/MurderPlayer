#ifndef REPORT_H
#define REPORT_H

/********************************************************************************
** report.h
** File defining the report class for MurderPlayer engine
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished
**
**  HOW IT WORKS:
**      m_investigation is an identifier (like the uid, for future updates)
**      The designation is basicly the investigations and the quality,
**      separated bay a "-". The info is the whole clue.
**
**
**  MEMBERS:
**      +int m_uid;
**      -QString m_investigation;
**      -int m_quality;
**      -QString m_designation;
**      -QString m_info;
**
**
**  METHODS:
**      CONSTRUCTOR:
**          Report(QString, int, QString);
**          Report(Report const &report);
**
**      GETTERS:
**          +QString getInvestigation() const;
**          +int getQuality() const;
**          +QString getDesignation() const;
**          +QString getInfo() const;
**
**
**
********************************************************************************/

#include <QtCore/QString>

struct Report
{
private:
    QString m_investigation;
    int m_quality;
    QString m_designation;
    QString m_info;

public:
    int m_uid;

    Report(QString, int, QString);
    Report(Report const &report);

    QString getInvestigation() const;
    int getQuality() const;
    QString getDesignation() const;
    QString getInfo() const;

};

#endif // REPORT_H

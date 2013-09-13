#ifndef INVESTIGATION_H
#define INVESTIGATION_H

/********************************************************************************
** investigation.h
** File defining the investigation class for MurderPlayer engine
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished
**
**  HOW IT WORKS:
**      The investigation is identified by a number, the id and it's title
**      Only one is needed to identify it, but as it's way much easier to
**      compare int than strings...
**      The reports should be stored in a std::array as we know before
**      compiling that theyre only 3 for each investigation, but as it's defined
**      only for ISO C++11, wich is not set by default on every machines, so
**      I decided to use a std::vector instead.
**
**
**
**  MEMBERS:
**      -int m_number;
**      -QString m_id;
**      -QString m_title;
**      -std::vector<Report> m_reports;
**
**
**  METHODS:
**      CONSTRUCTOR:
**          +Investigation(QString, QString, std::vector<Report>, int number);
**
**
**      GETTERS:
**          +int getNumber() const;
**          +QString getId() const;
**          +QString getTitle() const;
**          +std::vector<Report> getReports() const;
**          +void setReports(std::vector<Report>);
**
**
********************************************************************************/

#include <vector>

#include <QtCore/QString>

#include "report.h"


class Investigation
{
    int m_number;
    QString m_id;
    QString m_title;
    std::vector<Report> m_reports;

public:
    Investigation(QString, QString, std::vector<Report>, int number);

    int getNumber() const;
    QString getId() const;
    QString getTitle() const;
    std::vector<Report> getReports() const;
    void setReports(std::vector<Report>);
};

#endif // INVESTIGATION_H

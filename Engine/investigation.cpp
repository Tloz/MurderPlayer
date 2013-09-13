/********************************************************************************
** investigations.cpp
** Definitions of the functions presented in investigation.h
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished
**
**
********************************************************************************/

#include "investigation.h"

Investigation::Investigation(QString id, QString title, std::vector<Report> reports, int number)
{
    m_id = id;
    m_title = title;
    m_reports = reports;
    m_number = number;
}

QString Investigation::getId() const
{
    return m_id;
}

QString Investigation::getTitle() const
{
    return m_title;
}

std::vector<Report> Investigation::getReports() const
{
    return m_reports;
}

void Investigation::setReports(std::vector<Report> clues)
{
    m_reports = clues;
}

int Investigation::getNumber() const
{
    return m_number;
}

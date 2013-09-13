/********************************************************************************
** report.cpp
** Definitions of the functions presented in report.h
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished
**
**
********************************************************************************/

#include "report.h"

Report::Report(QString investigation, int quality, QString info = NULL)
{
    m_investigation = investigation;
    m_quality = quality;
    m_info = info;
    m_designation = m_investigation + QString("-" + QString::number(m_quality));
}

/* Copy Constructor */
Report::Report(Report const &report)
{
    m_investigation = report.m_investigation;
    m_quality = report.m_quality;
    m_info = report.m_info;
    m_designation = m_investigation + QString("-" + QString::number(m_quality));
}


int Report::getQuality() const
{
    return m_quality;
}

QString Report::getInvestigation() const
{
    return m_investigation;
}

QString Report::getDesignation() const
{
    return m_designation;
}

QString Report::getInfo() const
{
    return m_info;
}

/********************************************************************************
** event.cpp
** Definitions of the functions presented in event.h
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished
**
**
********************************************************************************/

#include "event.h"

Event::Event(QString name, QString description1, QString description2, QTime time)
{
    m_name = name;
    m_shortDescription = description1;
    m_longDescription = description2;
    m_time = time;
}

QString Event::getName() const
{
    return m_name;
}
QTime Event::getTime() const
{
    return m_time;
}
QString Event::getShortDescription() const
{
    return m_shortDescription;
}

QString Event::getLongDescription() const
{
    return m_longDescription;
}

#ifndef EVENT_H
#define EVENT_H

/********************************************************************************
** event.h
** File defining the event class for MurderPlayer engine
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished
**
**  HOW IT WORKS:
**      An event is a thing that happens at a precise time. So it is defined by
**      it's name, the time it takes place, and the descriptions. Everything is
**      pretty self explanatory here.
**
**
**  MEMBERS:
**      -QString m_name;
**      -QTime m_time;
**      -QString m_shortDescription;
**      -QString m_longDescription;
**
**
**  METHODS:
**      CONSTRUCTOR:
**          Event(QString name, QString shortD, QString longD, QTime);
**
**
**      GETTERS:
**          +QString getName() const ;
**          +QTime getTime() const ;
**          +QString getShortDescription() const ;
**          +QString getLongDescription() const ;
**
**
********************************************************************************/

#include <QtCore/QTime>
#include <QtCore/QString>

class Event
{
    QString m_name;
    QTime m_time;
    QString m_shortDescription;
    QString m_longDescription;
public:
    Event(QString name, QString shortD, QString longD, QTime);
    QString getName() const ;
    QTime getTime() const ;
    QString getShortDescription() const ;
    QString getLongDescription() const ;
};

#endif // EVENT_H

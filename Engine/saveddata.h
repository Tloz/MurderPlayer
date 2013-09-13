#ifndef SAVEDDATA_H
#define SAVEDDATA_H

/********************************************************************************
** saveddata.h
** File defining the saveddata class for MurderPlayer engine
**
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished
**
**  HOW IT WORKS:
**      This will load everything you need to save and load the save game
**
**
**  MEMBERS:
**      -int m_fileTimestamp;
**      -std::vector<Character*> m_players;
**      -QString m_log;
**      -std::vector<Event> m_unsolvedEvents;
**      -QTime m_elapsedTime;
**
**
**  METHODS:
**      CONSTRUCTOR:
**          +SavedData(int, std::vector<Character*>, QString, std::vector<Event>, QTime);
**
**      GETTERS:
**          +int getFileTimestamp() const;
**          +std::vector<Character*> getPlayers() const;
**          +QString getLog() const;
**          +std::vector<Event> getUnsolvedEvents() const;
**          +QTime getElapsedTime() const;
**
**      SETTERS:
**          +void setFileTimestamp(const int);
**          +void setPlayers(const std::vector<Character*>);
**          +void setLog(const QString);
**          +void setUnsolvedEvents(const std::vector<Event>);
**          +void setElapsedTime(const QTime);
**
**
********************************************************************************/

#include <vector>

#include <QtCore/QString>
#include <QtCore/QTime>

#include "event.h"
#include "character.h"

class SavedData
{
    int m_fileTimestamp;
    std::vector<Character*> m_players;
    QString m_log;
    std::vector<Event> m_unsolvedEvents;
    QTime m_elapsedTime;

public:
    SavedData(int, std::vector<Character*>, QString, std::vector<Event>, QTime);

    int getFileTimestamp() const;
    std::vector<Character*> getPlayers() const;
    QString getLog() const;
    std::vector<Event> getUnsolvedEvents() const;
    QTime getElapsedTime() const;

    void setFileTimestamp(const int);
    void setPlayers(const std::vector<Character*>);
    void setLog(const QString);
    void setUnsolvedEvents(const std::vector<Event>);
    void setElapsedTime(const QTime);
};

#endif // SAVEDDATA_H

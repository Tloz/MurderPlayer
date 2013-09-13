/********************************************************************************
** saveddata.cpp
** Definitions of the functions presented in saveddata.h
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished
**
**
********************************************************************************/

#include "saveddata.h"

SavedData::SavedData(int fileTimestamp, std::vector<Character*> players,
                     QString log, std::vector<Event> unsolvedEvents, QTime elapsedTime)
{
    m_fileTimestamp = fileTimestamp;
    m_players = players;
    m_log = log;
    m_unsolvedEvents = unsolvedEvents;
    m_elapsedTime = elapsedTime;
}

int SavedData::getFileTimestamp() const
{
    return m_fileTimestamp;
}

std::vector<Character*> SavedData::getPlayers() const
{
    return m_players;
}

QString SavedData::getLog() const
{
    return m_log;
}

std::vector<Event> SavedData::getUnsolvedEvents() const
{
    return m_unsolvedEvents;
}

QTime SavedData::getElapsedTime() const
{
    return m_elapsedTime;
}

void SavedData::setFileTimestamp(const int fileTimestamp)
{
    m_fileTimestamp = fileTimestamp;
}

void SavedData::setPlayers(const std::vector<Character*> players)
{
    m_players = players;
}

void SavedData::setLog(const QString log)
{
    m_log = log;
}

void SavedData::setUnsolvedEvents(const std::vector<Event> unsolvedEvents)
{
    m_unsolvedEvents = unsolvedEvents;
}

void SavedData::setElapsedTime(const QTime elapsedTime)
{
    m_elapsedTime = elapsedTime;
}

#ifndef SCENARIO_H
#define SCENARIO_H

/********************************************************************************
** scenario.h
** File defining the scenario class for MurderPlayer engine
**
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished
**
**  HOW IT WORKS:
**      Here are EVERY information about the story. Each are self explanatory
**      except a few of them so I'll explain them here:
**      -The m_versionID (or vID) is an indicator that tells wether the clues and
**      the diary are included in the file.
**      -The m_fileTimestamp is used to link the save to the story file, as they
**      all have a different timestamp.
**      -Finaly, the m_listModel is used to handle the events that happens
**      during the game (by the way, you just lost the game)
**
**
**  MEMBERS:
**      -int m_versionID;
**      -int m_fileTimestamp;
**      -Data *m_data;
**      -std::vector<Event> m_eventList;
**      -std::vector<Character*> m_playerTab;
**      -std::vector<Investigation> m_investigationTab;
**      -std::vector<Event> m_unresolvedEvents;
**      -QStringListModel* m_listmodel;
**
**
**  METHODS:
**      CONSTRUCTORS:
**          +Scenario(Data *data,
**           std::vector<Event> eventList,
**           std::vector<Character*> playerTab,
**           std::vector<Investigation> investigationTab,
**           int versionId, int fileTimestamp);
**
**      DESTRUCTOR:
**          +~Scenario();
**
**      GETTERS:
**          +Data* getData() const;
**          +std::vector<Event> getEventList() const;
**          +std::vector<Character*> getPlayerTab() const;
**          +std::vector<Investigation> getInvestigationTab() const;
**          +std::vector<Event> getUnresolvedEvents() const;
**          +int getVersionID() const;
**          +int getFileTimestamp() const;
**          +QStringListModel* getModel() const;
**
**      SETTERS:
**          +void setUnresolvedEvents(std::vector<Event>);
**
**
********************************************************************************/

#include <vector>

#include <QtCore/QString>
#include <QtCore/QTime>
#include <QtGui/QStringListModel>

#include "data.h"
#include "event.h"
#include "character.h"
#include "investigation.h"

class Scenario
{
    /* File relative */
    int m_versionID;
    int m_fileTimestamp;

    /* Game relative */
    Data *m_data;
    std::vector<Event> m_eventList;
    std::vector<Character*> m_playerTab;
    std::vector<Investigation> m_investigationTab;
    std::vector<Event> m_unresolvedEvents;
    QStringListModel* m_listmodel;
public:
    /* Constructors */
    Scenario(Data *data,
             std::vector<Event> eventList,
             std::vector<Character*> playerTab,
             std::vector<Investigation> investigationTab,
             int versionId, int fileTimestamp);

    ~Scenario();


    /* Getters */
    Data* getData() const;
    std::vector<Event> getEventList() const;
    std::vector<Character*> getPlayerTab() const;
    std::vector<Investigation> getInvestigationTab() const;
    std::vector<Event> getUnresolvedEvents() const;

    int getVersionID() const;
    int getFileTimestamp() const;
    QStringListModel* getModel() const;

    /* Setters */
    void setUnresolvedEvents(std::vector<Event>);
};

#endif // SCENARIO_H

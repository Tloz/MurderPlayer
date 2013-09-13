/********************************************************************************
** scenario.cpp
** Definitions of the functions presented in scenario.h
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished
**
**
********************************************************************************/

#include "scenario.h"

/* Constructor */
Scenario::Scenario(Data *data,
                   std::vector<Event> eventList,
                   std::vector<Character*> playerTab,
                   std::vector<Investigation> investigationTab,
                   int versionId, int fileTimestamp)
{
    m_data = data;
    m_versionID = versionId;
    m_playerTab = playerTab;
    m_investigationTab = investigationTab;
    m_eventList = eventList;
    m_fileTimestamp = fileTimestamp;
    m_listmodel = new QStringListModel();

    for(unsigned int i = 0; i < m_playerTab.size(); i++)
    {
        QVector<QPair<int, int> > reports = QVector<QPair<int, int> >();
        for (unsigned int j = 0; j < m_investigationTab.size(); j++)
        {
            QPair<int, int> pair;
            pair.first = 1;//m_investigationTab[i].getId();
            pair.second = 0;
            reports.push_back(pair);
        }
        m_playerTab[i]->setReports(reports);
    }
}

Scenario::~Scenario()
{
    delete m_listmodel;
}

std::vector<Character*> Scenario::getPlayerTab() const
{
    return m_playerTab;
}

std::vector<Investigation> Scenario::getInvestigationTab() const
{
    return m_investigationTab;
}

int Scenario::getVersionID() const
{
    return m_versionID;
}

int Scenario::getFileTimestamp() const
{
    return m_fileTimestamp;
}

std::vector<Event> Scenario::getEventList() const
{
    return m_eventList;
}

Data* Scenario::getData() const
{
    return m_data;
}

std::vector<Event> Scenario::getUnresolvedEvents() const
{
    return m_unresolvedEvents;
}

void Scenario::setUnresolvedEvents(std::vector<Event> elem)
{
    m_unresolvedEvents = elem;
}

QStringListModel* Scenario::getModel() const
{
    return m_listmodel;
}

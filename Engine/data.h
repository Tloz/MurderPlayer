#ifndef DATA_H
#define DATA_H

/********************************************************************************
** data.h
** File defining a scenario's internal data class for MurderPlayer engine
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished
**
**  HOW IT WORKS:
**      This class wasn't really necessary, as all the informations here were
**      previously in the class Scenario. It's only for convenience purpose
**      that I've made this one, in order not to have plenty of data in
**      class Scenario and clean the whole thing up.
**
**
**  MEMBERS:
**      -int m_nbMJ;
**      -int m_nbEvent;
**      -QString m_name;
**      -int m_nbPlayer;
**      -QTime m_length;
**      -QString m_author;
**      -QString m_summary;
**      -int m_creationYear;
**      -int m_nbInvestiagation;
**
**
**  METHODS:
**      CONSTRUCTOR:
**          +Data(int nbJ, int nbMJ, int nbI, int nbE, int date, QString name,
**                QString author, QTime length, QString summary);
**
**
**      GETTERS:
**          +int getNbMj() const;
**          +int getNbEvent() const;
**          +QString getName() const;
**          +int getNbPlayer() const;
**          +QTime getLength() const;
**          +QString getAuthor() const;
**          +int getCreationYear() const;
**          +int getNbInvestigation() const;
**          +QString getSummary() const;
**
**
**
********************************************************************************/

#include <QtCore/QTime>
#include <QtCore/QString>

class Data
{
    int m_nbMJ;
    int m_nbEvent;
    QString m_name;
    int m_nbPlayer;
    QTime m_length;
    QString m_author;
    QString m_summary;
    int m_creationYear;
    int m_nbInvestiagation;

public:
    Data(int nbJ, int nbMJ, int nbI, int nbE, int date, QString name,
         QString author, QTime length, QString summary);

    int getNbMj() const;
    int getNbEvent() const;
    QString getName() const;
    int getNbPlayer() const;
    QTime getLength() const;
    QString getAuthor() const;
    int getCreationYear() const;
    int getNbInvestigation() const;
    QString getSummary() const;
};

#endif // DATA_H

/********************************************************************************
** data.cpp
** Definitions of the functions presented in data.h
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished
**
**
********************************************************************************/

#include "data.h"

Data::Data(int nbJ, int nbMJ, int nbI, int nbE, int date, QString name,
           QString author, QTime length, QString summary)
{
    m_nbPlayer = nbJ;
    m_nbMJ = nbMJ;
    m_nbInvestiagation = nbI;
    m_nbEvent = nbE;
    m_creationYear = date;
    m_name = name;
    m_author = author;
    m_length = length;
    m_summary = summary;
}

int Data::getNbMj() const
{
    return m_nbMJ;
}

int Data::getNbEvent() const
{
    return m_nbEvent;
}

QString Data::getName() const
{
    return m_name;
}

int Data::getNbPlayer() const
{
    return m_nbPlayer;
}

QTime Data::getLength() const
{
    return m_length;
}

QString Data::getAuthor() const
{
    return m_author;
}

QString Data::getSummary() const
{
    return m_summary;
}

int Data::getCreationYear() const
{
    return m_creationYear;
}

int Data::getNbInvestigation() const
{
    return m_nbInvestiagation;
}

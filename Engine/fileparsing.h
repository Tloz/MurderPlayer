#ifndef FILEPARSING_H
#define FILEPARSING_H

/********************************************************************************
** fileparsing.h
** File defining the functions to load scenario, save and load game
** for thMurderPlayer engine
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Working, improvements to come (XML)
**
**  HOW IT WORKS:
**      Basicly line by line parsing on a text file
**
**
**  FUNCTIONS:
**      Scenario *readStoryFromPlainText(const QString s);
**          You give a textfile's name to this function, and it will load the
**          story stored inside
**      SavedData *readSaveFromPlainText(QString, Scenario*);
**          You give a textfile's name to this function and it will check that
**          the save correspond to the loaded scenario, and load it if yes
**      void saveToPlainText(Scenario*);
**          This function will save current's scenario state in text format
**      Scenario *readStoryFromXml(QString);
**          You give a XML file's name to this function, and it will load the
**          story stored inside
**      SavedData *readSaveFromXml(QString, Scenario*);
**          You give a XML file's name to this function and it will check that
**          the save correspond to the loaded scenario, and load it if yes
**      void saveToXml(Scenario*);
**          This function will save current's scenario state in XML format
**
**
********************************************************************************/

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <QtGui/QMessageBox>


#include "scenario.h"

class SavedData;

Scenario *readStoryFromPlainText(const QString s);
SavedData *readSaveFromPlainText(const QString s, Scenario*);
void saveToPlainText(const Scenario *s);

Scenario *readStoryFromXml(const QString s);
SavedData *readSaveFromXml(const QString s, Scenario*);
void saveToXml(const Scenario *s);

#endif // FILEPARSING_H

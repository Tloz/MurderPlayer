#ifndef LOG_H
#define LOG_H

/********************************************************************************
** log.h
** File defining the functions that handles the log file for MurderPlayer engine
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished, maybe some improvements in the future, but very unlikely
**
**  HOW IT WORKS:
**      Basicly line by line parsing on a text file
**
**
**  FUNCTIONS:
**      QString getLog();
**          Automaticly opens the log and load the whole file into a QString
**      void addLogEntry(QString);
**          Insert a QString in the log
**      void addLogEntry(const char*);
**          Insert a string in the log
**
********************************************************************************/

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>
#include <exception>


QString getLog();

void addLogEntry(QString);

void addLogEntry(const char*);

#endif // LOG_H

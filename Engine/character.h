#ifndef CHARACTER_H
#define CHARACTER_H

/********************************************************************************
** character.h
** File defining the character class for MurderPlayer engine
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished for the moment, potentially upgradable
**          some changes are already there, so you can find things that seems
**          useless, but they aren't
**
**  HOW IT WORKS:
**      Basicly, a characters has a name, some power points. This is pretty much
**      what defines them. For the convenience, I added the last report he has,
**      as well as the time he got it(for other people to copy it), the person
**      who's intercepting him.
**      The m_reports member is for a future update
**
**  MEMBERS:
**      -QString m_name
**      -int m_powerPoints;
**      -Report* m_lastReport;
**      -QTime m_lastReportTime;
**      -Character* m_interceptor;
**      -QVector<QPair<int, int> > m_reports;
**
**
**  METHODS:
**      CONSTRUCTORS:
**          +Character(const QString, int);
**          +Character(const Character &other);
**
**      DESTRUCTOR:
**          +~Character();
**
**      GETTERS:
**          +QString getName() const;
**          +int getPowerPoints() const;
**          +Report *getLastReport() const;
**          +Time getLastReportTime() const;
**          +Character *getInterceptor() const;
**          +bool getInterceptionState() const;
**          +QVector<QPair<int, int> > getReports() const;
**
**      SETTERS:
**          +void setPowerPoints(int ammount);
**          +void setLastReport(Report *report);
**          +void setLastReportTime(QTime time);
**          +void setInterceptor(Character *interceptor);
**          +void setReports(QVector<QPair<int, int> > reports);
**
**      MAIN GAME FUNCTIONS:
**          +Report *investigate(QString investigation, int extra_PP);
**          +Report *copy(Character *target);
**          +bool intercept(Character *target);
**
**        OTHERS:
**          +void addPowerPoints(int);
**          +void delPowerPoints(int);
**
**  EXCEPTIONS:
**      InterceptedException
**      TooLateException
**      NoLastReportExeption
**      HasInterceptorException
**      NotEnoughPowerException
**
**
********************************************************************************/

#include <exception>

#include <QtCore/QPair>
#include <QtCore/QTime>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QDebug>
#include "murder.h"
#include "report.h"
#include "investigation.h"

class Report;

class Character
{
    QString m_name;
    int m_powerPoints;
    Report* m_lastReport;
    QTime m_lastReportTime;
    Character* m_interceptor;
    QVector<QPair<int, int> > m_reports;

public:
    /* Constructor(s) */
    Character(const QString, const int);
    Character(const Character &other);

    /* Destructor */
    ~Character();
    /* Getters */

    /*
     * One for each member
     * one to get the implicit state of inteception via the interceptor
     * and One to rule them all
     */

    QString getName() const;
    int getPowerPoints() const;
    Report *getLastReport() const;
    QTime getLastReportTime() const;
    Character *getInterceptor() const;
    bool getInterceptionState() const;
    QVector<QPair<int, int> > getReports() const;

    /* Setters */
    // Don't need one for the name
    void setPowerPoints(int ammount);
    void setLastReport(Report *report);
    void setLastReportTime(QTime time);
    void setInterceptor(Character *interceptor);
    void setReports(QVector<QPair<int, int> > reports);

    void addPowerPoints(const int);
    void delPowerPoints(const int);

    /* Game Functions */
    Report* investigate(const QString investigation, const int extra_PP);
    Report* copy(Character *target);
    bool intercept(Character *target);

    /*
     * While playing ou can meet severals exceptions:
     * - Intercepted: when you investigate but someon will intercept you report
     * - TooLate: when you arrive too late to copy a report
     * - NoLastReport: when you try to copy a report from someone who don't have
     * - HasInterceptor: when you want to intercept someone's report while
     *   this person's report is already beiing intercepted
     * - NotEnoughPower: when you don't have enough power points, looser
     */

    class InterceptedException : public std::exception
    {
        Character *interceptor;
        Report *report;
    public:
        InterceptedException(Character *interceptor, Report *report) throw();
        Character* getInterceptor();
        Report* getReport();

    };

    class TooLateException : public std::exception
    {
        Character *target;
    public:
        TooLateException(Character *target) throw();
        Character* getTarget();

    };

    class NoLastReportExeption : public std::exception
    {
        Character *target;
    public:
        NoLastReportExeption(Character *target) throw();
        Character* getTarget();

    };

    class HasInterceptorException : public std::exception
    {
        Character *target;
    public:
        HasInterceptorException(Character *target) throw();
        Character* getTarget();
    };

    class NotEnoughPowerException : public std::exception
    {
        int actualPowerPoints;
        int neededPowerPoints;
    public:
        NotEnoughPowerException(int actual, const int needed) throw();
        int getActual();
        int getNeeded();
    };
};
#endif // CHARACTER_H

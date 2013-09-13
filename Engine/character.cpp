/********************************************************************************
** character.cpp
** Definitions of the functions presented in character.h
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Working, potentially upgradable, some changes are already there,
**          so you can find things that seems useless,
**          but they aren't, trust me...
**
**
********************************************************************************/

#include "character.h"

/* Constructor(s) */
Character::Character(const QString name, const int startPowerPoints)
{
    m_name = name;
    m_powerPoints = startPowerPoints;
    m_lastReportTime = QTime();
    m_lastReport = NULL;
    m_interceptor = NULL;
}

Character::~Character()
{

}

/* Getters */
QString Character::getName() const
{
    return m_name;
}

int Character::getPowerPoints() const
{
    return m_powerPoints;
}

Report *Character::getLastReport() const
{
    return m_lastReport;
}

QTime Character::getLastReportTime() const
{
    return m_lastReportTime;
}

bool Character::getInterceptionState() const
{
    if(m_interceptor == NULL)
        return false;
    return true;
}

Character* Character::getInterceptor() const
{
    return m_interceptor;
}

QVector<QPair<int, int> > Character::getReports() const
{
    return m_reports;
}

/* Setters */
void Character::setPowerPoints(int value)
{
    if(value < 0)
        throw NotEnoughPowerException(0, 0);
    else
        m_powerPoints = value;
}

void Character::setLastReport(Report *report)
{
    m_lastReport = report;
}

void Character::setLastReportTime(QTime value)
{
    m_lastReportTime = value;
}

void Character::setInterceptor(Character *player)
{
    m_interceptor = player;
}

void Character::setReports(QVector<QPair<int, int> > reports)
{
    m_reports = reports;
}

void Character::addPowerPoints(int value)
{
    m_powerPoints += value;
}

void Character::delPowerPoints(int value)
{
    int final = m_powerPoints -= value;
    if (final < 0)
        throw NotEnoughPowerException(m_powerPoints, - final);
    setPowerPoints(final);
}

/* Game Functions */
Report* Character::investigate(const QString investigation, const int extra_PP)
{
    /*
     * First checks if the player has enough PP to investigate
     * Then checks if he has enough PP to add to his result
     * Next computes the quality of the report
     * Checks if player is beeing intercepted
     * If everything is fine, finaly give the repot to the player
     */

    if(m_powerPoints<1)
    {
        qDebug() << m_name + " doesn't have enough power points";
        throw NotEnoughPowerException(this->m_powerPoints, 1);
    }

    if(extra_PP>0)
    {
        if(m_powerPoints < extra_PP+1)
        {
            qDebug() << m_name + " doesn't have enough power points";
            throw NotEnoughPowerException(this->m_powerPoints, extra_PP + 1);
        }
    }

    this->delPowerPoints(1+extra_PP);
    Report *r1 = new Report(investigation, solve_investigation(extra_PP), NULL);

    if(m_interceptor != NULL)
    {
        qDebug() << "The report has been intercepted (by "
                 << m_interceptor->getName() + ")";
        this->getInterceptor()->setLastReport(r1);
        this->getInterceptor()->setLastReportTime(QTime::currentTime ());
        Character *inter = m_interceptor;
        //if(inter->getReports().at(0).first == investigation)
        this->setInterceptor(NULL);
        throw InterceptedException(inter, r1);
    }

    qDebug() << m_name << " gets the report " << r1->getDesignation();
    this->setLastReport(r1);
    this->setLastReportTime(QTime::currentTime ());
    return r1;
}

Report* Character::copy(Character *target)
{
    /*
     * First checks if the player has enough PP to copy a report
     * Then checks if the target has a report
     * Next checks if it's not too late to copy a the report (less than two minutes)
     * If everything is fine, finaly give the repot to the player
     */

    if(m_powerPoints<2)
    {
        qDebug() << m_name + " doesn't have enough power points";
        throw NotEnoughPowerException(this->m_powerPoints, 2);
    }

    if(target->getLastReport() == NULL)
    {
        qDebug() << m_name + " doesn't have any report yet";
        throw NoLastReportExeption(target);
    }

    if(QTime::currentTime().secsTo(target->getLastReportTime())<-120)
    {
        qDebug() << m_name + " get his last report more than two minutes ago";
        throw TooLateException(target);
    }

    qDebug() << this->getName() << " copied " << target->getName() <<"'s last report";
    this->setLastReport(target->getLastReport());
    this->setLastReportTime(QTime::currentTime ());
    this->delPowerPoints(2);
    return target->getLastReport();
}

bool Character::intercept(Character *target)
{
    /*
     * First checks if the player has enough PP to intercept a report
     * Then checks if the target is already beeing intercepted
     * Next roll a dice
     * If it's more than one, the report will be intercepted
     */

    if(m_powerPoints<2)
    {
        qDebug() << m_name + " doesn't have enough power points";
        throw NotEnoughPowerException(this->m_powerPoints, 2);
    }

    if(target->getInterceptor()!=NULL)
    {
        qDebug() << target->getName() << " est déjà sous le coup d'une interception";
        throw HasInterceptorException(target);
    }

    this->delPowerPoints(2);
    int i=roll_dice(6);
    qDebug() << "Le dé fait " << i;
    if(i == 1)
    {
        qDebug() << " ce qui n'est pas suffisant pour intercepter le rapport" << endl;
        return false;
    }

    target->setInterceptor(this);
    qDebug() << QString::fromUtf8(" ce qui permet à ") << getName()
             << " d'intercepter le prochain rapport de " << target->getName();
    return true;
}

/* Exceptions */
Character::TooLateException::TooLateException(Character *target) throw()
{
    this->target = target;
}

Character* Character::TooLateException::TooLateException::getTarget()
{
    return target;
}

Character::NoLastReportExeption::NoLastReportExeption(Character *target) throw()
{
    this->target = target;
}

Character* Character::NoLastReportExeption::getTarget()
{
    return target;
}

Character::InterceptedException::InterceptedException(Character *interceptor, Report *report) throw()
{
    this->interceptor = interceptor;
    this->report = report;
}

Character* Character::InterceptedException::getInterceptor()
{
    return interceptor;
}

Report* Character::InterceptedException::getReport()
{
    return report;
}

Character::HasInterceptorException::HasInterceptorException(Character *target) throw()
{
    this->target = target;
}

Character* Character::HasInterceptorException::getTarget()
{
    return target;
}

Character::NotEnoughPowerException::NotEnoughPowerException(const int actual, const int needed) throw()
{
    actualPowerPoints = actual;
    neededPowerPoints = needed;
}

int Character::NotEnoughPowerException::getActual()
{
    return actualPowerPoints;
}

int Character::NotEnoughPowerException::getNeeded()
{
    return neededPowerPoints;
}

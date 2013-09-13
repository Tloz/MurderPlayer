/********************************************************************************
** fileparsing.cpp
** Definitions of the functions presented in fileparsing.h
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Working, improvements to come (XML)
**
**
********************************************************************************/

#include "fileparsing.h"

Scenario *readStoryFromPlainText(const QString fileName)
{
    QFile f(fileName);
    if(!f.open(QIODevice::ReadOnly))
    {
        f.close();
        qDebug() << "Error reading file";
        return NULL;
    }

    QTextStream ts(&f);
    QString header = ts.readLine();
    qDebug() << header;
    int vID = ts.readLine().toInt();
    int ft = ts.readLine().toInt();
    QString name = ts.readLine();
    QString author = ts.readLine();
    int year = ts.readLine().toInt();
    QTime length = QTime::fromString(ts.readLine(), "hh:mm:ss");
    qDebug() << length;
    int nbP  = ts.readLine().toInt();
    int nbDM = ts.readLine().toInt();
    int nbI  = ts.readLine().toInt();
    int nbE  = ts.readLine().toInt();

    /* Player list */
    qDebug() << endl << "Building Player List...";
    std::vector<Character*> pTab;

    for(int i = 0; i < nbP ; i++)
    {
        QString name(ts.readLine());
        int PP(ts.readLine().toInt());
        pTab.push_back(new Character(name, PP));
        qDebug() << "Player" << i+1 << ":" << pTab[i]->getName() << "with"
                 << pTab[i]->getPowerPoints() << "power points" << "created!";
    }

    /* Investigation list */
    qDebug() << endl << "Building Investigation List...";
    std::vector<Investigation> iTab;

    for(int i = 0; i < nbI ; i++)
    {
        QString t(ts.readLine());
        QString s(ts.readLine());
        std::vector<Report> a;
        iTab.push_back(Investigation(t, s, a, i));
        qDebug() << "Investigation" << iTab[i].getId() << ":"
                 << iTab[i].getTitle() << "created";
    }

    /* Clue list */
    if(vID == 1 || vID == 3)
    {
        qDebug() << endl << "Building Clue List...";

        for(int i = 0; i < nbI; i++)
        {
            std::vector<Report> cTab;

            for(int j = 0; j < 3; j++)
            {
                QString c1(ts.readLine());
                cTab.push_back(Report(iTab[i].getId(), j + 1, c1));
                qDebug() << "Report" << cTab[j].getDesignation() << cTab[j].getInfo();
            }

            iTab[i].setReports(cTab);
        }
    }

    /* Event list */
    std::vector<Event> eTab;

    if(vID == 2 || vID == 3)
    {
        qDebug() << endl << "Building Event List...";

        for(int i = 0; i < nbE; i++)
        {
            QString e1(ts.readLine()); // Name
            QTime e4 = QTime::fromString(ts.readLine(), "hh:mm:ss"); // Hour
            QString e2(ts.readLine()); // ShortD
            QString e3(ts.readLine()); // LongD
            eTab.push_back(Event(e1, e2, e3, e4));
            qDebug() << "Event" << eTab[i].getName()
                     << "succesfully created at" << eTab[i].getTime().toString();
        }
    }

    /* Summary */
    QString summary(ts.readAll());
    qDebug() << summary;

    f.close();
    Data *data = new Data(nbP, nbDM, nbI, nbE, year, name, author, length, summary);
    Scenario *val = new Scenario(data, eTab, pTab, iTab, vID, ft);
    return val;
}

SavedData* readSaveFromPlainText(const QString fileName, Scenario *story)
{
    QMessageBox::information(NULL, "Status", "Function not implemented yet, sorry");
    return NULL;
    QFile f(fileName);

    if(!f.open(QIODevice::ReadOnly))
    {
        f.close();
        qDebug() << "Error reading file";
        return NULL;
    }

    QTextStream ts(&f);

    if(ts.readLine().toInt() != story->getFileTimestamp())
    {
        qDebug() << "La sauvegarde ne correspond pas";
        EXIT_FAILURE;
    }

    else
    {
        qDebug() << "La sauvegarde correspond";

        /* Getting Character Info */
        std::vector<Character*> players;

        for(int i = 0; i < story->getData()->getNbPlayer(); i++)
        {
            players[i] = new Character(ts.readLine(), ts.readLine().toInt());
            players[i]->setLastReportTime(QTime::fromString(ts.readLine(), "hh:mm:ss"));
        }
    }
}

void saveToPlainText(const Scenario *story)
{
    QMessageBox::information(NULL, "Status", "Function not implemented yet, sorry");
    return;
    QFile f(story->getData()->getName() + ".mps");

    if(!f.open(QIODevice::WriteOnly))
    {
        f.close();
        qDebug() << "Error opening file";
        return;
    }

    QTextStream ts(&f);
    ts << story->getFileTimestamp() << endl;

    /* writing Character data */

    for(int i = 0; i < story->getData()->getNbPlayer(); i++)
    {
        ts << story->getPlayerTab()[i]->getName() << endl;
        ts << story->getPlayerTab()[i]->getPowerPoints() << endl;
        ts << story->getPlayerTab()[i]->getLastReportTime().toString() << endl;
    }

    for(int i = 0; i < story->getData()->getNbPlayer(); i++)
    {
        ts << story->getPlayerTab()[i]->getLastReport()->getInvestigation() << endl;
        ts << story->getPlayerTab()[i]->getLastReport()->getQuality() << endl;
        ts << story->getPlayerTab()[i]->getInterceptor() << endl;
    }

    /* writing log */
    //ts << log;

    /* Writing events */
    for(unsigned int i = 0; i < story->getUnresolvedEvents().size(); i++)
    {
        ts << story->getUnresolvedEvents()[i].getName() << endl;
        ts << story->getUnresolvedEvents()[i].getTime().toString() << endl;
        ts << story->getUnresolvedEvents()[i].getShortDescription() << endl;
        ts << story->getUnresolvedEvents()[i].getLongDescription() << endl;
    }

    /* Writing elapsed time */
    //ts <<


    f.close();
}

Scenario *readStoryFromXml(const QString s)
{
    return NULL;
}

SavedData *readSaveFromXml(QString, Scenario*)
{
    return NULL;
}

void saveToXml(Scenario*)
{

}

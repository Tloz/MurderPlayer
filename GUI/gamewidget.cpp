#include "gamewidget.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(Scenario *scenario, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    story = scenario;
    for(int i = 0; i < story->getData()->getNbInvestigation(); i++)
        ui->cb_investigation->addItem(story->getInvestigationTab()[i].getId());
    for(int i = 0; i < story->getData()->getNbPlayer(); i++)
    {
        ui->cb_target->addItem(story->getPlayerTab()[i]->getName());
        ui->cb_investigator->addItem(story->getPlayerTab()[i]->getName());
    }

    blockswitch();
    connect(ui->pb_Invest, SIGNAL(clicked()), this, SLOT(investigate()));
    connect(ui->pb_Copy, SIGNAL(clicked()), this, SLOT(copy()));
    connect(ui->pb_Intercept, SIGNAL(clicked()), this, SLOT(intercept()));
    connect(ui->cb_investigator, SIGNAL(currentIndexChanged(int)), this, SLOT(blockswitch()));
    connect(ui->cb_target, SIGNAL(currentIndexChanged(int)), this, SLOT(blockswitch()));

}

void GameWidget::investigate()
{
    Character *player = story->getPlayerTab()[ui->cb_investigator->currentIndex()];
    QString invest = story->getInvestigationTab()[ui->cb_investigation->currentIndex()].getId();
    int extra = ui->sb_morePP->value();
    try
    {
        Report *result = player->investigate(invest, extra);
        QMessageBox::information(NULL, tr("Result"), player->getName()
                                 + tr(" gets the report ")
                                 + result->getDesignation());

        QString entry(QTime::currentTime().toString()
                      + " - <font color=\"#006DA3\"><strong>"
                      + player->getName() + "</strong></font> "
                      + QString::fromUtf8(" enquête"));

        if(extra != 0)
        {
            entry.append(QString(", ajoute <strong>" + QString::number(extra) + "</strong> points de pouvoir,").toAscii());
        }

        entry.append(QString(" et obtient le rapport<strong>"
                             + QString(" ") + result->getDesignation()
                             + "</strong><br><br>").toAscii());
        addLogEntry(entry);

    }
    catch(Character::NotEnoughPowerException e)
    {
        QMessageBox::critical(NULL, tr("Error"), story->getPlayerTab()[ui->cb_investigator->currentIndex()]->getName()
                              + " has not enough power points\nActual: "
                              + QString::number(e.getActual()) + "\nNeeded: "
                              + QString::number(e.getNeeded()));
    }
    catch(Character::InterceptedException e)
    {
        QString s(tr("Give report ") + e.getReport()->getDesignation()
                  + tr(" to ") + e.getInterceptor()->getName());
        Event ev(Event(tr("Interception"), s, NULL, QTime::currentTime()));
        QStringList sl;
        sl << story->getModel()->stringList();
        sl << QString(ev.getTime().toString("hh:mm - ") + ev.getShortDescription());
        story->getModel()->setStringList(sl);
        QMessageBox::critical(NULL, tr("Interception!"), "Your report has been intercepted!");
        QMessageBox::information(NULL, tr("Interception"), s);

        addLogEntry(QTime::currentTime().toString() + " - <font color=\"#006DA3\"><strong>"
                    + player->getName() + "</strong></font> "
                    + QString::fromUtf8(" enquête mais son rapport (<strong>")
                    + e.getReport()->getDesignation()
                    + QString::fromUtf8("</strong>) a été intercepté (par <font color=\"#D92615\"><strong>")
                    + e.getInterceptor()->getName() + "</strong></font>)<br><br>");
    }
    return;
}

void GameWidget::intercept()
{
    Character *player = story->getPlayerTab()[ui->cb_investigator->currentIndex()];
    Character *targetedPlayer = story->getPlayerTab()[ui->cb_target->currentIndex()];

    try
    {
        bool result = player->intercept(targetedPlayer);
        if (result)
        {
            QMessageBox::information(NULL, tr("Result"), targetedPlayer->getName()
                                     + tr(" next's report will be intercepted by ")
                                     + player->getName());
            addLogEntry(QTime::currentTime().toString() + " - <font color=\"#D92615\"><strong>"
                        + player->getName() + "</strong></font> "
                        + QString::fromUtf8(" interceptera le prochain rapport de <font color=\"#006DA3\"><strong>")
                        + targetedPlayer->getName()
                        + QString::fromUtf8("</strong></font><br><br>"));
        }
        else
        {
            QMessageBox::warning(NULL, tr("Result"), tr("The interception has failed"));
            addLogEntry(QTime::currentTime().toString() + " - <font color=\"#D92615\"><strong>"
                        + player->getName() + "</strong></font> "
                        + QString::fromUtf8(" a tenté d'intercepter le prochain rapport de <font color=\"#006DA3\"><strong>")
                        + targetedPlayer->getName()
                        + QString::fromUtf8("</strong></font> mais sans succès<br><br>"));
        }
    }
    catch(Character::NotEnoughPowerException e)
    {
        QMessageBox::critical(NULL, tr("Error"), story->getPlayerTab()[ui->cb_investigator->currentIndex()]->getName() + " has not enough power points\nActual: " + QString::number(e.getActual()) + "\nNeeded: " + QString::number(e.getNeeded()));
    }
    catch(Character::HasInterceptorException e)
    {
        QMessageBox::warning(NULL, tr("Error"), e.getTarget()->getName() + " already has an interceptor");
    }
}

void GameWidget::copy()
{
    try
    {
        Character *player = story->getPlayerTab()[ui->cb_investigator->currentIndex()];
        Character *targetedPlayer = story->getPlayerTab()[ui->cb_target->currentIndex()];
        Report *result = player->copy(targetedPlayer);
        QMessageBox::information(NULL, tr("Result"), tr("Give ")
                                 + result->getDesignation()
                                 + tr(" to ") + player->getName());
        addLogEntry(QTime::currentTime().toString() + " - <font color=\"#207333\"><strong>"
                    + player->getName() + "</strong></font> "
                    + QString::fromUtf8(" copie le dernier rapport (<strong>")
                    + result->getDesignation()
                    + QString("</strong>)").toAscii()
                    + QString(" de <font color=\"#006DA3\"><strong>")
                    + targetedPlayer->getName()
                    + QString::fromUtf8("</strong></font><br><br>"));
    }
    catch(Character::NotEnoughPowerException e)
    {
        QMessageBox::critical(NULL, tr("Error"), story->getPlayerTab()[ui->cb_investigator->currentIndex()]->getName()
                              + " has not enough power points\nActual: "
                              + QString::number(e.getActual()) + "\nNeeded: "
                              + QString::number(e.getNeeded()));
    }
    catch(Character::TooLateException e)
    {
        QMessageBox::warning(NULL, tr("Error"), e.getTarget()->getName() + " got his last report more than two minutes ago");
    }
    catch(Character::NoLastReportExeption e)
    {
        QMessageBox::warning(NULL, tr("Error"), e.getTarget()->getName() + " has no report yet");
    }
}

void GameWidget::blockswitch()
{
    if(ui->cb_investigator->currentIndex() == ui->cb_target->currentIndex())
    {
        ui->pb_Copy->setDisabled(true);
        ui->pb_Intercept->setDisabled(true);
    }
    else
    {
        ui->pb_Copy->setDisabled(false);
        ui->pb_Intercept->setDisabled(false);
    }
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

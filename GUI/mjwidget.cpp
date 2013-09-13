#include "mjwidget.h"
#include "ui_mjwidget.h"

MJWidget::MJWidget(Scenario *scenario, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MJWidget)
{
    /* Setting values */
    story = scenario;
    elapsedTime = QTime(0, 0, 0);
    eventCounter = 0;

    /* Setting GUI */
    ui->setupUi(this);
    qDebug() << "Building interceptor list...";
    ui->cb_interceptor->addItem(QString("Aucun"));
    for(int i = 0; i < story->getData()->getNbPlayer(); i++)
    {
        ui->cb_player->addItem(story->getPlayerTab()[i]->getName());
        ui->cb_interceptor->addItem(story->getPlayerTab()[i]->getName());
    }
    qDebug() << "Done!";
    ui->sb_PP->setValue(story->getPlayerTab()[ui->cb_player->currentIndex()]->getPowerPoints());
    qDebug() << "Assignating interceptor value";
    ui->cb_investigation->addItem(QString("-"));
    for(int i = 0; i < story->getData()->getNbInvestigation(); i++)
        ui->cb_investigation->addItem(story->getInvestigationTab()[i].getId());
    ui->cb_quality->addItem(QString("-"));
    for(int i = 0; i < 3; i++)
        ui->cb_quality->addItem(QString::number(i + 1));
    ui->lw_UnsolvedEvents->setModel(story->getModel());
    ui->label_totalTime->setText(story->getData()->getLength().toString());

    /* Time Timer*/
    oneSec = new QTimer(this);
    connect(oneSec, SIGNAL(timeout()), this, SLOT(updateTimer()));
    oneSec->start(1000);
    qDebug() << "Time timer connected and started";

    /* Length Timer */
    int h = story->getData()->getLength().hour();
    int m = story->getData()->getLength().minute();
    int s = story->getData()->getLength().second();
    int lengthInSecs = h * 3600 + m * 60 + s;
    QTimer::singleShot(lengthInSecs * 1000, this, SLOT(stop()));
    qDebug() << "Length timer connected and started";

    /* Setting Events & their respective timers */
    for(unsigned int i = 0; i < story->getEventList().size(); i++)
    {   QTime time = story->getEventList()[i].getTime();
        int h = time.hour();
        int m = time.minute();
        int s = time.second();
        int lengthInSecs = h * 3600 + m * 60 + s;
        QTimer::singleShot(lengthInSecs * 1000, this, SLOT(handleEvents()));
        qDebug() << "Event \"" + story->getEventList()[i].getName() + "\" timer connected and started";
    }

    connect(ui->pb_Now, SIGNAL(clicked()), this, SLOT(changeTime()));
    connect(ui->pb_Validation, SIGNAL(clicked()), this, SLOT(applyChanges()));
    connect(ui->cb_player, SIGNAL(currentIndexChanged(int)), this, SLOT(playerChanged(int)));
    connect(ui->pb_eraseSelection, SIGNAL(clicked()), this, SLOT(eraseSelection()));
}

MJWidget::~MJWidget()
{
    delete ui;
}

void MJWidget::changeEvent(QEvent *e)
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

QComboBox* MJWidget::getPlayer()
{
    return ui->cb_player;
}

void MJWidget::handleEvents()
{
    Event ev = story->getEventList()[eventCounter];
    QStringList sl;
    sl << story->getModel()->stringList();
    sl << QString(QTime::currentTime().toString("hh:mm:ss - ") + ev.getName());
    story->getModel()->setStringList(sl);
    eventCounter++;
}

void MJWidget::changeTime()
{
    ui->te_LRT->setTime(QTime::currentTime());
}

void MJWidget::playerChanged(int)
{
    int index = ui->cb_player->currentIndex();
    if(story->getPlayerTab()[index]->getInterceptor() == NULL)
        ui->cb_interceptor->setCurrentIndex(0);
    for(int i = 0; i < 9; i++)
    {
        if (story->getPlayerTab()[index]->getInterceptor()==story->getPlayerTab()[i])
            ui->cb_interceptor->setCurrentIndex(i+1);
    }
    ui->sb_PP->setValue(story->getPlayerTab()[index]->getPowerPoints());

    if(story->getPlayerTab()[index]->getLastReport() == NULL)
    {
        ui->cb_investigation->setCurrentIndex(0);
        ui->cb_quality->setCurrentIndex(0);
    }
    else
    {
        ui->cb_investigation->setCurrentIndex(story->getPlayerTab()[index]->getLastReport()->getInvestigation().data()->toAscii() - 64);
        ui->cb_quality->setCurrentIndex(story->getPlayerTab()[index]->getLastReport()->getQuality());
        ui->te_LRT->setTime(story->getPlayerTab()[index]->getLastReportTime());
    }
}

void MJWidget::applyChanges()
{
    if (QMessageBox::question(NULL, "Confirmation", "Appliquer les changements?",
                              QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
    {
        /*
         * Si le dernier rapport n'a pas été donné à une heure postérieure à maintenant
         * Et que l'intercepteur n'est pas lui même
         */
        if ((QTime::currentTime().secsTo(ui->te_LRT->time()) < 0))
        {
            if (story->getPlayerTab()[ui->cb_player->currentIndex()]
                    != story->getPlayerTab()[ui->cb_interceptor->currentIndex()-1])
            {
                Character* state = new Character(story->getPlayerTab().at(ui->cb_player->currentIndex())->getName(), story->getPlayerTab().at(ui->cb_player->currentIndex())->getPowerPoints());
                state->setInterceptor(story->getPlayerTab()[ui->cb_player->currentIndex()]->getInterceptor());
                state->setLastReport(story->getPlayerTab()[ui->cb_player->currentIndex()]->getLastReport());
                state->setLastReportTime(story->getPlayerTab()[ui->cb_player->currentIndex()]->getLastReportTime());
                story->getPlayerTab()[ui->cb_player->currentIndex()]->setPowerPoints(ui->sb_PP->value());

                if (ui->cb_interceptor->currentIndex() == 0)
                    story->getPlayerTab()[ui->cb_player->currentIndex()]->setInterceptor(NULL);
                else
                    story->getPlayerTab()[ui->cb_player->currentIndex()]
                            ->setInterceptor(story->getPlayerTab()[ui->cb_interceptor->currentIndex()-1]);
                Report *r1;
                if(ui->cb_investigation->currentIndex() != 0)
                    r1 = new Report(ui->cb_investigation->currentText(), ui->cb_quality->currentIndex(), NULL);
                else
                    r1 = NULL;
                story->getPlayerTab()[ui->cb_player->currentIndex()]->setLastReport(r1);
                story->getPlayerTab()[ui->cb_player->currentIndex()]->setLastReportTime(ui->te_LRT->time());

                QString entry(QTime::currentTime().toString()
                              + QString::fromUtf8(" - <font color=\"#ffcc19\"><strong>MJ</strong></font> a modifié le joueur <font color=\"#207333\"><strong>")
                             + state->getName()
                             +  QString::fromUtf8("</font></strong>:<center>"));
                entry.append(QString::number(state->getPowerPoints()) + " PP -> ");
                entry.append(QString::number(story->getPlayerTab()[ui->cb_player->currentIndex()]->getPowerPoints()));
                entry.append(" PP<br>");

                if(state->getLastReport() == NULL)
                {
                    entry.append("Pas de rapport");
                }
                else
                {
                    entry.append(state->getLastReport()->getDesignation() + " (" + state->getLastReportTime().toString("hh:mm:ss") + ")");
                }

                entry.append(" -> ");

                if(story->getPlayerTab()[ui->cb_player->currentIndex()]->getLastReport() == NULL)
                {
                    entry.append("Pas de rapport<br>");
                }
                else
                {
                    entry.append(story->getPlayerTab()[ui->cb_player->currentIndex()]->getLastReport()->getDesignation() + " (" + story->getPlayerTab()[ui->cb_player->currentIndex()]->getLastReportTime().toString("hh:mm:ss") + ")<br>");
                }

                if(state->getInterceptor() == NULL)
                {
                    entry.append("Pas d'intercepteur");
                }
                else
                {
                    entry.append(QString::fromUtf8("Intercepté par <font color=\"#D92615\"><strong>") + state->getInterceptor()->getName() + "</strong></font>");
                }

                entry.append(" -> ");

                if(story->getPlayerTab()[ui->cb_player->currentIndex()]->getInterceptor() == NULL)
                {
                    entry.append("Pas d'intercepteur<br>");
                }
                else
                {
                    entry.append(QString::fromUtf8("Intercepté par <font color=\"#D92615\"><strong>") + story->getPlayerTab()[ui->cb_player->currentIndex()]->getInterceptor()->getName() + "</strong></font><br>");
                }

                entry.append("</center><br><br>");

                addLogEntry(entry);

                delete state;
                return;
            }
            else
                QMessageBox::warning(NULL, "Attention", QString::fromUtf8("Le joueur ne peut s'intercepter lui même!"));
        }
        else
            QMessageBox::warning(NULL, "Attention", QString::fromUtf8("L'heure donnée n'est pas encore passée!"));
    }
}

void MJWidget::stop()
{
    oneSec->stop();
    //QSound::play(":/sounds/bell.wav");
    QMessageBox::information(NULL, "Fin du jeu", QString::fromUtf8("La partie est  terminée!\nStoppez tout et référez vous à la feuille de jeu"));

}

void MJWidget::updateTimer()
{
    elapsedTime = elapsedTime.addSecs(1);
    ui->label_elapsedTime->setText(elapsedTime.toString("hh:mm:ss"));
}

void MJWidget::eraseSelection()
{
    QItemSelectionModel *selection = ui->lw_UnsolvedEvents->selectionModel();
    QModelIndexList indexList = selection->selectedIndexes();
    qDebug() << indexList.begin().i->v;
    //for(int i = 0; i < indexList.size(); i ++)
        //indexList.at(0).row()
        //ui->lw_UnsolvedEvents->model()->removeRow(i);
}

#include "datawidget.h"
#include "ui_datawidget.h"

DataWidget::DataWidget(Scenario *scenario, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataWidget)
{
    this->story = scenario;
    ui->setupUi(this);
    ui->label_author->setText(ui->label_author->text() + " " + story->getData()->getAuthor());
    ui->label_date->setText(ui->label_date->text() + " " + QString::number(story->getData()->getCreationYear()));
    ui->label_length->setText(ui->label_length->text() + " " + story->getData()->getLength().toString("hh:mm:ss"));
    ui->label_name->setText(ui->label_name->text() + " " + story->getData()->getName());
    ui->label_nbEvents->setText(ui->label_nbEvents->text() + " " + QString::number(story->getData()->getNbEvent()));
    ui->label_nbInvestigations->setText(ui->label_nbInvestigations->text() + " " + QString::number(story->getData()->getNbInvestigation()));
    ui->label_nbMJ->setText(ui->label_nbMJ->text() + " " + QString::number(story->getData()->getNbMj()));
    ui->label_nbPlayer->setText(ui->label_nbPlayer->text() + " " + QString::number(story->getData()->getNbPlayer()));
    connect(ui->pb_showInvest, SIGNAL(clicked()), this, SLOT(showInvests()));
    connect(ui->pb_showDiary, SIGNAL(clicked()), this, SLOT(showEvents()));
}

DataWidget::~DataWidget()
{
    delete ui;
}

void DataWidget::changeEvent(QEvent *e)
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


void DataWidget::showInvests()
{
    ClueView *cw = new ClueView(story);
    cw->show();
}
void DataWidget::showEvents()
{
    EventView *ew = new EventView(story);
    ew->show();
}

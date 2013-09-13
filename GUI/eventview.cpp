#include "eventview.h"
#include "ui_eventview.h"

EventView::EventView(Scenario *scenario, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventView)
{
    ui->setupUi(this);
    story = scenario;
    events = story->getEventList();

    QStandardItemModel *model = new QStandardItemModel();
    for(unsigned int i = 0; i < events.size(); i++)
    {
        QStandardItem *object = new QStandardItem(events[i].getName());
        model->appendRow(object);
        object->appendRow(new QStandardItem(events[i].getTime().toString()));
        object->appendRow(new QStandardItem(events[i].getShortDescription()));
        object->appendRow(new QStandardItem(events[i].getLongDescription()));
    }
    ui->tw_View->setModel(model);
    ui->tw_View->setHeaderHidden(true);
}

EventView::~EventView()
{
    delete ui;
}

void EventView::changeEvent(QEvent *e)
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

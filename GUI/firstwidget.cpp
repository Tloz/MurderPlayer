#include "firstwidget.h"
#include "ui_firstwidget.h"

FirstWidget::FirstWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstWidget)
{
    ui->setupUi(this);
}

FirstWidget::~FirstWidget()
{
    delete ui;
}

void FirstWidget::changeEvent(QEvent *e)
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

QPushButton* FirstWidget::get_PB_Begin()
{
    return ui->pb_Begin;
}

QPushButton* FirstWidget::get_PB_Choose()
{
    return ui->pb_Choose;
}

QPushButton* FirstWidget::get_PB_Save()
{
    return ui->pb_Save;
}

QPushButton* FirstWidget::get_PB_Load()
{
    return ui->pb_Load;
}

QPlainTextEdit* FirstWidget::getSummary()
{
    return ui->pte_summary;
}

Scenario* FirstWidget::get_Scenario()
{
    return story;
}

void FirstWidget::set_Scenario(Scenario *story)
{
    this->story = story;
}

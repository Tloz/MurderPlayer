#include "settingswidget.h"
#include "ui_settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
    sysThemeList << QStyleFactory::keys();
    ui->cb_theme->addItems(sysThemeList);
    connect(ui->cb_theme, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeTheme(QString)));
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::changeEvent(QEvent *e)
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
void SettingsWidget::changeTheme(QString theme)
{
    QApplication::setStyle(theme);
}

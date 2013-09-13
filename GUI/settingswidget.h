#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QtGui/QWidget>
#include <QStringList>
#include <QStyleFactory>

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SettingsWidget(QWidget *parent = 0);
    ~SettingsWidget();
    
protected:
    void changeEvent(QEvent *e);
    
private:
    Ui::SettingsWidget *ui;
    QStringList sysThemeList;

public slots:
    void changeTheme(QString theme);
};

#endif // SETTINGSWIDGET_H

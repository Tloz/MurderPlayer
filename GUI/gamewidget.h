#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>
#include "Engine/scenario.h"
#include "Engine/log.h"

namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit GameWidget(Scenario *scenario, QWidget *parent = 0);
    ~GameWidget();
    
protected:
    void changeEvent(QEvent *e);
    
private:
    Scenario *story;
    Ui::GameWidget *ui;

public slots:
    void investigate();
    void intercept();
    void copy();
    void blockswitch();
};

#endif // GAMEWIDGET_H

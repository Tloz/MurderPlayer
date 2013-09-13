#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QtGui/QWidget>
#include "Engine/scenario.h"
#include "clueview.h"
#include "eventview.h"

namespace Ui {
class DataWidget;
}

class DataWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit DataWidget(Scenario *scenario, QWidget *parent = 0);
    ~DataWidget();
    
protected:
    void changeEvent(QEvent *e);
    
private:
    Ui::DataWidget *ui;
    Scenario *story;

public slots:
    void showInvests();
    void showEvents();
};

#endif // DATAWIDGET_H

#ifndef EVENTVIEW_H
#define EVENTVIEW_H

#include <QtGui/QWidget>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QDebug>

#include "Engine/scenario.h"

namespace Ui {
class EventView;
}

class EventView : public QWidget
{
    Q_OBJECT
    
public:
    explicit EventView(Scenario* scenario, QWidget *parent = 0);
    ~EventView();
    
protected:
    void changeEvent(QEvent *e);
    
private:
    Scenario* story;
    Ui::EventView *ui;
    QStandardItemModel *model;
    std::vector<Event> events;
};

#endif // EVENTVIEW_H

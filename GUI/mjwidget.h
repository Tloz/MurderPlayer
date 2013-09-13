#ifndef MJWIDGET_H
#define MJWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QMessageBox>
#include <QtCore/QTimer>
#include <QtCore/QTime>
#include <QModelIndexList>
#include <QComboBox>
#include <QSound>
#include <QDebug>
#include "Engine/scenario.h"
#include "Engine/log.h"

namespace Ui {
class MJWidget;
}

class MJWidget : public QWidget
{
    Q_OBJECT
    
public:
    QComboBox* getPlayer();
    explicit MJWidget(Scenario *scenario, QWidget *parent = 0);
    ~MJWidget();
    
protected:
    void changeEvent(QEvent *e);
    
private:
    Ui::MJWidget *ui;
    Scenario *story;
    QTimer *oneSec;
    QTime elapsedTime;
    unsigned int eventCounter;

signals:
    void indexedTimeout(int);

public slots:
    void playerChanged(int index);
    void changeTime();
    void applyChanges();
    void stop();
    void updateTimer();
    void handleEvents();
    void eraseSelection();
};

#endif // MJWIDGET_H

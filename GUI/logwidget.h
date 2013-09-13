#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QtGui/QWidget>
#include <QtCore/QTimer>
#include <QTextEdit>
#include "Engine/log.h"

namespace Ui {
class LogWidget;
}

class LogWidget : public QWidget
{
    Q_OBJECT
    
public:
    QTextEdit* getLogView();
    explicit LogWidget(QWidget *parent = 0);
    ~LogWidget();
    
protected:
    void changeEvent(QEvent *e);
    
private:
    Ui::LogWidget *ui;
    QTimer *time5secs;
};

#endif // LOGWIDGET_H

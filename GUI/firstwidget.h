#ifndef FIRSTWIDGET_H
#define FIRSTWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QPlainTextEdit>
#include <Engine/scenario.h>

namespace Ui {
class FirstWidget;
}

class FirstWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit FirstWidget(QWidget *parent = 0);
    ~FirstWidget();
    QPushButton* get_PB_Begin();
    QPushButton* get_PB_Choose();
    QPushButton* get_PB_Save();
    QPushButton* get_PB_Load();
    QPlainTextEdit* getSummary();
    Scenario* get_Scenario();
    void set_Scenario(Scenario *story);


    
protected:
    void changeEvent(QEvent *e);
    
private:
    Ui::FirstWidget *ui;
    Scenario* story;
};

#endif // FIRSTWIDGET_H

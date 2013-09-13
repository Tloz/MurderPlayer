#ifndef CLUEVIEW_H
#define CLUEVIEW_H

#include <QWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTextEdit>
#include <QDebug>
#include <QPushButton>


#include "Engine/scenario.h"

class ClueView : public QWidget
{
    Q_OBJECT
public:
    explicit ClueView(Scenario *story, QWidget *parent = 0);
    QTextEdit *displayedClue;
    QStandardItemModel *modelI;
    QTreeView *viewI;
    QItemSelectionModel *selec;

private:
    std::vector<Investigation> invest;

signals:

public slots:
    void displayClue();


};
#endif // CLUEVIEW_H

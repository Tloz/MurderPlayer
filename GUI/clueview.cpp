#include "clueview.h"

ClueView::ClueView(Scenario *story, QWidget *parent) :
    QWidget(parent)
{
    invest = story->getInvestigationTab();
    modelI = new QStandardItemModel();
    for(unsigned int i = 0; i < invest.size(); i++)
    {
        QStandardItem *object = new QStandardItem(invest[i].getId() + " : " + invest[i].getTitle());
        modelI->appendRow(object);
        object->appendRow(new QStandardItem(tr("Clue") + " 1"));
        object->appendRow(new QStandardItem(tr("Clue") + " 2"));
        object->appendRow(new QStandardItem(tr("Clue") + " 3"));
        qDebug() << "ClueWidget" << endl
                 << "Investigation " + invest[i].getId() + " : " + invest[i].getTitle() + "added to the view";
    }

    viewI = new QTreeView(this);
    viewI->setModel(modelI);
    viewI->header()->hide();
    viewI->setEditTriggers(QAbstractItemView::NoEditTriggers);

    displayedClue = new QTextEdit(this);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(viewI, 5);
    layout->addWidget(displayedClue, 3);
    setLayout(layout);

    connect(viewI, SIGNAL(clicked(QModelIndex)), this, SLOT(displayClue()));
}

void ClueView::displayClue()
{


    selec = viewI->selectionModel();
    qDebug() << selec->selection();
    qDebug() << endl;
    qDebug() << selec->selection().indexes().at(0);
    /* trouver le numéro de la ligne parent et de la ligne enfant (entre 1 et 3) */
    /*qDebug() << selec->currentIndex().sibling(selec->currentIndex().row(), 0);
    qDebug << selec->currentIndex().model()->;

    int j = selec->currentIndex().row();
    //qDebug() << j;
    //displayedClue->setText(invest[i].getReports()[j].getInfo());
    */

    /*
    // Récupération de l'index de la sélection
    QModelIndex indexElementSelectionne = viewI->selectionModel()->currentIndex();
    // Récupération du parent de la sélection
    QStandardItem *parentSelection = modelI->itemFromIndex (indexElementSelectionne.parent());
    qDebug() << indexElementSelectionne << parentSelection->column();
    */
}

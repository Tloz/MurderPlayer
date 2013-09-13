#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QStackedLayout>
#include <QtGui/QProgressBar>
#include <QtGui/QMenu>
#include <QtCore/QFile>
#include <QtCore/QTime>
#include <QtGui/QAction>
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QLineEdit>
#include <QtGui/QStatusBar>
#include <QtGui/QMessageBox>
#include <QtGui/QCloseEvent>
#include <QtGui/QMainWindow>
#include <QtGui/QFileDialog>
#include <QtGui/QApplication>
#include <QtGui/QTextBrowser>
#include <QtGui/QInputDialog>
#include <QLabel>

#include "datawidget.h"
#include "gamewidget.h"
#include "firstwidget.h"
#include "logwidget.h"
#include "mjwidget.h"
#include "settingswidget.h"
#include "Engine/fileparsing.h"
#include "Engine/log.h"

void notYet();

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
protected:
    void changeEvent(QEvent *e);
    
private:
    Ui::MainWindow *ui;

    QStackedLayout *finalLayout;

    FirstWidget *fw;
    DataWidget *dw;
    GameWidget *gw;
    LogWidget *lw;
    MJWidget *mw;
    SettingsWidget *sw;

    Scenario *story;

    bool disabled;

    /* Menu de Jeu */
    QMenu *menuGame;
    QAction *actionInitiateGame;
    QAction *actionLoadGame;
    QAction *actionLoadScenario;
    QAction *actionSaveGame;
    QAction *actionQuit;
    QMenu *menuDM;
    QAction *actionPause;
    QAction *actionRollDice;
    QAction *actionaddEntry;
    QMenu *changePlayerPp;
    QAction *actionAddOPPp;
    QAction *actionDelOPPp;
    QAction *actionSetOPPp;
    QMenu *changeAllPlayerPp;
    QAction *actionAddAPPp;
    QAction *actionDelAPPp;
    QAction *actionSetAPPp;

    QMenu *menuWindow;
    QAction *winInit;
    QAction *winGame;
    QAction *winDM;
    QAction *winLog;
    QAction *winInfo;
    QAction *winOptions;

    QMenu *menuOther;
    QAction *actionHelp;
    QAction *actionOptions;
    QAction *actionChangelog;
    QAction *actionAboutQt;
    QAction *actionLegal;


    QToolBar *toolBar;
    QStatusBar *stateBar;
    QTime *currentTime;
    QProgressBar *timeGauge;


public slots:
    void LoadScenario();
    void InitiateGame();
    void LoadGame();
    void SaveGame();

    void Quit();
    void pause();

    void begin();
    void game();
    void dm();
    void log();
    void data();
    void options();

    void rollDice();
    void addEntry();
    void addOPPp();
    void delOPPp();
    void setOPPp();
    void addAPPp();
    void delAPPp();
    void setAPPp();
    void help();
    void changelog();
    void legal();

protected:
    //virtual void closeEvent(QCloseEvent*);

};

#endif // MAINWINDOW_H

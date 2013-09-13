#include "mainwindow.h"
#include "ui_mainwindow.h"

void notYet()
{
    QMessageBox::information(NULL, QString("Error"), QString("Function not implemented yet, sorry :/"));
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    disabled = false;
    /* Menu de Jeu */
    menuGame = menuBar()->addMenu(tr("&Game"));
    // Charger scénario: permet de charger un fichier scénario
    actionLoadScenario = menuGame->addAction(tr("Load Scenario"));
    actionLoadScenario->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    connect(actionLoadScenario , SIGNAL(triggered()), this, SLOT(LoadScenario()));
    // Initialiser partie: récupère les informations du scénario (personnages, points de pouvoir), les charge en mémoire et lance la partie (gère le temps)
    actionInitiateGame = menuGame->addAction(tr("&Begin Game"));
    actionInitiateGame->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_B));
    connect(actionInitiateGame, SIGNAL(triggered()), this, SLOT(InitiateGame()));
    menuGame->addSeparator();
    // Charger partie: charge une partie sauvegardée, utile si une pause s'impose ou en cas de plantage
    actionLoadGame = menuGame->addAction(tr("&Load Game"));
    actionLoadGame->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_L));
    connect(actionLoadGame, SIGNAL(triggered()), this, SLOT(LoadGame()));
    // Sauvegarde partie: sauvegarde l'état de la partie et des joueurs, utile si une pause s'impose ou en cas de plantage
    actionSaveGame = menuGame->addAction(tr("&Save Game"));
    actionSaveGame->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    connect(actionSaveGame, SIGNAL(triggered()), this, SLOT(SaveGame()));
    menuGame->addSeparator();
    // Quitter: quitte l'application
    actionQuit = menuGame->addAction(tr("&Quit"));
    connect(actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    /*
             * TODO:
             * Supprimer le raccourci pour la version finale
             */
    actionQuit->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    /* Menu DM */
    menuDM = menuBar()->addMenu(tr("&DM"));
    menuDM->setEnabled(false);
    // Pause: bloque tout le reste de l'application, la seule action possible est le unpause
    actionPause = menuDM->addAction(tr("&Pause"));
    actionPause->setCheckable(true);
    connect(actionPause, SIGNAL(triggered()), this, SLOT(pause()));
    // Lance un dé (plusieurs valeurs possible) pour déterminer un tirage au sort
    actionRollDice = menuDM->addAction(QIcon(":icones/de"), tr("Roll Dice"));
    connect(actionRollDice, SIGNAL(triggered()), this, SLOT(rollDice()));
    // Ecrit une phrase dans le log
    actionaddEntry = menuDM->addAction(tr("Add &log entry"));
    connect(actionaddEntry, SIGNAL(triggered()), this, SLOT(addEntry()));
    menuDM->addSeparator();
    // Sous menu pour changer les PP d'un joueur
    changePlayerPp = menuDM->addMenu(tr("Modify a player power points"));
    // Ajoute des PP à un joueur
    actionAddOPPp = changePlayerPp->addAction(tr("Add"));
    connect(actionAddOPPp, SIGNAL(triggered()), this, SLOT(addOPPp()));
    // Retire des PP à un joueur
    actionDelOPPp = changePlayerPp->addAction(tr("Delete"));
    connect(actionDelOPPp, SIGNAL(triggered()), this, SLOT(delOPPp()));
    // Redéfinit les PP d'un joueur
    actionSetOPPp = changePlayerPp->addAction(tr("Set"));
    connect(actionSetOPPp, SIGNAL(triggered()), this, SLOT(setOPPp()));
    // Sous menu pour changer les PP d'un joueur
    changeAllPlayerPp = menuDM->addMenu(tr("Modify all players power points"));
    // Ajoute des PP à tout les joueurs
    actionAddAPPp = changeAllPlayerPp->addAction(tr("Add"));
    connect(actionAddAPPp, SIGNAL(triggered()), this, SLOT(addAPPp()));
    // Retire des PP à tout les joueurs
    actionDelAPPp = changeAllPlayerPp->addAction(tr("Delete"));
    connect(actionDelAPPp, SIGNAL(triggered()), this, SLOT(delAPPp()));
    // Redéfinit les PP de tout joueurs
    actionSetAPPp = changeAllPlayerPp->addAction(tr("Set"));
    connect(actionSetAPPp, SIGNAL(triggered()), this, SLOT(setAPPp()));
    /* Menu Widget */
    menuWindow = menuBar()->addMenu(tr("&Windows"));
    menuWindow->setEnabled(false);
    // Va au widget de démarrage
    winInit = menuWindow->addAction(tr("&Begin"));
    winInit->setIcon(QIcon(":icones/begin"));
    winInit->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_I));
    connect(winInit, SIGNAL(triggered()), this, SLOT(begin()));
    winInit->setEnabled(false);
    // Va au widget de jeu
    winGame = menuWindow->addAction(tr("&Game"));
    winGame->setIcon(QIcon(":icones/dice"));
    connect(winGame, SIGNAL(triggered()), this, SLOT(game()));
    winGame->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_J));
    winGame->setEnabled(false);
    // Va au widget DM
    winDM = menuWindow->addAction(tr("&DM"));
    winDM->setIcon(QIcon(":icones/mj"));
    connect(winDM, SIGNAL(triggered()) , this, SLOT(dm()));
    winDM->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_M));
    winDM->setEnabled(false);
    // Va au widget de Log
    winLog = menuWindow->addAction(tr("&Log"));
    winLog->setIcon(QIcon(":icones/log"));
    winLog->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_L));
    connect(winLog, SIGNAL(triggered()), this, SLOT(log()));
    winLog->setEnabled(false);
    // Va au widget des données de scénario
    winInfo = menuWindow->addAction(tr("&Data"));
    winInfo->setIcon(QIcon(":icones/info"));
    winInfo->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_D));
    connect(winInfo, SIGNAL(triggered()), this, SLOT(data()));
    winInfo->setEnabled(false);
    // Va au widget des données d'options
    winOptions = menuWindow->addAction(tr("&Options"));
    winOptions->setIcon(QIcon(":icones/options"));
    winOptions->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_O));
    connect(winOptions, SIGNAL(triggered()), this, SLOT(options()));
    /* Menu autre */
    menuOther = menuBar()->addMenu(tr("&Misc"));
    // Affiche l'aide
    actionHelp = menuOther->addAction(tr("Help"));
    actionHelp->setShortcut(QKeySequence::HelpContents);
    connect(actionHelp, SIGNAL(triggered()), this, SLOT(help()));
    // Affiche les options
    actionOptions = menuOther->addAction(tr("Settings"));
    connect(actionOptions, SIGNAL(triggered()), this, SLOT(options()));
    // Affiche le changelog/what's new
    actionChangelog = menuOther->addAction(tr("Changelog"));
    connect(actionChangelog, SIGNAL(triggered()), this, SLOT(changelog()));
    // Affiche le aboutQt
    actionAboutQt = menuOther->addAction(tr("About Qt"));
    connect(actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    // Affiche les informations de licence
    actionLegal = menuOther->addAction(tr("Legal"));
    connect(actionLegal, SIGNAL(triggered()), this, SLOT(legal()));
    winOptions->setEnabled(false);

    /* Barre d'outils icones */
    toolBar = addToolBar("toolBar");
    toolBar->setMovable(false);
    toolBar->addAction(winInit);
    toolBar->addSeparator();
    toolBar->addAction(winGame);
    toolBar->addSeparator();
    toolBar->addAction(winDM);
    toolBar->addSeparator();
    toolBar->addAction(winLog);
    toolBar->addSeparator();
    toolBar->addAction(winInfo);
    toolBar->addSeparator();
    toolBar->addAction(winOptions);

    stateBar = statusBar();
    stateBar->setSizeGripEnabled(false);

    QWidget *central = new QWidget();
    finalLayout = new QStackedLayout();
    fw = new FirstWidget();
    finalLayout->addWidget(fw);
    central->setLayout(finalLayout);
    setCentralWidget(central);

    connect(fw->get_PB_Choose(), SIGNAL(clicked()), this, SLOT(LoadScenario()));
    connect(fw->get_PB_Begin(), SIGNAL(clicked()), this, SLOT(InitiateGame()));
    connect(fw->get_PB_Load(), SIGNAL(clicked()), this, SLOT(LoadGame()));
    connect(fw->get_PB_Save(), SIGNAL(clicked()), this, SLOT(SaveGame()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::LoadScenario() //Fini
{
    QString fileName = QFileDialog::getOpenFileName(NULL, tr("Choose a Scenario"),
                                                    QCoreApplication::applicationDirPath(),
                                                    tr("Scenario *.mpf"));
    story = readStoryFromPlainText(fileName);


    if(story == NULL)
    {
        QMessageBox::critical
                (NULL, tr("Error"), tr("Scenario hasn't been loaded"));
        fw->set_Scenario(story);
        fw->get_PB_Begin()->setEnabled(false);
        fw->get_PB_Save()->setEnabled(false);
        fw->get_PB_Load()->setEnabled(false);
    }
    else
    {
        fw->set_Scenario(story);
        fw->get_PB_Begin()->setEnabled(true);
        fw->get_PB_Save()->setEnabled(true);
        fw->get_PB_Load()->setEnabled(true);
        fw->getSummary()->setPlainText(story->getData()->getSummary());
        QMessageBox::information (NULL, tr("Status"),
                                  tr("Scenario \"" + story->getData()->getName().toAscii() + "\" succesfully loaded!"));
    }
}

void MainWindow::InitiateGame()	//Fini
{
    if(story == NULL)
    {
        QMessageBox::critical
                (NULL, tr("Error"), tr("You must specify a file to open"));
        return;
    }

    QFile logFile(/*m_logPath*/"log.txt");

    if( !logFile.open( QIODevice::WriteOnly) )
    {
        QMessageBox::critical
                (NULL, tr("Error"), tr("Couldn't open log file"));
    }

    QTextStream logStream(&logFile);

    logStream << "<div align=center>- " << QTime::currentTime().toString() << " -<br><u>"
              << story->getData()->getName() << "</u><br>La partie commence<br>"
              << "#=========================================#" << "</div><br>";
    logFile.close();

    gw = new GameWidget(story, this);
    mw = new MJWidget(story);
    lw = new LogWidget();
    dw = new DataWidget(story, this);
    sw = new SettingsWidget();

    finalLayout->addWidget(gw);
    finalLayout->addWidget(mw);
    finalLayout->addWidget(lw);
    finalLayout->addWidget(dw);
    finalLayout->addWidget(sw);
    finalLayout->setCurrentIndex(1);

    winGame->setEnabled(true);
    winDM->setEnabled(true);
    winLog->setEnabled(true);
    winInfo->setEnabled(true);
    menuDM->setEnabled(true);
    menuWindow->setEnabled(true);
    winInit->setEnabled(true);
    winOptions->setEnabled(true);
}

void MainWindow::LoadGame() //Fini
{
    QString fileName = QFileDialog::getOpenFileName(NULL, tr("Choose Save"),
                                                    QCoreApplication::applicationDirPath(),
                                                    tr("Save *.mps"));
    readSaveFromPlainText(fileName, story);
}

void MainWindow::SaveGame() //Fini
{
    saveToPlainText(story);
    QMessageBox::information(NULL, QString(tr("Saving")),
                             tr("Game saved in file ")
                             + QCoreApplication::applicationDirPath());
}

void MainWindow::Quit() //Vide
{
    notYet();
}

/* Slot DM */
void MainWindow::pause()
{
    /*
    if (disabled)
        disabled = false;
    else
        disabled = true;

    menuGame->setDisabled(disabled);
    menuWindow->setDisabled(disabled);
    menuOther->setDisabled(disabled);
    menuDM->setDisabled(disabled);
    */
    notYet();
}


void MainWindow::begin()
{
    finalLayout->setCurrentIndex(0);
}

void MainWindow::game()
{
    finalLayout->setCurrentIndex(1);
}

void MainWindow::dm()
{
    finalLayout->setCurrentIndex(2);
    mw->getPlayer()->setCurrentIndex(mw->getPlayer()->currentIndex());
}

void MainWindow::log()
{
    finalLayout->setCurrentIndex(3);
    lw->getLogView()->setText(getLog());
}

void MainWindow::data()
{
    finalLayout->setCurrentIndex(4);
}

void MainWindow::options()
{
    finalLayout->setCurrentIndex(5);
}

void MainWindow::rollDice()
{
    notYet();
}

void MainWindow::addEntry()
{
    notYet();
}

void MainWindow::addOPPp()
{
    notYet();
}

void MainWindow::delOPPp()
{
    notYet();
}

void MainWindow::setOPPp()
{
    notYet();
}

void MainWindow::addAPPp()
{
    notYet();
}

void MainWindow::delAPPp()
{
    notYet();
}

void MainWindow::setAPPp()
{
    notYet();
}

void MainWindow::help()
{
    notYet();
}

void MainWindow::changelog()
{
    notYet();
}

void MainWindow::legal()
{
    notYet();
}

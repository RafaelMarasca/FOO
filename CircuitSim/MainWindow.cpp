/********************************************************************************************
 * @file MainWindow.cpp
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 28 04 2021
 * @brief Implementação da classe MainWindow.
 * 
 * Este arquivo contém as implementações dos métodos e membros da classe MainWindow.
 * 
 * A classe MainWindow controla o fluxo de execução com base nas interações do usuário.
 *  
 ********************************************************************************************/


#include "MainWindow.h"
#include "Diagram.h"

#include <iostream>
#include <fstream>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QPushButton>
#include <QTabWidget>
#include <QTabBar>
#include <QFileInfo>
#include <QPixmap>
#include <QIcon>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QLabel>
#include <QColorDialog>

MainWindow* MainWindow::instance = nullptr;


//Retorna a instância da MainWindow
MainWindow* MainWindow::getMainWindow(){
    if(instance == nullptr){
        instance = new MainWindow;
    }
    return instance;
}

//Construtor da janela principal
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("CircuitSim");
    setGeometry(0,0,800,600);
    loadConfig();

    initializeMenu();
    initializeToolbar();
    initializeTabs();
    initializeStatusBar();
}

//Inicializa o menu inicial
void MainWindow::initializeMenu(){

    //Menu principal - Ações e menus.
    mainBar = new QMenuBar(this);

    //Menu de arquivos.
    fileMenu = new QMenu("Arquivo",this);
    mainBar->addMenu(fileMenu);

    newFileAct = new QAction("Novo Arquivo",this);
    fileMenu->addAction(newFileAct);

    connect(newFileAct,SIGNAL(triggered(bool)),this,SLOT(newFile()));

    openFileAct = new QAction("Abrir",this);
    fileMenu->addAction(openFileAct);

    connect(openFileAct,SIGNAL(triggered(bool)),this, SLOT(openFile()));

    saveFileAct = new QAction("Salvar",this);
    fileMenu->addAction(saveFileAct);

    connect(saveFileAct,SIGNAL(triggered(bool)),this, SLOT(saveFile()));

    saveFileAsAct = new QAction("Salvar como",this);
    fileMenu->addAction(saveFileAsAct);

    connect(saveFileAsAct,SIGNAL(triggered(bool)),this, SLOT(saveFileAs()));

    //Menu de preferências.
    prefMenu = new QMenu("Preferências",this);
    mainBar->addMenu(prefMenu);

    //Ações do menu de preferências.
    setBGColorAct = new QAction("Mudar Plano de Fundo");
    prefMenu->addAction(setBGColorAct);

    connect(setBGColorAct, SIGNAL(triggered(bool)),this,SLOT(setBGColor()));

    setGridColorAct = new QAction("Mudar Cor da Grade");
    prefMenu->addAction(setGridColorAct);

    connect(setGridColorAct, SIGNAL(triggered(bool)),this,SLOT(setGridColor()));

    setComponentColorAct = new QAction("Mudar Cor dos Componentes");
    prefMenu->addAction(setComponentColorAct);

    connect(setComponentColorAct, SIGNAL(triggered(bool)),this,SLOT(setComponentColor()));

    setSelectedColorAct = new QAction("Mudar Cor da Seleção");
    prefMenu->addAction(setSelectedColorAct);

    connect(setSelectedColorAct, SIGNAL(triggered(bool)),this,SLOT(setSelectedColor()));

    resetConfigAct = new QAction("Restaurar Configurações Padrão");
    prefMenu->addAction(resetConfigAct);

    connect(resetConfigAct, SIGNAL(triggered(bool)),this,SLOT(resetConfig()));

    //Menu de ajuda.
    helpMenu = new QMenu("Ajuda",this);
    mainBar->addMenu(helpMenu);

    //Ações do menu de ajuda.
    tutorialAct = new QAction("Tutorial",this);
    helpMenu->addAction(tutorialAct);

    connect(tutorialAct, SIGNAL(triggered(bool)),this,SLOT(tutorial()));

    //Seta o menu principal da janela principal
    setMenuBar(mainBar);
}

//Inicialiaza a barra de ferramentas.
void MainWindow::initializeToolbar() {

    toolbar = new QToolBar(this);

    //Botão do fonte vertical.
    QPushButton* vcc90Button = new QPushButton(toolbar);
    connect(vcc90Button,SIGNAL(clicked(bool)), this, SLOT(drawVcc90()));
    QPixmap vcc90Pixmap(":/icons/resourceFile/iconFile/vcc90.png");
    QIcon vcc90ButtonIcon(vcc90Pixmap.scaled(65, 65));
    vcc90Button->setIcon(vcc90ButtonIcon);
    vcc90Button->setIconSize(QSize(65, 65));
    toolbar->addWidget(vcc90Button);


    //Botão do fonte horizontal.
    QPushButton* vcc180Button = new QPushButton(toolbar);
    connect(vcc180Button,SIGNAL(clicked(bool)), this, SLOT(drawVcc180()));
    QPixmap vcc180Pixmap(":/icons/resourceFile/iconFile/vcc180.png");
    QIcon vcc180ButtonIcon(vcc180Pixmap.scaled(65, 65));
    vcc180Button->setIcon(vcc180ButtonIcon);
    vcc180Button->setIconSize(QSize(65, 65));
    toolbar->addWidget(vcc180Button);


    //Botão da resistor vertical.
    QPushButton* res90Button = new QPushButton(toolbar);
    connect(res90Button,SIGNAL(clicked(bool)),this, SLOT(drawRes90()));
    QPixmap res90Pixmap(":/icons/resourceFile/iconFile/resistor90.png");
    QIcon res90ButtonIcon(res90Pixmap.scaled(65, 65));
    res90Button->setIcon(res90ButtonIcon);
    res90Button->setIconSize(QSize(65, 65));
    toolbar->addWidget(res90Button);


    //Botão do resistor horizontal.
    QPushButton* res180Button = new QPushButton(toolbar);
    connect(res180Button,SIGNAL(clicked(bool)), this, SLOT(drawRes180()));
    QPixmap res180Pixmap(":/icons/resourceFile/iconFile/resistor180.png");
    QIcon res180ButtonIcon(res180Pixmap.scaled(65, 65));
    res180Button->setIcon(res180ButtonIcon);
    res180Button->setIconSize(QSize(65, 65));
    toolbar->addWidget(res180Button);

    toolbar->setMovable(false);

    addToolBar(Qt::RightToolBarArea, toolbar);
}

//Inicializa a barra de status.
void MainWindow::initializeStatusBar(){
    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);
}

//Inicializa o sistema de abas.
void MainWindow::initializeTabs(){
    tabs = new QTabWidget(this);
    tabs->setTabsClosable(true);
    connect(tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(int)));
    setCentralWidget(tabs);
}

//Cria um novo arquivo.
void MainWindow::newFile(){

    Diagram* D = new Diagram(this);
    diagrams.push_back(D);

    //Inicializa a aba com um nome padrão.
    QString untitled = "*untitled ";
    untitled.append(QString::number(tabs->count()));

    tabs->addTab(D,untitled);

    //Conecta o sinal de mudança de estado do diagrama às abas.
    connect(D,SIGNAL(modified(bool)),this,SLOT(setTabStatus(bool)));

    //Conecta o sinal de mensagem do diagrama à barra de status.
    connect(D,SIGNAL(statusBarText(QString)),statusBar,SLOT(showMessage(QString)));
}

//Abre um arquivo.
void MainWindow::openFile(){
    QString fileName = QFileDialog::getOpenFileName(this,"Abrir arquivo", "*.cct");

    if(fileName.isNull())
         return;

    Diagram* D = new Diagram(this);
    D->setFileName(fileName);

    try {
        D->load();
    }  catch (std::string s) {
        QMessageBox::warning(this, "CUIDADO", "Não foi possível abrir o arquivo.");
        return;
    }

    QFileInfo info(fileName);

    //Adiciona o diagrama ao vector de diagramas ativos.
    diagrams.push_back(D);
    //Adiciona o diagram às abas.
    tabs->addTab(D,info.fileName());

    statusBar->showMessage("\""+fileName+"\" Aberto com sucesso!");

    connect(D,SIGNAL(statusBarText(QString)),statusBar,SLOT(showMessage(QString)));
    //Conecta o sinal de mensagem do diagrama à barra de status.
    connect(D,SIGNAL(modified(bool)),this,SLOT(setTabStatus(bool)));
}

//Salva o arquivo.
void MainWindow::saveFile(){

    if(tabs->count() == 0)
        return;

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    //Se o arquivo não foi salvo anteriormente, salva ele.
    if((*it)->getStatus()==UNSAVED){
        saveFileAs();
        return;
    }

    (*it)->save();
    statusBar->showMessage("\""+(*it)->getFileName()+"\" Salvo com sucesso!");
}


//Abre a janela de seleção de diretório e salva o arquivo
void MainWindow::saveFileAs(){

    if(tabs->count()==0)
        return;

    QString fileName = QFileDialog::getSaveFileName(this, "*.cct");

    if(fileName.isNull())
        return;

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    QFileInfo info(fileName);

    tabs->setTabText(index,info.fileName());
    (*it)->setFileName(fileName);
    (*it)->save();
    statusBar->showMessage("\""+(*it)->getFileName()+"\" Salvo com sucesso!");
}

//Altera o status da aba
void MainWindow::setTabStatus(bool modified){
    int index = tabs->currentIndex();
    QString fileName = tabs->tabText(index);

    //Altera o onme do arquivo para inserir um asterisco caso o
    //arquivo tenha sido modificado.
    if(modified){
        fileName.prepend('*');
    }else if(fileName.at(0)=='*'){
        fileName.remove(0,1);
    }

    tabs->setTabText(index, fileName);
}


//Controla o botão de fechar das abas.
void MainWindow::closeFile(int index){

    std::list<Diagram*>::iterator it = diagrams.begin();
    std::advance(it,index);

    if((*it)->getStatus() == UNSAVED or (*it)->getStatus() == MODIFIED){
        QMessageBox::StandardButton b = QMessageBox::question(this, "CUIDADO", "Sair sem salvar?");
        if(b != QMessageBox::StandardButton::Yes)
            return;
    }

    diagrams.erase(it);
    delete (*it);
    tabs->removeTab(index);
}

//Menu de ajuda.
void MainWindow::tutorial(){
    QMessageBox::information(this,"Ajuda","Bem vindo ao CirucitSim - Simulador de Circuitos!");
    QMessageBox::information(this,"Ajuda","Vamos lhe ensinar como utilizar o simulador.");
    QMessageBox::information(this,"Ajuda","Na parte de cima encontram-se os menus.");
    QMessageBox::information(this,"Ajuda","O menu de arquivos lhe permite criar um novo projeto, "
                                          "salvá-lo ou abri-lo.");
    QMessageBox::information(this,"Ajuda","Ao lado, há o menu de preferências.");
    QMessageBox::information(this,"Ajuda","O menu de preferências lhe permite alterar o aspecto visual"
                                          " do programa.");
    QMessageBox::information(this,"Ajuda","Na parte inferior da tela, há uma barra de status.");
    statusBar->showMessage("Eu sou a barra de status!",3000);
    QMessageBox::information(this,"Ajuda","A barra de status fornece informações importantes acerca do programa, "
                                          "então, é recomendável ficar atento e observá-la.");
    QMessageBox::information(this,"Ajuda","Agora que você já sabe um pouco sobre o sistema de menus, "
                                          "vamos aprender sobre o sistema de construção de circuitos");
    QMessageBox::information(this,"Ajuda","Ao criar um novo arquivo, uma aba abrirá automáticamente.");
    QMessageBox::information(this,"Ajuda","Esta aba contém um plano de fundo quadriculado, onde os componentes "
                                          "podem ser inseridos.");
    QMessageBox::information(this,"Ajuda","Para se inserir um componente, se atente para a barra de ferramentas "
                                          "que se encontra no lado direito da tela.");
    QMessageBox::information(this,"Ajuda","Esta barra possui 4 botões, referentes aos componentes que podem "
                                          "ser inseridos.");
    QMessageBox::information(this,"Ajuda","Ao clicar em um destes botões, o componente é selecionado e basta clicar "
                                          "em um ponto da tela quadriculada para inseri-lo.");
    QMessageBox::information(this,"Ajuda","Para realizar uma conexão entre dois componentes, clique em uma das "
                                          "extremidades de um dos componentes e, em seguida, em uma das extremidades"
                                          " do outro componente.");
    QMessageBox::information(this,"Ajuda","Na parte inferior da tela, há dois botões, o botão play e o botão lápis.");
    QMessageBox::information(this,"Ajuda","Quando se desejar inserir, remover ou editar um componente, certifique-se "
                                          "de estar com o botão lápis selecionado.");
    QMessageBox::information(this,"Ajuda","Para editar ou remover um componente, clique neste com o botão direito do "
                                          "mouse e selecione a opção desejada.");
    QMessageBox::information(this,"Ajuda","Para consultar os valores do circuito, aperte o botão play, clique no "
                                          "componente desejado com o botão direito do mouse e selecione consultar."
                                          " Certifique-se de estar com o botão play selecionado.");
    QMessageBox::information(this,"Ajuda","O programa suporta múltiplas abas, permitindo editar vários circuitos de "
                                          "uma só vez.");
    QMessageBox::information(this,"Ajuda","Chegamos ao fim do tutorial e você, agora, está mais do que pronto para "
                                          "utilizar o CircuitSim! Esperamos que a experiência seja a melhor possível! "
                                          "Caso precise rever este tutorial, basta clicar no menu de ajuda.");
}

//Controla o botão de desenho de fonte vertical.
void MainWindow::drawVcc90(){
    if(tabs->count() == 0)
        return;

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    (*it)->setSelectedButton(VCC90);
}

//Controla o botão de desenho da fonte horizontal.
void MainWindow::drawVcc180(){
    if(tabs->count() == 0)
        return;

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    (*it)->setSelectedButton(VCC180);
}

//Controla o botão de desenho do resistor vertical.
void MainWindow::drawRes90(){
    if(tabs->count() == 0)
        return;

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    (*it)->setSelectedButton(RES90);
}

//Controla o botão de desenho do resistor horizontal.
void MainWindow::drawRes180(){
    if(tabs->count() == 0)
        return;

    int index = tabs->currentIndex();
    std::list<Diagram*>::iterator it = diagrams.begin();
    advance(it,index);

    (*it)->setSelectedButton(RES180);
}

//Carrega as configurações do programa
void MainWindow::loadConfig(){

    std::ifstream config;
    config.open("config.txt",std::ios::in);

    //Cria o arquivo de configurações caso ele não exista.
    if(not config.is_open()){
        saveConfig();
        return;
    }

    //Carrega as configurações.
    std::string hexCode;

    getline(config,hexCode);
    Diagram::setBGColor(QColor(hexCode.c_str()));

    getline(config,hexCode);
    Diagram::setGridColor(QColor(hexCode.c_str()));

    getline(config,hexCode);
    Diagram::setComponentColor(QColor(hexCode.c_str()));

    getline(config,hexCode);
    Diagram::setSelectedColor(QColor(hexCode.c_str()));

    config.close();
}

//Salva as configurações do programa.
void MainWindow::saveConfig(){

    std::ofstream config;
    config.open("config.txt",std::ios::out);

    if(not config.is_open()){
        return;
    }

    //Salva as configurações.
    QString hexCode;

    hexCode = Diagram::getBGColor().name();
    config<<hexCode.toStdString();
    config<<std::endl;

    hexCode = Diagram::getGridColor().name();
    config<<hexCode.toStdString();
    config<<std::endl;

    hexCode = Diagram::getComponentColor().name();
    config<<hexCode.toStdString();
    config<<std::endl;

    hexCode = Diagram::getSelectedColor().name();
    config<<hexCode.toStdString();
    config<<std::endl;

    config.close();
}

//Ação de mudança da cor do plano de fundo.
void MainWindow::setBGColor(){
    QColor color =QColorDialog::getColor(QColor(DEFAULT_BGC),this,"Selecione a cor para o plano de fundo");
    try{
        Diagram::setBGColor(color);
        saveConfig();
        statusBar->showMessage("Alterações salvas");
    }catch(std::string str){
        statusBar->showMessage(QString::fromStdString(str)+". As alterações não forma salvas");
    }
}

//Ação de mudança da cor da grade do plano de fundo.
void MainWindow::setGridColor(){
    QColor color =QColorDialog::getColor(QColor(DEFAULT_LC),this,"Selecione a cor para a grade");
    try{
        Diagram::setGridColor(color);
        saveConfig();
        statusBar->showMessage("Alterações salvas");
    }catch(std::string str){
        statusBar->showMessage(QString::fromStdString(str)+". As alterações não forma salvas");
    }

}

//Ação de mudança da cor dos componentes.
void MainWindow::setComponentColor(){

    QColor color =QColorDialog::getColor(QColor(DEFAULT_CC),this,"Selecione a cor para os componentes");
    try{
        Diagram::setComponentColor(color);
        saveConfig();
        statusBar->showMessage("Alterações salvas");
    }catch(std::string str){
        statusBar->showMessage(QString::fromStdString(str)+". As alterações não forma salvas");
    }
}

//Ação de mudança da cor de seleção dos componentes.
void MainWindow::setSelectedColor(){

    QColor color =QColorDialog::getColor(QColor(DEFAULT_SC),this,"Selecione a cor para a seleção");
    try{
        Diagram::setSelectedColor(color);
        saveConfig();
        statusBar->showMessage("Alterações salvas");
    }catch(std::string str){
        statusBar->showMessage(QString::fromStdString(str)+". As alterações não forma salvas");
    }
}

//Restaura as configurações padrão.
void MainWindow::resetConfig(){

    try{
        Diagram::setSelectedColor(DEFAULT_SC);
        Diagram::setComponentColor(DEFAULT_CC);
        Diagram::setGridColor(DEFAULT_LC);
        Diagram::setBGColor(DEFAULT_BGC);
        saveConfig();
        statusBar->showMessage("Configurações restauradas. Reinicie o programa para aplicá-las.");
    }catch(std::string str){
       statusBar->showMessage(QString::fromStdString(str)+". Não foi possível restaurar as configurações");
    }
}

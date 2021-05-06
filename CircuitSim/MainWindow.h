/********************************************************************************************
 * @file MainWindow.h
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 28 04 2021
 * @brief Declaração da classe MainWindow.
 * 
 * Este arquivo contém as delcarações dos métodos e membros da classe MainWindow, que 
 * representa a janela principal do programa. 
 * 
 * A classe MainWindow controla o fluxo de execução com base nas interações do usuário.
 *  
 ********************************************************************************************/

#ifndef MAINWIN_H
#define MAINWIN_H

#include "Diagram.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QString>
#include <QToolBar>
#include <QPushButton>


/******************************************************************************
 * Declaração da classe MainWindow.
 *
 * A classe MainWindow é implementada com o padrão signleton e controla o 
 * fluxo de execução do programa.
 ******************************************************************************/
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:

    /******************************************************************************
    * Construtor para a classe MainWindow.
    *
    * Constrói um objeto da classe MainWindow. O construtor é privatizado para
    * evitar que mais de um objeto da classe seja instanciado.
    * 
    * @param parent Objeto pai.
    * 
    ******************************************************************************/
    explicit MainWindow(QWidget *parent = nullptr);


    /******************************************************************************
    * Construtor de cópia para a classe MainWindow.
    * 
    * Privatiza o construtor de cópia para evitar que mais de um objeto da classe
    * MainWindow seja instanciado.
    ******************************************************************************/
    MainWindow(const MainWindow&);


    /******************************************************************************
    * Sobrescrita do operador = pra a classe MainWindow.
    *
    * Privatiza o operador = para evitar que mais de um objeto da classe 
    * MainWindow seja instanciado.
    ******************************************************************************/
    MainWindow operator=(MainWindow&);


    static MainWindow* instance; /**< Ponteiro estático para instância.*/

    std::list<Diagram*> diagrams; /**< Código hexadecimal para a cor padrão de seleção de componentes.*/

    QMenuBar *mainBar; /**< Barra de menus.*/

    QMenu *fileMenu; /**< Menu para manipulação de arquivos.*/
    QAction *openFileAct; /**< Ação para a abertura de arquivos.*/
    QAction *saveFileAct; /**< Ação para salvar um arquivo já criado.*/
    QAction *saveFileAsAct; /**< Ação para salvar um arquivo ainda não criado.*/
    QAction *newFileAct; /**< Ação para criar um novo arquivo.*/

    QMenu* prefMenu; /**< Menu para as preferências.*/
    QAction* setBGColorAct; /**< Ação para alterar a cor do plano de fundo.*/
    QAction* setGridColorAct; /**< Ação para alterar a cor da grade do plano de fundo.*/
    QAction* setComponentColorAct; /**< Ação para alterar a cor dos componentes.*/
    QAction* setSelectedColorAct; /**< Ação para alterar a cor de seleção dos componentes.*/
    QAction* resetConfigAct; /**< Ação para resetar as configurações padrão.*/

    QMenu *helpMenu; /**< Menu de ajuda.*/
    QAction *tutorialAct; /**< Ação para abrir o tutorial.*/
    
    QToolBar* toolbar; /**< Barra de ferramentas utilizada para inserir elementos na Classe Diagram.*/
    
    QStatusBar* statusBar; /**< Barra de status para informar atualizações.*/
    
    QTabWidget* tabs; /**< QTabWidget para controlar as abas do programa.*/

    /******************************************************************************
    * Método auxiliar para inicializar a barra de menus.
    *
    * Este método inicializa os componentes gráficos referentes à barra de menus.
    *
    * @return Void.
    ******************************************************************************/
    void initializeMenu();


   /******************************************************************************
    * Método auxiliar para inicializar a barra de ferramentas.
    *
    * Este método inicializa os componentes gráficos referentes à barra de 
    * ferramentas.
    *
    * @return Void.
    ******************************************************************************/
    void initializeToolbar();


    /******************************************************************************
    * Método auxiliar para inicializar o sistema de abas.
    *
    * Este método inicializa os componentes gráficos referentes ao sistema
    * de abas.
    *
    * @return Void.
    ******************************************************************************/
    void initializeTabs();


   /******************************************************************************
    * Método auxiliar para inicializar a barra de status.
    *
    * Este método inicializa os componentes gráficos referentes à barra de 
    * status.
    *
    * @return Void.
    ******************************************************************************/
    void initializeStatusBar();   


   /******************************************************************************
    * Carrega as configurações do programa.
    *
    * Este método faz a leitura do arquivo de configurações do programa e 
    * atualiza as informações do programa conforme o arquivo carregado.
    *
    * @return Void.
    ******************************************************************************/
    void loadConfig();


   /******************************************************************************
    * Salva as configurações do programa.
    *
    * Este método salva as configurações atuais em um arquivo de configuração.
    *
    * @return Void.
    ******************************************************************************/
    void saveConfig();

public:

   /******************************************************************************
    * Getter para a instância da classe MainWindow.
    *
    * Este método retorna um ponteiro para a instância para o singleton.
    *
    * @return Ponteiro para a instância do singleton.
    ******************************************************************************/
    static MainWindow* getMainWindow();


public slots:

   /******************************************************************************
    * Cria um novo objeto da classe Diagram.
    *
    * Este SLOT esta conectado com a ação referente à criação de um novo 
    * objeto da classe Diagram e adiciona uma nova aba contendo este objeto. 
    *
    * @return Void.
    ******************************************************************************/
    void newFile();


   /******************************************************************************
    * Abre um arquivo de projeto salvo anteriormente.
    *
    * Este SLOT esta conectado com a ação openFileAct. 
    * Carrega um projeto salvo anteriormente e adiciona à uma nova aba.
    *
    * @return Void.
    ******************************************************************************/
    void openFile();


   /******************************************************************************
    * Salva as alterações feitas no arquivo.
    *
    * Este SLOT esta conectado com a ação rsaveFileAct. Caso o projeto ja tenha 
    * sido salvo anteriormente, apenas assimila as alterações feitas ao arquivo. 
    * Caso arquivo ainda não tenha sido salvo, abre uma janela para a escolha do
    * nome e diretório do arquivo.
    *
    * @return Void.
    ******************************************************************************/
    void saveFile();


   /******************************************************************************
    * Salva o arquivo conforme as especificações do usuário.
    *
    * Este SLOT esta conectado com a ação saveFileAct. Abre uma janela para a
    * escolha do diretório e nome do arquivo em que se deseja salvar o projeto.
    *
    * @return Void.
    ******************************************************************************/
    void saveFileAs();


   /******************************************************************************
    * Altera o status da aba.
    *
    * Este SLOT esta conectado com a os sinais emitidos pela classe Diagram. 
    * Conforme o arquivo que contenha o diagrama for alterado, altera o nome
    * da aba para indicar se o arquivo tem alterações não salvas.
    * 
    * @param modified Valor booleano que indica se o objeto Diagram armazenado 
    * na aba foi modificado.
    *
    * @return Void.
    ******************************************************************************/
    void setTabStatus(bool modified);


   /******************************************************************************
    * Deleta uma aba e o objeto da classe Diagram associado à ela.
    *
    * Este SLOT esta conectado com o sinal de fechamento emitido pela aba,
    * deletando o objeto caso este já tenha sido salvo, caso contrário, pede
    * ao usuário se este deseja sair ou salvar as modificações não salvas.
    * 
    * @param modified Índice da aba a ser fechada.
    *
    * @return Void.
    ******************************************************************************/
    void closeFile(int index);


   /******************************************************************************
    * Seleciona o objeto a ser inserido em um objeto da classe Diagram.
    *
    * Este SLOT esta conectado com o sinal do botão de resistor vertical da 
    * barra de ferramentas. Ao clicar no botão, seleciona o componente desejado
    * na aba atual.
    *
    * @return Void.
    ******************************************************************************/
    void drawRes90();


   /******************************************************************************
    * Seleciona o objeto a ser inserido em um objeto da classe Diagram.
    *
    * Este SLOT esta conectado com o sinal do botão de resistor horizontal da 
    * barra de ferramentas. Ao clicar no botão, seleciona o componente desejado
    * na aba atual.
    *
    * @return Void.
    ******************************************************************************/
    void drawRes180();


   /******************************************************************************
    * Seleciona o objeto a ser inserido em um objeto da classe Diagram.
    *
    * Este SLOT esta conectado com o sinal do botão de Fonte vertical da 
    * barra de ferramentas. Ao clicar no botão, seleciona o componente desejado
    * na aba atual.
    *
    * @return Void.
    ******************************************************************************/
    void drawVcc90();


   /******************************************************************************
    * Seleciona o objeto a ser inserido na classe Diagram.
    *
    * Este SLOT esta conectado com o sinal do botão de Fonte horizontal da 
    * barra de ferramentas. Ao clicar no botão, seleciona o componente desejado
    * na aba atual.
    *
    * @return Void.
    ******************************************************************************/
    void drawVcc180();


   /******************************************************************************
    * Seleciona a cor do plano de fundo dos objetos da classe Diagram.
    *
    * Este SLOT esta conectado com o sinal do setBGColorAct do menu de 
    * preferências. Abre uma janela para seleção da cor desejada e salva no 
    * arquivo de configurações.
    *
    * @return Void.
    ******************************************************************************/
    void setBGColor();


   /******************************************************************************
    * Seleciona a cor da grade do plano de fundo dos objetos da classe Diagram.
    *
    * Este SLOT esta conectado com o sinal do setGridColorAct do menu de 
    * preferências. Abre uma janela para seleção da cor desejada e salva no 
    * arquivo de configurações.
    *
    * @return Void.
    ******************************************************************************/
    void setGridColor();


   /******************************************************************************
    * Seleciona a cor dos componentes dos objetos da classe Diagram.
    *
    * Este SLOT esta conectado com o sinal do setComponentColorAct do menu de 
    * preferências. Abre uma janela para seleção da cor desejada e salva no 
    * arquivo de configurações.
    *
    * @return Void.
    ******************************************************************************/
    void setComponentColor();


   /******************************************************************************
    * Seleciona a cor de seleção dos componentes dos objetos da classe Diagram.
    *
    * Este SLOT esta conectado com o sinal do setSelectedColorAct do menu de 
    * preferências. Abre uma janela para seleção da cor desejada e salva no 
    * arquivo de configurações.
    *
    * @return Void.
    ******************************************************************************/
    void setSelectedColor();


    /******************************************************************************
    * Reseta as configurações do programa para os valores padrão.
    *
    * Este SLOT esta conectado com o sinal do resetConfigAct do menu de 
    * preferências. Reseta o arquivo de configurações para os valores padrão.
    *
    * @return Void.
    ******************************************************************************/
    void resetConfig();


};

#endif // MAINWIN_H

/********************************************************************************************
 * @file Diagram.h
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 30 04 2021
 * @brief Declaração da classe Numeric.
 * 
 * Este arquivo contém as delcarações dos métodos e membros da classe Diagram.
 * 
 * A classe Diagram fornece as facilidades para inserir objetos da classe GraphicsComponent
 * graficamente, identificar as interações do usuário com estes objetos, bem como,
 * interligar a implementação gráfica com a parte numérica.
 *  
 ********************************************************************************************/

#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "Circuit.h"
#include "Graph.h"
#include "GraphicComponent.h"

#include <QWidget>
#include <QObject>
#include <QScrollBar>
#include <QPushButton>
#include <QScrollArea>
#include <QMouseEvent>
#include <stack>
#include <QMessageBox>
#include <QPropertyAnimation>


/** @defgroup Grupo1 Cores padrão
 *  Definição as macros para os códigos hexadecimais de cores padrão do tema do programa.
 *  @{
 */
#define DEFAULT_BGC "#272947" /**< Código hexadecimal para a cor padrão do plano de fundo.*/
#define DEFAULT_LC "#141516" /**< Código hexadecimal para a cor padrão da grade do plano de fundo.*/
#define DEFAULT_CC "#FFFFFF" /**< Código hexadecimal para a cor padrão dos componentes.*/
#define DEFAULT_SC "#0AA206" /**< Código hexadecimal para a cor padrão de seleção de componentes.*/
/** @} */


/***************************************************************
 *  Fornece uma identificação para os estilos de componentes
 * que podem ser inseridos.
 * 
 * Esta enumeração é utilizada em vários métodos ao longo
 * do código, com o intuito de identificar o estilo a ser
 * desenhado na tela.
 * 
 **************************************************************/
enum cmpStyle{
    VCC90, /**< Fonte de tensão vertical.*/
    VCC180, /**< Fonte de tensão horizontal.*/
    RES90, /**< Resistor vertical.*/
    RES180, /**< Resistor horizontal.*/
    NONE /**< Nenhum estilo selecionado.*/
    }; 

/***************************************************************
 * Fornece uma identificação para o estado atual do arquivo
 * que contém um objeto da classe Diagram. 
 * 
 * Esta enumeração é utilizada em vários métodos ao longo
 * do código, com o intuito de identificar o estado atual
 * do arquivo.
 * 
 **************************************************************/    
enum stats{
    UNSAVED, /**< Arquivo não salvo.*/
    MODIFIED, /**< Arquivo modificado.*/
    OK, /**< Arquivo salvo.*/
    ERROR /**< Erro de abertura de arquivo.*/
    };


/***************************************************************
 * Fornece uma identificação para o modo de atual do Diagrama.
 * 
 * Esta enumeração é utilizada em vários métodos ao longo
 * do código, com o intuito de identificar o modo de atuação
 * do diagrama.
 * 
 **************************************************************/ 
enum mode{
    EDIT, /**< Modo de edição.*/
    QUERY /**< Modo de consulta.*/
}; 


/******************************************************************************
 * Declaração da classe Diagram.
 *
 * Diagram herda da classe QWidget. Atua como uma inteface gráfica para a
 * utilização dos métodos da classe Circuit.
 ******************************************************************************/
class Diagram : public QWidget
{
    Q_OBJECT
private:

    CCT::Circuit circuit; /**< Representa o circuito do diagrama.*/

    std::string fileName; /**< Representa o nome do arquivo do diagrama.*/

    enum stats status; /**< Representa o estado atual do arquivo do diagrama.*/
    enum mode mode; /**< Representa o modo atual do diagrama (QEURY/EDIT).*/
    enum cmpStyle selectedButton; /**< Representa o botão selecionado.*/

    QPushButton* playButton; /**< Representa o botão play (entra em modo de consulta).*/
    QPushButton* editButton; /**< Representa o botão edit (entra em modo de edição).*/

    std::vector<GraphicComponent*> drawList; /**< Lista de componentes que devem ser desenhados na tela.*/

    GraphicComponent* selectedComponent; /**< Representa o componente atualmente selecionado.*/

    GRF::adjacencyMatrix connections; /**< Grafo que armazena as conexões entre os vértices dos componentes.*/

    unsigned int wireCounter; /**< Contador para a quantidade de cabos inseridos.*/
    unsigned int vtxCounter; /**< Contador para a quantidade de vértices inseridos.*/

    QMenu* editMenu; /**< Menu de edição.*/
    QMenu* queryMenu; /**< Menu de consulta.*/

    QPoint cursorLocation; /**< Armazena a posição do cursor do mouse.*/
    QPoint selectedPrev; /**< Armazena o último ponto selecionado.*/

    std::stack<std::pair<int,GraphicComponent*>> clickedStack; /**< Pilha que armazena o último
                                                                    componente selecionado.*/

    static QColor backgroundColor; /**< Membro estático que armazena a cor do plano
                                        de fundo dos objetos da classe Diagram.*/
    static QColor gridColor; /**< Membro estático que armazena a cor da grade do plano
                                   de fundo dos objetos da classe Diagram.*/
    static QColor componentColor; /**< Membro estático que armazena a cor dos componentes
                                        dos objetos da classe Diagram.*/
    static QColor selectedColor; /**< Membro estático que armazena a cor de seleção
                                      dos componentes dos objetos da classe Diagram.*/

   /******************************************************************************
    * Método que inicializa os elementos gráficos da classe Diagram.
    *
    * Este método inicializa os elementos gráficos da classe Diagram, tais como
    * menus e botões.
    *
    * @return Void.
    ******************************************************************************/
    void initializeDiagram();


   /******************************************************************************
    * Setter para o status do arquivo do objeto da classe Diagram.
    *
    * Este método altera o estado do arquivo que contém o diagrama.
    *
    * @param newStatus Novo estado do arquivo.
    *
    * @return Void.
    ******************************************************************************/
    void setStatus(enum stats newStatus);


   /******************************************************************************
    * Controla as ações referentes ao clique sobre componentes.
    *
    * Este método controla as ações ao se clicar em um componente com o botão
    * esquerdo no modo de edição.
    *
    * @param x Coordenada x do clique do mouse.
    * @param y Coordenada y do clique do mouse.
    * @param cArea Representa a área do componente que foi clicada (Área
    * correspondente ao vértice 1 ou vértice 2).
    *
    * @return Void.
    ******************************************************************************/
    void clickedControl(int x, int y, int cArea);


   /******************************************************************************
    * Getter para o pixMap de um dos tipos de representações gráficas dos
    * componentes.
    *
    * Este método retorna um std::pair contendo o retângulo que limita a área
    * do componente e o pixMap de uma das representações gráficas dos componentes
    * disponíveis.
    *
    * @param type Estilo do componente.
    *
    * @return std::pair contendo o retângulo que limita a área do componente e o
    * pixMap da representação gráfica do componente.
    ******************************************************************************/
    std::pair<QRect,QPixmap>getPixMap(enum cmpStyle type);


    /******************************************************************************
     * Método executado quando o o botão direito do mouse é pressionado.
     *
     * Este método controla as possíveis interações com os componentes gráficos
     * quando o botão direito do mouse é pressionado sobre um destes.
     *
     * @param x Coordenada x do clique do mouse.
     * @param y Coordenada y do clique do mouse.
     * @param cArea Representa a área do componente que foi clicada (Área
     * correspondente ao vértice 1 ou vértice 2).
     *
     * @return Void.
     ******************************************************************************/
     void rightButtonClicked(int x, int y, int cArea);


    /******************************************************************************
     * Método executado quando o o botão esquerdo do mouse é pressionado.
     *
     * Este método controla as possíveis interações com os componentes gráficos
     * quando o botão esquerdo do mouse é pressionado sobre um destes.
     *
     * @param x Coordenada x do clique do mouse.
     * @param y Coordenada y do clique do mouse.
     * @param cArea Representa a área do componente que foi clicada (Área
     * correspondente ao vértice 1 ou vértice 2).
     *
     * @return Void.
     ******************************************************************************/
     void leftButtonClicked(int x, int y, int cArea);

protected:

   /******************************************************************************
    * Sobrescrita do método paintEvent.
    *
    * Este método desenha a interface gráfica referente à área de desenho do
    * circuito.
    *
    * @return Void.
    ******************************************************************************/
    void paintEvent(QPaintEvent* event) override;


   /******************************************************************************
    * Sobrescrita do método mousePressEvent.
    *
    * Este método identifica o clique do mouse.
    *
    * @return Void.
    ******************************************************************************/
    void mousePressEvent(QMouseEvent* event) override;


   /******************************************************************************
    * Sobrescrita do método mouseMovePressEvent.
    *
    * Este método identifica o movimento do mouse.
    *
    * @return Void.
    ******************************************************************************/
    void mouseMoveEvent(QMouseEvent* event) override;

public:

   /******************************************************************************
    * Construtor para a classe Diagram.
    *
    * @param parent Pai do objeto.
    * 
    * Constrói um objeto da classe Diagram.
    ******************************************************************************/
    explicit Diagram(QWidget *parent = nullptr);


   /******************************************************************************
    * Getter para o nome do arquivo que contém o objeto.
    *
    * Retorna o nome do arquivo em que o diagrama está salvo.
    *
    * @return Nome do arquivo que contém o diagrama.
    ******************************************************************************/
    QString getFileName();


   /******************************************************************************
    * Setter para o nome do arquivo que contém o objeto.
    *
    * Altera o nome do arquivo que contém o diagrama.
    *
    * @param file Nome do arquivo.
    *
    * @return Void.
    ******************************************************************************/
    void setFileName(QString file);


   /******************************************************************************
    * Salva os dados cruciais do objeto da classe Diagram.
    *
    * Salva os dados necessários do objeto e dependências no arquivo que contém
    * o objeto.
    *
    * @return Void.
    ******************************************************************************/
    void save();


   /******************************************************************************
    * Carrega os dados previamente salvos para um objeto da classe Diagram.
    *
    * Lê os dados armazenados previamente um arquivo e transcreve estes dados
    * para um objeto da classe Diagram e dependências.
    *
    * @return Void.
    ******************************************************************************/
    void load();


   /******************************************************************************
    * Getter para o status do arquivo de um objeto da classe Diagram.
    *
    * Retorna o status atual do arquivo.
    *
    * @return Status atual do arquivo.
    ******************************************************************************/
    enum stats getStatus();


   /******************************************************************************
    * Setter para o botão selecionado na barra de ferramentas.
    *
    * Retorna o status atual do arquivo.
    *
    * @param button Botão pressionado na barra de ferramentas.
    *
    * @return Void.
    ******************************************************************************/
    void setSelectedButton(enum cmpStyle button);


   /******************************************************************************
    * Insere um componente em um objeto da classe Diagram.
    *
    * Insere um objeto gaficamente na janela e no membro da classe Circuit do
    * diagrama.
    *
    * @param x Coordenada x para inserção gráfica do componente.
    * @param y Coordenada y para inserção gráfica do componente.
    *
    * @return Void.
    ******************************************************************************/
    void insert(int x, int y);


   /******************************************************************************
    * Setter da cor do plano de fundo dos objetos da classe Diagram.
    *
    * Método estático para alterar a cor do plano de fundo de todos os objetos
    * ativos e que serão criados da classe Diagram.
    *
    * @param color Cor para o plano de fundo.
    *
    * @return Void.
    ******************************************************************************/
    static void setBGColor(QColor color);

   /******************************************************************************
    * Setter da cor da grade do plano de fundo dos objetos da classe Diagram.
    *
    * Método estático para alterar a cor da grade do plano de fundo de todos os
    * objetos ativos e que serão criados da classe Diagram.
    *
    * @param color Cor para a grade do plano de fundo.
    *
    * @return Void.
    ******************************************************************************/
    static void setGridColor(QColor color);


   /******************************************************************************
    * Setter da cor dos componentes dos objetos da classe Diagram.
    *
    * Método estático para alterar a cor dos componentes de todos os objetos
    * ativos e que serão criados da classe Diagram.
    *
    * @param color Cor para a grade do plano de fundo.
    *
    * @return Void.
    ******************************************************************************/
    static void setComponentColor(QColor color);


   /******************************************************************************
    * Setter da cor de seleção dos components dos objetos da classe Diagram.
    *
    * Método estático para alterar a cor de seleção de componentes de todos os
    * objetos ativos e que serão criados da classe Diagram.
    *
    * @param color Cor para a seleção de componentes.
    *
    * @return Void.
    ******************************************************************************/
    static void setSelectedColor(QColor color);


    /******************************************************************************
     * Getter para a cor do plano de fundo dos objetos da classe Diagram.
     *
     * Método estático que retorna a cor do plano de fundo de todos os objetos
     * ativos e que serão criados da classe Diagram.
     *
     * @return Cor do plano de fundo.
     ******************************************************************************/
     static QColor getBGColor();


    /******************************************************************************
     * getter da cor da grade do plano de fundo dos objetos da classe Diagram.
     *
     * Método estático que retorna a cor da grade do plano de fundo de todos os
     * objetos ativos e que serão criados da classe Diagram.
     *
     * @return Cor da grade do plano de fundo.
     ******************************************************************************/
     static QColor getGridColor();


    /******************************************************************************
     * Getter da cor dos componentes dos objetos da classe Diagram.
     *
     * Método estático que retorna a cor dos componentes de todos os objetos
     * ativos e que serão criados da classe Diagram.
     *
     * @return Cor dos componentes.
     ******************************************************************************/
     static QColor getComponentColor();


    /******************************************************************************
     * Setter da cor de seleção dos components dos objetos da classe Diagram.
     *
     * Método estático que retorna a cor de seleção de componentes de todos os
     * objetos ativos e que serão criados da classe Diagram.
     *
     * @return Cor de seleção dos componentes.
     ******************************************************************************/
     static QColor getSelectedColor(void);

signals:

    /******************************************************************************
     * Sinal emitido quando o diagrama é modificado.
     *
     * O sinal emite true assim que um componente é inserido na tela ou uma
     * conexão é feita.
     *
     * @param checked Valor booleano indicando se o diagrama foi modificado.
     *
     * @return Void.
     ******************************************************************************/
    void modified(bool checked = false);


   /******************************************************************************
    * Sinal emitido quando um erro de abertura de arquivo ocorre.
    *
    * O sinal emite true assim que ocorre erro na abertura de algum arquivo,
    * seja no processo de carregamento ou de salvamento.
    *
    * @param checked Valor booleano indicando se houve erro na abertura de um
    * arquivo.
    *
    * @return Void.
    ******************************************************************************/
    void loadError(bool checked = false);


   /******************************************************************************
    * Sinal emitido quando a classe Diagram necessita exibir uma mensagem na
    * barra de status da janela principal.
    *
    * O sinal emite a string que deve ser exibida na barra de status é emitido
    * assim que a classe entra no modo de edição ou modo de consulta.
    *
    * @param str String a ser exibida na barra de status.
    *
    * @return Void.
    ******************************************************************************/
    void statusBarText(QString str);

public slots:

   /******************************************************************************
    * Ativa o modo de Consulta para o circuito representado no diagrama.
    *
    * O SLOT é conectado com o sinal emitido pelo botão play. Assim que o botão
    * é pressionado, o programa entra em modo de consulta.
    *
    * @return Void.
    ******************************************************************************/
    void queryMode();


   /******************************************************************************
    * Ativa o modo de Edição para o circuito representado no diagrama.
    *
    * O SLOT é conectado com o sinal emitido pelo botão edit. Assim que o botão
    * é pressionado, o programa entra em modo de Edição.
    *
    * @return Void.
    ******************************************************************************/
    void editMode();


   /******************************************************************************
    * Ativa a dialog de edição.
    *
    * O SLOT é conectado com o sinal emitido pelo menu de edição. Quando o menu
    * de edição é selecionado, uma janela para a edição do valor associado ao
    * componente é exibida.
    *
    * @return Void.
    ******************************************************************************/
    void showEditDialog();


   /******************************************************************************
    * Altera o valor do componente selecionado.
    *
    * O SLOT é conectado com o sinal emitido pelo menu de edição. Quando o menu
    * de edição é selecionado, uma janela para a edição do valor associado ao
    * componente é exibida.
    *
    * @param newValue Novo valor associado ao componente.
    *
    * @return Void.
    ******************************************************************************/
    void edit(double newValue);


   /******************************************************************************
    * Remove o componente selecionado do circuito.
    *
    * O SLOT é conectado com o sinal emitido pelo menu de remoção. Quando o menu
    * de remoção é selecionado, o componente é removido do circuito e sua
    * representação gráfica é removida da tela.
    *
    * @return Void.
    ******************************************************************************/
    void remove();


    /******************************************************************************
     * Consulta os dados obtidos após a solução do circuito.
     *
     * O SLOT é conectado com o sinal emitido pelo menu de consulta. Quando o menu
     * de consulta é selecionado, os dados acerca do componente são exibidos na
     * tela.
     *
     * @return Void.
     ******************************************************************************/
     void query();
};

#endif // DIAGRAM_H

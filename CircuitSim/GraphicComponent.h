/********************************************************************************************
 * @file GraphicComponent.h
 * @authors: Lucas Carvalho; Rafael Marasca Martins
 * @date: 30 04 2021
 * @brief Declaração da classe GraphicComponent para a inserção gráfica de componentes.
 * 
 * Este arquivo contém as delcarações necessárias para se inserir componentes graficamente
 * em um objeto da classe Diagram.
 *  
 ********************************************************************************************/

#ifndef GRAPHICCOMPONENT_H
#define GRAPHICCOMPONENT_H

#include "Graph.h"
#include "Component.h"

#include <QObject>
#include <QRect>
#include <QPoint>
#include <QPainter>


/** @defgroup Grupo2 Tamanho dos Componentes
 *  Definição as macros para os tamanhos dos desenhos dos componentes na tela.
 *  @{
 */
#define HEIGHT 115
#define WIDTH 50
/** @} */


/**********************************************************************
 * Fornece uma identificação para a orientação do desenho do 
 * componente.
 * 
 * Esta enumeração é utilizada em vários métodos ao longo do código, 
 * com o intuito de identificar o estilo a ser desenhado na tela.
 *********************************************************************/
enum orien{
    VERTICAL, /**< Orientação vertical.*/
    HORIZONTAL /**< Orientação horizontal.*/
    };


/**********************************************************************************
 * Declaração da classe GraphicComponent.
 *
 * Herda da classe QObject. Implementa a representação gráfica de um componente e
 * permite a interação do usuário com estes objetos gráficos.
 **********************************************************************************/
class GraphicComponent : public QObject
{
    Q_OBJECT
protected:
    int x; /**< Coordenada x do desenho.*/
    int y; /**< Coordenada y do desenho.*/

    QRect vertexArea1; /**< Retângulo representando a área clicável referente ao vértice 1 do componente.*/
    QRect vertexArea2; /**< Retângulo representando a área clicável referente ao vértice 2 do componente.*/

    QRect boundRect; /**< Retângulo representando a área para desenho do componente.*/
    QPixmap map; /**< Pixmap para desenho do componente.*/

    unsigned int vertex1; /**< Aramazena o vértice 1 do componente.*/
    unsigned int vertex2; /**< Aramazena o vértice 2 do componente.*/

    CMP::type componentType; /**< Aramazena o tipo do componente.*/
    
    QString label; /**< Aramazena o nome de identificação do componente.*/

    double value; /**< Aramazena o valor associado ao componente.*/

    enum orien orientation; /**< Aramazena a orientação do componente.*/

public :

   /******************************************************************************
    * Construtor para a classe GraphicComponent.
    *  
    * Constrói um objeto da classe GraphicComponent. O sentido assumido para a 
    * corrente é saindo de vtx1 em direção a vtx2. 
    * 
    * @param x Coordenada x para a inserção do componente.
    * @param y Coordenada y para a inserção do componente.
    * @param vtx1 Vértice de saída .
    * @param vtx2 Vértice de entrada.
    * @param s Orientação do desenho.
    * @param parent Pai do objeto.
    ******************************************************************************/
    explicit GraphicComponent(int x, int y,  unsigned int vtx1, unsigned int vtx2,
                              enum orien s, QObject *parent = nullptr);


   /******************************************************************************
    * Identifica a área do componente que foi clicada.
    *  
    * Identifica qual o vértice foi clicado com base na área clicável do 
    * componente.
    * 
    * @param x Coordenada x clicada pelo mouse.
    * @param y Coordenada y clicada pelo mouse.
    * 
    * @return Número do vértice clicado.
    ******************************************************************************/         
    int clickedArea(int x, int y);


   /******************************************************************************
    * Desenha o componente na área do diagrama.
    *  
    * Cada objeto tem um modo único de se desenhar. Dessa forma, é conveniente
    * "pedir" ao objeto para se desenhar na tela.
    * 
    * @param painter Ponteiro par ao painter do diagrama.
    * @param color Cor do desenho.
    * 
    * @return Void.
    ******************************************************************************/  
    void draw(QPainter* painter,QColor color= QColor());


   /******************************************************************************
    * Getter para a altura do componente.
    *  
    * Retorna a altura do componente em pixels.
    * 
    * @return Altura do componente.
    ******************************************************************************/  
    int getHeight();


    /******************************************************************************
    * Getter para a largura do componente.
    *  
    * Retorna a largura do componente em pixels.
    * 
    * @return Largura do componente.
    ******************************************************************************/ 
    int getWidth();


    /******************************************************************************
    * Getter para o ponto inferior do componente.
    *  
    * Retorna o ponto Inferior localizado no eixo de simetria vertical do 
    * componente.
    * 
    * @return Ponto inferior do componente.
    ******************************************************************************/ 
    QPoint getBottom();


   /******************************************************************************
    * Getter para o ponto superior do componente.
    *  
    * Retorna o ponto superior localizado no eixo de simetria vertical do 
    * componente.
    * 
    * @return Ponto superior do componente.
    ******************************************************************************/ 
    QPoint getTop();


   /******************************************************************************
    * Getter para o ponto da esquerda do componente.
    *  
    * Retorna o ponto lateral esquerdo localizado no eixo de simetria horizontal
    * do componente.
    * 
    * @return Ponto esquerdo do componente.
    ******************************************************************************/ 
    QPoint getLeft();


   /******************************************************************************
    * Getter para o ponto da direita do componente.
    *  
    * Retorna o ponto lateral direito localizado no eixo de simetria horizontal
    * do componente.
    * 
    * @return Ponto direito do componente.
    ******************************************************************************/ 
    QPoint getRight();


    /******************************************************************************
    * Getter para o retângulo limitante do componente.
    *  
    * Retorna o retângulo que define a área de desenho do componente.
    * 
    * @return Retângulo limitante.
    ******************************************************************************/ 
    QRect getBoundRect();


    /******************************************************************************
    * Getter para a oritentação do compoenente.
    *  
    * Retorna a orientação do componente em questão.
    * 
    * @return Orientação do componente.
    ******************************************************************************/ 
    enum orien getOrientation();


    /******************************************************************************
    * Setter para o vértice 1 do componente.
    *  
    * Altera o número do vértice 1 do componente.
    * 
    * @param vtx Novo número de identificação para o vértice.
    * 
    * @return Void.
    ******************************************************************************/ 
    void setVertex1(unsigned int vtx);


   /******************************************************************************
    * Setter para o vértice 2 do componente.
    *  
    * Altera o número do vértice 2 do componente.
    * 
    * @param vtx Novo número de identificação para o vértice.
    * 
    * @return Void.
    ******************************************************************************/ 
    void setVertex2(unsigned int vtx);


   /******************************************************************************
    * Getter para o vértice 1 do componente.
    *  
    * Retorna  o número do vértice 1 do componente.
    * 
    * @return Vértice 1 do componente.
    ******************************************************************************/ 
    unsigned int getVertex1();


   /******************************************************************************
    * Getter para o vértice 2 do componente.
    *  
    * Retorna  o número do vértice 2 do componente.
    * 
    * @return Vértice 2 do componente.
    ******************************************************************************/ 
    unsigned int getVertex2();


   /******************************************************************************
    * Getter para o nome de identificação do componente.
    *  
    * Retorna o nome de identificação do componente.
    * 
    * @return Nome de identificação do componente.
    ******************************************************************************/ 
    std::string getLabel();


   /******************************************************************************
    * Getter para o tipo do componente.
    *  
    * Método virtual puro que retorna o tipo do componente.
    * 
    * @return tipo do componente.
    ******************************************************************************/ 
    virtual CMP::type getType() = 0;


   /******************************************************************************
    * Getter para o valor associado ao componente.
    *  
    * Retorna o valor associado ao componente consultado.
    * 
    * @return Valor do componente.
    ******************************************************************************/ 
    double getValue();


   /******************************************************************************
    * Setter para o valor associado ao componente.
    *  
    * Altera o valor associado ao componente.
    * 
    * @param newValue Novo valor do componente.
    * 
    * @return Void.
    ******************************************************************************/ 
    void setValue(double newValue);


   /******************************************************************************
    * Getter para o ponto do vértice 1 do componente.
    *  
    * Retorna o ponto no eixo de simetria (horizontal ou vertical) referente ao
    * vértice 1 do componente.
    * 
    * @return Ponto do vértice 1 do componente.
    ******************************************************************************/ 
    QPoint getVertex1Point();


   /******************************************************************************
    * Getter para o ponto do vértice 2 do componente.
    *  
    * Retorna o ponto no eixo de simetria (horizontal ou vertical) referente ao
    * vértice 2 do componente.
    * 
    * @return Ponto do vértice 2 do componente.
    ******************************************************************************/ 
    QPoint getVertex2Point();


   /******************************************************************************
    * Atualiza o nome de identificação do componente.
    *  
    * Este método é utilizado para alterar o nome e evitar colisões ao se remover
    * um componente da classe Diagram.
    * 
    * @return Void.
    ******************************************************************************/ 
    void updateName();
};



/**********************************************************************************
 * Declaração da classe Resistor.
 *
 * Herda da classe Resistor. Implementa a representação gráfica de um 
 * resistor e permite a interação do usuário com este objeto gráfico.
 **********************************************************************************/
class Resistor : public GraphicComponent
{
    Q_OBJECT
public:

/******************************************************************************
    * Construtor para a classe Resistor.
    *  
    * Constrói um objeto da classe Resistor. O sentido assumido para a 
    * corrente é saindo de vtx1 em direção a vtx2. 
    * 
    * @param x Coordenada x para a inserção do componente.
    * @param y Coordenada y para a inserção do componente.
    * @param vtx1 Vértice de saída .
    * @param vtx2 Vértice de entrada.
    * @param s Orientação do desenho.
    * @param parent Pai do objeto.
    ******************************************************************************/
    explicit Resistor(int x, int y,  unsigned int vtx1, unsigned int vtx2,
                      enum orien s = VERTICAL, QObject *parent = nullptr);


   /******************************************************************************
    * Getter para o tipo do componente.
    *  
    * Sobrescrita do método virtual puro da classe base que retorna o tipo do 
    * componente. 
    * 
    * @return CMP::RESISTOR.
    ******************************************************************************/                   
    CMP::type getType();
signals:

};


/**********************************************************************************
 * Declaração da classe Vcc.
 *
 * Herda da classe Vcc. Implementa a representação gráfica de uma fonte e permite 
 * a interação do usuário com este objeto gráfico.
 **********************************************************************************/
class Vcc : public GraphicComponent
{
    Q_OBJECT
    static unsigned int vccCounter;
public:

    /******************************************************************************
    * Construtor para a classe Vcc.
    *  
    * Constrói um objeto da classe Vcc. O sentido assumido para a corrente é 
    * saindo de vtx1 em direção a vtx2. 
    * 
    * @param x Coordenada x para a inserção do componente.
    * @param y Coordenada y para a inserção do componente.
    * @param vtx1 Vértice de saída .
    * @param vtx2 Vértice de entrada.
    * @param s Orientação do desenho.
    * @param parent Pai do objeto.
    ******************************************************************************/
    explicit Vcc(int x, int y,  unsigned int vtx1, unsigned int vtx2,
                 enum orien s = VERTICAL,QObject *parent = nullptr);


    /******************************************************************************
    * Getter para o tipo do componente.
    *  
    * Sobrescrita do método virtual puro da classe base que retorna o tipo do 
    * componente. 
    * 
    * @return CMP::VCC.
    ******************************************************************************/              
    CMP::type getType();

};

#endif // GRAPHICCOMPONENT_H

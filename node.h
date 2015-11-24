#ifndef NODE
#define NODE
#include <QDebug>
#include <QObject>

class Node{

public:
    uchar m_content;  //conteúdo
    int m_freq;       //frequencia
    Node* m_left;     //nó da esquerda
    Node* m_right;    //nó da direita

    Node(){
       m_freq = 0;
       m_left = NULL;
       m_right = NULL;
    }

    Node(uchar content, int freq, Node* left, Node* right){
        m_content = content;
        m_freq = freq;
        m_left = left;
        m_right = right;
    }

    //Retorna se o nó é folha
    bool NodeisLeaf(){
        if(m_left == NULL && m_right == NULL){

            return true;
        }

        return false;
    }

    //Exibe a arvore
    QString TreeDisplay(int num, Node* n){
        QString tmp;
        tmp += QString("   ").repeated(num);
        tmp.append(n->m_content).append('\n');

        if(n->NodeisLeaf()){
            return tmp;
        }

        else{
            tmp.insert(0,TreeDisplay(num + 1, n->m_right));
            tmp.append(TreeDisplay(num + 1, n->m_left));
            return tmp;
        }
    }
};

#endif // NODE

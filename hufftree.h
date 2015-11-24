#ifndef HUFFTREE_H
#define HUFFTREE_H
#include "node.h"
#include <QList>
#include <QByteArray>
#include <iostream>
#include <QPair>
#include <QHash>


class HuffTree
{
    Node* m_root;
    Node* m_current;
    //ordena a lista
    QList<Node*> insort(const QList<Node*> mylist);
    QPair<Node*,int >recursive(QByteArray TreeRepresetation, int pos);

public:
    HuffTree();
    HuffTree(Node* root);
    ~HuffTree();

    //constroi a arvore
    void buildHuffTree(int *array);

    //cria a representação da arvore
    QByteArray representation();

    //retorna a codificação de um caractere na arvore
    QByteArray code(const uchar cont);

    //lista as codificações de todos os caracteres do arquivo
    QHash<uchar, QByteArray> codeRef(int *array);

    void Rebuild(QByteArray TreeRepresentation);

    void showHuffTree();

    void ToLeft();

    void Toright();

    void ToRoot();

    bool transverse(bool value);
    Node *current() const;
    void setCurrent();
};

#endif // HUFFTREE_H

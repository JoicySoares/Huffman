#include "hufftree.h"

HuffTree::HuffTree()
{
    m_root = new Node();
}
HuffTree::HuffTree(Node *root)
{
     m_root = root;
}

HuffTree::~HuffTree()
{
    delete this;
}
//Cria a árvore de huffman
void HuffTree::buildHuffTree(int *array){

    QList<Node* > nodeList;

    for(int i = 0; i<256; ++i){
        if(array[i] != 0){
            Node* tmp = new Node(i, array[i], NULL, NULL);
            nodeList.append(tmp);

        }
    }

    while(nodeList.size() > 1){
        nodeList = insort(nodeList);
        Node* left = nodeList.at(0);
        Node* right = nodeList.at(1);
        Node* aux = new Node(0x2A, left->m_freq + right->m_freq, left, right);
        nodeList.removeFirst();
        nodeList.removeFirst();
        nodeList.prepend(aux);
    }

    m_root = nodeList.at(0);
    showHuffTree();
}
//Representação da árvore
QByteArray HuffTree::representation(){
    QByteArray aux;
    if(m_root == 0) return "";

       if(m_root->NodeisLeaf()){
           if(m_root->m_content == 0x28 || m_root->m_content == 0x2A) aux.append(0x2A);
           aux.append(m_root->m_content);
       }
        else{

            HuffTree* sub1 = new HuffTree(m_root->m_left);
            HuffTree* sub2 = new HuffTree(m_root->m_right);

            aux.append('(').append(sub1->representation()).append(sub2->representation());

        }
    return aux;
}

Node *HuffTree::current() const
{
    return m_current;
}

void HuffTree::setCurrent()
{
    m_current = m_root;
}

//Ordena a lista
QList<Node*> HuffTree::insort(const QList<Node*> mylist){
    QList<Node*> list = mylist;

    for(int i = 0; i< list.size() - 1; ++i){
         for(int j=i+1; j< list.size(); ++j){
             if(list.at(j)->m_freq < list.at(i)->m_freq){
                 list.swap(i, j);

             }
           }
       }
      return list;
}

//Recriação da arvore
QPair<Node *, int> HuffTree::recursive(QByteArray TreeRepresetation, int pos)
{
    unsigned char aux= TreeRepresetation.at(pos);
    if(aux!=0x28){
        if(aux==0x2A){
            pos++;
            aux=TreeRepresetation.at(pos);
        }
        return QPair<Node*,int> (new Node(aux,0,0,0),pos);
    }

    else{
        QPair<Node*,int> left= recursive(TreeRepresetation,  pos+1);
        QPair<Node*,int> right= recursive(TreeRepresetation,  left.second+1);
        Node *subTree= new Node (0x2A,0,left.first,right.first);
        return QPair<Node*,int>(subTree,right.second);
    }
}


//Gera a codificação dm binario
QByteArray HuffTree::code(const uchar cont){
    QByteArray Code;
    if(m_root->NodeisLeaf()){
        if(m_root->m_content == cont && m_root->m_freq != 0) return "";
    }
    else{
        HuffTree *sub1 = new HuffTree(m_root->m_right);
        HuffTree *sub2 = new HuffTree(m_root->m_left);

        if(!sub1->code(cont).isNull()){
            Code.append("1").append(sub1->code(cont));
        }
        else if(!sub2->code(cont).isNull()){
            Code.append("0").append(sub2->code(cont));
        }
    }
    return Code;
}
//Pega o caractere e a codificação em binário
QHash<uchar, QByteArray> HuffTree::codeRef(int *array){
    QByteArray aux;
    QHash<uchar, QByteArray> ref;
    for(int i = 0; i<256; ++i){
        if(array[i] != 0){
            aux = this->code(uchar(i));
            ref.insert(uchar(i), aux);
            //Exibe a codificação em binario por caractere.
          // qDebug()<<array[i]<< char(i)<< " codigo:" <<qPrintable(aux);

        }
    }
    return ref;

}

void HuffTree::showHuffTree(){
    qDebug("arvore:\n%s", qPrintable(m_root->TreeDisplay(0,m_root)));
}

void HuffTree::ToLeft()
{
    if(m_current) m_current=m_current->m_left;
}

void HuffTree::Toright()
{
    if(m_current) m_current=m_current->m_right;
}

void HuffTree::ToRoot()
{
    m_current= m_root;
}

bool HuffTree::transverse(bool value)
{
    if(value){
        this->Toright();

    }
    else{
         this->ToLeft();
    }
    return m_current->NodeisLeaf();
}
void HuffTree::Rebuild(QByteArray TreeRepresentation){
    m_root= recursive(TreeRepresentation,0).first ;
    m_current=m_root;
}

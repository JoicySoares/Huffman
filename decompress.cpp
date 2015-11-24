#include "decompress.h"
#include <QString>
#include <QFile>

void decompress(QString name, QString local){

    QFile file(name);
    Q_ASSERT_X(file.open(QIODevice::ReadOnly), Q_FUNC_INFO, "file not found.");
    QByteArray head =file.read(3);
    int Ttrash = (((uchar(head[0]))&0xe0)>>5);
    int Tsize =  (((qint16(head[0]))&0x1f)<<8)| ((quint16(head[1]))&0xff);
    int Tname = head.at(2);

    //caso tenha que mudar o local
    QString OriginalName= file.read(Tname);
    if(!local.isEmpty()){
       OriginalName = changesLocal(OriginalName,local);
    }

    //qDebug()<<OriginalName;
    QByteArray TreeRep= file.read(Tsize);
    //qDebug()<<TreeRep;
    HuffTree* tree = new HuffTree();
    tree->Rebuild(TreeRep);
    tree->showHuffTree();
    QByteArray data;

    //Lendo o arquivo e passando para bits.
    while (!file.atEnd()) {
         QByteArray line = file.read(1024);
         data.append(line);
    }
    file.close();
    QFile Original (OriginalName);
    Q_ASSERT_X(Original.open(QIODevice::WriteOnly), Q_FUNC_INFO, "file not found.");


    //Bits-Bytes
    QBitArray bit= ToBitArray(data);
    bit.resize(bit.size()-Ttrash);
    int bitsize=bit.size();
    QByteArray RetrieveData;
    //Lendo a arvore e copiando o nó para o arquivo
    for(int i=0;i<bitsize;++i){
        if(tree->transverse(bit.at(i))){
            RetrieveData.append( tree->current()->m_content);
            tree->setCurrent();
        }
    }
    Original.write(RetrieveData);
    Original.close();
    qDebug()<< "Arquivo Descomprimido! :)";
}

QBitArray ToBitArray(QByteArray byte)
{
    int bytesize=byte.size();
    QBitArray bit(bytesize*8);
    for(int i=0;i<bytesize;++i){
        for(int j=0;j<8;++j){
            bit.setBit(i*8+j,byte.at(i)&(1<<(7-j))); //Máscara
        }
    }
        return bit;
}

QString changesLocal(QString name,QString local){
    local.append('/');
       for(int i = name.size() - 1; i>0 ; --i){
           if((name.at(i) == '/' ) ||( name.at(i) == '\\' )){
               name.remove(0, i+1);
               break;
           }
       }
       name.insert(0,local);
   return name;
}

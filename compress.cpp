#include "compress.h"

//Conta a frequencia dos caracteres e coloca num bytearray
int* readbytes( QString name){
    int* array = new int[256];
    for(int i = 0; i<256; ++i){
         array[i] = 0;
    }
    QFile file(name);

    Q_ASSERT_X(file.open(QIODevice::ReadOnly), "Read::readbytes", "file not found.");

    while (!file.atEnd()) {
         QByteArray line = file.read(1024);
              for(int i = 0; i < line.size(); ++i) {
                 ++array[(unsigned char) line.at(i)];
              }
     }
    file.close();
    return array;

}

//Conta o lixo e passa o array de bits para bytes
QPair<QByteArray, int> toByteArray(QByteArray bits){
    int len = bits.size();  //tamanho do array
    int trash = 0;
    if( len%8 != 0){
        trash = 8 - len%8;
        bits.append(QByteArray("0").repeated(trash));
    }

    qDebug()<<"trash:"<< trash;
    QByteArray InBytes;
    QByteArray aux;
    for(int i=0; i<len; i+=8){
        for(int j=i; j<i+8; ++j){
           aux += bits.at(j);
        }
        bool ok;

        InBytes.append(uchar(aux.toInt(&ok, 2)));
        aux.clear();
    }

    return QPair<QByteArray, int> (InBytes, trash);

}

//Coloca zero em todas as posições restantes do ByteArray
QByteArray setzero(QByteArray str, int n){

    while(str.size() < n){
        str.insert(0,'0');
    }
    return str;
}

//Cabeçalho
QByteArray Head(int trash, int Tsize){
   QByteArray trash_size = QByteArray::number(trash,2);
   QByteArray tree_size = QByteArray::number(Tsize,2);
   QByteArray bits;
   bits.append(setzero(trash_size,3)).append(setzero(tree_size,13));

   QByteArray head;
   QByteArray aux;
   int len = bits.size();
   for(int i=0; i<len; i+=8){
       for(int j=i; j<i+8; ++j){
          aux += bits.at(j);
       }
       bool ok;

       head.append(uchar(aux.toInt(&ok, 2)));
       aux.clear();
   }

   return head;
}

//Vamos comprimir :)
void compress(QString name,QString newname)
{
    int* freq = readbytes(name);//conta frequênica
    HuffTree* tree = new HuffTree(); //cria arvore com frequencia dos caracteres
    tree->buildHuffTree(freq);
    QHash<uchar, QByteArray> ref = tree->codeRef(freq); //pega a codificação em binario dos caracteres
    QFile myfile(name); //coloca tudo em um arquivo
    myfile.open(QIODevice::ReadOnly);
    QByteArray bitArray;

    while (!myfile.atEnd()) {
         QByteArray line = myfile.read(1024);
         for(int i=0; i<line.size(); ++i){
             bitArray.append(ref.value(line.at(i)));

         }

    }
    myfile.close();

    QPair<QByteArray, int> pair = toByteArray(bitArray); //passa os bits para byte
    QByteArray code = pair.first;
    int trashSize = pair.second;
    QByteArray treeRep = tree->representation();

    int treeSize = treeRep.size();

    //Opção de mudar nome de arquivo ou não
     QString newFileName;
    if(newname.isEmpty()){
       newFileName = renamearquive(name);
    }
    else newFileName = newname;
    QFile newfile(newFileName);
    newfile.open(QIODevice::WriteOnly);

    int nameSize = name.size();

    QByteArray aux;
    aux = Head(trashSize, treeSize);
    aux.append(uchar(nameSize));
    newfile.write(aux);
    aux.clear();
    aux.append(name);

    newfile.write(aux);
    aux.clear();
    newfile.write(treeRep);
    newfile.write(code);
    code.clear();

    newfile.close();
    qDebug()<<"Arquivo" << newFileName <<"criado com sucesso!";

}

QString renamearquive(const QString name){
    QString rename = name;
    int j;

    for(j = rename.size() - 1; j>=0; --j){
        if(rename.at(j) == '.'){
              rename.remove(j,(name.size() - j ));
              rename.append(".huff");
              break;

         }

        if(j == 0){
            rename = name;
            rename.append(".huff");
        }
    }
    return rename;
}

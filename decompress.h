#ifndef DECOMPRESS_H
#define DECOMPRESS_H
#include <QDebug>
#include "hufftree.h"
#include <QBitArray>

//Metodo de descompressão
void decompress(QString name,QString local);

//Passa o array pra bits
QBitArray ToBitArray(QByteArray byte);

//Para o caso de mudar o local onde será salvado o arquivo descomprimido
QString changesLocal(QString name,QString local);


#endif // DECOMPRESS_H

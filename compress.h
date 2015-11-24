#ifndef COMPRESS
#define COMPRESS
#include <QFile>
#include <QTextStream>
#include <QBitArray>
#include "hufftree.h"


//passa os caracteres pra o bytearray
int* readbytes(QString name);

//transforma a codificação binaria em bytes
QPair<QByteArray, int> toByteArray(QByteArray bits);

QByteArray setzero(QByteArray str, int n);

//cabeçalho
QByteArray Head(int trash, int Tsize);

//comprime
void compress(QString name,QString newname);

//Renomea o arquivo,acrescenta a extensão!
QString renamearquive(const QString name);

#endif // COMPRESS

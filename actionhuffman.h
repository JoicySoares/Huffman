#ifndef ACTIONHUFFMAN_H
#define ACTIONHUFFMAN_H
#include "compress.h"
#include "decompress.h"

#include <QObject>

class ActionHuffman : public QObject{
    Q_OBJECT
public:
    Q_INVOKABLE static void doCompress(QString name,QString newname);
    Q_INVOKABLE static void doDecompress(QString name,QString local);
};

#endif // ACTIONHUFFMAN_H

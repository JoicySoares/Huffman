#include "actionhuffman.h"


void ActionHuffman::doCompress(QString name, QString newname){
    if(newname == "out")
        newname = "";
    compress(name,newname);
}

void ActionHuffman::doDecompress(QString name, QString local){
    if(local == "out")
        local = "";
    decompress(name,local);
}

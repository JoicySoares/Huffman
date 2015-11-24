import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

Column{
    property alias com: com
    property alias decom: decom
    anchors.verticalCenter: parent.verticalCenter
    spacing: 8
    MyButton{
        id: com
        txt.text: "Comprimir"
    }
    MyButton{
        id: decom
        txt.text: "Descomprimir"
    }
}


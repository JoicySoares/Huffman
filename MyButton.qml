import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Rectangle{
    property alias mouse: mouse
    property alias txt: txt
    property alias qbutton: qbutton
    id: qbutton
    height: mm(8)
    width: mm(28)
    color: "#333333"
    Text {
        id: txt
        anchors.centerIn: parent
        font.bold: true
        font.pixelSize: 15
        color:"#E15C5C"
    }
    MouseArea{
        id: mouse
        anchors.fill: parent
    }
}

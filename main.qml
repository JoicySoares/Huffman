import QtQuick 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

Window{
    function mm(value){
        return value*Screen.pixelDensity
    }
    id: ui
    visible: true
    height: mm(60)
    width: mm(130)
    Rectangle{
        id: aux
        anchors.fill: parent
        color: "#E15C5C"
    }
    MyMenu{
        id:menu
        com.mouse.onClicked: {
                _action.doCompress(choose.path.text,choose.pathOut.text)
        }
        decom.mouse.onClicked: {
                _action.doDecompress(choose.path.text,choose.pathOut.text)
        }
    }
    Rectangle{
        color: "#333333"
        height: ui.height
        width: 2
        anchors.left: menu.right
    }

    MyChoose{
        id: choose
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }
    Text {
        text: qsTr("Joicy")
        font.family: "Purisa"
        font.pixelSize: 20
        anchors.right: aux.right
        anchors.bottom: aux.bottom
    }
}

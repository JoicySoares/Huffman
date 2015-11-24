import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4

Column{
    spacing: 10
    property alias path: path
    property alias pathOut: pathOut
    property alias file: file
    property string txt: " "
    Row{
        spacing: parent.width/50
        FileDialog {
            id: file
            title: qsTr("Selecione " + txt)
            folder: shortcuts.home

            onAccepted: {
                path.text = (file.fileUrl) ;  path.text = path.text.replace("file://","")
                file.close()
            }
            onRejected: {
                file.close()
            }
        }
        Text {
            id: name
            text: txt
        }
        Rectangle{
            height: mm(8)
            width: mm(35)
            radius: mm(2)
            TextEdit{
                anchors.fill: parent
                anchors.centerIn: parent
                id: path
                font.pixelSize: 20
                clip: true
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: "Arquivo"
                font.family: "Furisa"
                opacity: 0.3
            }
        }
        MyButton{
            qbutton.radius: height/2
            qbutton.width : height
            qbutton.border.color: "white"
            txt.text: "..."
            mouse.onClicked: {
                file.open()
            }
        }
    }
    Rectangle{
        height: mm(8)
        width: mm(35)
        radius: mm(2)
        TextEdit{
            text: "out"
            anchors.fill: parent
            anchors.centerIn: parent
            id: pathOut
            font.pixelSize: 20
            clip: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: "Furisa"
            opacity: 0.3
        }
    }
}

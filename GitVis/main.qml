import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Window {
    // Path should be a c++ git property.
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")


    RowLayout{
        anchors.bottom: parent.bottom
        width: parent.width
        spacing:20
        Label{
            text: "Git Repo:"
        }

        TextField{
            text: fileReader.gitFolder
            Layout.fillWidth: true
        }
        Button {
            text: "Change"
            onClicked:
            {
                fileDialog.visible = true
            }
        }
    }

    FileDialog{
        id: fileDialog
        visible: false
        title: "Select your git repo."
        folder: shortcuts.home
        selectMultiple:false
        selectFolder: true
        onAccepted: {
            // Check if file is a .git file.
            fileReader.gitFolder = fileUrl.toString().replace(/^(file:\/{2})/,"");
            visible = false
        }
        onRejected: {
            visible = false
        }
    }
}

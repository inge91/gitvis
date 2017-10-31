import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick 2.7
import QtQml.Models 2.2

Item {
    id: treeVisualisation
    // currently only one branch
    property var model
    GridView {
        id: visualModel
        model: treeVisualisation.model
        delegate: Rectangle {
            Text {
                id: authorText
                text: "Author: " + author
            }
            Text {
                anchors.top: authorText.bottom
                text: "Message: " + message
            }
        }
   }
}

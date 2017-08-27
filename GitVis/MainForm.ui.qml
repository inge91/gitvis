import QtQuick 2.6

Rectangle {
    property alias mouseArea: mouseArea
    x: -1

    width: 360
    height: 360

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }
}

import QtQuick

Window {
    id: root
    visible: true
    title: "Error!"
    width:  600
    height: 400

    Text {
        anchors.centerIn: parent
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        text: "An error occurred while loading this application"
        color: "red"
    }
}

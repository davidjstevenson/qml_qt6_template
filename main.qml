import QtQuick

Window {
    id: root
    visible: true

    Image {
        source: Qt.resolvedUrl("resources/image_cat_CC0.jpg")
        anchors.centerIn: parent
        sourceSize.width: parent.width / 2
    }
}

import QtQuick
import libs.version 1.0

Window {
    id: root
    visible: true

    // use AppVersion directly
    AppVersion {
        id: appVersion
    }

    Text {
        anchors.top: parent.top
        anchors.left: parent.left
        text: "Application Version: " + appVersion.major + "." + appVersion.minor + " (" + appVersion.hash + ")"
    }

    Version {}
    Something {}

    Image {
        source: Qt.resolvedUrl("resources/image_cat_CC0.jpg")
        anchors.centerIn: parent
        sourceSize.width: parent.width / 2
    }
}

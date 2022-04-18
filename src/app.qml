import QtQuick
import QtQuick.Controls
import libs.version

Item {

    // use AppVersion directly
    AppVersion {
        id: appVersion
    }

    Text {
        anchors.top: parent.top
        anchors.left: parent.left
        text: "Application Version: " + appVersion.major + "." + appVersion.minor

        MouseArea {
            anchors.fill: parent
            onClicked: aboutDialog.open()
        }
    }

    Image {
        source: Qt.resolvedUrl("resources/image_cat_CC0.jpg")
        anchors.centerIn: parent
        sourceSize.width: parent.width / 2
    }

    Popup {
        id: aboutDialog
        x: 25
        y: 25
        width: parent.width - 50
        height: parent.height - 50
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        About {
            anchors.fill: parent
        }
    }
}

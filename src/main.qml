import QtQuick
import QtQuick.Controls
import QtQuick.Window
import Qt.labs.settings

ApplicationWindow {
    id: root
    width: Math.round(0.8 * Screen.width)
    height: Math.round(0.8 * Screen.height)
    visible: true

    title: "Title"

    function reload() {
        console.log("reloading...")
        loader.source = ""
        $App.clearComponentCache();
        loader.source = "app.qml"
    }

    Connections {
        target: $App
        onReload: root.reload()
    }

    Loader {
        id: loader
        anchors.fill: parent
        source: "app.qml"
    }

    Settings {
        property alias x: root.x
        property alias y: root.y
        property alias width: root.width
        property alias height: root.height
    }
}
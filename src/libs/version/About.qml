import QtQuick
import QtQuick.Layouts
import libs.version

Item {
    id: root

    AppVersion {
        id: appVersion
    }

    GridLayout {
        columns: 2

        Text { text: "Name" }
        Text { text: appVersion.appName }

        Text { text: "Version" }
        Text { text: appVersion.appVersion }

        Text { text: "Build" }
        Text { text: appVersion.hash }
    }
}

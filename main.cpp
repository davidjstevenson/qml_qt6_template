#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml/qqmlextensionplugin.h>

#include "qmlQt6_version.h"

// to make the qml plugin succesfully link, we must reference a symbol in the library
// this is done through the following macro, the value is the URI from the call to
// qt_add_qml_module with dots replaces with "_" and the capitalised "Plugin" added
Q_IMPORT_QML_PLUGIN(libs_versionPlugin);

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // we set QT_QML_OUTPUT_DIRECTORY, so add that as an import path too
    engine.addImportPath(QMLPLUGIN_OUTPUT_LOCATION);
    const auto url = QUrl(u"qrc:/gui/main.qml"_qs);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url, &engine](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            qDebug() << "failed to load main.qml" << "\n";
            engine.load(QUrl(u"qrc:/gui/fallback.qml"_qs));
        }
    }, Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}

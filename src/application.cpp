#include <QQmlContext>
#include <QDir>
#include <QDebug>
#include <iostream>
#include <filesystem>

#include "application.h"


Application::Application(int argc, char* argv[]) : QGuiApplication(argc, argv) {

#ifdef QML_SRC_DIR
    engine.addImportPath(QML_SRC_DIR);
    main_qml = QUrl::fromLocalFile(QML_SRC_DIR + u"/main.qml"_qs);
    fallback_qml = QUrl::fromLocalFile(QML_SRC_DIR + u"/fallback.qml"_qs);
    std::cout << main_qml.toString().toStdString() << std::endl;

    const auto rootPath = std::filesystem::path(QML_SRC_DIR);
    for (const auto& entry : std::filesystem::recursive_directory_iterator(rootPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".qml") {
            std::cout << "Watching file: " << entry.path() << "\n";
            watcher.addPath(QString::fromStdString(entry.path().generic_string()));
        }
    }
    watcher.addPath(QStringLiteral(QML_SRC_DIR));

    QObject::connect(&watcher, &QFileSystemWatcher::fileChanged, this, &Application::fileChanged);
    QObject::connect(&watcher, &QFileSystemWatcher::directoryChanged, this, &Application::fileChanged);
    reloadDedupTimer.setInterval(100);
    reloadDedupTimer.setSingleShot(true);
    QObject::connect(&this->reloadDedupTimer, &QTimer::timeout, this, &Application::reload);
#else
    engine.addImportPath(":/");
    main_qml = QUrl(u"qrc:/gui/main.qml"_qs);
    fallback_qml = QUrl(u"qrc:/gui/fallback.qml"_qs);
#endif

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        this, [this](QObject* obj, const QUrl& objUrl) {
            if (!obj && main_qml == objUrl) {
                qDebug() << "failed to load main.qml" << "\n";
                engine.load(fallback_qml);
            }
        }, Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("$App", this);
    engine.load(main_qml);
}

void Application::clearComponentCache() {
    engine.clearComponentCache();
}

void Application::fileChanged(const QString&) {
#ifdef QML_SRC_DIR
    this->reloadDedupTimer.start();
#endif
}

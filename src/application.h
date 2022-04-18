#pragma once

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#ifdef QML_SRC_DIR
#include <QFileSystemWatcher>
#include <QTimer>
#endif

class Application : public QGuiApplication {
    Q_OBJECT;
    QQmlApplicationEngine engine;

    QUrl main_qml;
    QUrl fallback_qml;

#ifdef QML_SRC_DIR
    QFileSystemWatcher watcher;
    QTimer reloadDedupTimer;
#endif

public:
    Application(int argc, char* argv[]);

    Q_INVOKABLE void clearComponentCache();

signals:
    void reload();

private slots:
    void fileChanged(const QString &);
};
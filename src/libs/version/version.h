#pragma once

#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>

#include "qmlQt6_version.h"

class AppVersion : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int major READ major CONSTANT)
    Q_PROPERTY(int minor READ minor CONSTANT)
    Q_PROPERTY(int patch READ patch CONSTANT)
    Q_PROPERTY(int tweak READ tweak CONSTANT)
    Q_PROPERTY(QString hash READ hash CONSTANT)
    Q_PROPERTY(QString appName READ appName CONSTANT)
    Q_PROPERTY(QString appVersion READ appVersion CONSTANT)

 public:
    int major() const;
    int minor() const;
    int patch() const;
    int tweak() const;
    const QString hash() const;
    const QString appName() const;
    const QString appVersion() const;
};

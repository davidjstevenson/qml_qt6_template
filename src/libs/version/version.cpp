#include "version.h"

int AppVersion::major() const { return version::cmake::project_version_major; }
int AppVersion::minor() const { return version::cmake::project_version_minor; }
int AppVersion::patch() const { return version::cmake::project_version_patch; }
int AppVersion::tweak() const { return version::cmake::project_version_tweak; }
const QString AppVersion::hash() const {
    return QString(version::cmake::git_sha.data());
}
const QString AppVersion::appName() const {
    return QString(version::cmake::project_name.data());
}
const QString AppVersion::appVersion() const {
    return QString(version::cmake::project_version.data());
}

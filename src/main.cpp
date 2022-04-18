#include <QtQml/qqmlextensionplugin.h>

// to make the qml plugin succesfully link, we must reference a symbol in the library
// this is done through the following macro, the value is the URI from the call to
// qt_add_qml_module with dots replaces with "_" and the capitalised "Plugin" added
Q_IMPORT_QML_PLUGIN(libs_versionPlugin);

#include "application.h"
#include "qmlQt6_version.h"

#if defined(WIN32) && (defined(OUTPUT_TO_CONSOLE) || defined(REDIRECT_CONSOLE_TO_DEBUG))
#include <Windows.h>
#include <iostream>
#endif

#if defined(WIN32) && defined(REDIRECT_CONSOLE_TO_DEBUG)
#include <sstream>

class streambuf : public std::streambuf {
public:
    virtual int_type overflow(int_type c = EOF) {
        if (c != EOF) {
            TCHAR buf[] = { (TCHAR)c, '\0' };
            OutputDebugString(buf);
        }
        return c;
    }
};
#endif

int main(int argc, char *argv[])
{
#if defined(WIN32) && defined(OUTPUT_TO_CONSOLE)
    AllocConsole();
    FILE [[maybe_unused]] *stdout_;
    FILE [[maybe_unused]] *stderr_;
    freopen_s(&stdout_, "CONOUT$", "w", stdout);
    freopen_s(&stderr_, "CONOUT$", "w", stderr);
#endif

#if defined(WIN32) && defined(REDIRECT_CONSOLE_TO_DEBUG)
    streambuf buf;
    std::cout.rdbuf(&buf);
#endif

    QCoreApplication::setOrganizationName("david");
    QCoreApplication::setOrganizationDomain("stevenson.nz");
    QCoreApplication::setApplicationName(QString(version::cmake::project_name.data()));
    QCoreApplication::setApplicationVersion(QString(version::cmake::project_version.data()));

    Application app(argc, argv);
    return app.exec();
}

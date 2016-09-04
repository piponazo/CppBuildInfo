#include "MainWindow.h"
#include <QApplication>

int main (int argc, char **argv)
{
    QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("FreeSoftware");
	QCoreApplication::setApplicationName("CppBuildInfo");

    MainWindow window;
    window.show();
    return app.exec();
}

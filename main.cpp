#include <QtGui>
#include "audiocapture.h"
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName(QObject::tr("iRecorder"));

    QTranslator translator;
    QString qm = QString(INSTALL_PREFIX "/share/irecorder/irecorder_") + QLocale::system().name();
    translator.load(qm);
    app.installTranslator(&translator);

    AudioCapturer ac;
    ac.setWindowTitle(QObject::tr("iRecorder"));
    ac.show();

    return app.exec();
}

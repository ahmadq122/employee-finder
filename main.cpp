#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Modules/WordFrquency/WordFrquency.h"
#include "Modules/ReadJsonFromFile/ReadJsonFromFile.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_Use96Dpi, true);

    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName("employee_finder");
    QGuiApplication::setApplicationVersion("1.0.0");
    QGuiApplication::setOrganizationName("Maes");
    QGuiApplication::setOrganizationDomain("maestronic.com");

    QQmlApplicationEngine engine;

    qmlRegisterSingletonType<WordFrequency>("Maes.WordFrquency", 1, 0, "WordFrquency", WordFrequency::singletonProvider);
    qmlRegisterSingletonType<ReadJsonFromFile>("Maes.ReadJsonFromFile", 1, 0, "ReadJsonFromFile", ReadJsonFromFile::singletonProvider);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

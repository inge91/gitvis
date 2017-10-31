#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <qgit2/qgitrepository.h>
#include <git2.h>
#include <filereader.h>
#include <iostream>
#include <qqmlcontext.h>
#include <qqmlapplicationengine.h>
#include <qqmlabstracturlinterceptor.h>

int main(int argc, char *argv[])
{
    git_libgit2_init();
    QGuiApplication app(argc, argv);

    FileReader fileReader;
    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("fileReader", QVariant::fromValue(&fileReader));

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}

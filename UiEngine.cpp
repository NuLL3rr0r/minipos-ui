#include "uiengine.hpp"

using namespace MiniPos;

struct UiEngine::Impl
{

};

UiEngine::UiEngine(QObject *parent) :
    QQmlApplicationEngine(parent)
{

}

UiEngine::UiEngine(const QUrl &url, QObject *parent) :
    QQmlApplicationEngine(url, parent)
{

}

UiEngine::UiEngine(const QString &filePath, QObject *parent) :
    QQmlApplicationEngine(filePath, parent)
{

}

UiEngine::~UiEngine() = default;


#include <QDebug>
#include <QQmlContext>
#include "uiengine.hpp"
#if defined(Q_OS_ANDROID)
#include "Android.hpp"
#endif // defined(Q_OS_ANDROID)
#include "Pool.hpp"

using namespace MiniPos;

struct UiEngine::Impl
{

};

UiEngine::UiEngine(QObject *parent) :
    QQmlApplicationEngine(parent)
{
    this->rootContext()->setContextProperty("uiEngine", this);
}

UiEngine::UiEngine(const QUrl &url, QObject *parent) :
    QQmlApplicationEngine(url, parent)
{
    this->rootContext()->setContextProperty("uiEngine", this);
}

UiEngine::UiEngine(const QString &filePath, QObject *parent) :
    QQmlApplicationEngine(filePath, parent)
{
    this->rootContext()->setContextProperty("uiEngine", this);
}

UiEngine::~UiEngine() = default;

bool UiEngine::notify(const QString &title, const QString &text, const int id) const
{
#if defined(Q_OS_ANDROID)
    return Pool::Android()->Notify(title, text, id);
#else
    qWarning() << "Notification is not implemented on this platform";
    qDebug() << title << text << id;
    return true;
#endif // defined(Q_OS_ANDROID)
}

bool UiEngine::showToast(const QString &text, const int duration) const
{
#if defined(Q_OS_ANDROID)
    return Pool::Android()->ShowToast(text, duration);
#else
    qWarning() << "Toast is not implemented on this platform";
    qDebug() << text << duration;
    return true;
#endif // defined(Q_OS_ANDROID)
}


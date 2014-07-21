#include <QDebug>
#include <QQmlContext>
#include "make_unique.hpp"
#include "uiengine.hpp"
#if defined(Q_OS_ANDROID)
#include "Android.hpp"
#endif // defined(Q_OS_ANDROID)
#include "Pool.hpp"
#include "Pos.hpp"

using namespace MiniPos;

struct UiEngine::Impl
{
private:
   UiEngine *m_parent;

public:
   Impl(UiEngine *parent);

public:
    void OnHeadSetStateChanged(const Pos::HeadSetState &state);

    void InitializeEvents();
};

UiEngine::UiEngine(QObject *parent) :
    QQmlApplicationEngine(parent),
    m_pimpl(std::make_unique<UiEngine::Impl>(this))
{
    this->rootContext()->setContextProperty("uiEngine", this);

    m_pimpl->InitializeEvents();
}

UiEngine::UiEngine(const QUrl &url, QObject *parent) :
    QQmlApplicationEngine(url, parent),
    m_pimpl(std::make_unique<UiEngine::Impl>(this))
{
    this->rootContext()->setContextProperty("uiEngine", this);

    m_pimpl->InitializeEvents();
}

UiEngine::UiEngine(const QString &filePath, QObject *parent) :
    QQmlApplicationEngine(filePath, parent),
    m_pimpl(std::make_unique<UiEngine::Impl>(this))
{
    this->rootContext()->setContextProperty("uiEngine", this);

    m_pimpl->InitializeEvents();
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

UiEngine::Impl::Impl(UiEngine *parent) :
    m_parent(parent)
{

}

void UiEngine::Impl::OnHeadSetStateChanged(const Pos::HeadSetState &state)
{
    switch (state) {
    case Pos::HeadSetState::DEVICE_IN:
        m_parent->showToast("Device In!");
        break;
    case Pos::HeadSetState::DEVICE_OUT:
        m_parent->showToast("Device Out!");
        break;
    case Pos::HeadSetState::DEVICE_CHECKED:
        m_parent->showToast("Device Checked!");
        break;
    case Pos::HeadSetState::DEVICE_CHECKED_TIMEOUT:
        m_parent->showToast("Device Device Checked Timeout!");
        break;
    default:
        break;
    }
}

void UiEngine::Impl::InitializeEvents()
{
    Pool::Pos()->HeadSetStateChanged().connect(
                std::bind(
                    &UiEngine::Impl::OnHeadSetStateChanged,
                    this,
                    std::placeholders::_1
                    )
                );
}


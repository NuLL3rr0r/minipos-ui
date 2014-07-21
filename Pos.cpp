#include "Pos.hpp"
#include "make_unique.hpp"
#include <QObject>          // This is necessary for typedef Q_OS_ANDROID.
#if defined(Q_OS_ANDROID)
#include "Android.hpp"
#endif /* defined(Q_OS_ANDROID) */

#include "Pool.hpp"

using namespace MiniPos;

struct Pos::Impl
{
    Pos::HeadSetStateChangedSignal_t HeadSetStateChangedSignal;

    void OnHeadSetStateChanged(int state);

    void InitializeEvents();
};

Pos::Pos() :
    m_pimpl(std::make_unique<Pos::Impl>())
{
    m_pimpl->InitializeEvents();
}

Pos::~Pos() = default;

Pos::HeadSetStateChangedSignal_t &Pos::HeadSetStateChanged()
{
    return m_pimpl->HeadSetStateChangedSignal;
}

void Pos::Impl::OnHeadSetStateChanged(int state)
{
    Pool::Pos()->HeadSetStateChanged()(static_cast<HeadSetState>(state));
}

void Pos::Impl::InitializeEvents()
{
#if defined(Q_OS_ANDROID)
    Pool::Android()->OnHeadSetStateChanged(
                std::bind(&Pos::Impl::OnHeadSetStateChanged,
                          this,
                          std::placeholders::_1)
                );
#endif /* defined(Q_OS_ANDROID) */
}


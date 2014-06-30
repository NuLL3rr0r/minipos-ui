#include "Pos.hpp"
#include "make_unique.hpp"
#if defined(Q_OS_ANDROID)
#include "Android.hpp"
#endif /* defined(Q_OS_ANDROID) */
#include "Android.hpp"
#include "Pool.hpp"

using namespace MiniPos;

struct Pos::Impl
{
    Pos::HeadSetStateChangedSignal_t HeadSetStateChangedSignal;

    void OnHeadSetStateChanged(HeadSetState state);

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

void Pos::Impl::OnHeadSetStateChanged(HeadSetState state)
{
    Pool::Pos()->HeadSetStateChanged()(state);
}

void Pos::Impl::InitializeEvents()
{
#if defined(Q_OS_ANDROID)
    Pool::Android()->OnHeadSetStateChanged(
                std::bind(&Pos::Impl::OnHeadSetStateChanged,
                          this,
                          std::placeholders::_1));
#endif /* defined(Q_OS_ANDROID) */
}


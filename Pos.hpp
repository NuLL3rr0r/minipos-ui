#ifndef MINIPOS_POS_HPP
#define MINIPOS_POS_HPP


#include <memory>
#include <boost/signals2/signal.hpp>

namespace MiniPos {
#if defined ( Q_OS_ANDROID )
class Android;
#endif // defined ( Q_OS_ANDROID )
class Pos;
}

class MiniPos::Pos
{
public:
    enum class HeadSetState : int {
        DEVICE_IN = 0,
        DEVICE_OUT = 1,
        DEVICE_CHECKED = 2,
        DEVICE_CHECKED_TIMEOUT = -1
    };

    typedef boost::signals2::signal<void(const HeadSetState &)> HeadSetStateChangedSignal_t;
    typedef HeadSetStateChangedSignal_t::slot_type HeadSetStateChangedSlot_t;

private:
    struct Impl;
    std::unique_ptr<Impl> m_pimpl;

public:
    HeadSetStateChangedSignal_t &HeadSetStateChanged();

public:
    Pos();
    ~Pos();
};


#endif /* MINIPOS_POS_HPP */

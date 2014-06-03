#ifndef MINIPOS_ANDROID_HPP
#define MINIPOS_ANDROID_HPP


class QString;

namespace MiniPos {
class Android;
}

class MiniPos::Android
{
private:
    struct Impl;
    std::unique_ptr<Impl> m_pimpl;

public:
    Android();
    virtual ~Android();
};


#endif // MINIPOS_ANDROID_HPP


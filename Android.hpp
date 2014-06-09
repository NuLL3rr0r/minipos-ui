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

public:
    bool Notify(const QString &title, const QString &text, const int id = 0);
    bool ShowToast(const QString &text, const int duration = 8000);
};


#endif // MINIPOS_ANDROID_HPP


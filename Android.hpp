/**
 * @author  Mohammad S. Babaei <info@babaei.net>
 */


#ifndef MINIPOS_ANDROID_HPP
#define MINIPOS_ANDROID_HPP


#include <functional>
#include <string>
#include <jni.h>
#include <QtAndroidExtras/QAndroidJniObject>

namespace MiniPos {
class Android;
}

class MiniPos::Android : public QAndroidJniObject
{
public:
    typedef std::function<void(int state)> OnHeadSetStateChangedHandler_t;

private:
    struct Impl;
    std::unique_ptr<Impl> m_pimpl;

public:
    Android();
    virtual ~Android();

public:
    void OnHeadSetStateChanged(OnHeadSetStateChangedHandler_t handler);

public:
    bool ExceptionCheck();
    void ExceptionClear();

    void Initialize();
    void Release();

    bool IsInitialized();

public:
    QString GetScreenType();
    bool Notify(const QString &title, const QString &text, const int id = 0);
    bool ShowToast(const QString &text, const int duration = 8000);
};


#endif /* MINIPOS_ANDROID_HPP */

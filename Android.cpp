#include <cassert>
#include <jni.h>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QtAndroidExtras>
#include <QtCore/QDebug>
#include "make_unique.hpp"
#include "Android.hpp"

#define     JAVA_CLASS      "com/rahpooyanco/minipos/Android"

using namespace MiniPos;

struct Android::Impl
{
    typedef std::unique_ptr<QAndroidJniObject> QAndroidJniObject_t;

    QAndroidJniObject_t AndroidJniObject;

    Impl();
    ~Impl();

    bool ExceptionCheck();
    void ExceptionClear();
};

Android::Android():
    m_pimpl(std::make_unique<Android::Impl>())
{
    assert(QAndroidJniObject::isClassAvailable(JAVA_CLASS));
}

Android::~Android() = default;

bool Android::Impl::ExceptionCheck()
{
    QAndroidJniEnvironment env;
    return env->ExceptionCheck();
}

void Android::Impl::ExceptionClear()
{
    QAndroidJniEnvironment env;
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }
}

Android::Impl::Impl() :
    AndroidJniObject(std::make_unique<QAndroidJniObject>(JAVA_CLASS))
{

}

Android::Impl::~Impl() = default;


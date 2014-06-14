#include <cassert>
#include <jni.h>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QtAndroidExtras>
#include <QtCore/QDebug>
#include <QtCore/QString>
#include "make_unique.hpp"
#include "Android.hpp"

#define     JAVA_CLASS      "com/rahpooyanco/minipos/Android"

using namespace MiniPos;

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *)
{
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        qCritical() << "  * Could not get the JNI enviroument !!";
        return -1;
    }

    return JNI_VERSION_1_6;
}

struct Android::Impl
{
    typedef std::unique_ptr<QAndroidJniObject> QAndroidJniObject_t;

    QAndroidJniObject_t AndroidJniObject;

    Impl();
    ~Impl();

    bool ExceptionCheck();
    void ExceptionClear();

    bool IsInterfaceInitialized();
    void Initialize();
    void Release();
};

Android::Android():
    m_pimpl(std::make_unique<Android::Impl>())
{
    assert(QAndroidJniObject::isClassAvailable(JAVA_CLASS));

    if (!m_pimpl->IsInterfaceInitialized()) {
        m_pimpl->Initialize();
    }
}

Android::~Android()
{
    if (m_pimpl->IsInterfaceInitialized()) {
        m_pimpl->Release();
    }
}

bool Android::Notify(const QString &title, const QString &text, const int id)
{
    m_pimpl->ExceptionClear();

    jboolean ret = QAndroidJniObject::callStaticMethod<jboolean>(
                JAVA_CLASS,
                "notify",
                "(Ljava/lang/CharSequence;Ljava/lang/CharSequence;I)Z",
                QAndroidJniObject::fromString(title).object<jstring>(),
                QAndroidJniObject::fromString(text).object<jstring>(),
                id);

    return ret;
}

bool Android::ShowToast(const QString &text, const int duration)
{
    m_pimpl->ExceptionClear();

    jboolean ret = QAndroidJniObject::callStaticMethod<jboolean>(
                JAVA_CLASS,
                "showToast",
                "(Ljava/lang/CharSequence;I)Z",
                QAndroidJniObject::fromString(text).object<jstring>(),
                duration);

    return ret;
}

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

bool Android::Impl::IsInterfaceInitialized()
{
    ExceptionClear();

    return QAndroidJniObject::callStaticMethod<jboolean>(
                JAVA_CLASS, "isInitialized", "()Z");
}

void Android::Impl::Initialize()
{
    ExceptionClear();

    AndroidJniObject->callMethod<void>(
                "<init>", "()V");
}

void Android::Impl::Release()
{
    ExceptionClear();

    QAndroidJniObject::callStaticMethod<jboolean>(
                JAVA_CLASS, "release", "()Z");
}


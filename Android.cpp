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

Android::OnHeadSetStateChangedHandler_t OnHeadSetStateChangedHandler;

static void onHeadSetStateChanged(JNIEnv *, jobject, int state)
{
    OnHeadSetStateChangedHandler(state);
}

static JNINativeMethod s_nativeMethods[] = {
    {"onHeadSetStateChanged", "(I)V", (void *)onHeadSetStateChanged}
};

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *)
{
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        qCritical() << "  * Could not get the JNI enviroument !!";
        return -1;
    }

    jclass clazz = env->FindClass(JAVA_CLASS);
    if (!clazz) {
        qCritical()<<"  * Could not find the Android interface class !!";
        return -1;
    }

    if (env->RegisterNatives(
                clazz,
                s_nativeMethods,
                sizeof(s_nativeMethods) / sizeof(s_nativeMethods[0])
                ) < 0) {
        qCritical()<<"   * Failed to Register native methods !!";
        return -1;
    }

    return JNI_VERSION_1_6;
}

struct Android::Impl
{
    QAndroidJniEnvironment AndroidJniEnvironment;
};

Android::Android() :
    m_pimpl(std::make_unique<Android::Impl>())
{

}

Android::~Android() = default;

bool Android::ExceptionCheck()
{
    return m_pimpl->AndroidJniEnvironment->ExceptionCheck();
}

void Android::OnHeadSetStateChanged(OnHeadSetStateChangedHandler_t handler)
{
    OnHeadSetStateChangedHandler = handler;
}

void Android::ExceptionClear()
{
    if (m_pimpl->AndroidJniEnvironment->ExceptionCheck()) {
        m_pimpl->AndroidJniEnvironment->ExceptionClear();
    }
}

void Android::Initialize()
{
    if (!IsInitialized()) {
        ExceptionClear();

        this->callMethod<void>(
                    "<init>", "()V");
    }
}

void Android::Release()
{
    ExceptionClear();

    QAndroidJniObject::callStaticMethod<jboolean>(
                JAVA_CLASS, "release", "()Z");
}

bool Android::IsInitialized()
{
    ExceptionClear();

    return QAndroidJniObject::callStaticMethod<jboolean>(
                JAVA_CLASS, "isInitialized", "()Z");
}


bool Android::Notify(const QString &title, const QString &text, const int id)
{
    ExceptionClear();

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
    ExceptionClear();

    jboolean ret = QAndroidJniObject::callStaticMethod<jboolean>(
                JAVA_CLASS,
                "showToast",
                "(Ljava/lang/CharSequence;I)Z",
                QAndroidJniObject::fromString(text).object<jstring>(),
                duration);

    return ret;
}


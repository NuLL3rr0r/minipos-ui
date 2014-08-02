#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
#include <QtCore/QTranslator>
#include "make_unique.hpp"
#include "Application.hpp"
#include "Pool.hpp"
#include "UiEngine.hpp"

using namespace MiniPos;

struct Application::Impl
{
    typedef std::unique_ptr<MiniPos::UiEngine> UiEngine_t;
    UiEngine_t UiEngine;
};

Application::Application(int &argc, char **argv) :
    QApplication(argc, argv),
    m_pimpl(std::make_unique<Application::Impl>())
{
    QFontDatabase::addApplicationFont(":/fonts/main.ttf");
    QApplication::setFont(QFont("XM Yekan"));
}

Application::~Application() = default;

void Application::OnEnglishMenuItemPressed()
{
    this->removeTranslator(Pool::Translator());
    Pool::Translator()->load("en", ":/translations/");
    this->installTranslator(Pool::Translator());
    emit m_pimpl->UiEngine->signal_LanguageChanged();
}

void Application::OnFarsiMenuItemPressed()
{
    this->removeTranslator(Pool::Translator());
    Pool::Translator()->load("fa", ":/translations/");
    this->installTranslator(Pool::Translator());
    emit m_pimpl->UiEngine->signal_LanguageChanged();
}

void Application::SetupUi()
{
    m_pimpl->UiEngine =
            std::make_unique<MiniPos::UiEngine>();
    m_pimpl->UiEngine->load(QUrl(QStringLiteral("qrc:///ui/main.qml")));

    QObject *uiRootObject = m_pimpl->UiEngine->rootObjects().first();

    QObject::connect(uiRootObject, SIGNAL(signal_englishMenuItemPressed()),
            this, SLOT(OnEnglishMenuItemPressed()));
    QObject::connect(uiRootObject, SIGNAL(signal_farsiMenuItemPressed()),
            this, SLOT(OnFarsiMenuItemPressed()));
}


#include "make_unique.hpp"
#include "Application.hpp"
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

}

Application::~Application() = default;

void Application::SetupUi()
{
    m_pimpl->UiEngine =
            std::make_unique<MiniPos::UiEngine>();
    m_pimpl->UiEngine->load(QUrl(QStringLiteral("qrc:///ui/main.qml")));
}


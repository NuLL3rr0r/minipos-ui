#include <memory>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <QtCore/QTranslator>
#include "make_unique.hpp"
#include "Application.hpp"
#include "Database.hpp"
#include "Pool.hpp"

void InitializeDatabase();

int main(int argc, char *argv[])
{
#if !defined ( Q_OS_ANDROID )
    /*! Change to executable path */
    boost::filesystem::path path(boost::filesystem::initial_path<boost::filesystem::path>());
    if (argc > 0 && argv[0] != NULL)
        path = boost::filesystem::system_complete(boost::filesystem::path(argv[0]));
    std::string appId(path.filename().string());
    std::string appPath(boost::algorithm::replace_last_copy(path.string(), appId, ""));
    boost::filesystem::current_path(appPath);
#endif // !defined ( Q_OS_ANDROID )

    InitializeDatabase();

    std::unique_ptr<MiniPos::Application> app =
            std::make_unique<MiniPos::Application>(argc, argv);

    MiniPos::Pool::Translator()->load(QLocale::system().name(), ":/translations/");
    app->installTranslator(MiniPos::Pool::Translator());

    app->SetupUi();
    return app->exec();
}

void InitializeDatabase()
{
    using namespace MiniPos;

    Pool::Database()->Initialize();
}


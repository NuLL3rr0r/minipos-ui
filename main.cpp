/**
 * @author  Mohammad S. Babaei <info@babaei.net>
 */


#include <iostream>
#include <memory>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include "make_unique.hpp"
#include "Application.hpp"
#include "Log.hpp"

int main(int argc, char *argv[])
{
    MiniPos::Log::Initialize(std::cout);

#if !defined ( Q_OS_ANDROID )
    /*! Change to executable path */
    boost::filesystem::path path(boost::filesystem::initial_path<boost::filesystem::path>());
    if (argc > 0 && argv[0] != NULL)
        path = boost::filesystem::system_complete(boost::filesystem::path(argv[0]));
    std::string appId(path.filename().string());
    std::string appPath(boost::algorithm::replace_last_copy(path.string(), appId, ""));
    boost::filesystem::current_path(appPath);
#endif // !defined ( Q_OS_ANDROID )

    std::unique_ptr<MiniPos::Application> app =
            std::make_unique<MiniPos::Application>(argc, argv);
    app->InitializeDatabase();
    app->SetupUi();

    return app->exec();
}


/**
 * @author  Mohammad S. Babaei <info@babaei.net>
 */


#include <mutex>
#include <cassert>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QTranslator>
#include "make_unique.hpp"
#include "Pool.hpp"
#if defined ( Q_OS_ANDROID )
#include "Android.hpp"
#endif // defined ( Q_OS_ANDROID )
#include "Crypto.hpp"
#include "Database.hpp"
#include "Pos.hpp"
#include "RestApi.hpp"

#if defined ( _WIN32 )
#define     DATABASE_RELATIVE_PATH          "resources\\db"
#else
#define     DATABASE_RELATIVE_PATH          "resources/db"
#endif // defined ( _WIN32 )
#define     DATABASE_FILE_NAME              "database.db"

using namespace std;
using namespace MiniPos;

struct Pool::Impl
{
    typedef std::unique_ptr<Pool::StorageStruct> Storage_t;
#if defined ( Q_OS_ANDROID )
    typedef std::unique_ptr<MiniPos::Android> Android_t;
#endif // defined ( Q_OS_ANDROID )
    typedef std::unique_ptr<MiniPos::Crypto> Crypto_t;
    typedef std::unique_ptr<MiniPos::Database> Database_t;
    typedef std::unique_ptr<MiniPos::Pos> Pos_t;
    typedef std::unique_ptr<MiniPos::RestApi> RestApi_t;
    typedef std::unique_ptr<QTranslator> Translator_t;

    static std::mutex StorageMutex;
    static Storage_t StorageInstance;

#if defined ( Q_OS_ANDROID )
    static std::mutex AndroidMutex;
    static Android_t AndroidInstance;
#endif // defined ( Q_OS_ANDROID )

    static std::mutex CryptoMutex;
    static Crypto_t CryptoInstance;

    static std::mutex DatabaseMutex;
    static Database_t DatabaseInstance;

    static std::mutex PosMutex;
    static Pos_t PosInstance;

    static std::mutex RestApiMutex;
    static RestApi_t RestApiInstance;

    static std::mutex TranslatorMutex;
    static Translator_t TranslatorInstance;
};

std::mutex Pool::Impl::StorageMutex;
Pool::Impl::Storage_t Pool::Impl::StorageInstance = nullptr;

#if defined ( Q_OS_ANDROID )
std::mutex Pool::Impl::AndroidMutex;
Pool::Impl::Android_t Pool::Impl::AndroidInstance = nullptr;
#endif // defined ( Q_OS_ANDROID )

std::mutex Pool::Impl::CryptoMutex;
Pool::Impl::Crypto_t Pool::Impl::CryptoInstance = nullptr;

std::mutex Pool::Impl::DatabaseMutex;
Pool::Impl::Database_t Pool::Impl::DatabaseInstance = nullptr;

std::mutex Pool::Impl::PosMutex;
Pool::Impl::Pos_t Pool::Impl::PosInstance = nullptr;

std::mutex Pool::Impl::RestApiMutex;
Pool::Impl::RestApi_t Pool::Impl::RestApiInstance = nullptr;

std::mutex Pool::Impl::TranslatorMutex;
Pool::Impl::Translator_t Pool::Impl::TranslatorInstance = nullptr;

Pool::StorageStruct *Pool::Storage()
{
    lock_guard<mutex> lock(Impl::StorageMutex);
    (void)lock;

    if (Impl::StorageInstance == nullptr) {
        Impl::StorageInstance =
                std::make_unique<Pool::StorageStruct>();
    }

    return Impl::StorageInstance.get();
}

#if defined ( Q_OS_ANDROID )
MiniPos::Android *Pool::Android()
{
    lock_guard<mutex> lock(Impl::AndroidMutex);
    (void)lock;

    if (Impl::AndroidInstance == nullptr) {
        Impl::AndroidInstance =
                std::make_unique<MiniPos::Android>();
    }

    return Impl::AndroidInstance.get();
}
#endif

MiniPos::Crypto *Pool::Crypto()
{
    lock_guard<mutex> lock(Impl::CryptoMutex);
    (void)lock;

    if (Impl::CryptoInstance == nullptr) {
        // Use this nice HEX/ASCII converter and your editor's replace dialog,
        // to create your own Key and IV.
        // http://www.dolcevie.com/js/converter.html
        // or
        // http://www.asciitohex.com/
        // To generate random password: https://strongpasswordgenerator.com/

        // Pvs%GT4[sC6QEMDh
        static constexpr Crypto::Byte_t KEY[] = {
            0x50, 0x76, 0x73, 0x25, 0x47, 0x54, 0x34, 0x5b, 0x73, 0x43, 0x36, 0x51, 0x45, 0x4d, 0x44, 0x68
        };

        // 34XK8D756Agg_6db
        static constexpr Crypto::Byte_t IV[] = {
            0x33, 0x34, 0x58, 0x4b, 0x38, 0x44, 0x37, 0x35, 0x36, 0x41, 0x67, 0x67, 0x5f, 0x36, 0x64, 0x62
        };

        Impl::CryptoInstance =
                std::make_unique<MiniPos::Crypto>(KEY, sizeof(KEY), IV, sizeof(IV));
    }

    return Impl::CryptoInstance.get();
}

MiniPos::Database *Pool::Database()
{
    lock_guard<mutex> lock(Impl::DatabaseMutex);
    (void)lock;

    if (Impl::DatabaseInstance == nullptr) {
        QString dbPath(QDir::currentPath());
        if (!dbPath.endsWith(QDir::separator()))
            dbPath += QDir::separator();
        dbPath += DATABASE_RELATIVE_PATH;
        if (!dbPath.endsWith(QDir::separator()))
            dbPath += QDir::separator();
        QString dbFile(dbPath + DATABASE_FILE_NAME);

        if (!QFileInfo(dbFile).exists()) {
            if (!QDir(dbPath).exists()) {
                assert(QDir().mkpath(dbPath));
            }
            Database::Vacuum(dbFile.toStdString());
            assert(QFile::setPermissions(dbFile, QFile::ReadOwner | QFile::WriteOwner));
        }

#if defined ( STATIC_LINK_DEPENDENCIES )
        if (!Database::IsSQLite3DriverLoaded())
            Database::LoadSQLite3Driver();
#endif  // defined ( STATIC_LINK_DEPENDENCIES )

        Impl::DatabaseInstance =
                std::make_unique<MiniPos::Database>(QDir::toNativeSeparators(dbFile).toStdString());
    }

    return Impl::DatabaseInstance.get();
}

MiniPos::Pos *Pool::Pos()
{
    lock_guard<mutex> lock(Impl::PosMutex);
    (void)lock;

    if (Impl::PosInstance == nullptr) {
        Impl::PosInstance =
                std::make_unique<MiniPos::Pos>();
    }

    return Impl::PosInstance.get();
}

MiniPos::RestApi *Pool::RestApi()
{
    lock_guard<mutex> lock(Impl::RestApiMutex);
    (void)lock;

    if (Impl::RestApiInstance == nullptr) {
        Impl::RestApiInstance =
                std::make_unique<MiniPos::RestApi>();
    }

    return Impl::RestApiInstance.get();
}

QTranslator *Pool::Translator()
{
    lock_guard<mutex> lock(Impl::TranslatorMutex);
    (void)lock;

    if (Impl::TranslatorInstance == nullptr) {
        Impl::TranslatorInstance =
                std::make_unique<QTranslator>();
    }

    return Impl::TranslatorInstance.get();
}


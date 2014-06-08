#include <mutex>
#include "make_unique.hpp"
#include "Pool.hpp"
#if defined(Q_OS_ANDROID)
#include "Android.hpp"
#endif /* defined(Q_OS_ANDROID) */
#include "Database.hpp"

using namespace std;
using namespace MiniPos;

struct Pool::Impl
{
    typedef std::unique_ptr<Pool::StorageStruct> Storage_t;
#if defined(Q_OS_ANDROID)
    typedef std::unique_ptr<MiniPos::Android> Android_t;
#endif /* defined(Q_OS_ANDROID) */
    typedef std::unique_ptr<MiniPos::Database> Database_t;
    typedef std::unique_ptr<MiniPos::DatabaseTables> DatabaseTables_t;

    static std::mutex StorageMutex;
    static Storage_t StorageInstance;

#if defined(Q_OS_ANDROID)
    static std::mutex AndroidMutex;
    static Android_t AndroidInstance;
#endif /* defined(Q_OS_ANDROID) */

    static std::mutex DatabaseMutex;
    static Database_t DatabaseInstance;
};

std::mutex Pool::Impl::StorageMutex;
Pool::Impl::Storage_t Pool::Impl::StorageInstance = nullptr;

#if defined(Q_OS_ANDROID)
std::mutex Pool::Impl::AndroidMutex;
Pool::Impl::Android_t Pool::Impl::AndroidInstance = nullptr;
#endif /* defined(Q_OS_ANDROID) */

std::mutex Pool::Impl::DatabaseMutex;
Pool::Impl::Database_t Pool::Impl::DatabaseInstance = nullptr;

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

#if defined(Q_OS_ANDROID)
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

MiniPos::Database *Pool::Database()
{
    lock_guard<mutex> lock(Impl::DatabaseMutex);
    (void)lock;

    if (Impl::DatabaseInstance == nullptr) {
        Impl::DatabaseInstance =
                std::make_unique<MiniPos::Database>(Storage()->DATABASE_FILE);
    }

    return Impl::DatabaseInstance.get();
}


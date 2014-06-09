#ifndef MINIPOS_POOL_HPP
#define MINIPOS_POOL_HPP


#include <QObject>
#include <memory>

namespace MiniPos {
#if defined(Q_OS_ANDROID)
class Android;
#endif /* defined(Q_OS_ANDROID) */
class Database;
class DatabaseTables;
class Pool;
}

class MiniPos::Pool
{
private:
    struct Impl;
    struct StorageStruct
    {
        const std::string DATABASE_FILE = "database.db";
    };

public:
    static StorageStruct *Storage();
#if defined(Q_OS_ANDROID)
    static MiniPos::Android *Android();
#endif /* defined(Q_OS_ANDROID) */
    static MiniPos::Database *Database();
};


#endif /* MINIPOS_POOL_HPP */


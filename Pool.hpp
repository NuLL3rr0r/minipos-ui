#ifndef MINIPOS_POOL_HPP
#define MINIPOS_POOL_HPP


#include <QtCore/QObject>
#include <memory>

class QTranslator;

namespace MiniPos {
#if defined(Q_OS_ANDROID)
class Android;
#endif /* defined(Q_OS_ANDROID) */
class Crypto;
class Database;
class Pool;
class Pos;
class RestApi;
}

class MiniPos::Pool
{
private:
    struct Impl;
    struct StorageStruct
    {
    };

public:
    static StorageStruct *Storage();
#if defined(Q_OS_ANDROID)
    static MiniPos::Android *Android();
#endif /* defined(Q_OS_ANDROID) */
    static MiniPos::Crypto *Crypto();
    static MiniPos::Database *Database();
    static MiniPos::Pos *Pos();
    static MiniPos::RestApi *RestApi();
    static QTranslator *Translator();
};


#endif /* MINIPOS_POOL_HPP */


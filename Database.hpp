#ifndef MINIPOS_DATABASE_HPP
#define MINIPOS_DATABASE_HPP


#include <memory>
#include <string>
#include <cppdb/frontend.h>

namespace MiniPos {
class Database;
}

class MiniPos::Database
{
public:
    enum class Table : unsigned char {
    };

private:
    struct Impl;
    std::unique_ptr<Impl> m_pimpl;

public:
#if defined ( STATIC_LINK_DEPENDENCIES )
    static bool IsSQLite3DriverLoaded();
    static void LoadSQLite3Driver();
#endif  // defined ( STATIC_LINK_DEPENDENCIES )

    static bool Vacuum(const std::string &databaseFile);

public:
    explicit Database(const std::string &databaseFile);
    virtual ~Database();

    cppdb::session &Sql();

    void CreateTable(const std::string &id);
    void DropTable(const std::string &id);

    void Insert(const std::string &id,
                const std::string &fields,
                const int count,
                ...);
    void Update(const std::string &id,
                const std::string &where,
                const std::string &value,
                const std::string &set,
                const int count,
                ...);
    void Delete(const std::string &id,
                const std::string &where,
                const std::string &value);

    void RegisterTable(const std::string &id,
                       const std::string &name,
                       const std::string &fields);
    std::string GetTableName(const std::string &id);
    std::string GetTableFields(const std::string &id);
    void Initialize();
};


#endif /* MINIPOS_DATABASE_HPP */


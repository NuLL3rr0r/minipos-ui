#include <unordered_map>
#include <cstdarg>
#include <sqlite3.h>
#include <cppdb/backend.h>
#include <cppdb/driver_manager.h>
#include "make_unique.hpp"
#include "Database.hpp"

using namespace std;
using namespace cppdb;
using namespace MiniPos;

struct Database::Impl
{
    typedef std::unordered_map<std::string, std::string> TableNames_t;
    typedef std::unordered_map<std::string, std::string> TableFields_t;

#if defined(STATIC_LINK_DEPENDENCIES)
    static bool IsSQLite3DriverLoaded;
#endif  // defined(STATIC_LINK_DEPENDENCIES)

    cppdb::session Sql;

    TableNames_t TableNames;
    TableFields_t TableFields;
};

#if defined(STATIC_LINK_DEPENDENCIES)
bool Database::Impl::IsSQLite3DriverLoaded = false;
#endif  // defined(STATIC_LINK_DEPENDENCIES)/

#if defined(STATIC_LINK_DEPENDENCIES)
extern "C" {
cppdb::backend::connection *cppdb_sqlite3_get_connection(cppdb::connection_info const &);
}
#endif  // defined(STATIC_LINK_DEPENDENCIES)/

#if defined(STATIC_LINK_DEPENDENCIES)
void Database::LoadSQLite3Driver()
{
    if (!Impl::IsSQLite3DriverLoaded) {
        Impl::IsSQLite3DriverLoaded = true;
        cppdb::driver_manager::instance()
                .install_driver("sqlite3",
                                new cppdb::backend::static_driver(cppdb_sqlite3_get_connection));
    }
}
#endif  // defined(STATIC_LINK_DEPENDENCIES)

bool Database::Vacuum(const std::string &databaseFile)
{
    sqlite3 *db;

    int rc = sqlite3_open(databaseFile.c_str(), &db);
    if (!rc) {
        sqlite3_exec(db, "VACUUM;", 0, 0, 0);
        return true;
    }

    return false;
}

Database::Database(const string &databaseFile) :
    m_pimpl(std::make_unique<Database::Impl>())
{
    if (!m_pimpl->Sql.is_open())
        m_pimpl->Sql.open("sqlite3:db=" + databaseFile);
}

Database::~Database()
{
    if (m_pimpl->Sql.is_open())
        m_pimpl->Sql.close();
}

cppdb::session &Database::Sql()
{
    return m_pimpl->Sql;
}

void Database::CreateTable(const std::string &id)
{
    m_pimpl->Sql << "CREATE TABLE IF NOT EXISTS [" + m_pimpl->TableNames[id] + "] ("
                    + m_pimpl->TableFields[id]
                    + ");"
                 << exec;
}

void Database::DropTable(const std::string &id)
{
    m_pimpl->Sql << "DROP TABLE IF EXISTS [" + m_pimpl->TableNames[id] + "];"
                 << exec;
}

void Database::Insert(const std::string &id,
                      const std::string &fields,
                      const int count,
                      ...)
{
    va_list args;
    va_start(args, count);

    string ph;
    for (int i = 0; i < count; ++i) {
        if (i != 0)
            ph += ", ";
        ph += "?";
    }

    statement stat = m_pimpl->Sql << "INSERT OR IGNORE INTO [" + m_pimpl->TableNames[id] + "] "
                                     "(" + fields + ") "
                                     "VALUES (" + ph + ");";

    for(int i = 0; i < count; ++i) {
        stat.bind(va_arg(args, char*));
    }

    va_end(args);

    stat.exec();
}

void Database::Update(const std::string &id,
                      const std::string &where,
                      const std::string &value,
                      const std::string &set,
                      const int count,
                      ...)
{
    va_list args;
    va_start(args, count);

    statement stat = m_pimpl->Sql << "UPDATE [" + m_pimpl->TableNames[id] + "] "
                                     "SET " + set + " "
                                     "WHERE " + where + "=?;";

    for(int i = 0; i < count; ++i) {
        stat.bind(va_arg(args, char*));
    }

    va_end(args);

    stat.bind(value);

    stat.exec();
}

void Database::Delete(const std::string &id,
                      const std::string &where,
                      const std::string &value)
{
    m_pimpl->Sql << "DELETE FROM [" + m_pimpl->TableNames[id] + "] "
                    "WHERE " + where + "=?;"
                 << value
                 << exec;
}

void Database::RegisterTable(const std::string &id,
                             const std::string &name,
                             const std::string &fields)
{
    m_pimpl->TableNames[id] = name;
    m_pimpl->TableFields[id] = fields;
}

std::string Database::GetTableName(const std::string &id)
{
    if (m_pimpl->TableNames.find(id) != m_pimpl->TableNames.end()) {
        return m_pimpl->TableNames[id];
    }

    return "{?}";
}

std::string Database::GetTableFields(const std::string &id)
{
    if (m_pimpl->TableFields.find(id) != m_pimpl->TableFields.end()) {
        return m_pimpl->TableFields[id];
    }

    return "{?}";
}

void Database::Initialize()
{
    cppdb::transaction guard(m_pimpl->Sql);

    for (Impl::TableNames_t::const_iterator it = m_pimpl->TableNames.begin();
         it != m_pimpl->TableNames.end();
         ++it) {
        CreateTable(it->first);
    }

    guard.commit();
}


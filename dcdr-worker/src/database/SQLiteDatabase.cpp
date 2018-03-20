#include <dcdr/database/SQLiteDatabase.h>

#include <dcdr/database/SQLiteStatement.h>

#include <sqlite3.h>

using namespace Dcdr::Database;

namespace
{
    void sqlite3_deleter(sqlite3* dbHandle)
    {
        sqlite3_close(dbHandle);
    }
}

struct SQLiteDatabase::Impl
{
    std::shared_ptr<sqlite3> dbHandle;
};

namespace
{
    sqlite3* open_database(const std::string &path)
    {
        sqlite3* dbHandle = nullptr;
        sqlite3_open(path.c_str(), &dbHandle);
        return  dbHandle;
    }
}

SQLiteDatabase::SQLiteDatabase(const std::string& path) :
    impl_(new Impl{ std::shared_ptr<sqlite3>(open_database(path), sqlite3_deleter) }) {}

SQLiteDatabase::StatementPtr SQLiteDatabase::prepare(const std::string &query)
{
    sqlite3_stmt* statement;
    sqlite3_prepare_v2(impl_->dbHandle.get(), query.c_str(), -1, &statement, nullptr);
    return std::make_shared<SQLiteStatement>(statement);
}

SQLiteDatabase::~SQLiteDatabase() = default;


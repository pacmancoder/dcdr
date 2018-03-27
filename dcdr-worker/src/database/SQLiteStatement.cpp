#include <dcdr/database/SQLiteStatement.h>

#include <dcdr/database/SQLiteCursor.h>

#include <cstring>

namespace
{
    void sqlite3_stmt_deleter(sqlite3_stmt* statement)
    {
        sqlite3_finalize(statement);
    }

    void array_deleter(void* data)
    {
        delete[] reinterpret_cast<char*>(data);
    }
}

Dcdr::Database::SQLiteStatement::SQLiteStatement(sqlite3_stmt* statement) :
    statement_(std::shared_ptr<sqlite3_stmt>(statement, sqlite3_stmt_deleter)),
    currentBindIndex_(1) {}


Dcdr::Database::IStatement::CursorPtr Dcdr::Database::SQLiteStatement::execute()
{
    return std::make_unique<SQLiteCursor>(statement_);
}

Dcdr::Database::IStatement &Dcdr::Database::SQLiteStatement::bind(int32_t value)
{
    sqlite3_bind_int(statement_.get(), currentBindIndex_++, value);
    return *this;
}

Dcdr::Database::IStatement &Dcdr::Database::SQLiteStatement::bind(int64_t value)
{
    sqlite3_bind_int64(statement_.get(), currentBindIndex_++, value);
    return *this;
}

Dcdr::Database::IStatement &Dcdr::Database::SQLiteStatement::bind(double value)
{
    sqlite3_bind_double(statement_.get(), currentBindIndex_++, value);
    return *this;
}

Dcdr::Database::IStatement &Dcdr::Database::SQLiteStatement::bind(const std::string &value)
{
    auto stringCopy = new char[value.size()];
    std::memcpy(stringCopy, value.data(), value.size());

    sqlite3_bind_text(statement_.get(), currentBindIndex_++, stringCopy, static_cast<int>(value.size()), array_deleter);
    return *this;
}

Dcdr::Database::IStatement &Dcdr::Database::SQLiteStatement::bind(std::vector<uint8_t> value)
{
    auto blobCopy = new char[value.size()];
    std::memcpy(blobCopy, value.data(), value.size());

    sqlite3_bind_blob(statement_.get(), currentBindIndex_++, blobCopy, static_cast<int>(value.size()), array_deleter);
    return *this;
}

Dcdr::Database::IStatement& Dcdr::Database::SQLiteStatement::bind(nullptr_t)
{
    sqlite3_bind_null(statement_.get(), currentBindIndex_++);
    return *this;
}

#include <dcdr/database/SQLiteCursor.h>

Dcdr::Database::SQLiteCursor::SQLiteCursor(std::shared_ptr<sqlite3_stmt> statement) :
    statement_(std::move(statement)) {}

bool Dcdr::Database::SQLiteCursor::is_null(size_t column)
{
    return sqlite3_column_type(statement_.get(), static_cast<int>(column)) == SQLITE_NULL;
}

int32_t Dcdr::Database::SQLiteCursor::get_int(size_t column)
{
    return sqlite3_column_int(statement_.get(), static_cast<int>(column));
}

int64_t Dcdr::Database::SQLiteCursor::get_int64(size_t column)
{
    return sqlite3_column_int64(statement_.get(), static_cast<int>(column));
}

double Dcdr::Database::SQLiteCursor::get_double(size_t column)
{
    return sqlite3_column_double(statement_.get(), static_cast<int>(column));
}

std::string Dcdr::Database::SQLiteCursor::get_string(size_t column)
{
    return std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement_.get(), static_cast<int>(column))));
}

std::vector<uint8_t> Dcdr::Database::SQLiteCursor::get_blob(size_t column)
{
    auto blobPtr = sqlite3_column_blob(statement_.get(), static_cast<int>(column));
    auto blobSize = sqlite3_column_bytes(statement_.get(), static_cast<int>(column));

    return std::vector<uint8_t>(
            reinterpret_cast<const uint8_t*>(blobPtr),
            reinterpret_cast<const uint8_t*>(blobPtr) + blobSize);
}

bool Dcdr::Database::SQLiteCursor::next()
{
    return sqlite3_step(statement_.get()) != SQLITE_DONE;
}

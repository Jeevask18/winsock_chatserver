#include "database.h"
#include <sqlite3.h>
#include <iostream>
using namespace std;

Database::Database(const string& dbName) {
    if (sqlite3_open(dbName.c_str(), (sqlite3**)&db)) {
        cerr << "Can't open database: " << sqlite3_errmsg((sqlite3*)db) << endl;
        db = nullptr;
    } else {
        const char* createTableSQL = 
            "CREATE TABLE IF NOT EXISTS messages ("
            "timestamp TEXT, "
            "sender TEXT, "
            "message TEXT);";

        if (sqlite3_exec((sqlite3*)db, createTableSQL, 0, 0, nullptr) != SQLITE_OK) {
            cerr << "Failed to create table: " << sqlite3_errmsg((sqlite3*)db) << endl;
        }
    }
}

void Database::SaveMessage(const string& timestamp, const string& sender, const string& message) {
    std::string sql = "INSERT INTO messages (timestamp, sender, message) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2((sqlite3*)db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, timestamp.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, sender.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, message.c_str(), -1, SQLITE_STATIC);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    } else {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg((sqlite3*)db) << endl;
    }
}

Database::~Database() {
    if (db) sqlite3_close((sqlite3*)db);
}

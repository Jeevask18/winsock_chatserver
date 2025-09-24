#ifndef DATABASE_H
#define DATABASE_H

#include <string>

class Database {
public:
    Database(const std::string& dbName);
    ~Database();
    void SaveMessage(const std::string& timestamp, const std::string& sender, const std::string& message);
private:
    void* db; // using void* to avoid direct sqlite3 exposure here
};

#endif

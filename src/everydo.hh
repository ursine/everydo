//
// Created by bear on 9/17/2022.
//

#pragma once

#include <string>
#include <memory>
#include <exception>
#include <sstream>
#include "sqlite3.h"
#include "exceptions.h"

class Context {

};


class SqlDatabase {
private:
   std::string filename;
   sqlite3* ppDb;

public:
    explicit SqlDatabase(const char* fn): filename(fn), ppDb(nullptr) {
        int err = sqlite3_open_v2(fn, &ppDb, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
        if (err!=SQLITE_OK) {
            std::ostringstream s("Unable to open '");
            s << filename << "'";
            throw std::runtime_error(s.str());
        }
    }
    SqlDatabase(): ppDb(nullptr) {}

    ~SqlDatabase() {
        int err = sqlite3_close_v2(ppDb);
    }

    void open() {}
    void close() {}
    void set_filename(const char* fn) {}

};


class SqlStatement {




};


// SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;



/*
int sqlite3_open_v2(
  const char *filename,   // Database filename (UTF-8) */
//sqlite3 **ppDb,         // OUT: SQLite db handle */
//int flags,              // Flags */
//const char *zVfs        // Name of VFS module to use */
//);



class Event {
public:
    Event() = default;

    std::wstring get_name() {}
};


class Configuration {

};
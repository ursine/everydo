//
// Created by bear on 9/17/2022.
//

#pragma once

#include <string>
#include <memory>
#include "sqlite3.h"
#include "sqlite3ext.h"


class Context {

};


class SqlContext {
private:
   sqlite3* ppDb;

public:
    SqlContext(): ppDb(nullptr) {}
    ~SqlContext() = default;
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
//
// Created by bear on 9/21/2022.
//

#pragma once

#include <stdexcept>
#include <string>
#include <format>
#include <sqlite3.h>

class SqlError: public std::runtime_error {
protected:
    const int err_code;
    const int ext_err_code;
    const std::string err_str;
    const std::string output;

public:
    SqlError(const char* file, int line, const char* func, sqlite3* db, const std::string& msg):
      err_code(sqlite3_errcode(db)), ext_err_code(sqlite3_extended_errcode(db)), err_str{sqlite3_errstr(err_code)},
      output(std::string("Exception in ")+func+" - "+file+":"+std::to_string(line)+" -- "+msg+" ("+err_str+")"),
      std::runtime_error(output) {}
};

class SqlInitializationException: public SqlError {
public:
    SqlInitializationException(const char *file, int line, const char *func, sqlite3 *db, const std::string &msg):
        SqlError(file, line, func, db, msg) {}
};

#define SqlInitEx(db, msg) SqlInitializationException(__FILE__, __LINE__, __PRETTY_FUNCTION__, db, msg)
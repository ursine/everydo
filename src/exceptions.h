//
// Created by bear on 9/21/2022.
//

#pragma once

#include <stdexcept>
#include <string>

/*class SqlError: public std::runtime_error {
private:
    int err_code;
    std::string err_str;

public:
    SqlError(sqlite3* const db):
      err_code(sqlite3_errcode(db)), err_str(sqlite3_errstr(err_code)), std::runtime_error(err_str) {}


};*/

namespace everydo {


    inline std::string error_factory(sqlite3* const db, const char* func, const char* file, const char* line) {
        const int err_code = sqlite3_errcode(db);
        const int ext_errcode = sqlite3_extended_errcode(db);
        std::string err_msg(sqlite3_errmsg(db));

    }




}


//sqlite3_errstr(mErrcode);
//sqlite3_extended_errcode(apSQLite)
//sqlite3_errcode(apSQLite)


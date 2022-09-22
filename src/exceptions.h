//
// Created by bear on 9/21/2022.
//

#pragma once

#include <stdexcept>

class SqlError: public std::runtime_error {
public:

};

//sqlite3_errstr(mErrcode);
//sqlite3_extended_errcode(apSQLite)
//sqlite3_errcode(apSQLite)


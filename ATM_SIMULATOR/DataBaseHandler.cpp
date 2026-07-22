#include <iostream>
#include "DataBaseHandler.hpp"
#include "ATMmachine.hpp"


bool initializeDataBase::accountExists( std::string &request){
    sqlite3* db;
    
    currentAcc =request;
    if (sqlite3_open("Bank_DataBase.db", &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string sql = "SELECT 1 FROM zenith_bank WHERE account_number = ?1;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare failed: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
}
      sqlite3_bind_text(stmt, 1, request.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    bool exists = (rc == SQLITE_ROW);
    std::cout<<"Db saw "<<request<<std::endl;

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return exists;
    
}

bool initializeDataBase::verifyPin( std::string& pin) {
    sqlite3* db;
    if (sqlite3_open("Bank_DataBase.db", &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    //Query
    std::string sql = "SELECT 1 FROM zenith_bank WHERE account_number = ?1 AND psw = ?2;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare failed: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

     std::cout<<"Db saw "<<currentAcc<<" "<<pin<<std::endl;

    sqlite3_bind_text(stmt, 1, currentAcc.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, pin.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    bool valid = (rc == SQLITE_ROW);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return valid;
}

double initializeDataBase::getBalance() {
    sqlite3* db;
    double balance = 0.0;

    if (sqlite3_open("Bank_DataBase.db", &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return balance;
    }

    std::string sql = "SELECT balance FROM zenith_bank WHERE account_number = ?1;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare failed: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return balance;
    }

    sqlite3_bind_text(stmt, 1, currentAcc.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        balance = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return balance;
}

bool initializeDataBase::updateBalance(double newBalance) {
    sqlite3* db;
    if (sqlite3_open("Bank_DataBase.db", &db)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    std::string sql = "UPDATE zenith_bank SET balance = ?1 WHERE account_number = ?2;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare failed: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_double(stmt, 1, newBalance);
    sqlite3_bind_text(stmt, 2, currentAcc.c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    bool success = (rc == SQLITE_DONE);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return success;
}


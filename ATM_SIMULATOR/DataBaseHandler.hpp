#include <iostream>
#include "sqlite3.h"

class initializeDataBase{
public:
std::string name;
    bool accountExists( std::string &request);

    bool verifyPin(std::string& pin);

    double getBalance();

    bool updateBalance(double newBalance);


    private:
 std::string acc;
        std::string pin ;
        std::string UID;
        double balance;
        std::string currentAcc;
};



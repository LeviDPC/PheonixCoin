//
// Created by Levi on 10/6/2018.
//

#ifndef BLOCKCHAINGOOFIN_TRANSACTION_H
#define BLOCKCHAINGOOFIN_TRANSACTION_H
#include <string>
#include <ctime>
#include <stddef.h>
#include <iostream>
#include "picosha2.h"
using namespace std;

//Questions: 1. Why was was const used in all the get functions
//           2. Why were values passed by const references in strings and passed by nonconst value in numeric types?
//Answers?   1. Const ensures the values can't be changed because of the function
//           2. Passing by references is more efficient because you don't have to actually copy the variable.
//              Using const ensures that it isn't changed. For reasons I didn't bother putting in to much effort to
//              understand it is more efficient to pass numeric types by value.
class transaction {

 
    int blockNumber;
    string sender="Pheonix Gen";
    string receiver="Levi Pfantz";
    double amount=0;
    time_t time=0;

public:


    transaction(const string &sender, int amount, const string &receiver);

    transaction(const string &sender, int amount, const string &receiver, int blockNumber);

    transaction();

    string getSelfHash() const;

    int getBlockNumber() const;

    void setBlockNumber(int blockNumber);

    const string &getSender() const;

    void setSender(const string &sender);

    const string &getreceiver() const;

    void setreceiver(const string &receiver);

    double getAmount() const;

    void setAmount(double amount);

    time_t getTime() const;

    void setTime();

    void setManTime(time_t time);

    string transactionToString() const;

	friend ostream& operator<< (ostream& stream, const transaction& in);




};


#endif //BLOCKCHAINGOOFIN_TRANSACTION_H

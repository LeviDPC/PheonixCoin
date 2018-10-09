//
// Created by Levi on 10/7/2018.
//

#ifndef BLOCKCHAINGOOFIN_BLOCK_H
#define BLOCKCHAINGOOFIN_BLOCK_H
#include <stddef.h>
#include <vector>
#include "transaction.h"
#include <iostream>
using std::vector;
class block {
    int blockNumber=-1;
    size_t prevHash=-1;
    vector<transaction> transactions;
   size_t selfHash=-1;
   time_t time=-1;
public:

    void displayBlock();

    void removeLatestTransaction();

    size_t getSelfHash() const;

    time_t getTime() const;

    void setTime(time_t time);

    void setSelfHash(size_t selfHash);

    void displayTransactions() const;


    void addTransaction(const transaction &trans);


    void addTransaction(const vector<transaction> &trans);


    size_t getPrevHash() const;

    void setPrevHash(size_t prevHash);

    const vector<transaction> &getTransactions() const;

    void setTransactions(const vector<transaction> &transactions);

    block(int blockNumber, size_t prevHash);

    block(int blockNumber, size_t prevHash, const vector<transaction> &transactions);

    block(transaction trans);


    block();

    int getBlockNumber() const;

    void setBlockNumber(int blockNumber);

};


#endif //BLOCKCHAINGOOFIN_BLOCK_H

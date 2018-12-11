//
// Created by Levi on 10/7/2018.
//

#ifndef BLOCKCHAINGOOFIN_BLOCK_H
#define BLOCKCHAINGOOFIN_BLOCK_H
#include <stddef.h>
#include <vector>
#include "Transaction.h"
#include <iostream>
#include <string>
#include <functional>
using std::vector;
class Block {
    int blockNumber=-1;
    string prevHash="";
    vector<Transaction> transactions;
   string selfHash="";
   time_t time=-1;
   int nonce = -1;
public:

	const bool verifyHash() const;

	const string genHash(time_t time, string prevHashIn, int nonce) const;

	string blockInfoToString() const;

	string JSONOutput(string whiteSpaceBeginning="\t", string tag="\"Block\": ") const;

    string toString() const;

	friend ostream& operator<< (ostream& stream, const Block& in);

    void removeLatestTransaction();

    string getSelfHash() const;

    time_t getTime() const;

    void setTime(time_t time);

    void setSelfHash(string selfHash);

	string transactoinsToString() const;


    void addTransaction(const Transaction &trans);


    void addTransaction(const vector<Transaction> &trans);


    string getPrevHash() const;

    void setPrevHash(string prevHash);

    const vector<Transaction> &getTransactions() const;

    void setTransactions(const vector<Transaction> &transactions);

    Block(int blockNumber, string prevHash);

    Block(int blockNumber, string prevHash, const vector<Transaction> &transactions);

    Block(Transaction trans);

    Block();

    int getBlockNumber() const;

    void setBlockNumber(int blockNumber);

	int getNonce() const;

	void setNonce(int nonce);

};


#endif //BLOCKCHAINGOOFIN_BLOCK_H

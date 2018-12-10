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
#include "user.h"

using namespace std;

//Questions: 1. Why was was const used in all the get functions
//           2. Why were values passed by const references in strings and passed by nonconst value in numeric types?
//Answers?   1. Const ensures the values can't be changed because of the function
//           2. Passing by references is more efficient because you don't have to actually copy the variable.
//              Using const ensures that it isn't changed. For reasons I didn't bother putting in to much effort to
//              understand it is more efficient to pass numeric types by value.
class transaction {

 
    int blockNumber;
    string senderName="";
    string senderKey="";
    string senderSig="";
    string receiverName="";
    string receiverKey="";

    double amount=0;
    time_t time=0;
public:
    const string &getSenderName() const;

    void setSenderName(const string &senderName);

    const string &getSenderKey() const;

    void setSenderKey(const string &senderKey);

    const string &getSenderSig() const;

    void setSenderSig(const string &senderSig);

    const string &getReceiverName() const;

    void setReceiverName(const string &receiverName);

    const string &getReceiverKey() const;

    void setReceiverKey(const string &receiverKey);

    transaction(const string &senderKey, const string &senderSig, int amount, const string &receiverKey);
    transaction(const string &senderName, const string &senderKey, const string &senderSig, int amount, const string &recieverName, const string &receiverKey);


    transaction();

    string getSelfHash() const;

    string JSONOutput(string whiteSpaceBeginning="\t", string tag="\"transaction\": ", bool multiLine=true) const;


	string toString() const;

	string toStringWithoutHash() const;

	friend ostream& operator<< (ostream& stream, const transaction& in);


	int getBlockNumber() const;

    void setBlockNumber(int blockNumber);


    double getAmount() const;

    void setAmount(double amount);

    time_t getTime() const;

    void setAutoTime();

    void setManTime(time_t time);

    bool verifySignature() const;

    bool verifyTransaction(const vector<user> &userListIn);

};


#endif //BLOCKCHAINGOOFIN_TRANSACTION_H

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
   //Integer Generated randomly for mining to ensure that a different hash is generated each mining attempt.
   //The final used is stored as an attribute of the block when it is done being mined.
   int nonce = -1;

public:

    //constructors
	Block(int blockNumber, string prevHash);
	Block(int blockNumber, string prevHash, const vector<Transaction> &transactions);
	Block(Transaction trans);
	Block();

    //Outputs Block attributes (including all transactions) to String
    string toString() const;

    //Outputs Block attributes to string but does't include transactions
    string blockInfoToString() const;

    //Outputs only the Blocks Transactions to string
    string transactoinsToString() const;

    //formats and outputs the object as a JSON file. Has the option to input leading white space, an opening tag
    //and whether it should be done on one line or multiple.
    string JSONOutput(string whiteSpaceBeginning="\t", string tag="\"Block\": ") const;

    //generates the blocks hash and compares it to the selfHash attribute
	const bool verifyHash() const;

    //generates a hash of the object by hashing all of its attributes as strings
	const string genHash(time_t time, string prevHashIn, int nonce) const;


    //Sets The time attribute to the current time
    void setAutoTime();

    //Sets the time attribute to whatever is inputted into this method
    void setManTime(time_t time);

    //add a single transaction to the Transaction vector
    void addTransaction(const Transaction &trans);

    //add a vector of transactions to the transaction vector
    void addTransaction(const vector<Transaction> &trans);

    //removes the last transaction in the Transactions vector attribute
    void removeLatestTransaction();

    //overload operators for istream and ostream
	friend ostream& operator<< (ostream& stream, const Block& in);
    friend istream& operator>> (istream& stream, Block& in);


    //setters and getters
    string getSelfHash() const;
    time_t getTime() const;
    void setSelfHash(string selfHash);
    string getPrevHash() const;
    void setPrevHash(string prevHash);
    const vector<Transaction> &getTransactions() const;
    void setTransactions(const vector<Transaction> &transactions);
    int getBlockNumber() const;
    void setBlockNumber(int blockNumber);
	int getNonce() const;
	void setNonce(int nonce);



};


#endif //BLOCKCHAINGOOFIN_BLOCK_H

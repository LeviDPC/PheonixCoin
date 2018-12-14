#ifndef BLOCKCHAINGOOFIN_TRANSACTION_H
#define BLOCKCHAINGOOFIN_TRANSACTION_H
#include <string>
#include <ctime>
#include <stddef.h>
#include <iostream>
#include "picosha2.h"
#include "User.h"


using namespace std;


class Transaction {

 
    int blockNumber;
    string senderName="";
    string senderKey="";
    string senderSig="";
    string receiverName="";
    string receiverKey="";

    double amount=0;
    time_t time=0;

public:

    //constructors
    //Input validation is performed to make sure that Sender Key, Sender Sig, and Receiver Key are non empty, valid
    //Hex Strings
    Transaction(const string &senderKey, const string &senderSig, int amount, const string &receiverKey);
    Transaction(const string &senderName, const string &senderKey, const string &senderSig, int amount, const string &recieverName, const string &receiverKey);
    Transaction();

    //outputs the object as a string including generating and including a hash
    string toString() const;
    //Outputs the object as a string but doesn't generate and include a hash
    string toStringWithoutHash() const;
    //formats and outputs the object as a JSON file. Has the option to input leading white space, an opening tag
    //and whether it should be done on one line or multiple.
    string JSONOutput(string whiteSpaceBeginning="\t", string tag="\"Transaction\": ", bool multiLine=true) const;


    //generates a hash of the Transaction object by hashing all of its attributes as strings
    string genSelfHash() const;

    //Set the time attribute to the current time
    void setAutoTime();
    //Set the time attribute to the time imputed
    void setManTime(time_t time);
    //Isn't actually implemented yet. Right now it just returns true. Ideally it would use Elliptical Curve Cryptography
    //To verify that the SenderKey attribute and the SenderSig Attribute were both generated from the same private key
    //and that the senderSig was generated specifically for this transaction.
    bool verifySignature() const;


    //overload operators for istream and ostream
    friend ostream& operator<< (ostream& stream, const Transaction& in);
    friend istream& operator>> (istream& stream, Transaction& in);


    //setters and getters
    //SetSenderKey, setSenderSig, and setReceiver Key have input validation to ensure that the input is a non empty, valid
    //Hex Strings. aside from that they are all basic setters and getters
    int getBlockNumber() const;
    void setBlockNumber(int blockNumber);
    double getAmount() const;
    void setAmount(double amount);
    time_t getTime() const;
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

};


#endif //BLOCKCHAINGOOFIN_TRANSACTION_H

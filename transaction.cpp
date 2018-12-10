//
// Created by Levi on 10/6/2018.
//

#include "transaction.h"

string transaction::getSelfHash() const {
    string out="";
    picosha2::hash256_hex_string(transaction::toStringWithoutHash(),out);

    return out;


}

string transaction::JSONOutput(string whiteSpaceBeginning, string tag, bool multiLine) const{
    stringstream stream;
    string whiteSpaceEnd;

    if(multiLine)
        whiteSpaceEnd="\n";
    else
        whiteSpaceEnd="";
    string whiteSpaceBeginningWithoutAddedTab=whiteSpaceBeginning;
    if(multiLine) {whiteSpaceBeginning+="\t";}

    stream<<whiteSpaceBeginningWithoutAddedTab<<tag<<"{"<<whiteSpaceEnd;

    stream<<whiteSpaceBeginning<<"\"senderName\": \""<<transaction::senderName<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"senderKey\": \""<<transaction::senderKey<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"senderSig\": \""<<transaction::senderSig<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"amount\": \""<<transaction::amount<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"receiverName\": \""<<transaction::receiverName<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"receiverKey\": \""<<transaction::receiverKey<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"time\": \""<<transaction::time<<"\""<<whiteSpaceEnd;
    stream<<whiteSpaceBeginningWithoutAddedTab<<"}";
    return stream.str();
}

string transaction::toString() const {
    stringstream stream;
    stream<<"Sender Name: "<<transaction::senderName<<"\nSender Key: "<<transaction::senderKey<<"\nSender Signature: "<<senderSig<<"\nAmount: "<<transaction::amount;
    stream<<"\nReceiver Name: "<<transaction::receiverName<<"\nReceiver Key: "<<transaction::receiverKey<<"\nTime: "<<transaction::time<<endl;
    stream<<"Transaction Hash: "<<getSelfHash();
    return stream.str();
}

string transaction::toStringWithoutHash() const {
    stringstream stream;
    stream<<"Sender Name: "<<transaction::senderName<<"\nSender Key: "<<transaction::senderKey<<"\nSender Signature: "<<senderSig<<"\nAmount: "<<transaction::amount;
    stream<<"\nReceiver Name: "<<transaction::receiverName<<"\nReceiver Key: "<<transaction::receiverKey<<"\nTime: "<<transaction::time<<endl;
    return stream.str();
}

ostream & operator<<(ostream & stream, const transaction & in)
{
	stream << in.toString();
	return stream;
}


transaction::transaction() {}

transaction::transaction(const string &senderKey, const string &senderSig, int amount, const string &receiverKey) {
    transaction::senderKey=senderKey;
    transaction::senderSig=senderSig;
    transaction::amount=amount;
    transaction::receiverKey=receiverKey;
    transaction::time=std::time(NULL);
}

transaction::transaction(const string &senderName, const string &senderKey, const string &senderSig, int amount, const string &recieverName, const string &receiverKey) {
    transaction::senderName=senderName;
    transaction::senderKey=senderKey;
    transaction::senderSig=senderSig;
    transaction::amount=amount;
    transaction::receiverName=recieverName;
    transaction::receiverKey=receiverKey;
    transaction::time=std::time(NULL);
}


int transaction::getBlockNumber() const {
    return blockNumber;
}

void transaction::setBlockNumber(int blockNumber) {
    transaction::blockNumber = blockNumber;
}



double transaction::getAmount() const {
    return amount;
}

void transaction::setAmount(double amount) {
    transaction::amount = amount;
}

time_t transaction::getTime() const {
    return time;
}

void transaction::setManTime(time_t time) {
    transaction::time = time;
}

void transaction::setAutoTime() {
    transaction::time=std::time(NULL);
}

const string &transaction::getSenderName() const {
    return senderName;
}

void transaction::setSenderName(const string &senderName) {
    transaction::senderName = senderName;
}

const string &transaction::getSenderKey() const {
    return senderKey;
}

void transaction::setSenderKey(const string &senderKey) {
    transaction::senderKey = senderKey;
}

const string &transaction::getSenderSig() const {
    return senderSig;
}

void transaction::setSenderSig(const string &senderSig) {
    transaction::senderSig = senderSig;
}

const string &transaction::getReceiverName() const {
    return receiverName;
}

void transaction::setReceiverName(const string &receiverName) {
    transaction::receiverName = receiverName;
}

const string &transaction::getReceiverKey() const {
    return receiverKey;
}

void transaction::setReceiverKey(const string &receiverKey) {
    transaction::receiverKey = receiverKey;
}

bool transaction::verifySignature() const{
    return true;
}

bool transaction::verifyTransaction(const vector<user> &userListIn){
    return true;
}





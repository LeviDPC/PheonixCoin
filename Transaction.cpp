//
// Created by Levi on 10/6/2018.
//

#include "Transaction.h"
#include "BlockChain.h"

string Transaction::getSelfHash() const {
    string out="";
    picosha2::hash256_hex_string(Transaction::toStringWithoutHash(),out);

    return out;


}

string Transaction::JSONOutput(string whiteSpaceBeginning, string tag, bool multiLine) const{
    stringstream stream;
    string whiteSpaceEnd;

    if(multiLine)
        whiteSpaceEnd="\n";
    else
        whiteSpaceEnd="";
    string whiteSpaceBeginningWithoutAddedTab=whiteSpaceBeginning;
    if(multiLine) {whiteSpaceBeginning+="\t";}

    stream<<whiteSpaceBeginningWithoutAddedTab<<tag<<"{"<<whiteSpaceEnd;

    stream<<whiteSpaceBeginning<<"\"senderName\": \""<<Transaction::senderName<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"senderKey\": \""<<Transaction::senderKey<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"senderSig\": \""<<Transaction::senderSig<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"amount\": \""<<Transaction::amount<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"receiverName\": \""<<Transaction::receiverName<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"receiverKey\": \""<<Transaction::receiverKey<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"time\": \""<<Transaction::time<<"\""<<whiteSpaceEnd;
    stream<<whiteSpaceBeginningWithoutAddedTab<<"}";
    return stream.str();
}

string Transaction::toString() const {
    stringstream stream;
    stream<<"Sender Name: "<<Transaction::senderName<<"\nSender Key: "<<Transaction::senderKey<<"\nSender Signature: "<<senderSig<<"\nAmount: "<<Transaction::amount;
    stream<<"\nReceiver Name: "<<Transaction::receiverName<<"\nReceiver Key: "<<Transaction::receiverKey<<"\nTime: "<<Transaction::time<<endl;
    stream<<"Transaction Hash: "<<getSelfHash();
    return stream.str();
}

string Transaction::toStringWithoutHash() const {
    stringstream stream;
    stream<<"Sender Name: "<<Transaction::senderName<<"\nSender Key: "<<Transaction::senderKey<<"\nSender Signature: "<<senderSig<<"\nAmount: "<<Transaction::amount;
    stream<<"\nReceiver Name: "<<Transaction::receiverName<<"\nReceiver Key: "<<Transaction::receiverKey<<"\nTime: "<<Transaction::time<<endl;
    return stream.str();
}

ostream & operator<<(ostream & stream, const Transaction & in)
{
	stream << in.toString();
	return stream;
}


Transaction::Transaction() {}

Transaction::Transaction(const string &senderKey, const string &senderSig, int amount, const string &receiverKey) {
    if(!BlockChain::ensureHex(senderKey))
        throw string("Sender Key must Be valid Hex String");
    if(!BlockChain::ensureHex(receiverKey))
        throw string("Receiver Key must Be valid Hex String");
    Transaction::senderKey=senderKey;
    Transaction::senderSig=senderSig;
    Transaction::amount=amount;
    Transaction::receiverKey=receiverKey;
    Transaction::time=std::time(NULL);
}

Transaction::Transaction(const string &senderName, const string &senderKey, const string &senderSig, int amount, const string &recieverName, const string &receiverKey) {
    if(!BlockChain::ensureHex(senderKey))
        throw string("Sender Key must Be valid Hex String");
    if(!BlockChain::ensureHex(receiverKey))
        throw string("Receiver Key must Be valid Hex String");
    Transaction::senderName=senderName;
    Transaction::senderKey=senderKey;
    Transaction::senderSig=senderSig;
    Transaction::amount=amount;
    Transaction::receiverName=recieverName;
    Transaction::receiverKey=receiverKey;
    Transaction::time=std::time(NULL);
}


int Transaction::getBlockNumber() const {
    return blockNumber;
}

void Transaction::setBlockNumber(int blockNumber) {
    Transaction::blockNumber = blockNumber;
}



double Transaction::getAmount() const {
    return amount;
}

void Transaction::setAmount(double amount) {
    Transaction::amount = amount;
}

time_t Transaction::getTime() const {
    return time;
}

void Transaction::setManTime(time_t time) {
    Transaction::time = time;
}

void Transaction::setAutoTime() {
    Transaction::time=std::time(NULL);
}

const string &Transaction::getSenderName() const {
    return senderName;
}

void Transaction::setSenderName(const string &senderName) {
    Transaction::senderName = senderName;
}

const string &Transaction::getSenderKey() const {

    return senderKey;
}

void Transaction::setSenderKey(const string &senderKey) {
    if(senderKey.compare("")==0)
        throw string("Valid input is required for Sender Key");
    if(!BlockChain::ensureHex(senderKey))
        throw string("Sender Key must Be valid Hex String");
    Transaction::senderKey = senderKey;
}

const string &Transaction::getSenderSig() const {

    return senderSig;
}

void Transaction::setSenderSig(const string &senderSig) {
    if(!BlockChain::ensureHex(senderSig))
        throw string("Sender Sig must Be valid Hex String");
    Transaction::senderSig = senderSig;
}

const string &Transaction::getReceiverName() const {
    return receiverName;
}

void Transaction::setReceiverName(const string &receiverName) {
    Transaction::receiverName = receiverName;
}

const string &Transaction::getReceiverKey() const {

    return receiverKey;
}

void Transaction::setReceiverKey(const string &receiverKey) {
    if(receiverKey.compare("")==0)
        throw string("Valid input is required for Receiver Key");
    Transaction::receiverKey = receiverKey;
}

bool Transaction::verifySignature() const{
    return true;
}

bool Transaction::verifyTransaction(const vector<user> &userListIn){
    return true;
}





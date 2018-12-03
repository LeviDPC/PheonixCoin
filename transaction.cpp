//
// Created by Levi on 10/6/2018.
//

#include "transaction.h"

string transaction::getSelfHash() const {
    string out="";
    picosha2::hash256_hex_string(transaction::transactionToString(),out);

    return out;


}

string transaction::transactionToString() const {
    stringstream stream;
    stream<<"Sender: "<<transaction::sender<<"\nAmount: "<<transaction::amount;
    stream<<"\nReceiver: "<<transaction::receiver<<"\nTime: "<<transaction::time<<endl;
    return stream.str();
}

ostream & operator<<(ostream & stream, const transaction & in)
{
	stream << in.transactionToString();
	return stream;
}


transaction::transaction() {}

transaction::transaction(const string &sender, int amount, const string &receiver) {
    transaction::sender=sender;
    transaction::amount=amount;
    transaction::receiver=receiver;
    transaction::time=std::time(NULL);
}

transaction::transaction(const string &sender, int amount, const string &receiver, int blockNumber){
    transaction::sender=sender;
    transaction::amount=amount;
    transaction::receiver=receiver;
    transaction::time=std::time(NULL);
    transaction::blockNumber=blockNumber;
}

int transaction::getBlockNumber() const {
    return blockNumber;
}

void transaction::setBlockNumber(int blockNumber) {
    transaction::blockNumber = blockNumber;
}

const string &transaction::getSender() const {
    return sender;
}

void transaction::setSender(const string &sender) {
    transaction::sender = sender;
}

const string &transaction::getreceiver() const {
    return receiver;
}

void transaction::setreceiver(const string &receiver) {
    transaction::receiver = receiver;
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

void transaction::setTime() {
    transaction::time=std::time(NULL);
}


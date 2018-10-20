//
// Created by Levi on 10/7/2018.
//

#include "block.h"
#include <vector>




const bool block::verifyHash() const {

	string generatedHash = block::genHash(block::time, block::prevHash, block::nonce);
	if (generatedHash.compare(block::selfHash) == 0)
		return true;
	
	else
		return false;
}

const string block::genHash(time_t time, string prevHashIn, int nonce) const {

	vector<transaction>::const_iterator i;
	int index = 0;
	stringstream stream;
	string hexString = "";


		//apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
		for (i = block::transactions.begin(); i != block::transactions.end(); ++i) {
			//based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
			//then I can't be bothered
			index = std::distance(block::transactions.begin(), i);
			stream << block::transactions[index].transactionToString();
		}
		stream << time << prevHashIn << nonce;
		picosha2::hash256_hex_string(stream.str(), hexString);
		return hexString;

	


}


void block::addTransaction(const transaction &trans) {
    block::transactions.push_back(trans);
}

void block::addTransaction(const vector<transaction> &trans) {
    //insert(Where to insert, beggining of range to insert, end of range to insert)
    block::transactions.insert(block::transactions.end(),trans.begin(),trans.end());
}



block::block() {}

block::block(transaction trans){
    block::addTransaction(trans);
}

int block::getBlockNumber() const {
    return blockNumber;
}


void block::setBlockNumber(int blockNumber) {
    block::blockNumber = blockNumber;
}

int block::getNonce() const {
	return block::nonce;
}


void block::setNonce(int nonce) {
	block::nonce = nonce;
}

block::block(int blockNumber, string prevHash, const vector<transaction> &transactions) : blockNumber(blockNumber),
                                                                                          prevHash(prevHash),
                                                                                          transactions(transactions) {}

block::block(int blockNumber, string prevHash) : blockNumber(blockNumber), prevHash(prevHash) {}

string block::getPrevHash() const {
    return prevHash;
}

void block::setPrevHash(string prevHash) {
    block::prevHash = prevHash;
}

const vector<transaction> &block::getTransactions() const {
    return transactions;
}

void block::setTransactions(const vector<transaction> &transactions) {
    block::transactions = transactions;
}

string block::getSelfHash() const {
    return selfHash;
}

void block::setSelfHash(string selfHash) {
    block::selfHash = selfHash;
}

time_t block::getTime() const {
    return time;
}

void block::setTime(time_t time) {
    block::time = time;
}

void block::removeLatestTransaction(){
    block::transactions.erase(block::transactions.end()-1);

}

void block::displayBlock() {
    cout<<"Block Number: "<<block::blockNumber<<endl;
    cout<<"Block Generation Time: "<<block::time<<endl;
    cout<<"Previous Block Hash: "<<block::prevHash<<endl;
    cout<<"This Block's Hash: "<<block::selfHash<<endl;
    cout<<"Number of Transactions in Block: "<<block::transactions.size()<<endl;
    displayTransactions();

}

void block::displayTransactions() const {

    vector<transaction>::const_iterator i;
    int index=0;

    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for(i = block::transactions.begin(); i != block::transactions.end(); ++i){
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index=std::distance(block::transactions.begin(), i);
        std::cout<<endl<<"Transaction Hash: "<<block::transactions[index].getSelfHash()<<endl;


        std::cout<<block::transactions[index].transactionToString()<<endl;
    }
}




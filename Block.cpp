//
// Created by Levi on 10/7/2018.
//

#include "Block.h"


const bool Block::verifyHash() const {

    string generatedHash = Block::genHash(Block::time, Block::prevHash, Block::nonce);
    if (generatedHash.compare(Block::selfHash) == 0)
        return true;

    else
        return false;
}

const string Block::genHash(time_t time, string prevHashIn, int nonce) const {

    vector<Transaction>::const_iterator i;
    int index = 0;
    stringstream stream;
    string hexString = "";


    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = Block::transactions.begin(); i != Block::transactions.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(Block::transactions.begin(), i);
        stream << Block::transactions[index].toString();
    }
    stream << time << prevHashIn << nonce;
    picosha2::hash256_hex_string(stream.str(), hexString);
    return hexString;


}


void Block::addTransaction(const Transaction &trans) {
    Block::transactions.push_back(trans);
}

void Block::addTransaction(const vector<Transaction> &trans) {
    //insert(Where to insert, beggining of range to insert, end of range to insert)
    Block::transactions.insert(Block::transactions.end(), trans.begin(), trans.end());
}


Block::Block() {}

Block::Block(Transaction trans) {
    Block::addTransaction(trans);
}

int Block::getBlockNumber() const {
    return blockNumber;
}


void Block::setBlockNumber(int blockNumber) {
    Block::blockNumber = blockNumber;
}

int Block::getNonce() const {
    return Block::nonce;
}


void Block::setNonce(int nonce) {
    Block::nonce = nonce;
}

Block::Block(int blockNumber, string prevHash, const vector<Transaction> &transactions) : blockNumber(blockNumber),
                                                                                          prevHash(prevHash),
                                                                                          transactions(transactions) {}

Block::Block(int blockNumber, string prevHash) : blockNumber(blockNumber), prevHash(prevHash) {}

string Block::getPrevHash() const {
    return prevHash;
}

void Block::setPrevHash(string prevHash) {
    Block::prevHash = prevHash;
}

const vector<Transaction> &Block::getTransactions() const {
    return transactions;
}

void Block::setTransactions(const vector<Transaction> &transactions) {
    Block::transactions = transactions;
}

string Block::getSelfHash() const {
    return selfHash;
}

void Block::setSelfHash(string selfHash) {
    Block::selfHash = selfHash;
}

time_t Block::getTime() const {
    return time;
}

void Block::setTime(time_t time) {
    Block::time = time;
}

void Block::removeLatestTransaction() {
    Block::transactions.erase(Block::transactions.end() - 1);

}

string Block::blockInfoToString() const {
    stringstream stream;

    stream << "Block Number: " << Block::blockNumber << endl;
    stream << "Block Generation Time: " << Block::time << endl;

    stream << "This Block's Hash: " << Block::selfHash << endl;
    stream << "Previous Block Hash: " << Block::prevHash << endl;

    stream << "Nonce: " << Block::nonce << endl;

    stream << "Number of Transactions in Block: " << Block::transactions.size() << endl;
    return stream.str();
}

string Block::JSONOutput(string whiteSpaceBeginning, string tag) const {
    stringstream stream;

    string whiteSpaceEnd = "\n";
    string whiteSpaceBeginningWithoutAddedTab = whiteSpaceBeginning;
    whiteSpaceBeginning += "\t";

    if(tag.compare("")!=0)
        stream << whiteSpaceBeginningWithoutAddedTab << tag << "{" << whiteSpaceEnd;
    else
        stream <<"{" << whiteSpaceEnd;

    stream << whiteSpaceBeginning << "\"blockNumber\": \"" << Block::blockNumber << "\"," << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"blockGenTime\": \"" << Block::time << "\"," << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"blockHash\": \"" << Block::selfHash << "\"," << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"prevBlockHash\": \"" << Block::prevHash << "\"," << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"nonce\": \"" << Block::nonce << "\"," << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"numbOfTrans\": \"" << Block::transactions.size() << "\"," << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"Transaction\": [";

    if (Block::transactions.size() > 0) {
        stream<<endl;
        vector<Transaction>::const_iterator i;
        int index = 0;
        //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
        for (i = Block::transactions.begin(); i != Block::transactions.end(); ++i) {
            //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
            //then I can't be bothered
            index = std::distance(Block::transactions.begin(), i);


            stream << whiteSpaceBeginning<<"\t" << Block::transactions[index].JSONOutput("", "", false);
            if (index != Block::transactions.size() - 1)
                stream << ",";
            stream << endl;
        }
        stream << whiteSpaceBeginning << "]\n";
    }
        else
            stream<<"\n]\n";

    if(tag.compare("")!=0)
        stream << whiteSpaceBeginningWithoutAddedTab << "}";
    else
        stream << whiteSpaceBeginning << "}";


    return stream.str();
}

string Block::toString() const {
    stringstream stream;

    stream << Block::blockInfoToString();
    stream << Block::transactoinsToString();

    return stream.str();
}

ostream &operator<<(ostream &stream, const Block &in) {
    stream << in.toString();
    return stream;
}

string Block::transactoinsToString() const {

    vector<Transaction>::const_iterator i;
    int index = 0;
    stringstream stream;
    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    if (Block::transactions.size() > 0) {
        for (i = Block::transactions.begin(); i != Block::transactions.end(); ++i) {
            //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
            //then I can't be bothered
            index = std::distance(Block::transactions.begin(), i);

            stream << Block::transactions[index].toString() << endl;
        }
    }

    return stream.

            str();
}




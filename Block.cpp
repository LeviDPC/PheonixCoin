//
// Created by Levi on 10/7/2018.
//

#include "Block.h"

//constructors
Block::Block(int blockNumber, string prevHash, const vector<Transaction> &transactions) : blockNumber(blockNumber),
                                                                    prevHash(prevHash), transactions(transactions) {}
Block::Block(int blockNumber, string prevHash) : blockNumber(blockNumber), prevHash(prevHash) {}

Block::Block(Transaction trans) {
    Block::addTransaction(trans);
}

Block::Block() {}



//Outputs Block attributes (including all transactions) to String
string Block::toString() const {
    stringstream stream;

    stream << Block::blockInfoToString();
    stream << Block::transactoinsToString();

    return stream.str();
}

//Outputs Block attributes to string but does't include transactions
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

//Outputs only the Blocks Transactions to string
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

//formats and outputs the object as a JSON file. Has the option to input leading white space, an opening tag
//and whether it should be done on one line or multiple.
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



//generates the blocks hash and compares it to the selfHash attribute
const bool Block::verifyHash() const {

    string generatedHash = Block::genHash(Block::time, Block::prevHash, Block::nonce);
    if (generatedHash.compare(Block::selfHash) == 0)
        return true;

    else
        return false;
}

//generates a hash of the object by hashing all of its attributes as strings
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



//Sets The time attribute to the current time
void Block::setAutoTime() {
    Block::time = std::time(NULL);
}

//Sets the time attribute to whatever is inputted into this method
void Block::setManTime(time_t time) {
    Block::time = time;
}



//add a single transaction to the Transaction vector
void Block::addTransaction(const Transaction &trans) {
    Block::transactions.push_back(trans);
}

//add a vector of transactions to the transaction vector
void Block::addTransaction(const vector<Transaction> &trans) {
    //insert(Where to insert, beggining of range to insert, end of range to insert)
    Block::transactions.insert(Block::transactions.end(), trans.begin(), trans.end());
}

//removes the last transaction in the Transactions vector attribute
void Block::removeLatestTransaction() {
    Block::transactions.erase(Block::transactions.end() - 1);

}



//overload operators for istream and ostream
ostream &operator<<(ostream &stream, const Block &in) {
    stream << in.toString();
    return stream;
}

istream &operator>>(istream &stream, Block &in){
    int blockNumber=-1;
    string prevHash="";
    vector<Transaction> transactions;
    string hash="";
    time_t time=-1;
    int nonce = -1;
    int numbTrans=0;
    Transaction temp;

    cout<<"Please input BlockNumber: ";
    stream>>blockNumber;
    in.setBlockNumber(blockNumber);
    cout<<endl;

    cout<<"Please input a the Previous Hash: ";
    stream>>prevHash;
    in.setPrevHash(prevHash);
    cout<<endl;

    cout<<"Please input this block's hash if Applicable: ";
    stream>>hash;
    in.setSelfHash(hash);
    cout<<endl;


    cout<<"Please input the nonce if Applicable: ";
    stream>>nonce;
    in.setNonce(nonce);
    cout<<endl;

    cout<<"Please input the number of transactions: ";
    stream>>numbTrans;
    cout<<endl;

    for(int i=0; i<numbTrans; i++){
        temp=Transaction();
        stream>>temp;
        transactions.push_back(temp);
    }

    in.setTransactions(transactions);
    in.setAutoTime();



    return stream;

}



//setters and getters
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









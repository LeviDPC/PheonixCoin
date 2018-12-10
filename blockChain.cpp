//
// Created by Levi on 10/7/2018.
//

#include "blockChain.h"




//Yo, We should *Eventually* add at least two things to this
//1. Set a resonable mining threshold (A hash to check the hash of the block against) so that you have to
//   actuall mine for a while to succeed.
//2. verifying the previous transaction

// This Method takes the transactions, the time, the hash of the previous block
// and a random number. It hashes all this than adds the block to a vector (basically an array list) that is a 
// class variable.

string ensureLength(string in);

bool hexComp(string in1, string in2);


blockChain::blockChain() {}

blockChain::blockChain(const vector<block> &minedBlocks) : minedBlocks(minedBlocks) {}

string blockChain::mine(block blockIn, const string &key) {


    verifyTransactions(blockIn);


    while (true) {
        //mining Threshold is a variable that the mined hash is check against. This is currently set to.
        //Using non hex formats may result in non intended results
        string miningThreshold = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
        //string miningThreshold="0000000000000000000000000000000000000000000000000000000000000000";
        time_t curTime = time(NULL);
        srand(curTime);
        int nonce = rand();
        //blockIn.addTransaction(transaction("Pheonix Gen", 50, "Levi Pfantz"));

        string hash = blockIn.genHash(curTime, blockChain::prevHash, nonce);


        //checks if the hash is less than the value of miningThreshold
        if (hexComp(static_cast<string>(hash), miningThreshold)) {
            // This line is just for testing purposes
            // if(blockChain::hexComp("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe", miningThreshold)){
            blockIn.setBlockNumber(blockChain::minedBlocks.size() + 1);
            blockIn.setTime(curTime);
            blockIn.setPrevHash(blockChain::prevHash);
            blockIn.setSelfHash(hash);
            blockIn.setNonce(nonce);


            addUserIfNotExists(key);

            blockIn.addTransaction(transaction("Pheonix Gen", "-1", "-1", 5, getUserByPublicKey(key).getUserName(), key));

            updateUsers(blockIn);

            blockChain::minedBlocks.push_back(blockIn);
            blockChain::prevHash = hash;

            blockIn=block();

            return hash;
        } else
            blockIn.removeLatestTransaction();

    }


}

void blockChain::updateUsers(const block &in) {
    vector<transaction>::const_iterator i;
    int index;
    transaction trans;


    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = in.getTransactions().begin(); i != in.getTransactions().end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(in.getTransactions().begin(), i);
        trans = in.getTransactions()[index];

        if(in.getTransactions()[index].getSenderKey().compare("-1")!=0)
            getUserByPublicKey(trans.getSenderKey()) -= trans.getAmount();

        addUserIfNotExists(trans.getReceiverKey());
        getUserByPublicKey(trans.getReceiverKey())+=trans.getAmount();

    }
}


//This function takes in two 64 digit (256 bit) hexadecimal numbers as strings and compares them. It returns true
// if the first parameter is less than or equal to the second one and false otherwise.
// If the input is input is less than 64 digits than the ensureLength function will add 0s at the beelining of the
// String. If it is more than it will just take the first 64 digits.
bool hexComp(string in1, string in2) {
    //This next line is just for testing the function
    //cout<<endl<<"hexString: "<<hex1<<endl<<"miningThreshold: "<<hex2<<endl;
    string sec1 = "";
    string sec2 = "";
    unsigned long long sec1Long = 0;
    unsigned long long sec2Long = 0;


    string hex1 = ensureLength(in1);
    string hex2 = ensureLength(in2);


    for (int i = 0; i < 8; i++) {
        sec1 = hex1.substr(i * 8, 8);
        sec2 = hex2.substr(i * 8, 8);
        sec1Long = std::stoull(sec1, NULL, 16);
        sec2Long = std::stoull(sec2, NULL, 16);
        //These next two commented lines are just for testing the method.
        //cout<<endl<<"Sec1: "<<sec1<<endl<<"sec2: "<<sec2<<endl;
        //cout<<endl<<"Sec1Long: "<<sec1Long<<endl<<"sec2Long: "<<sec2Long<<endl;
        if (sec1Long < sec2Long) {

            return true;
        }
        if (sec1Long > sec2Long) {
            return false;
        }
    }

    //This statement is what happens if the two hashes are equal. If its set to return true than it will return true if the
    //hashes are equal. If you set it to return false than the opposite will be true;
    return true;

}


string ensureLength(string in) {

    if (in.length() > 64) {
        in = in.substr(0, 64);
    }
    if (in.length() < 64) {

        for (int i = 0; i < (64 - in.length()); i++) {
            in = "0" + in;

        }

    }
    // Testing: cout << "Corrected string is: " << in << endl;
    return in;
}

//simply prints the entire block Chain

string blockChain::toString() const {
    vector<block>::const_iterator i;
    int index;
    stringstream stream;
    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = blockChain::minedBlocks.begin(); i != blockChain::minedBlocks.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(blockChain::minedBlocks.begin(), i);
        stream << blockChain::minedBlocks[index];
        stream << "------------------------------------------------------------" << endl;
    }
    return stream.str();
}

string blockChain::JSONOutput(string whiteSpaceBeginning, string tag) const {
    vector<block>::const_iterator i;
    int index;
    stringstream stream;

    string whiteSpaceEnd = "\n";
    string whiteSpaceBeginningWithoutAddedTab = whiteSpaceBeginning;
    whiteSpaceBeginning += "\t";


    stream << whiteSpaceBeginningWithoutAddedTab << tag << "{" << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"numbBlocks\": \"" << blockChain::minedBlocks.size() << "\"," << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"block\": [" << whiteSpaceEnd;



    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = blockChain::minedBlocks.begin(); i != blockChain::minedBlocks.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(blockChain::minedBlocks.begin(), i);
        stream << whiteSpaceBeginning << "\t" << blockChain::minedBlocks[index].JSONOutput("\t\t", "");
        if (index != blockChain::minedBlocks.size() - 1)
            stream << ",";
        stream << endl;

    }
    stream << whiteSpaceBeginning << "]" << whiteSpaceEnd;
    stream << whiteSpaceBeginningWithoutAddedTab << "}" << whiteSpaceEnd;

    return stream.str();
}


ostream &operator<<(ostream &stream, const blockChain &in) {
    stream << in.toString();
    return stream;
}


const block &blockChain::getBlockFromChain(int in) const {

    return minedBlocks[in];

}

const vector<block> &blockChain::getMinedBlocks() const {
    return minedBlocks;
}

void blockChain::setMinedBlocks(const vector<block> &minedBlocks) {
    blockChain::minedBlocks = minedBlocks;
}


const vector<user> &blockChain::getuserList() const {
    return userList;
}

void blockChain::setUserList(const vector<user> &listIn) {
    blockChain::userList = listIn;
}

void blockChain::addToUserList(const user &in) {
    if (in.getPublicKey().compare("-1") == 0 || blockChain::isPublicKeyInList(in.getPublicKey()))
        throw string("Public Key Already in Use");
    blockChain::userList.push_back(in);
}

string blockChain::userListToString() const {
    if (blockChain::userList.size() < 1)
        return "";
    vector<user>::const_iterator i;
    int index;
    stringstream stream;

    stream << "User List Length: " << blockChain::userList.size() << endl;

    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = blockChain::userList.begin(); i != blockChain::userList.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(blockChain::userList.begin(), i);
        stream << blockChain::userList[index].toString();
        stream << endl;
    }

    return stream.str();

}


string blockChain::userListJSONOutput(string whiteSpaceBeginning, string tag) const {
    vector<user>::const_iterator i;
    int index;
    stringstream stream;

    string whiteSpaceEnd = "\n";
    string whiteSpaceBeginningWithoutAddedTab = whiteSpaceBeginning;
    whiteSpaceBeginning += "\t";


    stream << whiteSpaceBeginningWithoutAddedTab << tag << "{" << whiteSpaceEnd;

    stream << whiteSpaceBeginning << "\"numbOfUser\": \"" << blockChain::userList.size() << "\"," << whiteSpaceEnd;

    stream << whiteSpaceBeginning << "\"user\": [";
    if (userList.size() > 0)
        stream << whiteSpaceEnd;



    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = blockChain::userList.begin(); i != blockChain::userList.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(blockChain::userList.begin(), i);
        stream << whiteSpaceBeginning << "\t" << blockChain::userList[index].JSONOutput("\t\t", "");
        if (index != blockChain::userList.size() - 1)
            stream << ",";
        stream << endl;

    }
    if (userList.size() > 0)
        stream << whiteSpaceBeginning;
    stream << "]" << whiteSpaceEnd;
    stream << whiteSpaceBeginningWithoutAddedTab << "}" << whiteSpaceEnd;

    return stream.str();
}


user& blockChain::getUserByPublicKey(const string &publicKey) {
    vector<user>::iterator i;
    int index;
    stringstream stream;
    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = blockChain::userList.begin(); i != blockChain::userList.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(blockChain::userList.begin(), i);
        if (publicKey.compare(userList[index].getPublicKey()) == 0)
            return userList[index];
    }
            user u("null", "null", -1);
    throw string("User: "+publicKey+" not on List");
;
}

user& blockChain::getUserByPublicKey(const string &publicKey, vector<user> &listIn){
    vector<user>::iterator i;
    int index;
    stringstream stream;
    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = listIn.begin(); i != listIn.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(listIn.begin(), i);
        if (publicKey.compare(listIn[index].getPublicKey()) == 0)
            return listIn[index];
    }

    throw string("User not on List");
}

bool blockChain::isPublicKeyInList(const string &publicKey) const {
    vector<user>::const_iterator i;
    int index;
    stringstream stream;
    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = blockChain::userList.begin(); i != blockChain::userList.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(blockChain::userList.begin(), i);
        if (publicKey.compare(userList[index].getPublicKey()) == 0)
            return true;
    }

    return false;
}

bool blockChain::isPublicKeyInList(const string &publicKey, const vector<user> &listIn) {
    vector<user>::const_iterator i;
    int index;
    stringstream stream;
    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = listIn.begin(); i != listIn.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(listIn.begin(), i);
        if (publicKey.compare(listIn[index].getPublicKey()) == 0)
            return true;
    }

    return false;
}

void blockChain::addUserIfNotExists(const string &publicKey) {
    if (!isPublicKeyInList(publicKey)) {
        blockChain::addToUserList(publicKey);
    }
}

void blockChain::addUserIfNotExists(string publicKey, vector<user> &listIn){
    if (!blockChain::isPublicKeyInList(publicKey, listIn)) {
        listIn.push_back(publicKey);
    }
}

bool blockChain::verifyTransactions(const block &in) const {
    vector<user> tempUserList=blockChain::userList;
    vector<transaction>::const_iterator i;
    int index;
    transaction trans;


    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = in.getTransactions().begin(); i != in.getTransactions().end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(in.getTransactions().begin(), i);

        trans = in.getTransactions()[index];

        trans.verifySignature();

        getUserByPublicKey(trans.getSenderKey(), tempUserList) -= trans.getAmount();
        addUserIfNotExists(trans.getReceiverKey(),tempUserList);
        getUserByPublicKey(trans.getReceiverKey(),tempUserList)+=trans.getAmount();

        if(trans.getAmount()<0){
            throw string("A positive value must sent!");
        }

        if(getUserByPublicKey(trans.getSenderKey(), tempUserList).getBalance()<0){
            throw string("Insufficient Funds!");
        }


    }

    return true;
}

void blockChain::addToUserByKey(const string &key, int intIn){
    vector<user>::iterator i;
    int index;
    stringstream stream;
    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = blockChain::userList.begin(); i != blockChain::userList.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(blockChain::userList.begin(), i);
        if (key.compare(userList[index].getPublicKey()) == 0) {
            user temp=blockChain::userList[index];
            int out=temp.getBalance()+intIn;
            blockChain::userList[index].setBalance(out);
        }
    }
}
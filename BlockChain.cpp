//
// Created by Levi on 10/7/2018.
//

#include "BlockChain.h"




//Yo, We should *Eventually* add at least two things to this
//1. Set a resonable mining threshold (A hash to check the hash of the Block against) so that you have to
//   actuall mine for a while to succeed.
//2. verifying the previous Transaction

// This Method takes the transactions, the time, the hash of the previous Block
// and a random number. It hashes all this than adds the Block to a vector (basically an array list) that is a
// class variable.

string ensureLength(string in);

bool hexComp(string in1, string in2);


BlockChain::BlockChain() {}

BlockChain::BlockChain(const vector<Block> &minedBlocks) : minedBlocks(minedBlocks) {}

string BlockChain::mine(Block blockIn, const string &key) {
    string miningThreshold = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";


    verifyTransactions(blockIn);

    if(key.compare("")==0)
        throw string("Valid input is required for Public Key in order to mine");


    while (true) {
        //mining Threshold is a variable that the mined hash is check against. This is currently set to.
        //Using non hex formats may result in non intended results

        //string miningThreshold="0000000000000000000000000000000000000000000000000000000000000000";
        time_t curTime = time(NULL);
        srand(curTime);
        int nonce = rand();
        //blockIn.addTransaction(Transaction("Pheonix Gen", 50, "Levi Pfantz"));

        string hash = blockIn.genHash(curTime, BlockChain::prevHash, nonce);


        //checks if the hash is less than the value of miningThreshold
        if (hexComp(static_cast<string>(hash), miningThreshold)) {
            // This line is just for testing purposes
            // if(BlockChain::hexComp("fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffe", miningThreshold)){

            blockIn.setBlockNumber(BlockChain::minedBlocks.size() + 1);
            blockIn.setTime(curTime);
            blockIn.setPrevHash(BlockChain::prevHash);
            blockIn.setSelfHash(hash);
            blockIn.setNonce(nonce);
            //


            addUserIfNotExists(key);

            blockIn.addTransaction(Transaction("Pheonix Gen", "-1", "-1", 5, getUserByPublicKey(key).getUserName(), key));

            updateUsers(blockIn);

            BlockChain::minedBlocks.push_back(blockIn);
            BlockChain::prevHash = hash;

            blockIn=Block();

            return hash;
        } else
            blockIn.removeLatestTransaction();

    }


}

void BlockChain::updateUsers(const Block &in) {
    vector<Transaction>::const_iterator i;
    int index;
    Transaction trans;


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
bool BlockChain::hexComp(string in1, string in2) {
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
        try {
            sec1Long = std::stoull(sec1, NULL, 16);
            sec2Long = std::stoull(sec2, NULL, 16);
        }
        catch(exception e)
        {
            throw string("Invalid Hex Number!");
        }
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


string BlockChain::ensureLength(string in, int intIn) {

    if (in.length() > intIn) {
        in = in.substr(0, intIn);
    }
    if (in.length() < intIn) {

        for (int i = 0; i < (intIn - in.length()); i++) {
            in = "0" + in;

        }

    }
    // Testing: cout << "Corrected string is: " << in << endl;
    return in;
}

//simply prints the entire Block Chain

string BlockChain::toString() const {
    vector<Block>::const_iterator i;
    int index;
    stringstream stream;
    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = BlockChain::minedBlocks.begin(); i != BlockChain::minedBlocks.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(BlockChain::minedBlocks.begin(), i);
        stream << BlockChain::minedBlocks[index];
        stream << "------------------------------------------------------------" << endl;
    }
    return stream.str();
}

string BlockChain::JSONOutput(string whiteSpaceBeginning, string tag) const {
    vector<Block>::const_iterator i;
    int index;
    stringstream stream;

    string whiteSpaceEnd = "\n";
    string whiteSpaceBeginningWithoutAddedTab = whiteSpaceBeginning;
    whiteSpaceBeginning += "\t";


    stream << whiteSpaceBeginningWithoutAddedTab << tag << "{" << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"numbBlocks\": \"" << BlockChain::minedBlocks.size() << "\"," << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"Block\": [" << whiteSpaceEnd;



    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = BlockChain::minedBlocks.begin(); i != BlockChain::minedBlocks.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(BlockChain::minedBlocks.begin(), i);
        stream << whiteSpaceBeginning << "\t" << BlockChain::minedBlocks[index].JSONOutput("\t\t", "");
        if (index != BlockChain::minedBlocks.size() - 1)
            stream << ",";
        stream << endl;

    }
    stream << whiteSpaceBeginning << "]" << whiteSpaceEnd;
    stream << whiteSpaceBeginningWithoutAddedTab << "}" << whiteSpaceEnd;

    return stream.str();
}


ostream &operator<<(ostream &stream, const BlockChain &in) {
    stream << in.toString();
    return stream;
}


const Block &BlockChain::getBlockFromChain(int in) const {

    return minedBlocks[in];

}

const vector<Block> &BlockChain::getMinedBlocks() const {
    return minedBlocks;
}

void BlockChain::setMinedBlocks(const vector<Block> &minedBlocks) {
    BlockChain::minedBlocks = minedBlocks;
}


const vector<user> &BlockChain::getuserList() const {
    return userList;
}

void BlockChain::setUserList(const vector<user> &listIn) {
    BlockChain::userList = listIn;
}

void BlockChain::addToUserList(const user &in) {
    if (in.getPublicKey().compare("-1") == 0 || BlockChain::isPublicKeyInList(in.getPublicKey()))
        throw string("Public Key Already in Use");
    BlockChain::userList.push_back(in);
}

string BlockChain::userListToString() const {
    if (BlockChain::userList.size() < 1)
        return "";
    vector<user>::const_iterator i;
    int index;
    stringstream stream;

    stream << "User List Length: " << BlockChain::userList.size() << endl;

    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = BlockChain::userList.begin(); i != BlockChain::userList.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(BlockChain::userList.begin(), i);
        stream << BlockChain::userList[index].toString();
        stream << endl;
    }

    return stream.str();

}


string BlockChain::userListJSONOutput(string whiteSpaceBeginning, string tag) const {
    vector<user>::const_iterator i;
    int index;
    stringstream stream;

    string whiteSpaceEnd = "\n";
    string whiteSpaceBeginningWithoutAddedTab = whiteSpaceBeginning;
    whiteSpaceBeginning += "\t";


    stream << whiteSpaceBeginningWithoutAddedTab << tag << "{" << whiteSpaceEnd;

    stream << whiteSpaceBeginning << "\"numbOfUser\": \"" << BlockChain::userList.size() << "\"," << whiteSpaceEnd;

    stream << whiteSpaceBeginning << "\"user\": [";
    if (userList.size() > 0)
        stream << whiteSpaceEnd;



    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = BlockChain::userList.begin(); i != BlockChain::userList.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(BlockChain::userList.begin(), i);
        stream << whiteSpaceBeginning << "\t" << BlockChain::userList[index].JSONOutput("\t\t", "");
        if (index != BlockChain::userList.size() - 1)
            stream << ",";
        stream << endl;

    }
    if (userList.size() > 0)
        stream << whiteSpaceBeginning;
    stream << "]" << whiteSpaceEnd;
    stream << whiteSpaceBeginningWithoutAddedTab << "}" << whiteSpaceEnd;

    return stream.str();
}


user& BlockChain::getUserByPublicKey(const string &publicKey) {

    vector<user>::iterator i;
    int index;
    stringstream stream;
    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = BlockChain::userList.begin(); i != BlockChain::userList.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(BlockChain::userList.begin(), i);
        if (publicKey.compare(userList[index].getPublicKey()) == 0)
            return userList[index];
    }


    throw string("User: "+publicKey+" not on List!");

;
}

user& BlockChain::getUserByPublicKey(const string &publicKey, vector<user> &listIn){

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

bool BlockChain::isPublicKeyInList(const string &publicKey) const {
    vector<user>::const_iterator i;
    int index;
    stringstream stream;
    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = BlockChain::userList.begin(); i != BlockChain::userList.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(BlockChain::userList.begin(), i);
        if (publicKey.compare(userList[index].getPublicKey()) == 0)
            return true;
    }

    return false;
}

bool BlockChain::isPublicKeyInList(const string &publicKey, const vector<user> &listIn) {
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

void BlockChain::addUserIfNotExists(const string &publicKey) {
    if (!isPublicKeyInList(publicKey)) {
        BlockChain::addToUserList(publicKey);
    }
}

void BlockChain::addUserIfNotExists(string publicKey, vector<user> &listIn){
    if (!BlockChain::isPublicKeyInList(publicKey, listIn)) {
        listIn.push_back(publicKey);
    }
}

bool BlockChain::verifyTransactions(const Block &in) const {
    vector<user> tempUserList=BlockChain::userList;
    vector<Transaction>::const_iterator i;
    int index;
    Transaction trans;


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

        if(trans.getAmount()<=0){
            throw string("A positive value must sent!");
        }

        if(getUserByPublicKey(trans.getSenderKey(), tempUserList).getBalance()<0){
            throw string("Insufficient Funds!");
        }


    }

    return true;
}

void BlockChain::addToUserByKey(const string &key, int intIn){
    vector<user>::iterator i;
    int index;
    stringstream stream;
    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = BlockChain::userList.begin(); i != BlockChain::userList.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(BlockChain::userList.begin(), i);
        if (key.compare(userList[index].getPublicKey()) == 0) {
            user temp=BlockChain::userList[index];
            int out=temp.getBalance()+intIn;
            BlockChain::userList[index].setBalance(out);
        }
    }
}

void BlockChain::subtractFromUserByKey(const string &key, int intIn){
    vector<user>::iterator i;
    int index;
    stringstream stream;
    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for (i = BlockChain::userList.begin(); i != BlockChain::userList.end(); ++i) {
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index = std::distance(BlockChain::userList.begin(), i);
        if (key.compare(userList[index].getPublicKey()) == 0) {
            user temp=BlockChain::userList[index];
            int out=temp.getBalance()-intIn;
            BlockChain::userList[index].setBalance(out);
        }
    }
}

bool BlockChain::ensureHex(const string &in) {
    string lower;
    string safeArray[]= {"0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f"};
    vector<string> safeVector(begin(safeArray), end(safeArray));
    std::vector<string>::iterator it;

    for(int i=0; i<in.length(); i++){

        if(in.at(i)!='a' && in.at(i)!='b' && in.at(i)!='c' && in.at(i)!='d' &&
           in.at(i)!='e' && in.at(i)!='f' && in.at(i)!='1' && in.at(i)!='2' &&
           in.at(i)!='3' && in.at(i)!='4' && in.at(i)!='5' && in.at(i)!='6' &&
           in.at(i)!='7' && in.at(i)!='8' && in.at(i)!='9' && in.at(i)!='0' && in.at(i)!='-')
            return false;
    }
    return true;
}
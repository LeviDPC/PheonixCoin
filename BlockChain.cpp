#include "BlockChain.h"


//constructors
BlockChain::BlockChain(const vector<Block> &minedBlocks, const vector<User> &userList) : minedBlocks(minedBlocks),
                                                                                         userList(userList) {}
BlockChain::BlockChain() {}

//Outputs the object and its blocks to a string without the user list
string BlockChain::toString() const {
    vector<Block>::const_iterator i;
    int index;
    stringstream stream;
   
    for (i = BlockChain::minedBlocks.begin(); i != BlockChain::minedBlocks.end(); ++i) {
       
        index = std::distance(BlockChain::minedBlocks.begin(), i);
        stream << BlockChain::minedBlocks[index];
        stream << "------------------------------------------------------------" << endl;
    }
    return stream.str();
}

//Outputs the object's user list to a string
string BlockChain::userListToString() const {
    if (BlockChain::userList.size() < 1)
        return "";
    vector<User>::const_iterator i;
    int index;
    stringstream stream;

    stream << "User List Length: " << BlockChain::userList.size() << endl;

    
    for (i = BlockChain::userList.begin(); i != BlockChain::userList.end(); ++i) {

        index = std::distance(BlockChain::userList.begin(), i);
        stream << BlockChain::userList[index].toString();
        stream << endl;
    }

    return stream.str();

}


//formats and outputs the object and it's blocks as a JSON file without the user list.
//Has the option to input leading white space, an opening tag
//and whether it should be done on one line or multiple.
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




    for (i = BlockChain::minedBlocks.begin(); i != BlockChain::minedBlocks.end(); ++i) {

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

//formats and outputs the object's UserList as a JSON file. Has the option to input leading white space,
//an opening tag and whether it should be done on one line or multiple.
string BlockChain::userListJSONOutput(string whiteSpaceBeginning, string tag) const {
    vector<User>::const_iterator i;
    int index;
    stringstream stream;

    string whiteSpaceEnd = "\n";
    string whiteSpaceBeginningWithoutAddedTab = whiteSpaceBeginning;
    whiteSpaceBeginning += "\t";


    stream << whiteSpaceBeginningWithoutAddedTab << tag << "{" << whiteSpaceEnd;

    stream << whiteSpaceBeginning << "\"numbOfUser\": \"" << BlockChain::userList.size() << "\"," << whiteSpaceEnd;

    stream << whiteSpaceBeginning << "\"User\": [";
    if (userList.size() > 0)
        stream << whiteSpaceEnd;




    for (i = BlockChain::userList.begin(); i != BlockChain::userList.end(); ++i) {

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


//This method takes in a block to be mined and a user key to credit 5 pheonix coins to for successful mining.
//More detailed documentaiton is availiable within the function
string BlockChain::mine(Block blockIn, const string &key) {
    //This is the mining Threshold. When a hash is generated it is checked against this to see if the
    //mining was successful. Right now it is set the the max value a 256 bit hexadecimal number can be.
    //This means that mining is instantaneous for the purpose of testing and demonstration we have left it this way.
    string miningThreshold = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff";
    bool tempBool;
    int nonce;
    time_t curTime;

    //This verifies that all the transactions have valid signatures and that the senders have the currency that they
    //are trying to send.
    verifyTransactions(blockIn);

    //verifies that a valid user key was passed int
    if(!ensureHex(key))
        throw string("Valid input is required for Public Key in order to mine");

    //will keep mining until a hash under the mining threshold is found
    while (true) {

        //gets current time and generates random nonce
        curTime = time(NULL);
        srand(curTime);
        nonce = rand();

        //generates hash
        string hash = blockIn.genHash(curTime, BlockChain::prevHash, nonce);

        //check if hash is equal to or less than the mining threshold
        try{tempBool=hexComp(static_cast<string>(hash), miningThreshold);}
        catch( string e){throw string("Ivalid Hex used in Mining Function"+e);}

        //If it is less than or equal
        if (tempBool) {

            //then setup block
            blockIn.setBlockNumber(BlockChain::minedBlocks.size() + 1);
            blockIn.setManTime(curTime);
            blockIn.setPrevHash(BlockChain::prevHash);
            blockIn.setSelfHash(hash);
            blockIn.setNonce(nonce);

            //if user who did the mining doesn't exist than add them to the user list
            addUserIfNotExists(key);

            //credit them with 5 phoenix coins for successfully mining
            blockIn.addTransaction(Transaction("Pheonix Gen", "-1", "-1", 5, getUserByPublicKey(key).getUserName(), key));

            //apply the transactions and update userlist
            updateUsers(blockIn);

            //add block to minedBlocks List
            BlockChain::minedBlocks.push_back(blockIn);

            //set the BlockChains previous Hash attribute to the hash of hte block that was just mined
            BlockChain::prevHash = hash;


            return hash;
        }

    }


}

//Gets the Nth Block from the BlockChain
const Block &BlockChain::getBlockFromChain(int in) const {

    return minedBlocks[in];

}

//verifies the transactions within the block passed. It verifies both the transaction signatures and it
//checks with the BlockChains UserList to make sure tha tall senders have the currency they are trying to send
bool BlockChain::verifyTransactions(const Block &in) const {
    vector<User> tempUserList=BlockChain::userList;
    vector<Transaction>::const_iterator i;
    int index;
    Transaction trans;



    for (i = in.getTransactions().begin(); i != in.getTransactions().end(); ++i) {

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



//adds a user to the user list
void BlockChain::addToUserList(const User &in) {
    if (in.getPublicKey().compare("-1") == 0 || BlockChain::isPublicKeyInList(in.getPublicKey()))
        throw string("Public Key Already in Use");
    BlockChain::userList.push_back(in);
}

//Takes in a block it's transactions to the user list
void BlockChain::updateUsers(const Block &in) {
    vector<Transaction>::const_iterator i;
    int index;
    Transaction trans;



    for (i = in.getTransactions().begin(); i != in.getTransactions().end(); ++i) {

        index = std::distance(in.getTransactions().begin(), i);
        trans = in.getTransactions()[index];

        if(in.getTransactions()[index].getSenderKey().compare("-1")!=0)
            getUserByPublicKey(trans.getSenderKey()) -= trans.getAmount();

        addUserIfNotExists(trans.getReceiverKey());
        getUserByPublicKey(trans.getReceiverKey())+=trans.getAmount();

    }
}


//find a user in a userList based on it's public key and return it. There is a static version that accepts
//a userList as an argument and a non static version that uses the BlockChain object's userList
User& BlockChain::getUserByPublicKey(const string &publicKey) {

    vector<User>::iterator i;
    int index;
    stringstream stream;

    for (i = BlockChain::userList.begin(); i != BlockChain::userList.end(); ++i) {

        index = std::distance(BlockChain::userList.begin(), i);
        if (publicKey.compare(userList[index].getPublicKey()) == 0)
            return userList[index];
    }


    throw string("User: "+publicKey+" not on List!");

;
}

User& BlockChain::getUserByPublicKey(const string &publicKey, vector<User> &listIn){

    vector<User>::iterator i;
    int index;
    stringstream stream;

    for (i = listIn.begin(); i != listIn.end(); ++i) {

        index = std::distance(listIn.begin(), i);
        if (publicKey.compare(listIn[index].getPublicKey()) == 0)
            return listIn[index];
    }

    throw string("User not on List");
}


//Checks if there is a user on a user list with the specified key. There is a static version that accepts
//a userList as an argument and a non static version that uses the BlockChain object's userList
bool BlockChain::isPublicKeyInList(const string &publicKey) const {
    vector<User>::const_iterator i;
    int index;
    stringstream stream;

    for (i = BlockChain::userList.begin(); i != BlockChain::userList.end(); ++i) {

        index = std::distance(BlockChain::userList.begin(), i);
        if (publicKey.compare(userList[index].getPublicKey()) == 0)
            return true;
    }

    return false;
}

bool BlockChain::isPublicKeyInList(const string &publicKey, const vector<User> &listIn) {
    vector<User>::const_iterator i;
    int index;
    stringstream stream;

    for (i = listIn.begin(); i != listIn.end(); ++i) {

        index = std::distance(listIn.begin(), i);
        if (publicKey.compare(listIn[index].getPublicKey()) == 0)
            return true;
    }

    return false;
}


//Checks if there is a user on a user list with the specified user Key. If the user isn't on the list it adds them.
//There is a static version that accepts a userList as an argument and a non static version that uses the
// BlockChain object's userList
void BlockChain::addUserIfNotExists(const string &publicKey) {
    if (!isPublicKeyInList(publicKey)) {
        BlockChain::addToUserList(publicKey);
    }
}

void BlockChain::addUserIfNotExists(string publicKey, vector<User> &listIn){
    if (!BlockChain::isPublicKeyInList(publicKey, listIn)) {
        listIn.push_back(publicKey);
    }
}


//Ensures that a string is a certain length. If the string is greater than it will take the first N Characters
//If the string is less than it will add leading zeros to the string
string BlockChain::ensureLength(string in, int intIn) {

    if (in.length() > intIn) {
        in = in.substr(0, intIn);
    }
    if (in.length() < intIn) {

        for (int i = 0; i < (intIn - in.length()); i++) {
            in = "0" + in;

        }

    }

    return in;
}

//Ensures that a string is non empty valid Hex Number
bool BlockChain::ensureHex(const string &in) {
    string lower;
    char character;

    if(in.compare("")==0)
        return false;

    for(int i=0; i<in.length(); i++){

        if(in.at(i)!='-')
            character=char(tolower(in.at(i)));
        else
            character='-';

        if(character!='a' && character!='b' && character!='c' && character!='d' &&
           character!='e' && character!='f' && character!='1' && character!='2' &&
           character!='3' && character!='4' && character!='5' && character!='6' &&
           character!='7' && character!='8' && character!='9' && character!='0' && character!='-')
            return false;
    }
    return true;
}

//This function takes in two 64 digit (256 bit) hexadecimal numbers as strings and compares them. It returns true
// if the first parameter is less than or equal to the second one and false otherwise.
// If the input is input is less than 64 digits than the ensureLength function will add 0s at the beelining of the
// String. If it is more than it will just take the first 64 digits.
bool BlockChain::hexComp(string in1, string in2) {

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

        if (sec1Long < sec2Long) {

            return true;
        }
        if (sec1Long > sec2Long) {
            return false;
        }
    }


    return true;

}



//overload operators for istream and ostream
ostream &operator<<(ostream &stream, const BlockChain &in) {
    stream << in.toString();
    return stream;
}

istream &operator>>(istream &stream, BlockChain &in){
    int userNum=0;
    int blockNum=0;

    vector<User> tempUserList;
    vector<Block> tempBlockList;

    Block tempBlock;
    User tempUser;

    cout<<"Please input how many users you would like to enter: ";
    stream>>userNum;
    cout<<endl;

    for(int i=0; i<userNum; i++){
        tempUser=User();
        stream>>tempUser;
        tempUserList.push_back(tempUser);
    }

    in.setUserList(tempUserList);

    cout<<"Please input how many blocks you would like to enter: ";
    stream>>blockNum;
    cout<<endl;

    for(int i=0; i<blockNum; i++){
        tempBlock=Block();
        stream>>tempBlock;
        tempBlockList.push_back(tempBlock);
    }

    in.setMinedBlocks(tempBlockList);


    return stream;

}




//Setters and Getters
const vector<Block> &BlockChain::getMinedBlocks() const {
    return minedBlocks;
}

void BlockChain::setUserList(const vector<User> &listIn) {
    BlockChain::userList = listIn;
}

void BlockChain::setMinedBlocks(const vector<Block> &minedBlocks) {
    BlockChain::minedBlocks = minedBlocks;
}

const vector<User> &BlockChain::getuserList() const {
    return userList;
}

const string &BlockChain::getPrevHash() const {
    return prevHash;
}

void BlockChain::setPrevHash(const string &prevHash) {
    BlockChain::prevHash = prevHash;
}

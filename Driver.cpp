//
// Created by Levi on 12/10/2018.
//

#include "Driver.h"

//constructors
Driver::Driver() {}

Driver::Driver(const string &configName, const string &resultFileName, const Block &unminedBlock,
               const BlockChain &primaryChain) : configName(configName), unminedBlock(unminedBlock),
               primaryChain(primaryChain) {}



//primary method
const string Driver::drive() {


    bool opPerformed = false;
    string op = "";
    string out="";

    op = getOpFromConfigFile();



    if (op.compare("newuser") == 0) {

        opPerformed = true;

        try{
            out=newUser();
            return out;}
        catch(string e)
        {
            throw string("Error creating new User! "+e);
        }

    }

    if (op.compare("newtrans") == 0) {
        opPerformed = true;
        try{
            out=newTrans();
            return out;
        }
        catch(string e)
        {
            throw string("Error creating new transaction! "+e);
        }
    }

    if (op.compare("mine") == 0) {
        opPerformed = true;

        try{
            out=mine();
            return out;
        }
        catch(string e)
        {
            throw string("Error Mining! "+e);
        }

    }


    if (op.compare("run") == 0) {
        stringstream stream;
        opPerformed = true;
        stream<<"{"<<endl;
        stream << "\t\"status\" : \"Success!\","<<endl;
        stream<<"\t\"operation\" : \"Program Ran!\"" << endl;
        stream <<"}";
        return stream.str();
    }

    if (opPerformed == false)
        return "No Valid Operation Selected!";
}


//These next three methods are worker methods
const string Driver::newUser() {

    if (Driver::getLinesInConfig() < 2 || Driver::getLinesInConfig() > 4) {
        throw string("Invalid input File");
    }

    string publicKey = "";
    string privateKey = "";
    string userName = "";
    fstream config(configName);
    bool hasKeySet = false;
    string line = "";


    getline(config, line);
    getline(config, line);

    if (line.compare("true") == 0)
        hasKeySet = true;
    else if (line.compare("false") != 0) {
        throw string("Import Key boolean must be true or false");

    }

    getline(config, userName);
    getline(config, publicKey);


    User out;
    //
    if (hasKeySet) {

        try {
            out.setPublicKey(publicKey);
        }
        catch (string e) {
            throw e;

        }
    } else {
        privateKey = User::genPrivateKey();
        out.genSetPublicKey(privateKey);
    }

    out.setBalance(0);

    out.setUserName(userName);

    primaryChain.addToUserList(out);

    stringstream stream;
    stream<<"{";
    stream << "\t\"status\" : \"Success!\","<<endl;
    stream<<"\t\"operation\" : \"New User created\"," << endl;
    stream << "\t\"username\" : \"" << out.getUserName()<<"\"," << endl;
    stream << "\t\"publickey\" : \"" << out.getPublicKey()<<"\"," << endl;
    stream << "\t\"privatekey\" : \"" << privateKey<<"\"," << endl;
    stream << "\t\"balance\" : \"" << out.getBalance()<<"\"" << endl;
    stream <<"}";

    return stream.str();

}


const string Driver::newTrans() {
    string senderKey = "";
    string senderPrivateKey = "";
    string amount = "";

    string receiverKey = "";

    Block tempBlock;

    fstream config(configName);

    string line = "";



    if (getLinesInConfig() != 5) {
        if(getLinesInConfig()==4)
            throw string("Unable to set Receiver Key: Reciever Key cannot be Blank");
        else
            throw string("Invalid Config File");
    }





    getline(config, line);
    getline(config, senderKey);
    getline(config, senderPrivateKey);
    getline(config, amount);
    getline(config, receiverKey);


    Transaction out;


        try{out.setSenderKey(senderKey);}
        catch (string e) {throw string("Unable to Set Sender Key: "+e);}

        out.setSenderSig(User::genSignature(senderPrivateKey));


        try{out.setReceiverKey(receiverKey);}
        catch (string e) {throw string("Unable to Set Reciever Key: "+e);}

        try{out.setAmount(stoi(amount));}
        catch (exception e) {throw string("Transaction amount must be valid base 10 Number");}
        out.setAutoTime();


    try {
        tempBlock.addTransaction(out);
        primaryChain.verifyTransactions(tempBlock);

    }
    catch (string e) {
        throw e;
    }
    if (!primaryChain.isPublicKeyInList(receiverKey))
        primaryChain.addToUserList(User(receiverKey));



    try {out.setReceiverName(primaryChain.getUserByPublicKey(receiverKey).getUserName());}
    catch(string e){throw string("Problem with Reciever Key! "+e);}

    try {out.setSenderName(primaryChain.getUserByPublicKey(senderKey).getUserName());}
    catch(string e){throw string("Problem with Sender Key! "+e);}


    if (out.getAmount() <= 0) {

        throw string("A positive value must sent!");


    }

    if (primaryChain.getUserByPublicKey(senderKey).getBalance() < out.getAmount()) {
        throw string("Insufficient Funds!");

    }


    unminedBlock.addTransaction(out);

    stringstream stream;

    stream<<"{";
    stream << "\t\"status\" : \"Success!\","<<endl;
    stream<<"\t\"operation\" : \"New Transaction Created!\"," << endl;
    stream << "\t\"sendername\" : \"" << out.getSenderName()<<"\"," << endl;
    stream << "\t\"senderkey\" : \"" << out.getSenderKey()<<"\"," << endl;
    stream << "\t\"amount\" : \"" << out.getAmount()<<"\"," << endl;
    stream << "\t\"receivername\" : \"" << out.getReceiverName()<<"\"," << endl;
    stream << "\t\"receiverkey\" : \"" << out.getReceiverKey()<<"\"," << endl;
    stream << "\t\"time\" : \"" << out.getTime()<<"\"" << endl;
    stream <<"}";


    return stream.str();

}


const string Driver::mine() {
    ifstream config(configName);
    string key;
    string hash="";


    getline(config, key);
    getline(config, key);


    try {

        hash = primaryChain.mine(unminedBlock, key);

    }
    catch (string e) {

        throw e;
    }

    unminedBlock = Block();

    stringstream stream;

    stream<<"{";
    stream << "\t\"status\" : \"Success!\","<<endl;
    stream<<"\t\"operation\" : \"Block Mined!\"," << endl;
    stream << "\t\"hash\" : \"" << hash<<"\"," << endl;
    stream << "\t\"userkey\" : \"" << key<<"\"" << endl;
    stream <<"}";

    return stream.str();

}

//method to output objects that opperations were prefomed on
void Driver::outPut(Block &blockIn, BlockChain &blockChainIn) {
    blockIn = Driver::unminedBlock;
    blockChainIn = Driver::primaryChain;
}


//helper Methods
//This method gets the opperation to perform from the config file
const string Driver::getOpFromConfigFile() {
    string line = "";
    ifstream config(Driver::configName);
    if (config.is_open())
        getline(config, line);
    config.close();
    return line;

}

//This opperation gets the ammount of lines in the config file
const int Driver::getLinesInConfig() {
    ifstream config(Driver::configName);
    string line = "";
    int count = 0;
    while (config.peek() != EOF) {
        count++;
        getline(config, line);
    }
    config.close();
    return count;
}


//setters and getters
const string &Driver::getConfigName() const {
    return configName;
}

void Driver::setConfigName(const string &configName) {
    Driver::configName = configName;
}

const BlockChain &Driver::getPrimaryChain() const {
    return primaryChain;
}

void Driver::setPrimaryChain(const BlockChain &primaryChain) {
    Driver::primaryChain = primaryChain;
}

const Block &Driver::getUnminedBlock() const {
    return unminedBlock;
}

void Driver::setUnminedBlock(const Block &unminedBlock) {
    Driver::unminedBlock = unminedBlock;
}

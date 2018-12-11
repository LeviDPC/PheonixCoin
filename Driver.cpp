//
// Created by Levi on 12/10/2018.
//

#include "Driver.h"

Driver::Driver() {}

Driver::Driver(const string &configName, const string &resultFileName, const Block &unminedBlock,
               const BlockChain &primaryChain) : configName(configName), resultFileName(resultFileName),
                                                 unminedBlock(unminedBlock), primaryChain(primaryChain) {}


void Driver::outPutResults(const string &in) {
    ofstream result(resultFileName);
    if (result.is_open())
        result << in;
    result.close();
}

string Driver::getOpFromConfigFile() {
    string line = "";
    ifstream config(Driver::configName);
    if (config.is_open())
        getline(config, line);
    config.close();
    return line;

}

int Driver::getLinesInConfig() {
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

void Driver::drive() {


    bool opPerformed = false;
    string op = "";
    op = getOpFromConfigFile();
    //--


    if (op.compare("newuser") == 0) {

        opPerformed = true;
        newUser();

    }

    if (op.compare("newtrans") == 0) {
        opPerformed = true;
        newTrans();
    }

    if (op.compare("mine") == 0) {
        opPerformed = true;
        mine();
    }


    if (op.compare("run") == 0) {
        opPerformed = true;
        outPutResults("Success!\nProgram Run");
    }

    if (opPerformed == false)
        outPutResults("Error!\nNo Valid Operation Selected!");
}

int Driver::newUser() {

    if (Driver::getLinesInConfig() < 2 || Driver::getLinesInConfig() > 4) {
        outPutResults("Error!\nInvalid Information Passed in!");
        return -1;
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
        outPutResults("Error!\nImport Key boolean must be true or false");
        return -1;
    }

    getline(config, userName);
    getline(config, publicKey);


    user out;
    //
    if (hasKeySet) {

        try {
            out.setPublicKey(publicKey);
        }
        catch (string e) {
            outPutResults("Error!\n" + static_cast<string>(e));
            return 111;
        }
    } else {
        privateKey = user::genPrivateKey();
        out.genSetPublicKey(privateKey);
    }

    out.setBalance(0);

    out.setUserName(userName);

    primaryChain.addToUserList(out);

    stringstream stream;
    stream << "Success!\nNew user created" << endl;
    stream << "UserName: " << out.getUserName() << endl;
    stream << "Public Key: " << out.getPublicKey() << endl;
    stream << "Private Key: " << privateKey << endl;
    stream << "Balance: " << out.getBalance() << endl;

    outPutResults(stream.str());

    return 0;

}


int Driver::newTrans() {
    if (getLinesInConfig() != 5) {
        outPutResults("Error!\nInvalid Information Passed in!");
        return -1;
    }


    string senderKey = "";
    string senderPrivateKey = "";
    string amount = "";


    string receiverKey = "";

    fstream config(configName);

    string line = "";


    getline(config, line);
    getline(config, senderKey);
    getline(config, senderPrivateKey);
    getline(config, amount);
    getline(config, receiverKey);


    Transaction out;

    try {
        out.setSenderKey(senderKey);
        out.setSenderSig(user::genSignature(senderPrivateKey));
        out.setReceiverKey(receiverKey);
        out.setAmount(stoi(amount));
    }
    catch (string e) {
        outPutResults("Error!\n" + e);
        return -1;
    }

    try {
        out.verifyTransaction(primaryChain.getuserList());
    }
    catch (string e) {
        outPutResults("Error!\n" + e);
        return -1;
    }
    if (!primaryChain.isPublicKeyInList(receiverKey))
        primaryChain.addToUserList(user(receiverKey));

    out.setReceiverName(primaryChain.getUserByPublicKey(receiverKey).getUserName());
    out.setSenderName(primaryChain.getUserByPublicKey(senderKey).getUserName());

    if (out.getAmount() <= 0) {

        outPutResults("Error\nA positive value must sent!");
        return -1;

    }

    if (primaryChain.getUserByPublicKey(senderKey).getBalance() < out.getAmount()) {
        outPutResults("Error!\nInsufficient Funds!");
        return -1;
    }


    unminedBlock.addTransaction(out);

    stringstream stream;
    stream << "Success!\nNew Transaction Created!" << endl;
    stream << out;

    outPutResults(stream.str());

    return 0;
}


int Driver::mine() {
    ifstream config(configName);

    string key;

    getline(config, key);

    getline(config, key);


    try {
        string hash = primaryChain.mine(unminedBlock, key);
        outPutResults("Success!\nBlock Hash: " + hash);
        unminedBlock = Block();
    }
    catch (string e) {
        outPutResults("Error!\n" + e);
        return -1;
    }
}


void Driver::outPut(Block &blockIn, BlockChain &blockChainIn) {
    blockIn = Driver::unminedBlock;
    blockChainIn = Driver::primaryChain;
}


const string &Driver::getConfigName() const {
    return configName;
}

void Driver::setConfigName(const string &configName) {
    Driver::configName = configName;
}

const string &Driver::getResultFileName() const {
    return resultFileName;
}

void Driver::setResultFileName(const string &resultFileName) {
    Driver::resultFileName = resultFileName;
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

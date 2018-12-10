//This now uses sha256 for hashing. This functionality comes from the file picosha2.h. I got it from google. Its
// open source under the MIT licence. The licence is included in the file itself.

//TODO:
//Next up:

//      mine needs to update balance of users
//      do IO in a class
// Eventually:
//      implemnt bool verifyTransaction(const vector<user> &userListIn) in transaction
//      implemnt verifyTransactions(blockIn.getTransactions()) in blockchain.cpp
//      implement veirfySignature() in transaction.cpp
//      implement genSignature() in user.cpp
//      implement verify keys imputed are in hex form with throwing errors
//      inputting users into transactions
//      increase polymorphism in main

#include <iostream>
#include <string>
#include <fstream>
#include "transaction.h"
#include "block.h"
#include "blockChain.h"
#include "user.h"

using namespace std;

string getOpFromConfigFile();

string configName = "cppConfig.txt";

string resultFileName = "result.txt";

string userFileName = "users.json";

string unminedBlockFileName = "unminedBlock.json";

string blockChainFileName = "blockchain.json";

string tempFileName="temp.json";

void outPutResults(const string &in);

int getLines(string nameOfFile);

int newUser(blockChain &blockChainIn);

int newTrans(block &blockIn, blockChain &blockChainIn);

int mine(block &blockIn, blockChain &blockChainIn);

void writeBlockChain(const blockChain &blockChainIn);

void writeUsers(const blockChain &blockChainIn);

void writeUnminedBlock(const block &blockIn);


void printFile(string fileName);

void loadData(block &blockIn, blockChain &blockChainIn);


int loadBlockData(block &blockIn, string inputFileName=unminedBlockFileName);

void loadBlockChainData(blockChain &blockChainIn);

int loadUserData(blockChain &blockChainIn);

void skipLine(ifstream &, int = 1);

string getBetweenQuestionMakrs(const string &stringIn, int intIn);

transaction transFromString(const string &in);

void addLinesToStream(ofstream &outStream, ifstream &inStream, int number);

int runNumb=1;

int main() {
    blockChain primaryChain = blockChain();
    block unminedBlock = block();

    loadData(unminedBlock, primaryChain);

    //




    //primaryChain.addToUserList(user("Levi Pfantz", "325423432", 0));
    //primaryChain.addToUserList(user("Hunter", "4563544334252", 43));
    //primaryChain.addToUserList(user("Ibrahim", "547576", 555));

    bool opPerformed = false;
    string op = "";
    op = getOpFromConfigFile();
    //--


    if (op.compare("newuser") == 0) {

        opPerformed = true;
        newUser(primaryChain);

    }

    if (op.compare("newtrans") == 0) {
        opPerformed = true;
        newTrans(unminedBlock, primaryChain);
    }

    if (op.compare("mine") == 0) {
        opPerformed = true;
        mine(unminedBlock, primaryChain);
    }


    if (op.compare("run") == 0) {
        opPerformed = true;
        outPutResults("Success!\nProgram Run");
    }

    if (opPerformed == false)
        outPutResults("Error!\nNo Valid Operation Selected!");


    writeBlockChain(primaryChain);
    writeUsers(primaryChain);
    writeUnminedBlock(unminedBlock);


    //printFile(configName);

    //system("Pause");

        return 0;
}

void loadData(block &blockIn, blockChain &blockChainIn) {
    if (getLines(unminedBlockFileName) > 0)
        loadBlockData(blockIn);

    if (getLines(blockChainFileName) > 0)
        loadBlockChainData(blockChainIn);

    if (getLines(userFileName) > 0) {
        loadUserData(blockChainIn);
    }
}

int loadBlockData(block &blockIn, string inputFileName) {
    block out = block();
    string line = "";
    ifstream inputFile(inputFileName);
    string blockNum;
    string blockGenTime;
    string blockHash;
    string prevBlockHash;
    string nonce;
    string numTransString;
    int numTrans;


    skipLine(inputFile, 2);

    getline(inputFile, line);
    blockNum = getBetweenQuestionMakrs(line, 2);

    getline(inputFile, line);
    blockGenTime = getBetweenQuestionMakrs(line, 2);

    getline(inputFile, line);
    blockHash = getBetweenQuestionMakrs(line, 2);

    getline(inputFile, line);
    prevBlockHash = getBetweenQuestionMakrs(line, 2);

    getline(inputFile, line);
    nonce = getBetweenQuestionMakrs(line, 2);

    getline(inputFile, line);
    numTransString = getBetweenQuestionMakrs(line, 2);


    skipLine(inputFile);

    try {

        out.setBlockNumber(std::stoi(blockNum));

        out.setTime(std::stoi(blockGenTime));

        out.setSelfHash(blockHash);
        out.setPrevHash(prevBlockHash);

        out.setNonce(stoi(nonce));

        numTrans = stoi(numTransString);

    }

    catch (exception e) {

        outPutResults("Error!\n" + static_cast<string>(e.what()));
        if(inputFileName.compare(unminedBlockFileName)==0)
        exit(201);
        else
            exit(301);
    }

    for (int i = 0; i < numTrans; i++) {
        getline(inputFile, line);
        out.addTransaction(transFromString(line));
    }

    inputFile.close();

    blockIn = out;

    runNumb++;
    return 0;
}

transaction transFromString(const string &in) {
    string line = in;



    transaction out = transaction();



    string userName = getBetweenQuestionMakrs(line, 2);
    string senderKey = getBetweenQuestionMakrs(line, 4);
    string senderSig = getBetweenQuestionMakrs(line, 6);
    string amount = getBetweenQuestionMakrs(line, 8);
    string receiverName = getBetweenQuestionMakrs(line, 10);
    string receiverKey = getBetweenQuestionMakrs(line, 12);
    string time = getBetweenQuestionMakrs(line, 14);

    try {
        out.setSenderName(userName);
        out.setSenderKey(senderKey);
        out.setSenderSig(senderSig);
        out.setReceiverName(receiverName);
        out.setReceiverKey(receiverKey);

        out.setAmount(stoi(amount)); //this method is throwing the error

        out.setManTime(stoi(time));
    }
     catch (exception e) {
        outPutResults("Error!\n" + static_cast<string>(e.what()));
        exit(-112);
    }

    return out;

}

void loadBlockChainData(blockChain &blockChainIn) {
    ifstream inputFile(blockChainFileName);
    ofstream temp(tempFileName);
    vector<block> tempList;
    block tempBlock;
    int numbBlocks;
    int numbTrans;
    string line;
    stringstream builder;

    skipLine(inputFile,2);

    getline(inputFile,line);

    try{
        numbBlocks=stoi(getBetweenQuestionMakrs(line, 2));
    } catch (exception e) {
        outPutResults("Error!\n" + static_cast<string>(e.what()));
        exit(-125);
    }


    for(int i=0; i<numbBlocks; i++){
        builder=stringstream();
        builder<<i<<tempFileName;
        temp=ofstream(builder.str());
        tempBlock=block();
        addLinesToStream(temp, inputFile, 9);
        getline(inputFile, line);

        while(line.find("]")==string::npos){
            temp<<line<<endl;

            getline(inputFile,line);

        }
        temp.close();


        loadBlockData(tempBlock, builder.str());

        tempList.push_back(tempBlock);
        

        
    }
    blockChainIn.setMinedBlocks(tempList);
    inputFile.close();
}

int loadUserData(blockChain &blockChainIn) {
    vector<user> out;
    user temp = user();
    ifstream inputFile(userFileName);
    string line = "";
    string numbOfUsersString = "";

    string userName = "";
    string userKey = "";
    int balance = 0;

    skipLine(inputFile, 4);

    getline(inputFile, line);


    while (line.find("{")!=std::string::npos) {

        getline(inputFile, line);
        userName = getBetweenQuestionMakrs(line, 2);

        getline(inputFile, line);
        userKey = getBetweenQuestionMakrs(line, 2);

        getline(inputFile, line);

        try {
            balance = stoi(getBetweenQuestionMakrs(line, 2));
        }
        catch (string e) {
            outPutResults("Error!\n" + e);
            exit(-143);
        }

        skipLine(inputFile);
        getline(inputFile, line);

        temp.setUserName(userName);
        temp.setPublicKey(userKey);
        temp.setBalance(balance);
        out.push_back(temp);

    }



    blockChainIn.setUserList(out);


}

void skipLine(ifstream &streamIn, int intIn) {
    string temp;
    for (int i = 0; i < intIn; i++)
        getline(streamIn, temp);
}

string getBetweenQuestionMakrs(const string &stringIn, int intIn = 1) {
    int firstMark;
    int secondMark = -1;
    for (int i = 0; i < intIn; i++) {
        firstMark = stringIn.find("\"", secondMark + 1);
        secondMark = stringIn.find("\"", firstMark + 1);
    }
    return stringIn.substr(firstMark + 1, secondMark - firstMark - 1);
}

string getOpFromConfigFile() {
    string line = "";
    ifstream config(configName);
    if (config.is_open())
        getline(config, line);
    config.close();
    return line;

}

void addLinesToStream(ofstream &outStream, ifstream &inStream, int number=1){
    string line;
    for(int i=0; i<number; i++){
        getline(inStream, line);
        outStream<<line<<endl;

    }

}

void outPutResults(const string &in) {
    ofstream result(resultFileName);
    if (result.is_open())
        result << in;
    result.close();
}

int getLines(string nameOfFile = configName) {
    ifstream config(nameOfFile);
    string line = "";
    int count = 0;
    while (config.peek() != EOF) {
        count++;
        getline(config, line);
    }
    config.close();
    return count;
}


int newUser(blockChain &blockChainIn) {

    if (getLines() < 2 || getLines() > 4) {
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
        outPutResults("Error!\nInvalid Information Passed in!");
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

    blockChainIn.addToUserList(out);

    stringstream stream;
    stream << "Success!\nNew user created" << endl;
    stream << "UserName: " << out.getUserName() << endl;
    stream << "Public Key: " << out.getPublicKey() << endl;
    stream << "Private Key: " << privateKey << endl;
    stream << "Balance: " << out.getBalance() << endl;

    outPutResults(stream.str());

    return 0;

}

int newTrans(block &blockIn, blockChain &blockChainIn) {
    if (getLines() != 5) {
        outPutResults("Error!\nInvalid Information Passed in!");
        return -1;
    }


    string senderKey = "";
    string senderPrivateKey = "";
    string amount="";

    string receiverKey = "";

    fstream config(configName);

    string line = "";


    getline(config, line);
    getline(config, senderKey);
    getline(config, senderPrivateKey);
    getline(config, amount);
    getline(config, receiverKey);


    transaction out;

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
        out.verifyTransaction(blockChainIn.getuserList());
    }
    catch (string e) {
        outPutResults("Error!\n" + e);
        return -1;
    }
    if (!blockChainIn.isPublicKeyInList(receiverKey))
        blockChainIn.addToUserList(user(receiverKey));

    out.setReceiverName(blockChainIn.getUserByPublicKey(receiverKey).getUserName());
    out.setSenderName(blockChainIn.getUserByPublicKey(senderKey).getUserName());
    blockIn.addTransaction(out);

    stringstream stream;
    stream << "Success!\nNew Transaction Created!" << endl;
    stream << out;

    outPutResults(stream.str());

    return 0;
}

int mine(block &blockIn, blockChain &blockChainIn) {
    ifstream config(configName);
    string line;
    string key;

    skipLine(config);

    getline(config, line);

    key=getBetweenQuestionMakrs(line,2);


    try {
        string hash = blockChainIn.mine(blockIn, key);
        outPutResults("Success!\nBlock Hash: " + hash);
        blockIn=block();
    }
    catch (string e) {
        outPutResults("Error!\n" + e);
        return -1;
    }
}

void writeBlockChain(const blockChain &blockChainIn) {
    ofstream out(blockChainFileName);
    if (out.is_open()) {
        out << "{" << endl;
        out << blockChainIn.JSONOutput();
        out << "}";
    }
    out.close();

}

void writeUsers(const blockChain &blockChainIn) {

    ofstream out(userFileName);
    if (out.is_open()) {
        out << "{" << endl;
        out << blockChainIn.userListJSONOutput() << endl;
        out << "}";
    }
    out.close();


}

void writeUnminedBlock(const block &blockIn) {
    ofstream out(unminedBlockFileName);
    if (out.is_open()) {
        out << "{" << endl;
        out << blockIn.JSONOutput() << endl;
        out << "}";
    }
    out.close();


}

void printFile(string fileName) {
    fstream fileIn(fileName);
    string line;
    while (fileIn.peek() != EOF) {
        getline(fileIn, line);
        cout << line;
        if (line.compare("") == 0)
            cout << "BLANK";
    }

}

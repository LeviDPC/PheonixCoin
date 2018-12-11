//This now uses sha256 for hashing. This functionality comes from the file picosha2.h. I got it from google. Its
// open source under the MIT licence. The licence is included in the file itself.

//TODO:
//Next up:

//
//      do IO in a class
// Eventually:
//      implemnt bool verifyTransaction(const vector<user> &userListIn) in Transaction
//      implemnt verifyTransactions(blockIn.getTransactions()) in blockchain.cpp
//      implement veirfySignature() in Transaction.cpp
//      implement genSignature() in user.cpp
//      implement verify keys imputed are in hex form with throwing errors
//      inputting users into transactions
//      increase polymorphism in main

#include <iostream>
#include <string>
#include <fstream>
#include "Transaction.h"
#include "Block.h"
#include "BlockChain.h"
#include "User.h"
#include "Driver.h"

using namespace std;



string configName = "cppConfig.txt";

string resultFileName = "result.txt";

string userFileName = "users.json";

string unminedBlockFileName = "unminedBlock.json";

string blockChainFileName = "blockchain.json";

string tempFileName="temp.json";

void outPutResults(const string &in);

int getLines(string nameOfFile);

void writeBlockChain(const BlockChain &blockChainIn);

void writeUsers(const BlockChain &blockChainIn);

void writeUnminedBlock(const Block &blockIn);

void printFile(string fileName);

void loadData(Block &blockIn, BlockChain &blockChainIn);


int loadBlockData(Block &blockIn, string inputFileName=unminedBlockFileName);

void loadBlockChainData(BlockChain &blockChainIn);

int loadUserData(BlockChain &blockChainIn);

void skipLine(ifstream &, int = 1);

string getBetweenQuestionMakrs(const string &stringIn, int intIn);

Transaction transFromString(const string &in);

void addLinesToStream(ofstream &outStream, ifstream &inStream, int number);

int runNumb=1;

int main() {
    BlockChain primaryChain = BlockChain();
    Block unminedBlock = Block();


    loadData(unminedBlock, primaryChain);

    Driver driver(configName, resultFileName, unminedBlock, primaryChain);

    driver.drive();

    driver.outPut(unminedBlock, primaryChain);




    //primaryChain.addToUserList(user("Levi Pfantz", "325423432", 0));
    //primaryChain.addToUserList(user("Hunter", "4563544334252", 43));
    //primaryChain.addToUserList(user("Ibrahim", "547576", 555));



    writeBlockChain(primaryChain);
    writeUsers(primaryChain);
    writeUnminedBlock(unminedBlock);


    //printFile(configName);

    //system("Pause");

        return 0;
}

void loadData(Block &blockIn, BlockChain &blockChainIn) {
    if (getLines(unminedBlockFileName) > 0)
        loadBlockData(blockIn);

    if (getLines(blockChainFileName) > 0)
        loadBlockChainData(blockChainIn);

    if (getLines(userFileName) > 0) {
        loadUserData(blockChainIn);
    }
}

int loadBlockData(Block &blockIn, string inputFileName) {
    Block out = Block();
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

Transaction transFromString(const string &in) {
    string line = in;



    Transaction out = Transaction();



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

void loadBlockChainData(BlockChain &blockChainIn) {
    ifstream inputFile(blockChainFileName);
    ofstream temp(tempFileName);
    vector<Block> tempList;
    Block tempBlock;
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
        tempBlock=Block();
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

int loadUserData(BlockChain &blockChainIn) {
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








void writeBlockChain(const BlockChain &blockChainIn) {
    ofstream out(blockChainFileName);
    if (out.is_open()) {
        out << "{" << endl;
        out << blockChainIn.JSONOutput();
        out << "}";
    }
    out.close();

}

void writeUsers(const BlockChain &blockChainIn) {

    ofstream out(userFileName);
    if (out.is_open()) {
        out << "{" << endl;
        out << blockChainIn.userListJSONOutput() << endl;
        out << "}";
    }
    out.close();


}

void writeUnminedBlock(const Block &blockIn) {
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

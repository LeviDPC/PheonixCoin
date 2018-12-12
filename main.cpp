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
#include "Serializer.h"

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


int loadUnminedBlockData(Block &blockIn, string inputFileName=unminedBlockFileName);

void loadBlockChainData(BlockChain &blockChainIn);

int loadUserData(BlockChain &blockChainIn);

void skipLineMain(ifstream &, int = 1);

string getBetweenQuestionMarks(const string &stringIn, int intIn);

Transaction transFromString(const string &in);

void addLinesToStreamMainMain(ofstream &outStream, ifstream &inStream, int number);

int runNumb=1;

int main() {
    BlockChain primaryChain = BlockChain();
    Block unminedBlock = Block();
    Serializer serializer;
    Driver driver;

    //loadData(unminedBlock, primaryChain);

    unminedBlock=serializer.readBlock(unminedBlockFileName);
    primaryChain=serializer.readBlockChain(blockChainFileName);
    primaryChain.setUserList(serializer.readUserList(userFileName));

    driver =Driver(configName, resultFileName, unminedBlock, primaryChain);

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
    if (getLines(unminedBlockFileName) > 0) {
        try{
        loadUnminedBlockData(blockIn);}
        catch (string e)
        {
            outPutResults("Error!\n "+e);
            exit(532);
        }
    }

    if (getLines(blockChainFileName) > 0)
    {
        try{
            loadBlockChainData(blockChainIn);}
        catch (string e)
        {
            outPutResults("Error!\n "+e);
            exit(570);
        }
    }

    if (getLines(userFileName) > 0) {
        loadUserData(blockChainIn);
    }
}

int loadUnminedBlockData(Block &blockIn, string inputFileName) {
    Block out = Block();
    string line = "";
    ifstream inputFile(inputFileName);
    string blockNum;
    string blockGenTime;
    string blockHash;
    string prevBlockHash;
    string nonce;
    string numTransString;
    int numTransInt=0;
    int blockNumInt=0;
    int timeInt=0;
    int nonceInt=301;


    skipLineMain(inputFile, 2);

    getline(inputFile, line);
    blockNum = getBetweenQuestionMarks(line, 2);

    getline(inputFile, line);
    blockGenTime = getBetweenQuestionMarks(line, 2);

    getline(inputFile, line);
    blockHash = getBetweenQuestionMarks(line, 2);

    getline(inputFile, line);
    prevBlockHash = getBetweenQuestionMarks(line, 2);

    getline(inputFile, line);
    nonce = getBetweenQuestionMarks(line, 2);

    getline(inputFile, line);
    numTransString = getBetweenQuestionMarks(line, 2);


    skipLineMain(inputFile);

    try {

        int numTransInt;
        int blockNumInt=std::stoi(blockNum);
        int timeInt=std::stoi(blockGenTime);
        int nonceInt=stoi(nonce);

        out.setBlockNumber(blockNumInt);

        out.setTime(timeInt);

        out.setSelfHash(blockHash);
        out.setPrevHash(prevBlockHash);

        out.setNonce(nonceInt);

        numTransInt = stoi(numTransString);

    }

    catch (exception e) {

        inputFile.close();
        if(inputFileName.compare(unminedBlockFileName)==0)
            throw string("Problem loading in unmined block");
        else
            throw string("Problem loading in blockChain");
    }

    for (int i = 0; i < numTransInt; i++) {
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



    string userName = getBetweenQuestionMarks(line, 2);
    string senderKey = getBetweenQuestionMarks(line, 4);
    string senderSig = getBetweenQuestionMarks(line, 6);
    string amount = getBetweenQuestionMarks(line, 8);
    string receiverName = getBetweenQuestionMarks(line, 10);
    string receiverKey = getBetweenQuestionMarks(line, 12);
    string time = getBetweenQuestionMarks(line, 14);

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

    skipLineMain(inputFile,2);

    getline(inputFile,line);

    try{
        numbBlocks=stoi(getBetweenQuestionMarks(line, 2));
    } catch (exception e) {

        exit(-125);
    }

    remove("0temp.json");

    for(int i=1; i<=numbBlocks; i++){

        temp=ofstream(to_string(i));
        tempBlock=Block();
        addLinesToStreamMainMain(temp, inputFile, 9);
        getline(inputFile, line);

        while(line.find("]")==string::npos){
            temp<<line<<endl;

            getline(inputFile,line);

        }
        temp.close();

        try {
            loadUnminedBlockData(tempBlock, to_string(i));
        }
        catch(string e){
            inputFile.close();


            throw string(e+"\nThe error occurred on loading block: "+to_string(i));

        }

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

    skipLineMain(inputFile, 4);

    getline(inputFile, line);


    while (line.find("{")!=std::string::npos) {

        getline(inputFile, line);
        userName = getBetweenQuestionMarks(line, 2);

        getline(inputFile, line);
        userKey = getBetweenQuestionMarks(line, 2);

        getline(inputFile, line);

        try {
            balance = stoi(getBetweenQuestionMarks(line, 2));
        }
        catch (string e) {
            outPutResults("Error!\n" + e);
            exit(-143);
        }

        skipLineMain(inputFile);
        getline(inputFile, line);

        temp.setUserName(userName);
        temp.setPublicKey(userKey);
        temp.setBalance(balance);
        out.push_back(temp);

    }



    blockChainIn.setUserList(out);


}

void skipLineMain(ifstream &streamIn, int intIn) {
    string temp;
    for (int i = 0; i < intIn; i++)
        getline(streamIn, temp);
}

string getBetweenQuestionMarks(const string &stringIn, int intIn = 1) {
    int firstMark;
    int secondMark = -1;
    for (int i = 0; i < intIn; i++) {
        firstMark = stringIn.find("\"", secondMark + 1);
        secondMark = stringIn.find("\"", firstMark + 1);
    }
    return stringIn.substr(firstMark + 1, secondMark - firstMark - 1);
}



void addLinesToStreamMainMain(ofstream &outStream, ifstream &inStream, int number=1){
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

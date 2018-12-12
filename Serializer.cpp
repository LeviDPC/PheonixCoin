//
// Created by Levi on 12/11/2018.
//

#include "Serializer.h"

Block Serializer::readBlock(const string &fileName, bool readingUnmined) {
    Block out = Block();
    string line = "";
    ifstream inputFile(fileName);
    string blockNum;
    string blockGenTime;
    string blockHash;
    string prevBlockHash;
    string nonce;
    string numTransString;
    int numTransInt = 0;
    int blockNumInt = 0;
    int timeInt = 0;
    int nonceInt = 0;


    skipLine(inputFile, 2);

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


    skipLine(inputFile);

    try {

         numTransInt;
         blockNumInt = std::stoi(blockNum);
         timeInt = std::stoi(blockGenTime);
         nonceInt = stoi(nonce);

        out.setBlockNumber(blockNumInt);

        out.setTime(timeInt);

        out.setSelfHash(blockHash);
        out.setPrevHash(prevBlockHash);

        out.setNonce(nonceInt);

        numTransInt = stoi(numTransString);

    }

    catch (exception e) {

        inputFile.close();
        if (readingUnmined){

            throw string("Problem loading in unmined block");
        }
        else {

            throw string("Problem loading in blockChain");
        }
    }

    for (int i = 0; i < numTransInt; i++) {
        getline(inputFile, line);
        out.addTransaction(transFromString(line));
    }

    inputFile.close();

    return out;

}

BlockChain Serializer::readBlockChain(const string &fileName) {
    ifstream inputFile(fileName);
    ofstream temp;
    vector<Block> tempList;
    Block tempBlock;
    BlockChain out;
    int numbBlocks;
    string line;
    stringstream builder;

    skipLine(inputFile, 2);

    getline(inputFile, line);

    try {
        numbBlocks = stoi(getBetweenQuestionMarks(line, 2));
    } catch (exception e) {

        throw string("Error Reading number of Blocks in BlockChain");
    }



    for (int i = 1; i <= numbBlocks; i++) {

        temp = ofstream(to_string(i));
        tempBlock = Block();
        addLinesToStream(temp, inputFile, 9);
        getline(inputFile, line);

        while (line.find("]") == string::npos) {
            temp << line << endl;

            getline(inputFile, line);

        }
        temp.close();

        try {
            tempBlock=readBlock(to_string(i), false);
        }
        catch (string e) {
            inputFile.close();


            throw string(e + "\nThe error occurred on loading block: " + to_string(i));

        }

        tempList.push_back(tempBlock);


    }

    inputFile.close();

    out.setMinedBlocks(tempList);
    return out;
}

vector<user> Serializer::readUserList(const string &fileName){
    vector<user> out;
    user temp = user();
    ifstream inputFile(fileName);
    string line = "";
    string numbOfUsersString = "";

    string userName = "";
    string userKey = "";
    int balance = 0;

    skipLine(inputFile, 4);

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
        catch (exception e) {
            inputFile.close();
            throw string("Error Loading user Data From File\nInvalid user balance!");
        }

        skipLine(inputFile);
        getline(inputFile, line);

        temp.setUserName(userName);
        temp.setPublicKey(userKey);
        temp.setBalance(balance);
        out.push_back(temp);

    }



    return out;
}

Transaction Serializer::transFromString(const string &in) {
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
        throw string("error reading transaction data!");
    }

    return out;

}


string Serializer::getBetweenQuestionMarks(const string &stringIn, int intIn = 1) {
    int firstMark;
    int secondMark = -1;
    for (int i = 0; i < intIn; i++) {
        firstMark = stringIn.find("\"", secondMark + 1);
        secondMark = stringIn.find("\"", firstMark + 1);
    }
    return stringIn.substr(firstMark + 1, secondMark - firstMark - 1);
}

void Serializer::skipLine(ifstream &streamIn, int intIn) {
    string temp;
    for (int i = 0; i < intIn; i++)
        getline(streamIn, temp);
}


void Serializer::addLinesToStream(ofstream &outStream, ifstream &inStream, int number=1){
    string line;
    for(int i=0; i<number; i++){
        getline(inStream, line);
        outStream<<line<<endl;

    }

}

//
// Created by Levi on 12/11/2018.
//

#include "Serializer.h"

//constructor
Serializer::Serializer() {}

//Method to Read a JSON file and create a Block object from it
Block Serializer::readBlock(const string &fileName, bool readingUnmined) {
    Block out = Block();
    string line = "";
    ifstream inputFile(fileName);
    string blockNum = "";
    string blockGenTime = "";
    string blockHash = "";
    string prevBlockHash = "";
    string nonce = "";
    string numTransString = "";
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

        try { blockNumInt = std::stoi(blockNum); }
        catch (exception e) { throw string("Problem Reading BlockNum!"); }

        try { timeInt = std::stoi(blockGenTime); }
        catch (exception e) { throw string("Problem Reading BlockTime!"); }

        try { nonceInt = stoi(nonce); }
        catch (exception e) { throw string("Problem Reading Nonce!"); }

        try { numTransInt = stoi(numTransString); }
        catch (exception e) { throw string("Problem Reading Number of Transactions In Block!"); }

        out.setBlockNumber(blockNumInt);
        out.setTime(timeInt);
        out.setSelfHash(blockHash);
        out.setPrevHash(prevBlockHash);
        out.setNonce(nonceInt);


        for (int i = 1; i <= numTransInt; i++) {
            getline(inputFile, line);
            try {
                out.addTransaction(transFromString(line));
            }
            catch (string e) {
                throw string("Error Reading block on transaction: " + to_string(i) + " " + e);
            }
        }

    }
    catch (string e) {

        inputFile.close();

        //I had multiple levels of try blocks so that I can can build the exception based on where this
        //method is being called from
        if (readingUnmined)
            throw string("Problem loading in unmined block!\n" + e);
        else
            throw string("Problem loading in blockChain!\n" + e);

    }


    inputFile.close();

    return out;

}

//Method to read a JSON file and create a block chain from it
BlockChain Serializer::readBlockChain(const string &fileName) {
    ifstream inputFile(fileName);
    ofstream temp;
    vector<Block> tempList;
    Block tempBlock;
    BlockChain out;
    int numbBlocks = 0;
    string line = "";
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
            tempBlock = readBlock(to_string(i), false);
        }
        catch (string e) {
            inputFile.close();

            throw string("Error occurred on loading block: " + to_string(i) + "! " + e);
        }


        remove(to_string(i).c_str());

        tempList.push_back(tempBlock);


    }

    inputFile.close();

    out.setMinedBlocks(tempList);
    return out;
}

//Method to read a JSON file and construct a vector of users from it
vector<User> Serializer::readUserList(const string &fileName) {
    vector<User> out;
    User temp = User();
    ifstream inputFile(fileName);
    string line = "";
    string numbOfUsersString = "";

    string userName = "";
    string userKey = "";
    int balance = 0;

    skipLine(inputFile, 4);

    getline(inputFile, line);


    while (line.find("{") != std::string::npos) {

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
            throw string(
                    "Error Loading User Data From File! Balance: " + getBetweenQuestionMarks(line, 2) + " is Invalid!");
        }

        skipLine(inputFile);
        getline(inputFile, line);

        temp.setUserName(userName);
        try { temp.setPublicKey(userKey); }
        catch (string e) {
            throw string("Error Reading User List From File! User Key: " + userKey + " Is Invalid! " + e);
        }
        temp.setBalance(balance);

        out.push_back(temp);

    }


    return out;
}

//Uses the Block Classes JSONOutput() Method to write a Block Object to a JSON file
void Serializer::write(const Block &unminedBlock, const string &fileName) {
    ofstream out(fileName);
    if (out.is_open()) {
        out << "{" << endl;
        out << unminedBlock.JSONOutput() << endl;
        out << "}";
    }
    out.close();
}

//Uses the BlockChain Classes JSONOutput() Method to write a BlockChain Object to a JSON file
void Serializer::write(const BlockChain &primaryChain, const string &fileName) {
    ofstream out(fileName);
    if (out.is_open()) {
        out << "{" << endl;
        out << primaryChain.JSONOutput();
        out << "}";
    }
    out.close();
}

//Uses the BlockChain Classes userListJSONOutput() Method to write a Block Object to a JSON file
void Serializer::write(const vector<User> &userList, const string &fileName) {
    ofstream out(fileName);
    BlockChain temp;
    temp.setUserList(userList);
    if (out.is_open()) {
        out << "{" << endl;
        out << temp.userListJSONOutput() << endl;
        out << "}";
    }
    out.close();

}

//Helper Method to construct a Transaction from a JSON Formated String
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


    out.setSenderName(userName);


    try { out.setSenderKey(senderKey); }
    catch (string e) { throw string("Error Loading Sender Key from Transaction"); }


    try { out.setSenderSig(senderSig); }
    catch (string e) { throw string("Error Loading Sender Key from Transaction"); }

    out.setReceiverName(receiverName);


    try { out.setReceiverKey(receiverKey); }
    catch (string e) { throw string("Error Loading Receiver Key from Transaction"); }


    try { out.setAmount(stoi(amount)); }
    catch (exception e) { throw string("Error Loading Amount from Transaction"); }


    try { out.setManTime(stoi(time)); }
    catch (exception e) { throw string("Error Loading Time from Transaction"); }


    return out;

}

//Takes in a string and gets the value between the Nth set of question marks
string Serializer::getBetweenQuestionMarks(const string &stringIn, int intIn) {
    int firstMark;
    int secondMark = -1;
    for (int i = 0; i < intIn; i++) {
        firstMark = stringIn.find("\"", secondMark + 1);
        secondMark = stringIn.find("\"", firstMark + 1);
    }
    return stringIn.substr(firstMark + 1, secondMark - firstMark - 1);
}

//Skips N amount of lines in a file
void Serializer::skipLine(ifstream &streamIn, int intIn) {
    string temp;
    for (int i = 0; i < intIn; i++)
        getline(streamIn, temp);
}

//Read N amount of lines form a file and writes them to a different file
void Serializer::addLinesToStream(ofstream &outStream, ifstream &inStream, int number = 1) {
    string line;
    for (int i = 0; i < number; i++) {
        getline(inStream, line);
        outStream << line << endl;

    }

}

//Formats and outputs a message to a json file
void Serializer::outPutResultsError(const string &in, const string &resultFileName) {
    ofstream result(resultFileName);
    if (result.is_open()) {
        result << "{" << endl;
        result << "\t\"Status\" : \"Error!\"," << endl;
        result << "\t\"Error\" : \"" << in << "\"" << endl;
        result << "}";
    }
    result.close();
}


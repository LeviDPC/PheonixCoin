//
// Created by Levi on 12/11/2018.
//

#ifndef PHEONIXCOINCURRENTBRANCH_SERIALIZER_H
#define PHEONIXCOINCURRENTBRANCH_SERIALIZER_H

#include "Transaction.h"
#include "Block.h"
#include "BlockChain.h"
#include "user.h"

class Serializer {


public:

    //Constructor
    Serializer();

    //Methods to read data from files and put it into objects
    Block readBlock(const string &fileName, bool readingUnmined=true);
    BlockChain readBlockChain(const string &fileName);
    vector<user> readUserList(const string &fileName);

    //methods to take objects and put them into files
    void write(const Block &unminedBlock, const string &fileName);
    void write(const BlockChain &primaryChain, const string &fileName);
    void write(const vector<user> &userList, const string &fileName);

    //helper methods
    Transaction transFromString(const string &in);
    string getBetweenQuestionMarks(const string &stringIn, int intIn);
    void skipLine(ifstream &streamIn, int intIn=1);
    void addLinesToStream(ofstream &outStream, ifstream &inStream, int number);
    void outPutResultsError(const string &in, const string &resultFileName);

};


#endif //PHEONIXCOINCURRENTBRANCH_SERIALIZER_H

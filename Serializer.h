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
    Block readBlock(const string &fileName, bool readingUnmined=true);
    BlockChain readBlockChain(const string &fileName);
    vector<user> readUserList(const string &fileName);

    void write(const BlockChain &primaryChain, const string &fileName);
    void write(const Block &unminedBlock, const string &fileName);
    void write(const vector<user> &primaryChain, const string &fileName);

    Transaction transFromString(const string &in);
    string getBetweenQuestionMarks(const string &stringIn, int intIn);
    void skipLine(ifstream &streamIn, int intIn=1);
    void addLinesToStream(ofstream &outStream, ifstream &inStream, int number);

};


#endif //PHEONIXCOINCURRENTBRANCH_SERIALIZER_H

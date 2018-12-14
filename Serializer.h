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
private:
    string resultFileName;

public:

    //Constructors
    Serializer();
    Serializer(const string &resultFileName);

    //Methods to read data from files and put it into objects
    Block readBlock(const string &fileName, bool readingUnmined=true);
    BlockChain readBlockChain(const string &fileName);
    vector<User> readUserList(const string &fileName);

    //methods to take objects and put them into files
    void write(const Block &unminedBlock, const string &fileName);
    void write(const BlockChain &primaryChain, const string &fileName);
    void write(const vector<User> &userList, const string &fileName);

    //helper methods
    //Extracts a transaction From a string
    const Transaction transFromString(const string &in);
    //Takes in a string and gets the value between the Nth set of question marks
    const string getBetweenQuestionMarks(const string &stringIn, int intIn=1);
    //Skips N amount of lines in a file
    void skipLine(ifstream &streamIn, int intIn=1);
    //Read N amount of lines form a file and writes them to a different file
    void addLinesToStream(ofstream &outStream, ifstream &inStream, int number);
    //Formats and outputs an Error message the result file
    void outPutResultsError(const string &in);
    //Formats and outputs a message to the result file
    void outPutResults(const string &in);

    //Getter and Setter
    const string &getResultFileName() const;
    void setResultFileName(const string &resultFileName);

};


#endif //PHEONIXCOINCURRENTBRANCH_SERIALIZER_H

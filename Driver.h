//
// Created by Levi on 12/10/2018.
//

#ifndef PHEONIXCOINCURRENTBRANCH_DRIVER_H
#define PHEONIXCOINCURRENTBRANCH_DRIVER_H

#include <string>
#include "Block.h"
#include "BlockChain.h"

using namespace std;

class Driver {
private:
    string configName;
    string resultFileName;

    BlockChain primaryChain;
    Block unminedBlock;


public:
    //constructors
    Driver();
    Driver(const string &configName, const string &resultFileName, const Block &unminedBlock, const BlockChain &primaryChain);

    //helper Methods
    void outPutResultsError(const string &in);
    void outPutResults(const string &in);
    string getOpFromConfigFile();
    int getLinesInConfig();

    //primaryMethod
    void drive();

    //worker methods
    int newUser();
    int newTrans();
    int mine();

    //method to output objects that opperations were prefomed on
    void outPut(Block &blockIn, BlockChain &blockChainIn);

    //setters and getters
    const string &getConfigName() const;
    void setConfigName(const string &configName);
    const string &getResultFileName() const;
    void setResultFileName(const string &resultFileName);
    const BlockChain &getPrimaryChain() const;
    void setPrimaryChain(const BlockChain &primaryChain);
    const Block &getUnminedBlock() const;
    void setUnminedBlock(const Block &unminedBlock);



};


#endif //PHEONIXCOINCURRENTBRANCH_DRIVER_H

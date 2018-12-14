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


    BlockChain primaryChain;
    Block unminedBlock;


public:
    //constructors
    Driver();
    Driver(const string &configName, const string &resultFileName, const Block &unminedBlock, const BlockChain &primaryChain);


    //primary Method
    const string drive();

    //worker methods
    const string newUser();
    const string newTrans();
    const string mine();

    //method to output objects that opperations were prefomed on
    void outPut(Block &blockIn, BlockChain &blockChainIn);

    //helper Methods
    //This method gets the opperation to perform from the config file
    const string getOpFromConfigFile();
    //This opperation gets the ammount of lines in the config file
    const int getLinesInConfig();

    //setters and getters
    const string &getConfigName() const;
    void setConfigName(const string &configName);
    const BlockChain &getPrimaryChain() const;
    void setPrimaryChain(const BlockChain &primaryChain);
    const Block &getUnminedBlock() const;
    void setUnminedBlock(const Block &unminedBlock);



};


#endif //PHEONIXCOINCURRENTBRANCH_DRIVER_H

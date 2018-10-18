//
// Created by Levi on 10/7/2018.
//

#ifndef BLOCKCHAINGOOFIN_BLOCKCHAIN_H
#define BLOCKCHAINGOOFIN_BLOCKCHAIN_H

#include "block.h"
#include <functional>

class blockChain {
    std::vector<block> minedBlocks;
    //default hash is the hash of "Levi is Awesome"
    string prevHash="6C2671C57AA36868264BC533BA9EFF0A6E4AC802646DF1188201308F1DE374EC";
public:
    blockChain(const vector<block> &minedBlocks);

    void displayBlockChain();

    blockChain();

    string mine(block block);

    bool hexComp(string hex1, string hex2);
};


#endif //BLOCKCHAINGOOFIN_BLOCKCHAIN_H

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
    size_t prevHash=3036377018;
public:
    blockChain(const vector<block> &minedBlocks);

    void displayBlockChain();

    blockChain();

    size_t mine(block block);
};


#endif //BLOCKCHAINGOOFIN_BLOCKCHAIN_H

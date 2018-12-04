//
// Created by Levi on 10/7/2018.
//

#ifndef BLOCKCHAINGOOFIN_BLOCKCHAIN_H
#define BLOCKCHAINGOOFIN_BLOCKCHAIN_H

#include "block.h"
#include "user.h"
#include <functional>
#include <iostream>

class blockChain {
    std::vector<block> minedBlocks;
	std::vector<user> userList;
    //default hash is the hash of "Levi is Awesome"
    string prevHash="6C2671C57AA36868264BC533BA9EFF0A6E4AC802646DF1188201308F1DE374EC";
public:
    blockChain(const vector<block> &minedBlocks);

    string toString() const;

	friend ostream& operator<< (ostream& stream, const blockChain& in);

    blockChain();

    string mine(block block);

    const block &getBlockFromChain(int in) const;

	const vector<block> &getMinedBlocks() const;

    void setMinedBlocks(const vector<block> &minedBlocks);

	const vector<block> &getMinedBlocks() const;

	void setMinedBlocks(const vector<block> &minedBlocks);

	const vector<user> &getuserList() const;

	void setUserList(const vector<user> &listIn);
	
	user getByPublcKey(string publicKey);

	bool isPublicKeyInList(string publicKey);

};


#endif //BLOCKCHAINGOOFIN_BLOCKCHAIN_H

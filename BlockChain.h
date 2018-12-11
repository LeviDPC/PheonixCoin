//
// Created by Levi on 10/7/2018.
//

#ifndef BLOCKCHAINGOOFIN_BLOCKCHAIN_H
#define BLOCKCHAINGOOFIN_BLOCKCHAIN_H

#include "Block.h"
#include "User.h"
#include <functional>
#include <iostream>

class BlockChain {
    std::vector<Block> minedBlocks;
	std::vector<user> userList;
    //default hash is the hash of "Levi is Awesome"
    string prevHash="6C2671C57AA36868264BC533BA9EFF0A6E4AC802646DF1188201308F1DE374EC";

public:
	BlockChain(const vector<Block> &minedBlocks);

    string toString() const;

	string JSONOutput(string whiteSpaceBeginning="\t", string tag="\"BlockChain\": ") const;

	friend ostream& operator<< (ostream& stream, const BlockChain& in);

    BlockChain();

    string mine(Block block, const string &key);

    void updateUsers(const Block &in);

    const Block &getBlockFromChain(int in) const;

	const vector<Block> &getMinedBlocks() const;

	void setMinedBlocks(const vector<Block> &minedBlocks);

	const vector<user> &getuserList() const;

	void setUserList(const vector<user> &listIn);

	void addToUserList(const user &in);

	string userListToString() const;

	string userListJSONOutput(string whiteSpaceBeginning="\t", string tag="\"userList\": ") const;
//update uml
    user &getUserByPublicKey(const string &publicKey);
// add to uml
    static user &getUserByPublicKey(const string &publicKey, vector<user> &listIn);

	bool isPublicKeyInList(const string &publicKey) const;
//add to uml
    static bool isPublicKeyInList(const string &publicKey, const vector<user> &listIn);
//add to uml
	void addUserIfNotExists(const string &publicKey);
//add to uml
    static void addUserIfNotExists(string publicKey, vector<user> &listIn);

	bool verifyTransactions(const Block &in) const;
	//add to uml
	void addToUserByKey(const string &key, int intIn);
	//add to uml
	void subractFromUserByKey(const string &key);

};


#endif //BLOCKCHAINGOOFIN_BLOCKCHAIN_H

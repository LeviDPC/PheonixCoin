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

	string JSONOutput(string whiteSpaceBeginning="\t", string tag="\"blockChain\": ") const;

	friend ostream& operator<< (ostream& stream, const blockChain& in);

    blockChain();

    string mine(block block, const string &key);

    void updateUsers(const block &in);

    const block &getBlockFromChain(int in) const;

	const vector<block> &getMinedBlocks() const;

	void setMinedBlocks(const vector<block> &minedBlocks);

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

	bool verifyTransactions(const block &in) const;
	//add to uml
	void addToUserByKey(const string &key, int intIn);
	//add to uml
	void subractFromUserByKey(const string &key);

};


#endif //BLOCKCHAINGOOFIN_BLOCKCHAIN_H

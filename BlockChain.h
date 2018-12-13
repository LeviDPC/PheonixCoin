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
private:
    std::vector<Block> minedBlocks;
    std::vector<User> userList;
    //default hash is the hash of "Levi is Awesome"
    string prevHash = "6C2671C57AA36868264BC533BA9EFF0A6E4AC802646DF1188201308F1DE374EC";


public:
    BlockChain(const vector<Block> &minedBlocks);

    bool static hexComp(string in1, string in2);

    string toString() const;

    string JSONOutput(string whiteSpaceBeginning = "\t", string tag = "\"BlockChain\": ") const;

    friend ostream &operator<<(ostream &stream, const BlockChain &in);

    friend istream &operator>>(istream &stream, BlockChain &in);

    BlockChain();

    string mine(Block block, const string &key);

    void updateUsers(const Block &in);

    const Block &getBlockFromChain(int in) const;

    const vector<Block> &getMinedBlocks() const;

    void setMinedBlocks(const vector<Block> &minedBlocks);

    const vector<User> &getuserList() const;

    void setUserList(const vector<User> &listIn);

    void addToUserList(const User &in);

    string userListToString() const;

    string userListJSONOutput(string whiteSpaceBeginning = "\t", string tag = "\"userList\": ") const;

    User &getUserByPublicKey(const string &publicKey);

    static User &getUserByPublicKey(const string &publicKey, vector<User> &listIn);

    bool isPublicKeyInList(const string &publicKey) const;

    static bool isPublicKeyInList(const string &publicKey, const vector<User> &listIn);

    void addUserIfNotExists(const string &publicKey);

    static void addUserIfNotExists(string publicKey, vector<User> &listIn);

    bool verifyTransactions(const Block &in) const;

    void addToUserByKey(const string &key, int intIn);

    void subtractFromUserByKey(const string &key, int intIn);

    string static ensureLength(string in, int intIn = 64);

    static bool ensureHex(const string &in);


};


#endif //BLOCKCHAINGOOFIN_BLOCKCHAIN_H

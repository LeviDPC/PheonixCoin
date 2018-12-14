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

    //constructors
    BlockChain(const vector<Block> &minedBlocks, const vector<User> &userList);
    BlockChain();


    //Outputs the object and its blocks to a string without the user list
    string toString() const;

    //Outputs the object's user list to a string
    string userListToString() const;

    //formats and outputs the object and it's blocks as a JSON file without the user list.
    //Has the option to input leading white space, an opening tag
    //and whether it should be done on one line or multiple.
    string JSONOutput(string whiteSpaceBeginning = "\t", string tag = "\"BlockChain\": ") const;

    //formats and outputs the object's UserList as a JSON file. Has the option to input leading white space,
    //an opening tag and whether it should be done on one line or multiple.
    string userListJSONOutput(string whiteSpaceBeginning = "\t", string tag = "\"userList\": ") const;



    //This method takes in a block to be mined and a user key to credit 5 pheonix coins to for successful mining.
    //More detailed documentaiton is availiable within the function
    string mine(Block block, const string &key);

    //Gets the Nth Block from the BlockChain
    const Block &getBlockFromChain(int in) const;

    //verifies the transactions within the block passed. It verifies both the transaction signatures and it
    //checks with the BlockChains UserList to make sure tha tall senders have the currency they are trying to send
    bool verifyTransactions(const Block &in) const;

    //adds a user to the user list
    void addToUserList(const User &in);

    //Takes in a block it's transactions to the user list
    void updateUsers(const Block &in);

    //find a user in a userList based on it's public key and return it. There is a static version that accepts
    //a userList as an argument and a non static version that uses the BlockChain object's userList
    User &getUserByPublicKey(const string &publicKey);
    static User &getUserByPublicKey(const string &publicKey, vector<User> &listIn);

    //Checks if there is a user on a user list with the specified key. There is a static version that accepts
    //a userList as an argument and a non static version that uses the BlockChain object's userList
    bool isPublicKeyInList(const string &publicKey) const;
    static bool isPublicKeyInList(const string &publicKey, const vector<User> &listIn);


    //Checks if there is a user on a user list with the specified user Key. If the user isn't on the list it adds them.
    //There is a static version that accepts a userList as an argument and a non static version that uses the
    // BlockChain object's userList
    void addUserIfNotExists(const string &publicKey);
    static void addUserIfNotExists(string publicKey, vector<User> &listIn);

    //Ensures that a string is a certain length. If the string is greater than it will take the first N Characters
    //If the string is less than it will add leading zeros to the string
    string static ensureLength(string in, int intIn = 64);

    //Ensures that a string is non empty valid Hex Number
    static bool ensureHex(const string &in);

    //This function takes in two 64 digit (256 bit) hexadecimal numbers as strings and compares them. It returns true
    // if the first parameter is less than or equal to the second one and false otherwise.
    // If the input is input is less than 64 digits than the ensureLength function will add 0s at the beelining of the
     // String. If it is more than it will just take the first 64 digits.
    bool static hexComp(string in1, string in2);

    //overload operators for istream and ostream
    friend ostream &operator<<(ostream &stream, const BlockChain &in);
    friend istream &operator>>(istream &stream, BlockChain &in);

    //setters and getters
    void setMinedBlocks(const vector<Block> &minedBlocks);
    const vector<User> &getuserList() const;
    void setUserList(const vector<User> &listIn);
    const vector<Block> &getMinedBlocks() const;
    const string &getPrevHash() const;
    void setPrevHash(const string &prevHash);



};


#endif //BLOCKCHAINGOOFIN_BLOCKCHAIN_H

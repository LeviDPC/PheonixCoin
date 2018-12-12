//This now uses sha256 for hashing. This functionality comes from the file picosha2.h. I got it from google. Its
// open source under the MIT licence. The licence is included in the file itself.

//TODO:
//Next up:

//
//      do IO in a class
// Eventually:
//      implemnt bool verifyTransaction(const vector<user> &userListIn) in Transaction
//      implemnt verifyTransactions(blockIn.getTransactions()) in blockchain.cpp
//      implement veirfySignature() in Transaction.cpp
//      implement genSignature() in user.cpp
//      implement verify keys imputed are in hex form with throwing errors
//      inputting users into transactions
//      increase polymorphism in main

#include <iostream>
#include <string>
#include <fstream>
#include "Transaction.h"
#include "Block.h"
#include "BlockChain.h"
#include "User.h"
#include "Driver.h"
#include "Serializer.h"

using namespace std;




int main() {
    string configName = "cppConfig.txt";
    string resultFileName = "result.txt";
    string userFileName = "users.json";
    string unminedBlockFileName = "unminedBlock.json";
    string blockChainFileName = "blockchain.json";

    BlockChain primaryChain = BlockChain();
    Block unminedBlock = Block();
    Serializer serializer;
    Driver driver;






    try {
        unminedBlock = serializer.readBlock(unminedBlockFileName);
        primaryChain = serializer.readBlockChain(blockChainFileName);

        primaryChain.setUserList(serializer.readUserList(userFileName));

    }
    catch(string e){
        driver.outPutResults("Error!\n"+e);
    }




    driver=Driver(configName, resultFileName, unminedBlock, primaryChain);
    try {
        driver.drive();
    }
    catch(string e)
    {
        driver.outPutResults("Error!\n"+e);
    }

    driver.outPut(unminedBlock, primaryChain);



    serializer.write(unminedBlock, unminedBlockFileName);
    serializer.write(primaryChain, blockChainFileName);
    serializer.write(primaryChain.getuserList(), userFileName);


        return 0;
}
//Program: PheonixCoin
//Comp Sci 371 Final Project - Or at least a part of it
//Levi Pfantz, Hunter Osterman and Ibrahim Budul


#include <string>
#include "Block.h"
#include "BlockChain.h"
#include "User.h"
#include "Driver.h"
#include "Serializer.h"

using namespace std;




int main() {
    //file name variables
    string configName = "cppConfig.txt";
    string resultFileName = "result.json";
    string userFileName = "users.json";
    string unminedBlockFileName = "unminedBlock.json";
    string blockChainFileName = "blockchain.json";

    //objects that are going to be used
    BlockChain primaryChain = BlockChain();
    Block unminedBlock = Block();
    Serializer serializer;
    Driver driver;





    //Load Objects from files
    try {
        unminedBlock = serializer.readBlock(unminedBlockFileName);
        primaryChain = serializer.readBlockChain(blockChainFileName);
        primaryChain.setUserList(serializer.readUserList(userFileName));

    }
    catch(string e){
        //If loading fails then write the error to the results file and exit
        serializer.outPutResultsError(e, resultFileName);
        exit(-101);
    }



    //Initialize Driver object and pass in file names and objects
    driver=Driver(configName, resultFileName, unminedBlock, primaryChain);

    //execute the operation passed in through the config file
    driver.drive();

    //retrieve the objects now that the operation has been performed on them
    driver.outPut(unminedBlock, primaryChain);


    //store the objects as files for hte next time the program runs
    serializer.write(unminedBlock, unminedBlockFileName);
    serializer.write(primaryChain, blockChainFileName);
    serializer.write(primaryChain.getuserList(), userFileName);

        return 0;
}
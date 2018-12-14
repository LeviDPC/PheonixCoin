//Program: PheonixCoin
//Comp Sci 371 Final Project - Or at least a part of it
//Levi Pfantz, Hunter Osterman and Ibrahim Budul

//This program uses the picosha2 library for hashing. This library is contained int the file picosha2.h
//and is realeased under the MIT liscence which can be found in the file.

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
    BlockChain primaryChain;
    Block unminedBlock;
    Serializer serializer(resultFileName);
    Driver driver;

    //string to store message to output to result file.
    string messageOut="";



    //Load Objects from files
    try {
        unminedBlock = serializer.readBlock(unminedBlockFileName);
        primaryChain = serializer.readBlockChain(blockChainFileName);
        primaryChain.setUserList(serializer.readUserList(userFileName));

    }
    catch(string e){
        //If loading fails then write the error to the results file and exit
        serializer.outPutResultsError(e);
        exit(-101);
    }



    //Initialize Driver object and pass in file names and objects
    driver=Driver(configName, resultFileName, unminedBlock, primaryChain);

    //execute the operation passed in through the config file and output the result
    try{
        messageOut=driver.drive();
        serializer.outPutResults(messageOut);
    }
    catch(string e){
        serializer.outPutResultsError(e);
    }

    //retrieve the objects now that the operation has been performed on them
    driver.outPut(unminedBlock, primaryChain);


    //store the objects as files for hte next time the program runs
    serializer.write(unminedBlock, unminedBlockFileName);
    serializer.write(primaryChain, blockChainFileName);
    serializer.write(primaryChain.getuserList(), userFileName);

        return 0;
}
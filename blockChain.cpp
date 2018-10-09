//
// Created by Levi on 10/7/2018.
//

#include "blockChain.h"




//Yo, We should *Eventually* add at least two things to this
//1. Actual mining (i.e. making sure that the resulting hash is bellow a certain value)
//2. veryifying the previous transaction

// This Method takes the transactions, the time, the hash of the previous block
// and a random number. It hashes all this than adds the block to a vector (basically an array list) that is a 
// class variable.
size_t blockChain::mine(block blockIn) {


    vector<transaction>::const_iterator i;
    int index;
    stringstream stream;

    while (true) {
        time_t curTime = time(NULL);
        srand(curTime);
        blockIn.setBlockNumber(blockChain::minedBlocks.size() + 1);
        blockIn.setTime(curTime);
        blockIn.setPrevHash(blockChain::prevHash);
        blockIn.addTransaction(transaction("Pheonix Gen", 50, "Levi Pfantz"));
        //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
        for (i = blockIn.getTransactions().begin(); i != blockIn.getTransactions().end(); ++i) {
            //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
            //then I can't be bothered
            index = std::distance(blockIn.getTransactions().begin(), i);
            stream << blockIn.getTransactions()[index].transactionToString();
        }
        stream << curTime << blockIn.getPrevHash() << rand();
        size_t out = hash<string>{}(stream.str());
       
		//checks if the hash is below a value, currently set to the maximum value of size_t (the type that hash returns)
		if (out < SIZE_MAX) {
            blockIn.setSelfHash(out);
            blockChain::minedBlocks.push_back(blockIn);
            blockChain::prevHash=out;
            return out;
        } else
            blockIn.removeLatestTransaction();

    }


}

//simply prints the entire block Chain

void blockChain::displayBlockChain() {
    vector<block>::iterator i;
    int index;

    //apparently using ++i is best practice? I'm not going ot worry about right now assuming the code works
    for(i = blockChain::minedBlocks.begin(); i != blockChain::minedBlocks.end(); ++i){
        //based on my research I am pretty sure there are better ways to iterate through a vector, but if this works
        //then I can't be bothered
        index=std::distance(blockChain::minedBlocks.begin(), i);
        blockChain::minedBlocks[index].displayBlock();
        cout<<"------------------------------------------------------------"<<endl;
    }
}

blockChain::blockChain() {}

blockChain::blockChain(const vector<block> &minedBlocks) : minedBlocks(minedBlocks) {}




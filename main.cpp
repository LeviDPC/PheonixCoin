//This now uses sha256 for hashing. This functionality comes from the file picosha2.h. I got it from google. Its
// open source under the MIT licence. The licence is included in the file itself.

#include <iostream>
#include <string>
#include "transaction.h"
#include "block.h"
#include "blockChain.h"
using namespace std;

int main() {

    transaction trans2("Levi Pfantz", 10, "Ibrahiam");
    transaction trans3("Levi Pfantz", 10, "Hunter");
    transaction trans4("Levi Pfatnz", 10, "UWGB");

    block levisBlock1;
    block levisBlock2(trans2);
    block levisBlock3(trans3);
    block levisBlock4(trans4);

    blockChain daChain;

    daChain.mine(levisBlock1);
    daChain.mine(levisBlock2);
    daChain.mine(levisBlock3);
    daChain.mine(levisBlock4);

    daChain.displayBlockChain();


    system("Pause");
    return 0;
}
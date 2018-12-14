#include "Transaction.h"
#include "BlockChain.h"

//constructors
//Input validation is performed to make sure that Sender Key, Sender Sig, and Receiver Key are non empty, valid
//Hex Strings

Transaction::Transaction(const string &senderKey, const string &senderSig, int amount, const string &receiverKey) {
    if (!BlockChain::ensureHex(senderKey))
        throw string("Sender Key must Be valid Hex String");
    if (!BlockChain::ensureHex(receiverKey))
        throw string("Receiver Key must Be valid Hex String");
    Transaction::senderKey = senderKey;
    Transaction::senderSig = senderSig;
    Transaction::amount = amount;
    Transaction::receiverKey = receiverKey;
    Transaction::time = std::time(NULL);
}

Transaction::Transaction(const string &senderName, const string &senderKey, const string &senderSig, int amount,
                         const string &recieverName, const string &receiverKey) {
    if (!BlockChain::ensureHex(senderKey))
        throw string("Sender Key must Be valid Hex String");
    if (!BlockChain::ensureHex(receiverKey))
        throw string("Receiver Key must Be valid Hex String");
    Transaction::senderName = senderName;
    Transaction::senderKey = senderKey;
    Transaction::senderSig = senderSig;
    Transaction::amount = amount;
    Transaction::receiverName = recieverName;
    Transaction::receiverKey = receiverKey;
    Transaction::time = std::time(NULL);
}

Transaction::Transaction() {}


//outputs the object as a string including generating and including a hash
string Transaction::toString() const {
    stringstream stream;
    stream << "Sender Name: " << Transaction::senderName << "\nSender Key: " << Transaction::senderKey
           << "\nSender Signature: " << senderSig << "\nAmount: " << Transaction::amount;
    stream << "\nReceiver Name: " << Transaction::receiverName << "\nReceiver Key: " << Transaction::receiverKey
           << "\nTime: " << Transaction::time << endl;
    stream << "Transaction Hash: " << genSelfHash();
    return stream.str();
}

//Outputs the object as a string but doesn't generate and include a hash
string Transaction::toStringWithoutHash() const {
    stringstream stream;
    stream << "Sender Name: " << Transaction::senderName << "\nSender Key: " << Transaction::senderKey
           << "\nSender Signature: " << senderSig << "\nAmount: " << Transaction::amount;
    stream << "\nReceiver Name: " << Transaction::receiverName << "\nReceiver Key: " << Transaction::receiverKey
           << "\nTime: " << Transaction::time << endl;
    return stream.str();
}

//formats and outputs the object as a JSON file. Has the option to input leading white space, an opening tag
//and whether it should be done on one line or multiple.
string Transaction::JSONOutput(string whiteSpaceBeginning, string tag, bool multiLine) const {
    stringstream stream;
    string whiteSpaceEnd;

    if (multiLine)
        whiteSpaceEnd = "\n";
    else
        whiteSpaceEnd = "";
    string whiteSpaceBeginningWithoutAddedTab = whiteSpaceBeginning;
    if (multiLine) { whiteSpaceBeginning += "\t"; }

    stream << whiteSpaceBeginningWithoutAddedTab << tag << "{" << whiteSpaceEnd;

    stream << whiteSpaceBeginning << "\"senderName\": \"" << Transaction::senderName << "\"," << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"senderKey\": \"" << Transaction::senderKey << "\"," << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"senderSig\": \"" << Transaction::senderSig << "\"," << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"amount\": \"" << Transaction::amount << "\"," << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"receiverName\": \"" << Transaction::receiverName << "\"," << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"receiverKey\": \"" << Transaction::receiverKey << "\"," << whiteSpaceEnd;
    stream << whiteSpaceBeginning << "\"time\": \"" << Transaction::time << "\"" << whiteSpaceEnd;
    stream << whiteSpaceBeginningWithoutAddedTab << "}";
    return stream.str();
}



//generates a hash of the Transaction object by hashing all of its attributes as strings
string Transaction::genSelfHash() const {
    string out = "";
    picosha2::hash256_hex_string(Transaction::toStringWithoutHash(), out);

    return out;


}

//Set the time attribute to the current time
void Transaction::setAutoTime() {
    Transaction::time = std::time(NULL);
}

//Set the time attribute to the time imputed
void Transaction::setManTime(time_t time) {
    Transaction::time = time;
}

//Isn't actually implemented yet. Right now it just returns true. Ideally it would use Elliptical Curve Cryptography
//To verify that the SenderKey attribute and the SenderSig Attribute were both generated from the same private key
//and that the senderSig was generated specifically for this transaction.
bool Transaction::verifySignature() const {
    return true;
}


//overload operators for istream and ostream
ostream &operator<<(ostream &stream, const Transaction &in) {
    stream << in.toString();
    return stream;
}

istream &operator>>(istream &stream, Transaction &in){
    string senderUserName="";
    string senderKey = "";
    string senderPrivateKey = "";
    string receiverName="";
    string receiverKey = "";
    int amount=0;

    cout<<"Please input a the sender's UserName: ";
    stream>>senderUserName;
    in.setSenderName(senderUserName);
    cout<<endl;

    cout<<"Please input a the sender's Public Key: ";
    stream>>senderKey;
    in.setSenderKey(senderKey);
    cout<<endl;

    cout<<"Please input the sender's Private Key: ";
    stream>>senderPrivateKey;
    cout<<endl;
    in.setSenderSig(User::genSignature(senderPrivateKey));

    cout<<"Please input ammount being sent: ";
    stream>>amount;
    in.setAmount(amount);
    cout<<endl;

    cout<<"Please input the receiver's UserName: ";
    stream>>receiverName;
    in.setReceiverName(receiverName);
    cout<<endl;

    cout<<"Please input the receiver's Public Key: ";
    stream>>receiverKey;
    in.setReceiverKey(receiverKey);
    cout<<endl;

    in.setAutoTime();



    return stream;

}



//setters and getters
//SetSenderKey, setSenderSig, and setReceiver Key have input validation to ensure that the input is a non empty, valid
//Hex Strings. aside from that they are all basic setters and getters

int Transaction::getBlockNumber() const {
    return blockNumber;
}

void Transaction::setBlockNumber(int blockNumber) {
    Transaction::blockNumber = blockNumber;
}

double Transaction::getAmount() const {
    return amount;
}

void Transaction::setAmount(double amount) {
    Transaction::amount = amount;
}

time_t Transaction::getTime() const {
    return time;
}

const string &Transaction::getSenderName() const {
    return senderName;
}

void Transaction::setSenderName(const string &senderName) {
    Transaction::senderName = senderName;
}

const string &Transaction::getSenderKey() const {

    return senderKey;
}

void Transaction::setSenderKey(const string &senderKey) {
    if (!BlockChain::ensureHex(senderKey))
        throw string("Sender Key must Be valid Hex String");
    Transaction::senderKey = senderKey;
}

const string &Transaction::getSenderSig() const {

    return senderSig;
}

void Transaction::setSenderSig(const string &senderSig) {
    if (!BlockChain::ensureHex(senderSig))
        throw string("Sender Sig must Be valid Hex String");
    Transaction::senderSig = senderSig;
}

const string &Transaction::getReceiverName() const {
    return receiverName;
}

void Transaction::setReceiverName(const string &receiverName) {
    Transaction::receiverName = receiverName;
}

const string &Transaction::getReceiverKey() const {

    return receiverKey;
}

void Transaction::setReceiverKey(const string &receiverKey) {
    if (!BlockChain::ensureHex(receiverKey))
        throw string("Receiver Key must Be valid Hex String");
    Transaction::receiverKey = receiverKey;
}









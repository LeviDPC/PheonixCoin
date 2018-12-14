#include "User.h"
#include "BlockChain.h"

//constructors the last three all validate public Key
User::User(){}

User::User(string userName, string publicKey, long balance) {
    if(!BlockChain::ensureHex(publicKey))
        throw string("Public Key must be a Valid Hex Number");

    User::userName = userName;
    User::publicKey=publicKey;
    User::balance = balance;

}

User::User(string publicKey, long balance) {
    if(!BlockChain::ensureHex(publicKey))
        throw string("Public Key must be a Valid Hex Number");
    User::userName = "";
    User::publicKey=publicKey;
    User::balance = balance;

}

User::User(string publicKey) {
    if(!BlockChain::ensureHex(publicKey))
        throw string("Public Key must be a Valid Hex Number");
    User::userName = "";
    User::publicKey=publicKey;
    User::balance = 0;

}




//Method for outputing User as a JSON File
string User::JSONOutput(string whiteSpaceBeginning, string tag, bool multiLine) const{
    stringstream stream;
    string whiteSpaceEnd;

    if(multiLine)
        whiteSpaceEnd="\n";
    else
        whiteSpaceEnd="";

    string whiteSpaceBeginningWithoutAddedTab=whiteSpaceBeginning;
    if(multiLine) {whiteSpaceBeginning+="\t";}

    if(tag.compare("")!=0)
        stream << whiteSpaceBeginningWithoutAddedTab << tag << "{" << whiteSpaceEnd;
    else
        stream <<"{" << whiteSpaceEnd;



    stream<<whiteSpaceBeginning<<"\"userName\": \""<<User::userName<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"userKey\": \""<<User::publicKey<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"balance\": \""<<User::balance<<"\""<<whiteSpaceEnd;
    if(tag.compare("")!=0)
        stream << whiteSpaceBeginningWithoutAddedTab << "}";
    else
        stream << whiteSpaceBeginning << "}";
    return stream.str();
}

//Method for outputing User as a string
string User::toString() const{
	stringstream stream;
	stream << "Username: " << User::userName<<endl;
	stream << " Public Key: " << User::publicKey<<endl;
	stream << " Balance: " << User::balance<<endl;
	return stream.str();
}



//Generate a public Key from a private key and set it as the objects Public Key attribute
//Ideally this would be down with eliptical curve cryptogrophy, however I didn't have time to implement
//that as the Math is pretty advanced. Right now it just returns a hash of the private key
string User::genSetPublicKey(const string &privateKeyIn){


    string key="";
    string priv=privateKeyIn+"noise";
    picosha2::hash256_hex_string(priv,key);
    User::publicKey=key;
    return key;
}

//Generates a random private key
string User::genPrivateKey(){
   return rand256Gen();
}

//Generates a Signature. Same as with the public Key It would be Ideal if This was genearted with Eliptical Curve Cryptography
//However right now it is the hash of hte private key and the string "Noise";
string User::genSignature(const string &privateKeyIn){

    string out="";
    string toHash=privateKeyIn+"Noise";

    if(!BlockChain::ensureHex(privateKeyIn))
        throw string("Private Key must be a Valid Hex Number");

    picosha2::hash256_hex_string(toHash,out);
    return out;
}

//Generates a random 256 bit hexidecimal number
string User::rand256Gen() {
    int random = 0;
    stringstream out;
    for (int i = 0; i < 64; i++) {
        srand(time(NULL)+i);
        random = rand() % 15;
        if (random < 10)
            out << to_string(random);
        else {
            switch (random){
                case 10 :
                    out << "A";
                    break;
                case 11 :
                    out<<"B";
                    break;
                case 12 :
                    out<<"C";
                    break;
                case 13 :
                    out<<"D";
                    break;
                case 14 :
                    out<<"E";
                    break;
                case 15 :
                    out<<"F";
                    break;
            }
        }
    }
    return out.str();
}



//Add to and subtract from user balance
void User::addToBalance(long in) {
    //cout<<"HEllow from User.cpp: "<<User::balance<<endl;
    User::balance += in;
    //cout<<"HEllow from User.cpp: "<<User::balance<<endl;
}

void User::subtractFromBalance(long in) {
    User::balance -= in;
}


//Increment amd Decrement user balance
User& User::operator +=(const long &in){
    this->balance+=in;
    return *this;
}

User& User::operator -=(const long &in) {
    this->balance-=in;
    return *this;
}

//compare user balance
bool User::operator>(const User &in) {
    return User::balance > in.getBalance();
}

bool User::operator<(const User &in) {
    return User::balance < in.getBalance();
}

//Methods to output user to an ostream and input a user with an istream
ostream &operator<<(ostream &stream, const User &in) {
    stream << in.toString();
    return stream;
}

istream &operator>>(istream &stream, User &in){
    string UserName="";
    string publicKey = "";
    int balance=0;

    cout<<"Please input a the UserName: ";
    stream>>UserName;
    in.setUserName(UserName);
    cout<<endl;

    cout<<"Please input a the Public Key: ";
    stream>>publicKey;
    in.setPublicKey(publicKey);
    cout<<endl;

    cout<<"Please input the User's Balance: ";
    stream>>balance;
    in.setBalance(balance);
    cout<<endl;

    return stream;

}

//setters and getters
string User::getUserName() const {
    return User::userName;
}

string User::getPublicKey() const {
    return User::publicKey;
}

long User::getBalance() const {
    return User::balance;
}

void User::setUserName(string in) {
    User::userName = in;
}

void User::setPublicKey(string in) {
    if(!BlockChain::ensureHex(in))
        throw string("Public Key must be a Valid Hex Number");
    User::publicKey = in;
}

void User::setBalance(long in) {
    User::balance = in;
}


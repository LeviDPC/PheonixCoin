#include "User.h"


user::user(){}

user::user(string userName, string publicKey, long balance) {
    user::userName = userName;
    user::publicKey=publicKey;
    user::balance = balance;

}

user::user(string publicKey, long balance) {
    user::userName = "";
    user::publicKey=publicKey;
    user::balance = balance;

}

user::user(string publicKey) {
    user::userName = "";
    user::publicKey=publicKey;
    user::balance = 0;

}

string user::getUserName() const {
	return user::userName;
}

string user::getPublicKey() const {
	return user::publicKey;
}

long user::getBalance() const {
	return user::balance;
}

void user::setUserName(string in) {
	user::userName = in;
}

void user::setPublicKey(string in) {
    if(in.compare("")==0)
        throw string("Valid input is required for Public Key");
	user::publicKey = in;
}

void user::setBalance(long in) {
	user::balance = in;
}

void user::addToBalance(long in) {
    //cout<<"HEllow from user.cpp: "<<user::balance<<endl;
	user::balance += in;
	//cout<<"HEllow from user.cpp: "<<user::balance<<endl;
}

void user::subtractFromBalance(long in) {
	user::balance -= in;
}

string user::JSONOutput(string whiteSpaceBeginning, string tag, bool multiLine) const{
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



    stream<<whiteSpaceBeginning<<"\"userName\": \""<<user::userName<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"userKey\": \""<<user::publicKey<<"\","<<whiteSpaceEnd;
    stream<<whiteSpaceBeginning<<"\"balance\": \""<<user::balance<<"\""<<whiteSpaceEnd;
    if(tag.compare("")!=0)
        stream << whiteSpaceBeginningWithoutAddedTab << "}";
    else
        stream << whiteSpaceBeginning << "}";
    return stream.str();
}

string user::toString() const{
	stringstream stream;
	stream << "Username: " << user::userName<<endl;
	stream << " Public Key: " << user::publicKey<<endl;
	stream << " Balance: " << user::balance<<endl;
	return stream.str();
}

ostream &operator<<(ostream &stream, const user &in)
{
	stream << in.toString();
	return stream;
}

bool user::operator>(const user &in)
{
	return user::balance > in.getBalance();
}

bool user::operator<(const user &in)
{
	return user::balance < in.getBalance();
}

user& user::operator +=(const long &in){
	this->balance+=in;
	return *this;
	}

user& user::operator -=(const long &in) {
    this->balance-=in;
    return *this;
}


string user::genPrivateKey(){
   return rand256Gen();
}

string user::genSetPublicKey(const string &privateKeyIn){


    string key=user::rand256Gen();
    user::publicKey=key;
    return key;
}

string user::genSignature(const string &privateKeyIn){
    user temp;
    return temp.rand256Gen();
}

string user::rand256Gen() {
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


#include "user.h"


user::user(){}


user::user(string userName, string publickKey, long balance) {
	user::userName = userName;
	user::publicKey = publicKey;
	user::balance = balance;

}

user::user(string publickKey, long balance) {
	user::publicKey = publicKey;
	user::balance = balance;
}

user::user(string publickKey) {
	user::publicKey = publicKey;
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
	user::publicKey = in;
}

void user::setBalance(long in) {
	user::balance = in;
}

void user::addToBalance(long in) {
	user::balance += in;
}

void user::subtractFromBalance(long in) {
	user::balance -= in;
}

string user::toString() const{
	stringstream stream;
	stream << "Username: " << user::userName;
	stream << " Public Key: " << user::publicKey;
	stream << " Balance: " << user::balance;
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

user user::operator +=(const long &in){
	return user(user::userName, user::publicKey, user::balance + in);
	}

user user::operator -=(const long &in) {
	return user(user::userName, user::publicKey, user::balance - in);
}
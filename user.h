#pragma once
#include <string>
#include <sstream>
using namespace std;
class user
{

private:
	string userName="";
	string publicKey="";
	long balance=0;

public:
	user();
	user(string userName, string publickKey, long balance);
	user(string publickKey, long balance);
	user(string publickKey);
	
	string getUserName() const;
	string getPublicKey() const;
	long getBalance() const;

	void setUserName(string in);
	void setPublicKey(string in);
	void setBalance(long in);

	void addToBalance(long in);
	void subtractFromBalance(long in);

	string toString() const;

	friend ostream &operator << (ostream &, const user &);

	bool operator > (const user &);
	bool operator < (const user &);

	user operator +=(const long &);
	user operator -=(const long &);
	

};


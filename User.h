#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include "picosha2.h"
using namespace std;
class user
{

private:
	string userName="";
	string publicKey="";
	long balance=0;

public:
	user();
    user(string userName, string publicKey, long balance);
	user(string publicKey, long balance);
    user(string publicKey);




    string getUserName() const;
	string getPublicKey() const;
	long getBalance() const;

	void setUserName(string in);
	void setPublicKey(string in);
	void setBalance(long in);

	void addToBalance(long in);
	void subtractFromBalance(long in);

    string JSONOutput(string whiteSpaceBeginning="\t", string tag="\"user\": ", bool multiLine=true) const;

	string toString() const;

	friend ostream &operator << (ostream &, const user &);

	bool operator > (const user &);
	bool operator < (const user &);

	user &operator +=(const long &);
	user &operator -=(const long &);

	string genSetPublicKey(const string &privateKeyIn);

    static string genPrivateKey();

    static string genSignature(const string &privateKeyIn);

    static string rand256Gen();



};


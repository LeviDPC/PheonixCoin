#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include "picosha2.h"

using namespace std;

class User {

private:
    string userName = "";
    string publicKey = "";
    long balance = 0;

public:
    User();

    User(string userName, string publicKey, long balance);

    User(string publicKey, long balance);

    User(string publicKey);


    string getUserName() const;

    string getPublicKey() const;

    long getBalance() const;

    void setUserName(string in);

    void setPublicKey(string in);

    void setBalance(long in);

    void addToBalance(long in);

    void subtractFromBalance(long in);

    string JSONOutput(string whiteSpaceBeginning = "\t", string tag = "\"User\": ", bool multiLine = true) const;

    string toString() const;

    friend ostream &operator<<(ostream &, const User &);

    friend istream &operator>>(istream &stream, User &in);

    bool operator>(const User &);

    bool operator<(const User &);

    User &operator+=(const long &);

    User &operator-=(const long &);

    string genSetPublicKey(const string &privateKeyIn);

    static string genPrivateKey();

    static string genSignature(const string &privateKeyIn);

    static string rand256Gen();


};


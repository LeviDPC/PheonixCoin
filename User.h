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
	//constructors the last three all validate public Key To ensure that a non empty, valid Hex number is imputed
    User();
    User(string userName, string publicKey, long balance);
    User(string publicKey, long balance);
    User(string publicKey);

	//Method for outputting User as a JSON File. Has the option to input leading white space, an opening tag
	//and whether it should be done on one line or multiple.
    string JSONOutput(string whiteSpaceBeginning = "\t", string tag = "\"User\": ", bool multiLine = true) const;
	//Method for outputting User as a string
    string toString() const;

	//Generate a public Key from a private key and set it as the objects Public Key attribute
	//Ideally this would be down with eliptical curve cryptogrophy, however I didn't have time to implement
	//that as the Math is pretty advanced. Right now it just returns a hash of the private key
    string genSetPublicKey(const string &privateKeyIn);
	//Generates a random private key
    static string genPrivateKey();
	//Generates a Signature. Same as with the public Key It would be Ideal if This was genearted with Eliptical Curve Cryptography
	//However right now it is the hash of hte private key and the string "Noise";
    static string genSignature(const string &privateKeyIn);

	//Generates a random 256 bit hexidecimal number
    static string rand256Gen();

	//Add to and subtract from user balance
    void addToBalance(long in);
    void subtractFromBalance(long in);

	//Increment amd Decrement user balance
    User &operator+=(const long &);
    User &operator-=(const long &);

	//compare user balance
    bool operator>(const User &);
    bool operator<(const User &);

	//Methods to output user to an ostream and input a user with an istream
    friend ostream &operator<<(ostream &, const User &);
    friend istream &operator>>(istream &stream, User &in);

	//setters and getters
	//Set Username has some input verification to ensure that a non empty, valid hex number is inputed.
	//Aside from that they are all standard and boring setters and getters
    string getUserName() const;
    string getPublicKey() const;
    long getBalance() const;
    void setUserName(string in);
    void setPublicKey(string in);
    void setBalance(long in);


};


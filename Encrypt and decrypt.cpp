
//
// Description : A program to encrypt and decrypt a message using a shift cipher
// The plaintext message must only contain lowercase alpha and digits 0-9
//
// command line arguments
// -p theplaintextmessage1 - the plaintext (p) message to be encrypted
// -C 2 qnyujrw2n62vn11jpna - the cipher (C) text to be decrypted
// -k 9 - the key (k) shift value
// -E - the option to encrypt (E)
// -D - the option to decrypt (D)
//
#include <iostream> // std :: cout , std :: cin , etc.
#include <cstdlib> //C++ version of stdlib .h
#include <cstring> //C++ version of string .h
#include <string>	//for getline


using namespace std;

#define CBL 64	//codebook length

char codebook[]
= { 
	'a','A','b','B','c','C','d','D','e','E',
	'f','F','g','G','h','H','i','I','j','J',
	'k','K','l','L','m','M','n','N','o','O',
	'p','P','q','Q','r','R','s','S','t','T',
	'u','U','v','V','w','W','x','X','y','Y',
	'z','Z','0','1','2','3','4','5','6','7',
	'8','9','@','$' };


//function prototypes
int indexOfChar(char aChar);
//
// where plaintext and k are the values parsed from the command line
// and s is a reference to a string
//
void encrypt(std::string& plaintext, int k);
//
// where ciphertext and k are the values parsed from the command line
// and s is a reference to a string
//
void decrypt(std::string& ciphertext, int k);
//
// function to copy a cstring to a C++ string
// s is a reference to either the plaintext or ciphertext string
// text is the command line cstring from argv
//
void copy_string(std::string& s, char* text);



int main(int argc, char* argv[])
{
	// todo : return if not enough input
	// todo : declare variables for A01 , an example below :
	int index_of_plaintext = 0; // argv index of plaintext
	int index_of_ciphertext = 0; // argv index of ciphertext
	bool encryptFlag = false; bool decryptFlag = false;
	int k = 0;

	string plainText = "";
	string cipherText = "";

	// todo : process the command line arguments using a loop
	for (int i = 1; i < argc; i++) {
		// use strcmp to compare command line switches to argv [i]
		// .... your code goes here
		if (strcmp(argv[i], "-p") == 0) {
			i++;	//go to next argv
			copy_string(plainText, argv[i]);
		}
		else if (strcmp(argv[i], "-C") == 0) {
			i++;	//go to next argv
			cipherText = argv[i];
		}
		else if (strcmp(argv[i], "-E") == 0) {
			decryptFlag = false;
			encryptFlag = true;
		}
		else if (strcmp(argv[i], "-D") == 0) {
			decryptFlag = true;
			encryptFlag = false;
		}
		else if (strcmp(argv[i], "-k") == 0) {
			i++;	//go to next argv
			k = atoi(argv[i]);
		}
	}
	// todo : -E encrypt the plaintext with key value k
	if (encryptFlag) {
		// use a nested loop to search and replace plaintext with shifted text
		// .... your code goes here
		encrypt(plainText, k);
	}
	// todo : -D decrypt the ciphertext -C with key value k
	if (decryptFlag) {
		// use a nested loop to search and replace ciphertext with plaintext
		// .... your code goes here
		decrypt(cipherText, k);
	}

}

//function implementations
int indexOfChar(char aChar) {
	for (int i = 0; i < CBL; i++) {
		if (codebook[i] == aChar) {
			return i;
		}
	}
	return -1;
}

void encrypt(std::string& plaintext, int k)
{
	string s = "";
	for (int i = 0; i < plaintext.size(); i++) {
		char aChar = plaintext.at(i);
		int p = indexOfChar(aChar);
		p = (p + k) % CBL;
		s += codebook[p];
	}
	cout << "The plaintext was: " << plaintext << endl;
	cout << "The ciphertext is: " << s << endl;
}

void decrypt(std::string& ciphertext, int k)
{
	string s = "";
	for (int i = 0; i < ciphertext.size(); i++) {
		char aChar = ciphertext.at(i);
		int C = indexOfChar(aChar);
		C = C - k;
		if (C >= 0) {
			C = C % CBL;
		}
		else {
			C = (C % CBL + CBL) % CBL;
		}
		s += codebook[C];
	}
	cout << "The ciphertext is: " << ciphertext << endl;
	cout << "The plaintext is: " << s << endl;
}

void copy_string(std::string& s, char* text)
{
	s = "";
	while (*text != '\0') {  //look for non-end of line
		s += *text; //copy a char from text-pointer to string s
		text++;		//points to next char
	}
}

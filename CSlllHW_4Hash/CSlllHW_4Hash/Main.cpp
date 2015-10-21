#include <iostream>
#include <fstream>
#include <map>
#include "HashTable.h"
using namespace std;

const int outputFreq = 1;   

void TheWordGame();

void mapLetterValues(map<char, int>& letterValue);
int sumOfLetterValues(string, map<char, int>);
int FindLengthValue(string);
int findBonus(int);

struct hashNode
{
	string key;
	int count;
	
	hashNode() : key(""), count(1) {}
	string toString()
	{
		stringstream ss;
		ss << "Key: " << key << "  Count : " << count << endl; 
		return ss.str();
	}
};


int main()
{
	TheWordGame();
}




void TheWordGame()
{
	int totalScore = 0;
	string fileKey;
	ifstream file;
	map<char, int> letterValue;
	mapLetterValues(letterValue);
	HashTable<string, hashNode> hashT(100);
	hashNode* bringBack;
	file.open("Game0.txt");
	for (int j = 0; !file.eof(); j++)
	{
		file >> fileKey;
		hashNode* hNode = new hashNode;
		hNode->key = fileKey;
		bringBack = hashT.find(fileKey);  //checks to see if node already exists
		if (bringBack == nullptr)
			hashT.insert(hNode->key, hNode);    //if not, inserted
		else
			bringBack->count++;        //if is, incremented
		int lengthValue = FindLengthValue(fileKey);
		int bonus = findBonus(hashT.find(fileKey)->count);
		int letterSum = sumOfLetterValues(fileKey, letterValue);
		totalScore += lengthValue*bonus*letterSum;
		if (j > outputFreq-1)
		{
			j = 0;
			cout << "The score until now is: " << totalScore << endl;
		}
	}
	cout << endl << "The final score is: " << totalScore << endl;
	file.close();
	cout << hashT.toString() << endl;
}



void mapLetterValues(map<char, int>& letterValue)
{
	letterValue['a'] = 1;
	letterValue['b'] = 3;
	letterValue['c'] = 3;
	letterValue['d'] = 2;
	letterValue['e'] = 1;
	letterValue['f'] = 4;
	letterValue['g'] = 2;
	letterValue['h'] = 4;
	letterValue['i'] = 1;
	letterValue['j'] = 8;
	letterValue['k'] = 5;
	letterValue['l'] = 1;
	letterValue['m'] = 3;
	letterValue['n'] = 1;
	letterValue['o'] = 1;
	letterValue['p'] = 3;
	letterValue['q'] = 10;
	letterValue['r'] = 1;
	letterValue['s'] = 1;
	letterValue['t'] = 1;
	letterValue['u'] = 1;
	letterValue['v'] = 4;
	letterValue['w'] = 4;
	letterValue['x'] = 8;
	letterValue['y'] = 4;
	letterValue['z'] = 10;
}


int FindLengthValue(string word)
{
	int lengthValue = word.length() - 2;
	if (word.length() > 8)
		lengthValue = 8;
	if (word.length() < 3)
		lengthValue = 0;
	return lengthValue;
}

int findBonus(int freq)
{
	int bonus;
	freq--;
	if (freq < 0) bonus = 5;
	else if (freq > 0 && freq < 6) bonus = 4;
	else if (freq > 5 && freq < 11) bonus = 3;
	else if (freq > 10 && freq < 16) bonus = 2;
	else bonus = 1;
	return bonus;
}

int sumOfLetterValues(string word, map<char, int> letterValue)
{
	int sum = 0;
	for (int i = 0; i < word.length(); i++)
	{
		sum += letterValue.find(word[i])->second;
	}
	return sum;
}

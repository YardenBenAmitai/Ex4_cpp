
#include "SmartGuesser.hpp"
#include "calculate.hpp"

#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;

void SmartGuesser::startNewGame(unsigned int len){
	length=len;
	int ListLength=10;
	
	for(int i=0; i<length; i++){
		ListLength = ListLength * length;
	}
	
	for(int i=ListLength/10; i<ListLength; i++){
		string NumToList;
		ostringstream oss;
		oss << i;
		NumToList= oss.str();
		this->MyList.push_back(NumToList);
	}
	
	cout<<"a new game starts now"<<endl;
}


string SmartGuesser::guess() {
	list<string>::iterator it = this->MyList.begin();
	advance(it, rand()% MyList.size() + 1);
	string MyGuess= *it;
	this->LastGuess= *it;
	return MyGuess;
}


void SmartGuesser::learn(string s) {
	pair <int, int> p= stringToPair(s);
	
	list<string>::iterator ite = this->MyList.begin();
	while(ite!=this->MyList.end()){
		if (stringToPair(calculateBullAndPgia(LastGuess, *ite)) != p){
			ite = this->MyList.erase(ite);
		} else
			++ite;
	}
}
	
pair<int, int> SmartGuesser::stringToPair(string s){
	string delimiter = ",";
	string bull = s.substr(0, s.find(delimiter));
	bull.erase(0,s.find(delimiter));
	string pgia=s;
	stringstream sb(bull);
	stringstream sp(pgia);
	pair <int, int> p;
	sb >> p.first;
	sp >> p.second;
	return p;
}

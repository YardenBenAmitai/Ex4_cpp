
#include "SmartGuesser.hpp"
#include "calculate.hpp"

#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include<cstdlib>
#include<ctime>

using namespace std;

void SmartGuesser::startNewGame(unsigned int len){
	length=len;
	int ListLength=1;
	
	for(unsigned int i=0; i<length; i++){
		ListLength = ListLength * 10;
	}
	
	for(int j=0; j<ListLength; j++){
		string s(len - to_string(j).length() , '0');
		s=s+to_string(j);
		this->MyList.push_back(s);
		cout<<(s)<<" ";
	}
	cout<<endl;
}


string SmartGuesser::guess() {
	if(this->MyList.size() <=0){
		return "";
	} 
	
	list<string>::iterator it = this->MyList.begin();
	if(this->MyList.size()==1){
		return *it;
	}
	advance(it, rand() % this->MyList.size());
	string MyGuess= *it;
	this->LastGuess= *it;
	return MyGuess;
}


void SmartGuesser::learn(string s) {
	pair <int, int> p= stringToPair(s);
	pair <int, int> guess;
	list<string>::iterator ite = this->MyList.begin();
	while(ite != this->MyList.end()){
		guess=stringToPair(calculateBullAndPgia(LastGuess, *ite));
		if (guess != p){
			ite = this->MyList.erase(ite);
		} else{
			++ite;
		}
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

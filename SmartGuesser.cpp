
#include "SmartGuesser.hpp"
#include "calculate.hpp"

#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>

using namespace std;

void SmartGuesser::startNewGame(unsigned int len){
	cout<<"start new game with len "<<len<<endl;
	length=len;
	int ListLength=1;
	
	for(unsigned int i=0; i<length; i++){
		ListLength = ListLength * 10;
	}
	
	for(int j=0; j<ListLength; j++){
		string s(len - to_string(j).length() , '0');
		s=s+to_string(j);
		this->MyList.push_back(s);
		cout<<s<<" ";
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
	cout<<"start learn with "<<s<<endl;
	pair <int, int> p= stringToPair(s);
	list<string>::iterator ite = this->MyList.begin();
	while(ite != this->MyList.end()){
		if (stringToPair(calculateBullAndPgia(LastGuess, *ite)) != p){
			ite = this->MyList.erase(ite);
		} else{
			++ite;
		}
	}
	list<string>::iterator it = this->MyList.begin();
	while(ite != this->MyList.end()){
		cout<<*it<<" ";
		++it;
	}
	cout<<"end learn"<<endl;
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

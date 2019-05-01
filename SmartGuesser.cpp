
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
	}
}


string SmartGuesser::guess() {
	if(this->MyList.size() <=0){
		return "";
	} else if (this->MyList.size()==1){
		return *(this->MyList.begin());
	} else{
		list<string>::iterator it = this->MyList.begin();
		srand(time(0));
		advance(it, rand() % this->MyList.size());
		string MyGuess= *it;
		this->LastGuess= *it;
		return MyGuess;
	}
}


void SmartGuesser::learn(string s) {
	pair <int, int> p= stringToPair(s);
	list<string>::iterator ite = this->MyList.begin();
	for (auto ite = this->MyList.begin(); ite!=this->MyList.end(); ite++){
		if (stringToPair(calculateBullAndPgia(LastGuess, *ite)) != p){
			ite = this->MyList.erase(ite);
		}
	}
	//for (auto it = this->MyList.begin(); ite!=this->MyList.end(); ite++){
	//	cout<<*it<<" ";
	//}
	//cout<<endl;
}


pair<int, int> SmartGuesser::stringToPair(string s){
	string bull = s.substr(0, s.find(","));
	bull.erase(0,s.find(","));
	string pgia=s;
	
	stringstream sb(bull);
	stringstream sp(pgia);
	pair <int, int> p;
	sb >> p.first;
	sp >> p.second;
	return p;
}

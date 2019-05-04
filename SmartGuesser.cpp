
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
	cout<<"smart guesser new game with length "<<len<<endl;
	this->length=len;
	(this->MyList).clear();
	int ListLength=1;
	
	for(unsigned int i=0; i<this->length; i++){
		ListLength = ListLength * 10;
	}
	
	for(int j=0; j<ListLength; j++){
		string s(len - to_string(j).length() , '0');
		s=s+to_string(j);
		this->MyList.push_back(s);
		//cout<<(s)<<" ";
	}
	//cout<<"end of new game with length "<<this->MyList.size()<<endl;
	//cout<<endl;
	//if(this->length==4){
	//	for (auto ite = this->MyList.begin(); ite != this->MyList.end(); ite++){
	//		cout<<*ite<<" ";
	//	}
	//	cout<<endl;
	//}
}


string SmartGuesser::guess() {
	//cout<<"smart guesser guess"<<endl;
	if(this->MyList.size() ==0){
		return "";
	} else if(this->MyList.size()==1){
		this->LastGuess = *(this->MyList.begin());
		cout<<"my guess ==1 "<<this->LastGuess<<endl;
		return *(this->MyList.begin());
	}else{
		list<string>::iterator it = this->MyList.begin();
		//srand(time(0));
		advance(it, rand() % this->MyList.size());
		string MyGuess= *it;
		this->LastGuess= *it;
		cout<<"my guess "<<MyGuess<<endl;
		return MyGuess;
	}
}


void SmartGuesser::learn(string s) {
	cout<<"smart guesser learn from "<<s<<endl;
	pair <int, int> p= stringToPair(s);
	pair <int, int> curr; 
	//int looped=0;
	//cout<<"my list size i "<<this->MyList.size()<<endl;
	auto ite = this->MyList.begin();
	while (ite != this->MyList.end()){
		//looped++;
		
		curr=stringToPair(calculateBullAndPgia(this->LastGuess, *ite));
		if ( curr.first != p.first || curr.second != p.second){
			if (this->length==4)
				cout<<*ite<<endl;
			ite = (this->MyList).erase(ite);
		}
		else
			++ite;
	}
	cout<<" "<<endl;
	
}
	
pair<int, int> SmartGuesser::stringToPair(string s){
	//cout<<"smart guesser string to pair"<<endl;
	string bull = s.substr(0, s.find(","));
	s.erase(0,s.find(",")+1);
	string pgia=s;
	
	stringstream sb(bull);
	stringstream sp(pgia);
	pair <int, int> p;
	sb >> p.first;
	sp >> p.second;
	return p;
}

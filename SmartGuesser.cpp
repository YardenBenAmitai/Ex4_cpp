
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
	cout<<"new game with length of "<<len<<endl;
	(this->MyList).clear();
	this->LastGuess="";
	this->FirstTurn=0;
	this->length=len;
	
	int ListLength=1;
	
	for(unsigned int i=0; i<this->length; i++){
		ListLength = ListLength * 10;
	}
	
	for(unsigned int j=0; j<ListLength; j++){
		string s(len - to_string(j).length() , '0');
		s=s+to_string(j);
		this->MyList.push_back(s);
		//cout<<(s)<<" ";
	}
	//cout<<endl;
}


string SmartGuesser::guess() {
	//cout<<"guess"<<endl;
	if(this->MyList.size() <=0){
		return "";
	} else if(this->MyList.size()==1){
		this->LastGuess = *(this->MyList.begin());
		cout<<"my guess ==1 "<<this->LastGuess<<endl;
		return *(this->MyList.begin());
	} else{
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
	cout<<"learn from "<<s<<endl;
	pair <int, int> p= stringToPair(s);
	pair <int, int> curr; 
	if(this->FirstTurn==0){
		ClearList(p);
	}
	
	//cout<<endl;
	auto ite=this->MyList.begin();
	while ( ite != this->MyList.end()){
		curr=stringToPair(calculateBullAndPgia(LastGuess, *ite));
		//cout<<"pair is "<<curr.first<<","<<curr.second<<" for guess and it "<<*ite<<endl;
		if ( curr.first != p.first || curr.second != p.second){
			ite = this->MyList.erase(ite);
		}
		else
			++ite;
	}
	
}

void SmartGuesser::ClearList(pair<int, int> p){
	this->FirstTurn=1;
	if(p.first==0 && length>2){
		auto ite=this->MyList.begin();
		while(ite!=this->MyList.end()){
			if ((*ite)[0]==this->LastGuess[0]){
				auto ite2=ite;
				advance (ite2, 10*(length-1));
				ite= this->MyList.erase(ite, ite2);
			} else if((*ite)[1]==this->LastGuess[1]){
				auto ite2=ite;
				advance (ite2, 10*(length-2));
				ite=this->MyList.erase(ite, ite2);
			} else{
				++ite;
			}
		} 
	//	ite = this->MyList.begin();
	//while(ite!=this->MyList.end()){
	//	cout<<*ite<<" ";
	//	++ite;
	//}
		cout<<"clear list done"<<endl;
	}
}


pair<int, int> SmartGuesser::stringToPair(string s){
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

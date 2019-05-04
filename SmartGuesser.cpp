
#include "SmartGuesser.hpp"
#include "calculate.hpp"

#include<bits/stdc++.h> 
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include<cstdlib>
#include<ctime>

using namespace std;

void SmartGuesser::startNewGame(unsigned int len){
	//cout<<"new game with "<<len<<endl;
	this->MyList.clear();
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
	//auto ite = this->MyList.begin();
	//while(ite!=this->MyList.end()){
	//	cout<<*ite<<" ";
	//	++ite;
	//}
	//cout<<endl;
}


string SmartGuesser::guess() {
	if(this->MyList.size() ==0){
		return "";
	} else if(this->MyList.size()==1){
		//cout<<"my guess ==1 "<<this->LastGuess<<endl;
		return *(this->MyList.begin());
	} else{
		list<string>::iterator it = this->MyList.begin();
		//srand(time(0));
		advance(it, rand() % this->MyList.size());
		string MyGuess= *it;
		this->LastGuess= *it;
		//cout<<"my guess "<<MyGuess<<endl;
		return MyGuess;
	}
}


void SmartGuesser::learn(string s) {
	//cout<<"learn from "<<s<<endl;
	pair <int, int> p= stringToPair(s);
	pair <int, int> curr; 
	if (this->FirstTurn>=2 || (p.first==0 && this->FirstTurn<2)){
		if(this->FirstTurn<2 && this->length>2 && p.first==0){
			ClearList(p);
			//cout<<this->MyList.size()<<endl;
		}
		else {
			auto ite = this->MyList.begin();
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
	}
}

void SmartGuesser::ClearList(pair<int, int> p){
	++(this->FirstTurn);
	//auto ite = this->MyList.begin();
	//while ( ite != this->MyList.end()){
	//	cout<<*ite<<" ";
	//	++ite;
	//}
	//cout<<"clearlist"<<endl;
		auto ite=this->MyList.begin();
		while(ite!=this->MyList.end()){
			if ((*ite)[0]==this->LastGuess[0]){
				auto ite2=ite;
				if((*ite)[0]=='9'){
					ite2=this->MyList.end();
				} else
					advance (ite2, pow(10,length-1));
				
				ite= this->MyList.erase(ite, ite2);
			/**} else if((*ite)[1]==this->LastGuess[1]){
				auto ite2=ite;
				if((*ite)[1]=='9' && (*ite)[0]=='9'){
					ite2=this->MyList.end();
				} else
					advance (ite2, pow(10,length-2));
				ite=this->MyList.erase(ite, ite2);
			} else if((*ite)[2]==this->LastGuess[2]){
				auto ite2=ite;
				if((*ite)[2]=='9' &&(*ite)[1]=='9' && (*ite)[0]=='9'){
					ite2=this->MyList.end();
				} else
					advance (ite2, pow(10,length-3));
				ite=this->MyList.erase(ite, ite2);
			**/} else{
				++ite;
			}
		}
//cout<<"done clear list"<<endl;		
	
	//auto ite1 = this->MyList.begin();
	//while(ite1!=this->MyList.end()){
	//	cout<<*ite1<<" ";
	//	++ite1;
	//}
	//cout<<endl;
	//cout<<endl;
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

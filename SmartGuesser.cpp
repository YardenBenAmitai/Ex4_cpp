
#include "SmartGuesser.hpp"
#include "calculate.hpp"

#include<bits/stdc++.h> 
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iterator>

using namespace std;

/**
starts a new game by first setting all the fields to their initial values
and then assigning the length for the combinations.
the method also creates a 'pool' of all the different combinations possible, for method 'learn' to eliminate from.
**/
void SmartGuesser::startNewGame(unsigned int len){
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
	}
}

/**
the method chooses a random number ranged from 0 to |pool| (number of elements in pool)
and advances an iterator, the chosen number of steps and then return that value as the next guess.
**/
string SmartGuesser::guess() {
	if(this->MyList.size() ==0){
		return "";
	} else if(this->MyList.size()==1){
		return *(this->MyList.begin());
	} else{
		list<string>::iterator it = this->MyList.begin();
		//srand(time(0));
		advance(it, rand() % this->MyList.size());
		string MyGuess= *it;
		this->LastGuess= *it;
		return MyGuess;
	}
}

/**
learn method receives a string in the form of "x,y" (bull,pgia).
if its the first run in a new game then the method will look for "0,y" so it could eliminate a larg number of elements from the pool at once,
otherwise it will do nothing.
if it is not the first run then method proceeds with a partial knuth's "five-steps" algorithm,
where the last guess is compared to every element in the pool and must produce the same form as the given string, otherwise it is eliminated.
**/
void SmartGuesser::learn(string s) {
	pair <int, int> p= stringToPair(s);
	pair <int, int> curr; 
	if (this->FirstTurn>=1 || (p.first==0 && this->FirstTurn<1)){
		if(this->FirstTurn<1 && this->length>2){
			ClearList();
		}
		auto ite = this->MyList.begin();
		while ( ite != this->MyList.end()){
			curr=stringToPair(calculateBullAndPgia(LastGuess, *ite));
			if ( curr.first != p.first || curr.second != p.second){
				ite = this->MyList.erase(ite);
			} else
				++ite;
		}
	}
}

/**
private:
the method clears the initial pool with accordance to the last guess, assuming the comparison resulted in "0,y"
**/
void SmartGuesser::ClearList(){
	++(this->FirstTurn);
	if(this->length >2){
		auto ite=this->MyList.begin();
		while(ite!=this->MyList.end()){
			if ((*ite)[0]==this->LastGuess[0]){
				auto ite2=ite;
				if((*ite)[0]=='9'){
					ite2=this->MyList.end();
				} else
					advance (ite2, pow(10,length-1));
				
				ite= this->MyList.erase(ite, ite2);
			} else if((*ite)[1]==this->LastGuess[1]){
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
			} else{
				++ite;
			}
		}
	}
}

/**
private:
the method receives a string in the form of "x,y" and returns a pair of <int, int>
such that <x,y>
**/
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

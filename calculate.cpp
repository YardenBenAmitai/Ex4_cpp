
#include "calculate.hpp"
#include <iostream>
#include <string>
using namespace std;

/**
the method compare between two given strings and  produce a string in the form of "x,y",
where x is bull (the number of chars that are identically placed between the two strings) and y is pgia (the number of chars both strings have in common).
a char counted by bull can not be counted again by pgia also each pgia can only be counted by one char from each string
(for example, #2## and 2#2# results is 1 pgia).
**/

string calculateBullAndPgia(string choise, string guess){
	unsigned int bull=0, pgia=0;
	unsigned int i, j;
		
	i=0;
	//while loop calculates how many bull-s there are and then erase them so they would not be calculated twice.
	while(i < choise.length()){ 
		if(choise[i]==guess[i]){
			bull++;
			choise.erase (i, 1);
			guess.erase (i, 1);
		}else
			i++;
	}
	
	i=0;
	//two for loops calculate how many pgia-s there are and then erase them.
	while (i<choise.length()){
		j=0;
		while( j<guess.length() && i<choise.length()){
			if(choise[i]==guess[j]){
				pgia++;
				//choise.erase (i, 1);
				guess.erase (j, 1);
				//--i;
				break;
			}else
				j++;
				
		}
		i++;
	}
	
	return std::to_string(bull)+","+std::to_string(pgia);
}

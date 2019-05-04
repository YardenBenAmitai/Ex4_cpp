
#include "calculate.hpp"
#include <iostream>
#include <string>
using namespace std;

string calculateBullAndPgia(string choise, string guess){
	//cout<<"calculate between "<<choise<<" "<<guess<<endl;
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
				choise.erase (i, 1);
				guess.erase (j, 1);
				--i;
				break;
			}else
				j++;
				
		}
		i++;
	}
	
	return std::to_string(bull)+","+std::to_string(pgia);
}

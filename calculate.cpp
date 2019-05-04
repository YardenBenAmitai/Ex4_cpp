
#include "calculate.hpp"
#include <iostream>
#include <string>
using namespace std;

string calculateBullAndPgia(string choise, string guess){
	cout<<"calculate between "<<choise<<" "<<guess<<endl;
		unsigned int bull, pgia;
		unsigned int i, j;
		
		bull=0;
		i=0;
		//while loop calculates how many bull-s there are and then erase them so they would not be calculated twice.
		while ( i < choise.length() ){ 
			if(choise[i]==guess[i]){
				bull++;
				choise.erase (i, 1);
				guess.erase (i, 1);
			}
			else 
				i++;
		}
		
		
		pgia=0;
		//two for loops calculate how many pgia-s there are and then erase them.
		for( i=0; i<choise.length(); i++){
			for(j=0; j<guess.length() && i<choise.length(); j++){
				if(choise[i]==guess[j]){
					pgia++;
					choise.erase (i, 1);
					guess.erase (j, 1);
					i--; j--;
				}
			}
		}
		
		return std::to_string(bull)+","+std::to_string(pgia);
	}
	

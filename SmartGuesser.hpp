
#ifndef SMART_G
#define SMART_G

#include "Guesser.hpp"
#include "calculate.hpp"
#include <stdlib.h>
#include <string>
#include <list>

using namespace std;

class SmartGuesser: public bullpgia::Guesser {
	public:
	SmartGuesser() { }
	string guess() override;
	void learn(string) override;
	void startNewGame(unsigned int len) override;
	
	private:
	pair<int, int> stringToPair(string);
	void ClearList(pair<int,int>);
	
	protected:
	list<string> MyList;
	string LastGuess;
	int FirstTurn;
};

#endif

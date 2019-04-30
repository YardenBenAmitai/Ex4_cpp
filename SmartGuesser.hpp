
#ifndef SMART_G
#define SMART_G

#include "Guesser.hpp"
#include "calculate.hpp"
#include <stdlib.h>
#include <string>
#include <list>

using namespace std;

class SmartGuesser: public bullpgia::Guesser {
	string guess() override;
	void learn(string) override;
	void startNewGame(unsigned int len) override;
	pair<int, int> stringToPair(string);
	
	protected:
	list<string> MyList;
	string LastGuess;
};

#endif
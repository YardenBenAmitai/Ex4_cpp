#ifndef GUESSER
#define GUESSER
#include <string>
#include <iostream>
using namespace std;
namespace bullpgia{
	
	class Guesser{
		
		protected:
		unsigned int length;
		
		public:
		virtual std::string guess() {return "";}
		virtual void learn(string s) {};
		virtual void startNewGame(unsigned int len){length=len;}
		
	};
}

#endif
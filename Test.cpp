/**
 * A demo program for bull-pgia.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */


#include <iostream>
using namespace std;

#include "play.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
#include "badkan.hpp"
#include <iostream>
#define COMMA ,

using namespace bullpgia;

int main() {

	badkan::TestCase testcase;
	int grade=0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0) {
		// BASIC TESTS - DO NOT CHANGE
		ConstantChooser c1234{"1234"}, c12345{"12345"}, c9999{"9999"};
		ConstantGuesser g1234{"1234"}, g12345{"12345"}, g9999{"9999"};

		testcase.setname("Calculate bull and pgia")
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1234"), "4,0")      // 4 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","4321"), "0,4")      // 0 bull, 4 pgia
		;

		testcase.setname("Play with dummy choosers and guessers")
		.CHECK_EQUAL(play(c1234, g1234, 4, 100), 1)      // guesser wins in one turn.
		.CHECK_EQUAL(play(c1234, g9999, 4, 100), 101)    // guesser loses by running out of turns 
		.CHECK_EQUAL(play(c1234, g12345, 4, 100), 101)   // guesser loses technically by making an illegal guess (too long).
		.CHECK_EQUAL(play(c12345, g1234, 4, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
		;

		testcase.setname("Play with smart guesser");
		RandomChooser randy;
		SmartGuesser smarty;
		for (unsigned int i=0; i<100; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 4, 100)<=100, true);  // smarty should always win in at most 10 turns!
		}
		
		// ADDITIONAL TESTS
		ConstantChooser cc1{""}, cc2{"2864"};
		RandomChooser rc;
		RandomGuesser rg;
		SmartGuesser sg;
		
		testcase.setname("our test")
		.CHECK_OUTPUT(calculateBullAndPgia("1234", "5678"), "0,0")
		.CHECK_OUTPUT(calculateBullAndPgia("7289", "0139"), "1,0")
		.CHECK_OUTPUT(calculateBullAndPgia("7209", "2422"), "0,1")
		.CHECK_OUTPUT(calculateBullAndPgia("1447", "4944"), "1,1")
		.CHECK_OUTPUT(calculateBullAndPgia("9003", "3009"), "2,2")

		
		.CHECK_EQUAL(play(cc1, rg, 0, 1), 1)              		//guesser wins in one turn
		.CHECK_EQUAL(play(cc2, sg, 4, 100) <=12, true)          //smart guesser deduce the number in under 6 turns.
		.CHECK_EQUAL(play(rc, sg, 6, 100)<=20, true)		//smart guesser guesses correctly under 50 tries.
		;
		
		grade = testcase.grade();
	} else {
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "Your grade is: "  << grade << endl;
	return 0;
}

#pragma once
#include "State.h"

class Transition
{
public:
	char input;
	char output;
	//false to the left true to the right
	bool moveDirection;
	int nextState;
public:
	Transition();
	Transition(char transitionInput, char transitionOutput, int transitionNextState, bool direction);
	~Transition();
	char getInput();
	void setInput(char newInput);
	char getOutput();
	void setOutput(char newOutput);
	void setNextState(int newNextState);
	int getNextState();
	bool getDirection();
};


#include "Transition.h"
Transition::Transition()
{

}

Transition::Transition(char transitionInput, char transitionOutput, int transitionNextState, bool direction)
{
	input = transitionInput;
	output = transitionOutput;
	nextState = transitionNextState;
	moveDirection = direction;
}


Transition::~Transition()
{
}


char Transition::getInput() {
	return input;
}
void Transition::setInput(char newInput)
{
	input = newInput;
}
char Transition::getOutput()
{
	return output;
}
void Transition::setOutput(char newOutput)
{
	output = newOutput;
}
void Transition::setNextState(int newNextState)
{
	nextState = newNextState;
}
int Transition::getNextState()
{
	return nextState;
}
bool Transition::getDirection()
{
	return moveDirection;
}
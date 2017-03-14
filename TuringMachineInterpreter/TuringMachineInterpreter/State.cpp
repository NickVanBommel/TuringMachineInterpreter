#include "State.h"
#include "Transition.h"
State::State()
{
	stateID = -1;
	stateTransitions = std::vector<Transition>();
}
State::State(int newStateID)
{
	stateID = newStateID;
	stateTransitions = std::vector<Transition>();
}

State::~State()
{
}
void State::addNewTransition(Transition newTransition)
{
	stateTransitions.push_back(newTransition);
}
int State::getStateID()
{
	return stateID;
}

int State::getNextState(std::string &tape, int &tapeIndex)
{
	if (tapeIndex >= tape.length())
		tape = tape + "_";
	else if (tapeIndex < 0)
	{
		tape = "_" + tape;
		tapeIndex++;
	}
	char currentInput = tape[tapeIndex];
	Transition* currentTransition = getTransitionByInput(currentInput);
	if (currentTransition == NULL)
	{
		return -1;
	}
	else
	{
		tape[tapeIndex] = currentTransition->getOutput();
		bool direction = currentTransition->getDirection();
		if (direction)
			tapeIndex++;
		else
			tapeIndex--;
		return currentTransition->getNextState();
	}
}

Transition* State::getTransitionByInput(char input) {
	for (int i = 0; i < stateTransitions.size(); i++)
	{
		if (stateTransitions[i].getInput() == input)
			return &stateTransitions[i];
	}
	return NULL;
}

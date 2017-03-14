#pragma once
#include <vector>
#include <string>
class Transition;
class State
{
private:
	int stateID;
	std::vector<Transition> stateTransitions;

public:
	State();
	State(int newStateID);
	~State();
	void addNewTransition(Transition newTransition);
	int getStateID();
	int getNextState(std::string &tape, int &tapeIndex);
	Transition* getTransitionByInput(char input);
};


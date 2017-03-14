#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Transition.h"
#include "State.h"
using namespace std;


int findNextState(string &currentTape, int tapeIndex, vector<State> &states, State &currentState)
{

	int nextState = currentState.getNextState(currentTape, tapeIndex);
	if (nextState == -1)
	{
		return currentState.getStateID();
	}
	else
	{
		for (int i = 0; i < states.size(); i++)
		{
			if (states[i].getStateID() == nextState)
			{
				return findNextState(currentTape, tapeIndex, states, states[i]);
			}
		}
	}
	return 0;
}
bool evaluateString(string &tape, vector<State> &states, vector<int> &finalStates)
{
	int endingState = -1;
	//find first state
	for (int i = 0; i < states.size(); i++)
	{
		if (states[i].getStateID() == 0)
		{
			endingState = findNextState(tape, 1, states, states[i]);
		}
	}
	for (int i = 0; i < finalStates.size(); i++)
	{
		if (finalStates[i] == endingState)
			return true;
	}
	return false;	
}

int main()
{
	ifstream inputFile("input.txt");
	vector<State> states;
	vector<string> testInputLines;
	vector<int> finalStates;
	string inputLine;
	//read the inputs
	if (inputFile.is_open())
	{
		while (getline(inputFile, inputLine))
		{
			//if this is a transition parse out the states
			if (inputLine[0] == 't')
			{
				string currentValue;
				int indexOfValues = 0;
				int stateFrom = -1;
				int stateTo = -1;
				char input;
				char output;
				bool direction;
				for (int i = 2; i < inputLine.length(); i++)
				{
					if (inputLine[i] != ' ')
					{
						currentValue += inputLine[i];
					}
					else if (currentValue != "")
					{
						switch (indexOfValues)
						{
							//state from
						case 0:
							stateFrom = stoi(currentValue);
							indexOfValues++;
							break;
							//input
						case 1:
							input = currentValue[0];
							indexOfValues++;
							break;
							//state to
						case 2:
							stateTo = stoi(currentValue);
							indexOfValues++;
							break;
							//output
						case 3:
							output = currentValue[0];
							indexOfValues++;
							break;
							//direction
						case 4:
							if (currentValue == "R")
								direction = true;
							else if (currentValue == "L")
								direction = false;
							indexOfValues++;
							break;
						}
						currentValue = "";
					}
				}
				if (currentValue != "")
				{
					switch (indexOfValues)
					{
						//state from
					case 0:
						stateFrom = stoi(currentValue);
						indexOfValues++;
						break;
						//input
					case 1:
						input = currentValue[0];
						indexOfValues++;
						break;
						//state to
					case 2:
						stateTo = stoi(currentValue);
						indexOfValues++;
						break;
						//output
					case 3:
						output = currentValue[0];
						indexOfValues++;
						break;
						//direction
					case 4:
						if (currentValue == "R")
							direction = true;
						else if (currentValue == "L")
							direction = false;
						indexOfValues++;
						break;
					}
					currentValue = "";
				}
				//build states and transitions
				bool stateExists = false;
				for (int i = 0; i < states.size(); i++)
				{
					if (stateTo == states[i].getStateID())
					{
						stateExists = true;
						break;
					}
				}
				//create the from state
				if (!stateExists)
				{
					State newEndState = State(stateTo);
					states.push_back(newEndState);
				}


				//create the transition
				Transition newTransition;
				for (int i = 0; i < states.size(); i++)
				{
					if (stateTo == states[i].getStateID())
					{
						newTransition = Transition(input, output, states[i].getStateID(), direction);
					}
				}
				stateExists = false;
				for (int i = 0; i < states.size(); i++)
				{
					if (stateFrom == states[i].getStateID())
					{
						stateExists = true;
						states[i].addNewTransition(newTransition);
						break;
					}
				}
				//create the from state
				if (!stateExists){
					State newStartState = State(stateFrom);
					newStartState.addNewTransition(newTransition);
					states.push_back(newStartState);
				}
			}
			//if this is an input
			else if (inputLine[0] == 'i')
			{
				string inputString = inputLine.substr(2, inputLine.length() - 2);
				inputString = "_" + inputString + "_";
				testInputLines.push_back(inputString);
			}
			//if this the list of final states
			else if (inputLine[0] == 'f')
			{
				string currentValue;
				for (int i = 2; i < inputLine.length(); i++)
				{
					if (inputLine[i] != ' ')
					{
						currentValue += inputLine[i];
					}
					else if (currentValue != "")
					{
						finalStates.push_back(stoi(currentValue));
						currentValue = "";
					}
				}
				if (currentValue != "")
				{
					finalStates.push_back(stoi(currentValue));
					currentValue = "";
				}
			}
		}
		inputFile.close();
	}
	ofstream outputFile;
	outputFile.open("output.txt");
	for (int i = 0; i < testInputLines.size(); i++)
	{
		string tape = testInputLines[i];
		bool acceptInput = evaluateString(tape, states, finalStates);
		outputFile << tape << endl;
		if (acceptInput)
			outputFile << "ACCEPT\n\n";
		else
			outputFile << "REJECT\n\n";
	}
}

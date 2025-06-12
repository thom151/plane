#pragma once


#include <glm/glm.hpp>
#include <vector>
#include <iostream>

enum Operation {
	ADD,
	MULTIPLY
};

struct Calculation {
	Operation op;
	std::vector<glm::vec3*> vectors;
	glm::vec3 result;
};

class Calculator {
public:
	Calculator(std::vector<glm::vec3>* userPoints):
	m_userPoints {userPoints}
	{
		std::cout << "Calculator made\n";
	}


	void appendToCurrent() {
		//TODO
	}

	void clearCurrent() {
		//TODO
	}


	void calculateCurrent() {
		currentCalculation.result = glm::vec3(0.0f, 0.0f, 0.0f);
		for (int i = 0; i < currentCalculation.vectors.size(); ++i) {
			currentCalculation.result += currentCalculation.vectors[i];
		}
		
	}
private:
	std::vector<Calculation*> calculationList;
	bool equalPending;
	bool operatorIsNext;
	Calculation currentCalculation;
	std::vector<glm::vec3>* m_userPoints;
	
};
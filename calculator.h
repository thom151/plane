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
	std::vector<glm::vec3*> vecColors;
	glm::vec3 result;
};

class Calculator {
public:

	std::vector<char> vectorsSelected;

	Calculator(std::vector<glm::vec3>* userPoints, std::vector<glm::vec3>* userColors):
	m_userPoints {userPoints}, equalPending {false}, addMode{ false }, m_userColors {userColors}
	{
		std::cout << "Calculator made\n";
	}


	void appendToCurrent(glm::vec3& userPoint, glm::vec3& userColor) {
		currentCalculation.vectors.push_back(&userPoint);
		currentCalculation.vecColors.push_back(&userColor);
	}

	void clearCurrent() {
		std::cout << "current";
		currentCalculation.result = glm::vec3(0.0f, 0.0f, 0.0f);
		currentCalculation.vectors.clear();
		currentCalculation.vecColors.clear();
	}


	void appendVecSelected() {
		vectorsSelected.push_back(false);
	}

	void setAddMode() {
		currentCalculation.op = ADD;
		addMode = true;
		equalPending = true;
	}

	void setAddModeOff() {
		addMode = false;
		equalPending = false;
	}

	void setCalcFinish() {	
		if (currentCalculation.op == ADD) {
			assert(currentCalculation.vectors.size() > 1);
			glm::vec3 result = glm::vec3(0.0f);
			for (size_t i = 0; i < currentCalculation.vectors.size(); ++i) {
				result += *currentCalculation.vectors[i];
				std::cout << "curr x:" << currentCalculation.vectors[i]->x << '\n';
			}
			currentCalculation.result = result;
			calculationList.push_back(currentCalculation);
			equalPending = false;

			std::cout << "result x: " << calculationList[0].result.x << '\n';
			std::cout << "result y: " << calculationList[0].result.y << '\n';
		}
	}

	void reCalculateCurrent() {
		if (currentCalculation.op == ADD) {
			assert(currentCalculation.vectors.size() > 1);
			glm::vec3 result = glm::vec3(0.0f);
			for (size_t i = 0; i < currentCalculation.vectors.size(); ++i) {
				result += *currentCalculation.vectors[i];
				std::cout << "curr x:" << currentCalculation.vectors[i]->x << '\n';
			}
			currentCalculation.result = result;
			calculationList[0] = currentCalculation;
			equalPending = false;

			std::cout << "result x: " << calculationList[0].result.x << '\n';
			std::cout << "result y: " << calculationList[0].result.y << '\n';
		}
	}


	//getters
	bool getAddMode() {
		return addMode;
	}

	void arrowVerticesUpdate(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& colors) {
		std::cout << "updating arrows\n";
			
		std::vector<glm::vec3*> tempCurrCalc = calculationList[0].vectors;
		vertices.push_back(glm::vec3(0.0f, 0.0f, 0.0f)); //origin
		colors.push_back(*calculationList[0].vecColors[0]); //color of first/origin

		glm::vec3 currSum = glm::vec3(0.0f);
		for (size_t j = 0; j < calculationList[0].vectors.size() - 1; ++j) {
			
			
			//current tip
			currSum += *tempCurrCalc[j];
			vertices.push_back(currSum);
			colors.push_back(*calculationList[0].vecColors[j]);

			//tail  
			vertices.push_back(currSum);
			colors.push_back(*calculationList[0].vecColors[j + 1]);
			
			
		}

		//then this would be the last tip
		vertices.push_back(calculationList[0].result);
		colors.push_back(*calculationList[0].vecColors.back());


		//from origin to the sum
		vertices.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		vertices.push_back(calculationList[0].result);

		colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		
	}



	

private:
	std::vector<Calculation> calculationList;
	bool equalPending;
	bool operatorIsNext;
	bool addMode;
	Calculation currentCalculation;
	std::vector<glm::vec3>* m_userPoints;
	std::vector<glm::vec3>* m_userColors;
	
};
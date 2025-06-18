#pragma once


#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "gridRenderer.h"

enum Operation {
	ADD,
	MULTIPLY,
	NOOP,
};

struct Calculation {
	Operation op;
	std::vector<glm::vec3*> vectors;
	std::vector<glm::vec3*> vecColors;
	std::vector<glm::mat4*> matrices;
	glm::vec3 result;
	glm::mat4 matrixResult;
};






class Calculator {
public:

	std::vector<char> vectorsSelected;
	std::vector<char> matricesSelected;


	Calculator(std::vector<glm::vec3>* userPoints, std::vector<glm::vec3>* userColors, std::vector<glm::mat4>* userMatrices, GridRenderer& grid):
	m_userPoints {userPoints}, equalPending {false}, addMode{ false }, m_userColors {userColors}, m_userMatrices {userMatrices}, gridToTraslate {grid}
	{
		std::cout << "Calculator made\n";
	}


	void appendToCurrent(glm::vec3& userPoint, glm::vec3& userColor) {
		currentCalculation.vectors.push_back(&userPoint);
		currentCalculation.vecColors.push_back(&userColor);
	}

	void appendMatToCurrent(glm::mat4& userMatrix) {
		currentCalculation.matrices.push_back(&userMatrix);
	}




	void appendVecSelected() {
		vectorsSelected.push_back(false);
	}

	void appendedMatSelected() {
		matricesSelected.push_back(false);
	}


	void setAddMode() {
		clearCurrent();
		currentCalculation.op = ADD;
		addMode = true;
		equalPending = true;
	}

	void setAddModeOff() {
		addMode = false;
		equalPending = false;
		resetSelectedBool();
	}

	bool getAddMode() {
		return addMode;
	}

	void calcCurrent() {	
		if (currentCalculation.op == ADD) {
			assert(currentCalculation.vectors.size() > 1);
			glm::vec3 result = glm::vec3(0.0f);
			for (size_t i = 0; i < currentCalculation.vectors.size(); ++i) {
				result += *currentCalculation.vectors[i];
			}
			currentCalculation.result = result;
			calculationList.push_back(currentCalculation);
			equalPending = false;

		}
		else if (currentCalculation.op == MULTIPLY) {
			glm::mat4 result = glm::mat4(1.0f);
			for (size_t i = 0; i < currentCalculation.matrices.size(); ++i) {
				result *= *currentCalculation.matrices[i];
			}
			currentCalculation.matrixResult = result;
			calculationList.push_back(currentCalculation);
			equalPending = false;
			gridToTraslate.transform(result);
		}
	}

	void reCalculate() {
		if (calculationList.empty()) {
			std::cout << "Empty calculation list\n";
			return;
		}

		for (size_t n = 0; n < calculationList.size(); ++n) {
			if (calculationList[n].op == ADD) {
				glm::vec3 result = glm::vec3(0.0f);
				for (size_t i = 0; i < calculationList[n].vectors.size(); ++i) {
					result += *calculationList[n].vectors[i];
					std::cout << "curr x:" << calculationList[n].vectors[i]->x << '\n';
				}
				calculationList[n].result = result;
				equalPending = false;
			}
		}
		
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


	//MAT MULTIPLICATION
	void setMultiplyMode() {
		clearCurrent();
		currentCalculation.op = MULTIPLY;
		multiplyMode = true;
		equalPending = true;
	}

	void setMultipleModeOff() {
		multiplyMode = false;
		equalPending = false;
		resetSelectedBool();
	}

	bool getMultiplyMode() {
		return multiplyMode;
	}


	void clearCalculationList() {
		calculationList.clear();
	}

	Calculation& getCurrCalculation() {
		return currentCalculation;
	}

private:
	std::vector<Calculation> calculationList;
	bool equalPending;
	bool addMode;
	bool multiplyMode;
	Calculation currentCalculation;
	std::vector<glm::vec3>* m_userPoints;
	std::vector<glm::vec3>* m_userColors;
	std::vector<glm::mat4>* m_userMatrices;
	GridRenderer& gridToTraslate;

	void resetSelectedBool() {
		for (size_t i = 0; i < vectorsSelected.size(); ++i) {
			vectorsSelected[i] = false;
		}
	}

	void clearCurrent() {
		std::cout << "current";
		currentCalculation.result = glm::vec3(0.0f, 0.0f, 0.0f);
		currentCalculation.vectors.clear();
		currentCalculation.vecColors.clear();
		currentCalculation.op = NOOP;
		equalPending = false;
		addMode = false;
	}
	
};
#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"

class GridRenderer {
public:
	GridRenderer(int slices, float edge)
		: m_edge{ edge }, m_slices{ slices } {
		generateGrid(slices, edge);
		setupBuffers();
	};

	~GridRenderer() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &colorVBO);
	}; //destructor cleans up VAO/VBO

	void draw(const Shader& shader) {
		glLineWidth(1.0f);
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, gridLines.size());
	};

	void enableXZ(bool enable) {
		m_xzEnabled = enable;
		generateGrid(m_slices, m_edge);
		updateBuffers();
	};
	void enableYZ(bool enable) {
		m_yzEnabled = enable;
		generateGrid(m_slices, m_edge);
		updateBuffers();
	};



private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int colorVBO;

	size_t numLines;


	float m_edge;
	int m_slices;

	float m_xzEnabled = false;
	float m_yzEnabled = false;

	std::vector<glm::vec3> gridLines;
	std::vector<glm::vec3> gridColors;


	void generateGrid(int slices, float edge) {
		gridLines.clear();
		gridColors.clear();

		float pos = -edge;
		for (int i = 0; i <= slices; ++i) {
			float x = pos;

			//(XY PLANE)
			//vertical lines
			gridLines.push_back(glm::vec3(x, edge, 0.0f)); //top point
			gridLines.push_back(glm::vec3(x, -edge, 0.0f)); //bottom point

			//horizontal lines
			gridLines.push_back(glm::vec3(-edge, x, 0.0f)); //left point
			gridLines.push_back(glm::vec3(edge, x, 0.0f)); //right point

			//(XZ PLANE)
			gridLines.push_back(glm::vec3(0.0f, 0.0f, edge)); //top point
			gridLines.push_back(glm::vec3(0.0f, 0.0f, -edge)); //bottom point


			if (m_xzEnabled) {
				addXZ();
			}

			if (m_yzEnabled) {
				addYZ();
			}


			pos += 0.1;
		}

		for (size_t i = 0; i < gridLines.size(); ++i) {
			gridColors.push_back(glm::vec3(1.0f, 1.0f, 1.0f)); // white color for all lines
		}

	};



	//adds xz lines to grid lines list
	void addXZ() {
		float pos = -m_edge;
		for (int i = 0; i <= m_slices; ++i) {
			float x = pos;
			//(XZ PLANE)
			//vertical lines
			gridLines.push_back(glm::vec3(x, 0.0f, m_edge)); //top point
			gridLines.push_back(glm::vec3(x, 0.0f, -m_edge)); //bottom point

			//horizontal lines
			gridLines.push_back(glm::vec3(-m_edge, 0.0f, x)); //left point
			gridLines.push_back(glm::vec3(m_edge, 0.0f, x)); //right point

			pos += 0.1;
		}
	};




	//adds yz lines on grid lines list
	void addYZ() {
		float pos = -m_edge;
		for (int i = 0; i <= m_slices; ++i) {
			float x = pos;
			//(YZ PLANE)
			//vertical lines
			gridLines.push_back(glm::vec3(0.0f, m_edge, x)); //top point
			gridLines.push_back(glm::vec3(0.0f, -m_edge, x)); //bottom point

			//horizontal lines
			gridLines.push_back(glm::vec3(0.0f, x, -m_edge)); //left point
			gridLines.push_back(glm::vec3(0.0f, x, m_edge)); //right point

			pos += 0.1;
		}
	}


	void setupBuffers() {
		// a storage for vertices NOTE: this is the ID
		glGenBuffers(1, &VBO); // this creates a n buffers

		// VAO ----- a storage box for our VBO

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);


		// VAO will then rememver the following:
		glBindBuffer(GL_ARRAY_BUFFER, VBO); //give array buffer the id && any calls to GL_ARRAY_BUFFER will change VBO
		// this just copies our vertices to the bound buffer
		glBufferData(GL_ARRAY_BUFFER, gridLines.size() * sizeof(glm::vec3), gridLines.data(), GL_STATIC_DRAW);

		// NOTE:  up to this point OpenGL still doesn't know how to connect our vertices to the vertex shader and how it should interpret data in memory (buffer remember? VB0?)

		//HOW TO INTERPRET DATA:
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Connects VBO and shaders too
		glEnableVertexAttribArray(0);


		glGenBuffers(1, &colorVBO);

		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		glBufferData(GL_ARRAY_BUFFER, gridColors.size() * sizeof(glm::vec3), gridColors.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	};




	void updateBuffers() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO); //give array buffer the id && any calls to GL_ARRAY_BUFFER will change VBO
		// this just copies our vertices to the bound buffer
		glBufferData(GL_ARRAY_BUFFER, gridLines.size() * sizeof(glm::vec3), gridLines.data(), GL_STATIC_DRAW);


		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		glBufferData(GL_ARRAY_BUFFER, gridColors.size() * sizeof(glm::vec3), gridColors.data(), GL_STATIC_DRAW);

	}
	
};
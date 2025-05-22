	#include <glad/glad.h>
	#include <GLFW/glfw3.h>
	#include <iostream>

	#include <glm/glm.hpp>
	#include <glm/gtc/matrix_transform.hpp>
	#include <glm/gtc/type_ptr.hpp>
	#include <vector>


	#include "shader.h"

	//open gl calls this function when we resize window
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow* window);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);


	const int screenWidth = 800;
	const int screenHeight = 600;
	const int slices = 20;

	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.3f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); //to be added with cameraPos so that the camera looks at a new point when moved
	glm::vec3 worldUp = glm::vec3(0.0f, 0.1f, 0.0f);

	float dt = 0.0f;
	float lastFrame = 0.0f;

	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX = 400, lastY = 300;

	bool firstMouse = true;

	//##############================ MAIN ===================###################
	int main() {
		glfwInit();
		//this just says that we need at least OPENGL VERSION 3 or glfw will fail
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		//subset of opengl to emit features we don't need
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//we are going to create a windowwwwww
		GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
		if (window == NULL) {
			std::cout << "Failed to create GLFW window \n";
			glfwTerminate();
			return -1;
		}

		// use our newly created window as our art desk
		glfwMakeContextCurrent(window);

		//tools to drawwwww
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		//let open gl know the dimension of window so it can determine coordinates relative to the window
		glViewport(0, 0, screenWidth, screenHeight); //firs two is lower left, last two is upper right


		//let glfw know about the call back function
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(window, mouse_callback);

		glEnable(GL_DEPTH_TEST);

		//--------------------------- BUFFERS ---------------------------------------------//


		//COORDINATE PLANE
	

	
		std::vector<glm::vec3> gridLines;
		float aspect = 1;
		float pos = -1.0f;
		float adder = 0.1f;
		float edge = 0.5;
		

		for (int i = 0; i <= slices; ++i) {
			float x = pos;
	
			//(XY PLANE)
			//vertical lines
			gridLines.push_back(glm::vec3(x, 1.0f, 0.0f)); //top point
			gridLines.push_back(glm::vec3(x, -1.0f, 0.0f)); //bottom point
			//horizontal lines
			gridLines.push_back(glm::vec3(-1.0f, x, 0.0f)); //left point
			gridLines.push_back(glm::vec3(1.0f,  x, 0.0f)); //right point

			//(XZ PLANE)
			//vertical lines
			gridLines.push_back(glm::vec3(x, 0.0f, 1.0f)); //top point
			gridLines.push_back(glm::vec3(x, 0.0f, -1.0f)); //bottom point
			//horizontal lines
			gridLines.push_back(glm::vec3(-1.0f, 0.0f, x )); //left point
			gridLines.push_back(glm::vec3(1.0f, 0.0f, x )); //right point


			//(YZ PLANE)
			//vertical lines
			gridLines.push_back(glm::vec3(0.0f, 1.0f, x)); //top point
			gridLines.push_back(glm::vec3(0.0f, -1.0f, x)); //bottom point
			//horizontal lines
			gridLines.push_back(glm::vec3(0.0f, x , -1.0f)); //left point
			gridLines.push_back(glm::vec3(0.0f, x , 1.0f)); //right point

			pos += adder;
		}


	
	


		unsigned int VBO; // a storage for vertices NOTE: this is the ID
		glGenBuffers(1, &VBO); // this creates a n buffers

		// VAO ----- a storage box for our VBO
		unsigned int VAO;
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


		//---------------------------------------------------------------------------------
		Shader ourShader("shader.vs", "shader.fs");


		//++++++++++++++ MODEL MATRIX (local -> world space) +++++++++++++++++++++
		//identity matrix
		//model matrix
		//view matrix

		//projection matrix

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		//USING OUR SHADER CLASS
		//========================= RENDER LOOP ===================================
		while (!glfwWindowShouldClose(window))
		{
			float currFrame = glfwGetTime();
			dt = currFrame - lastFrame;
			lastFrame = currFrame;
			processInput(window); //check for input


			//rendering commands go here
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // opengl will wipe the art desk (window) with this color
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			ourShader.use(); //ACTIVATE THE PROGRAM == rendering object (use the shaders)

			
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 projection = glm::mat4(1.0f);
			
			

			//CAMERA / VIEW
			view = glm::lookAt(cameraPos, cameraPos + cameraFront, worldUp);
			projection = glm::perspective(glm::radians(60.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

			ourShader.setMat4("model", model);
			ourShader.setMat4("view", view);
			ourShader.setMat4("projection", projection);

			glBindVertexArray(VAO);
			glDrawArrays(GL_LINES, 0, gridLines.size());

			glfwSwapBuffers(window); //two buffers, front and back. Back draws and get shown if and only if drawing is ready
			glfwPollEvents(); /// check for keyboard input or mouse movement
		}


		glfwTerminate();
		return 0;
	}




	//CALLBACKS
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}


	//INPUTS
	void processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		float movementSpeed = 0.5f * dt;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			cameraPos += movementSpeed * cameraFront; //scale the z axis by movementspeed
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			cameraPos -= movementSpeed * cameraFront;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			//we need to get the right vector
		
			cameraPos -= glm::normalize(glm::cross(cameraFront, worldUp)) * movementSpeed;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			cameraPos += glm::normalize(glm::cross(cameraFront, worldUp)) * movementSpeed;
		}
	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float dx = xpos - lastX;
		float dy = lastY - ypos; // this will be added to pitch

		lastX = xpos;
		lastY = ypos;

		const float sensitivity = 0.1f;


		yaw += dx * sensitivity;
		pitch += dy * sensitivity;

		if (pitch > 89.0f) {
			pitch = 89.0f;
		}

		if (pitch < -89.0f) {
			pitch = -89.0f;
		}

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch)); //we want to start at x = 0. since yaw if initailized to -90 cos(90) would be 0 
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch)); // since x = 0, as the mouse move along the x-axis, we want the z-coord to move along the sin curve

		cameraFront = glm::normalize(direction);

	}
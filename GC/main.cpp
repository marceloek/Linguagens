/**
 * Basic usege of OpenGL and GLFW. 
 */

#include <iostream>
#include <GLFW/glfw3.h>

#define WIDTH 500
#define HEIGHT 500

float x1 = -0.9;

float x2 = 0.9;

float sentido = 1;


int main() {
	GLFWwindow* window;
	int width, height;

	if (!glfwInit()) {
		std::cout << "Problem to initialize GLFW" << std::endl;
		exit(1);
	}
	
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello world, GLFW!", NULL, NULL);

	if (!window) {
		std::cout << "Problem to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);

	while(glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) == 0) {
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		if(x1+0.2 >= 0.9){
			sentido= -1;
			x1 = 0.7;
			x2 = -0.9;
		}
		if(x1 <= -0.9){
			sentido= 1;
			x1 = -0.9;
			x2 = 0.7;
		}

		x1 = x1 + 0.015*sentido;
		x2 = x2 - 0.015*sentido;

		glBegin(GL_LINES);
			glColor3f(1.f, 0.f, 0.f);

			glVertex3f(x2, -0.3f, 0.f);
			glVertex3f(x2+0.2, -0.3f, 0.f);

			glVertex3f(x2, -0.1f, 0.f);
			glVertex3f(x2+0.2, -0.1f, 0.f);

			glVertex3f(x2, -0.3f, 0.f);
			glVertex3f(x2, -0.1f, 0.f);

			glVertex3f(x2+0.2, -0.3f, 0.f);
			glVertex3f(x2+0.2, -0.1f, 0.f);


			glColor3f(0.f, 1.f, 0.f);

			glVertex3f(x1, 0.3f, 0.f);
			glVertex3f(x1+0.2, 0.3f, 0.f);

			glVertex3f(x1, 0.1f, 0.f);
			glVertex3f(x1+0.2, 0.1f, 0.f);

			glVertex3f(x1, 0.1f, 0.f);
			glVertex3f(x1, 0.3f, 0.f);

			glVertex3f(x1+0.2, 0.1f, 0.f);
			glVertex3f(x1+0.2, 0.3f, 0.f);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

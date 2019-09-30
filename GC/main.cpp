/**
 * Basic usege of OpenGL and GLFW. 
 */

#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#define WIDTH 500
#define HEIGHT 500

float x1 = -0.99;

float x2 = 0.1;

float sentido = 1;

GLfloat rx = 0;

int main()
{
	GLFWwindow *window;
	int width, height;

	if (!glfwInit())
	{
		std::cout << "Problem to initialize GLFW" << std::endl;
		exit(1);
	}

	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello world, GLFW!", NULL, NULL);

	if (!window)
	{
		std::cout << "Problem to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);

	while (glfwWindowShouldClose(window) == 0 && glfwGetKey(window, GLFW_KEY_ESCAPE) == 0)
	{
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		// if (x1 + 0.6 >= 0.99)
		// {
		// 	sentido = -1;
		// 	//x1 = 1;
		// }
		// if (x1 <= -0.9)
		// {
		// 	sentido = 1;
		// 	//x1 = -1;
		// }
		// x1 = x1 + 0.0002 * sentido;


		glBegin(GL_LINES);
		// green
		glColor3f(0.0f, 1.0f, 0.0f);

		// linha vertical
		glVertex3f(x1, -0.1f, 0.f);
		glVertex3f(x1, 0.3f, 0.f);

		// linha horizontal
		glVertex3f(x1, 0.3f, 0.f);
		glVertex3f(x1 + 0.4, 0.3f, 0.f);

		// linha horizontal
		glVertex3f(x1, -0.1f, 0.f);
		glVertex3f(x1 + 0.4, -0.1f, 0.f);

		// linha vertical
		glVertex3f(x1 + 0.4, -0.1f, 0.f);
		glVertex3f(x1 + 0.4, 0.3f, 0.f);


		glScalef(4, 4, 4);

		// red
		glColor3f(1.0f, 0.0f, 0.0f);

		// // linha vertical
		glVertex3f(x1 + 0.6, 0.1f, 0.f);
		glVertex3f(x1 + 0.6, 0.5f, 0.f);

		// // linha vertical
		glVertex3f(x1 + 0.2, 0.5f, 0.f);
		glVertex3f(x1 + 0.2, 0.1f, 0.f);

		// // linha horizontal
		glVertex3f(x1 + 0.6, 0.1f, 0.f);
		glVertex3f(x1 + 0.2, 0.1f, 0.f);

		// // linha horizontal
		glVertex3f(x1 + 0.6, 0.5f, 0.f);
		glVertex3f(x1 + 0.2, 0.5f, 0.f);

		// // blue
		glColor3f(0.0f, 0.0f, 1.0f);

		// // linha diagonal
		glVertex3f(x1 + 0.6, 0.1f, 0.f);
		glVertex3f(x1 + 0.4, -0.1f, 0.f);

		// // linha diagonal
		glVertex3f(x1 + 0.6, 0.5f, 0.f);
		glVertex3f(x1 + 0.4, 0.3f, 0.f);

		// // linha diagonal
		glVertex3f(x1 + 0.2, 0.1f, 0.f);
		glVertex3f(x1, -0.1f, 0.f);

		// // linha diagonal
		glVertex3f(x1 + 0.2, 0.5f, 0.f);
		glVertex3f(x1, 0.3f, 0.f);

		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

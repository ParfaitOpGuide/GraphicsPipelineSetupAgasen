#include <GLFW/glfw3.h>
#include <cmath>
#define PI 3.14

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(690, 690, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_POLYGON);
		glVertex2f(cos((2 * (PI)) / 5), (sin((2 * (PI)) / 5)));
		glVertex2f(cos((4 * (PI)) / 5), (sin((4 * (PI)) / 5)));
		glVertex2f(cos((6 * (PI)) / 5), (sin((6 * (PI)) / 5)));
		glVertex2f(cos((8 * (PI)) / 5), (sin((8 * (PI)) / 5)));
		glVertex2f(cos((10 * (PI)) / 5), (sin((10 * (PI)) / 5)));
		glEnd();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
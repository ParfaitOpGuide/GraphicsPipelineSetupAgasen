#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

//GLM HEADERS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define PI 3.14

//Modifier for the model's x
float x_mod = 0;
//Modifier for the model's y
float y_mod = 0;
//Modifier for the model's z
float z_mod = -2;
//Modifier for the model's SCALE (qe)
float scale_mod = 0;
//Modifier for the model's ROTATION <>
float theta_mod = 90;
//Modifier for the camera fov
float fov_mod = 60;

void Key_Callback(GLFWwindow* window, //pointer to window
	int key, //keycode of press
	int scancode, //physical position of the press
	int action,//either press/release
	int mods) //modifier keys
{
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_D:
			x_mod += .1f;
			break;
		case GLFW_KEY_A:
			x_mod -= .1f;
			break;
		case GLFW_KEY_W:
			y_mod += .1f;
			break;
		case GLFW_KEY_S:
			y_mod -= .1f;
			break;
		case GLFW_KEY_SPACE:
			x_mod = 0.0f;
			y_mod = 0.0f;
		}
	}
}

int main(void)
{
	GLFWwindow* window;


	/* Initialize the library */
	if (!glfwInit())
		return -1;

	float width = 600.0f, height = 600.0f;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//IDENTITY MATRIXES
	glm::mat3 identity_matrix3 = glm::mat3(1.0f);
	glm::mat4 identity_matrix4 = glm::mat4(1.0f);

	//Load shader file into a strin steam
	std::fstream vertSrc("Shaders/sample.vert");
	std::stringstream vertBuff;

	vertBuff << vertSrc.rdbuf();

	std::string vertS = vertBuff.str();
	const char* v = vertS.c_str();

	//same but for frag
	std::fstream fragSrc("Shaders/sample.frag");
	std::stringstream fragBuff;

	fragBuff << fragSrc.rdbuf();

	std::string fragS = fragBuff.str();
	const char* f = fragS.c_str();

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	gladLoadGL();

	//glViewport(0, 0, 1200, 600); min x min y total width total height for rendering. doesnt resize the window but squeezes down where it can be rendered

	//set the callback function to the window
	glfwSetKeyCallback(window, Key_Callback);

	//create vertex shader 
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Assign source to vertex shader
	glShaderSource(vertexShader, 1, &v, NULL);
	glCompileShader(vertexShader);

	//create frag shader 
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Assign source to frag shader
	glShaderSource(fragShader, 1, &f, NULL);
	glCompileShader(fragShader);

	//create shader progrram
	GLuint shaderProg = glCreateProgram();
	//attach both
	glAttachShader(shaderProg, vertexShader);
	glAttachShader(shaderProg, fragShader);

	//finalize compilation
	glLinkProgram(shaderProg);



	std::string path = "3D/bunny.obj"; //change to what is needed to be rendered
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> material;
	std::string warning, error;

	tinyobj::attrib_t attributes;

	bool success = tinyobj::LoadObj(
		&attributes,
		&shapes,
		&material,
		&warning,
		&error,
		path.c_str()
	);

	std::vector<GLuint> mesh_indices;
	for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
		mesh_indices.push_back(
			shapes[0].mesh.indices[i].vertex_index
		);
	}

	GLfloat vertices[]{
		//x y z
		0.f, 0.5f, 0.f, //0
		-0.5f, -0.5f, 0.f, //1
		0.5f, -0.5f, 0.f //2
	};

	GLuint indices[]{
		0,1,2 //traingle with vertices using points 0 to 1 to 2 from vertices above
	};

	GLuint VAO, VBO, EBO; //openGL unsigned int
	glGenVertexArrays(1, &VAO); //assigns an id to var
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//tell opengl to use the shaderprog for the vaos
	glUseProgram(shaderProg);
	// editing VAO = null=
	glBindVertexArray(VAO);
	// editing VBO = null
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//editing VBO = VBO
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(GL_FLOAT) * attributes.vertices.size(), //bytes
		attributes.vertices.data(), //array
		GL_STATIC_DRAW);

	//interpret points not given indices
	glVertexAttribPointer(
		0, //index
		3, //3 because xyz
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),//size in bytes, matching xyz
		(void*)0
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, //edit
		sizeof(GLuint) * mesh_indices.size(),
		mesh_indices.data(),
		GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); //id given to pointer index


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	float x, y, z;
	x = y = z = 0;


	float scale_x, scale_y, scale_z = 1.f;
		scale_x = scale_y = scale_z = 1.f;


	float axis_x, axis_y, axis_z, theta = 0.f;
	axis_x = axis_y = axis_z = theta = 0.f;

	axis_y = 1;

	/*	glm::mat4 projectionMatrix = glm::ortho(
			-2.f, //Left
			2.f,//Right
			-2.f,//Bot
			2.f,//Top
			-1.f,//Near
			1.f //Far
		);*/



	glm::mat4 projectionMatrix = glm::perspective(
		glm::radians(60.f), //FOV
		height / width, //aspect ratio
		0.1f, //ZNear > 0
		100.f
	);

	z = -2.f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		x = x_mod;
		z = z_mod;
		theta = theta_mod;

		//start with the translation matrix
		glm::mat4 transformation_matrix = glm::translate(identity_matrix4, glm::vec3(x, y, z));

		//scale
		transformation_matrix = glm::scale(transformation_matrix, glm::vec3(scale_x, scale_y, scale_z));

		//rotate
		transformation_matrix = glm::rotate(transformation_matrix, glm::radians(theta), glm::normalize(glm::vec3(axis_x, axis_y, axis_z)));

		unsigned int projectionLoc = glGetUniformLocation(shaderProg, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		//grab shader transform variable
		unsigned int transformLoc = glGetUniformLocation(shaderProg, "transform");
		//assign to matrix
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix));


		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3); type (POLYGONS etc), index, point number || this is for drawing given no indices
		glDrawElements(GL_TRIANGLES, mesh_indices.size(), GL_UNSIGNED_INT, 0);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}
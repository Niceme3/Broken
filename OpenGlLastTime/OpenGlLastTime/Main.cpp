#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <GL/gl3w.h>
#include <GL/gl3w.c>
#include <GL\glcorearb.h>
#include <KHR/khrplatform.h>
#include <iostream>
#include <LoadShaders.h>
using namespace std;
/// These are almost like tables, VAos store the Triangles, and the amount
///We will later on Bind The VAO's And Buffer
/////
enum VAO_IDs { Trianagles, NumVaos };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };  // unknown

GLuint VAOs[NumVaos]; // Now, we can indivdually accces the inside of the tables
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6; // The number of vertices in total is 6

// init
void init(void)
{ // creates all of the vertices, the [2] is to show the amount
	static const GLfloat vertices[NumVertices][2] =
	{
		{-0.90, -0.90},
		{0.85, -0.90},
		{-0.9, 0.85},
		{0.9, -0.85},
		{0.9, 0.9},
		{-0.85, 0.9},

	};
	// Both of the buffers come from line 12 and 13, from the enum
	glCreateBuffers(NumBuffers, Buffers);
	// Allocates size stirage in byets, resort to page 21
	glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices), vertices, 0);
	//Creates the shader for vertex and fragment (position, and colors)
	ShaderInfo  shaders[] =
	{
		{GL_VERTEX_SHADER, "triangles.vert"},
		{GL_FRAGMENT_SHADER, "triangles.frag"},
		{GL_NONE, NULL}
	};
	// Program is just a way to load the shaders up
	GLuint program = LoadShaders(shaders);
	// We set up the loading of shaders
	glUseProgram(program);

	// Links the vertex aarys to a buffer object
	glGenVertexArrays(NumVaos, VAOs);
	glBindVertexArray(VAOs[Trianagles]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(vPosition);


}
// display

void display(void)
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, black);
	glBindVertexArray(VAOs[Trianagles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);


}

// main

int main(int argc, char ** argv)
{
	glfwInit();


	GLFWwindow* window = glfwCreateWindow(640, 480, "Triangles", NULL, NULL);

	glfwMakeContextCurrent(window);
	gl3wInit();

	init();
	while (!glfwWindowShouldClose(window))
	{
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();


	}
	glfwDestroyWindow(window);
	glfwTerminate();
}
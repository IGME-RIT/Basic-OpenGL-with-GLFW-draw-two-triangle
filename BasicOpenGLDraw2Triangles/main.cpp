#include <iostream>
#include <vector>
// We are using the glew32s.lib
// Thus we have a define statement
// If we do not want to use the static library, we can include glew32.lib in the project properties
// If we do use the non static glew32.lib, we need to include the glew32.dll in the solution folder
// The glew32.dll can be found here $(SolutionDir)\..\External Libraries\GLEW\bin\Release\Win32
#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>


//Now we want to draw multiple entities
//Each entity will need a set of vertices, 
//a vertex buffer object(VBO),
//a vertex array object(VAO)
//We use a struct as it simplifies the example.

struct shape {
	std::vector<GLfloat> vertices; //Here we use a vector (similar to C# lists) instead of an arry to store our vertices as it is more flexible.
	GLuint VAO;
	GLuint VBO;
};

// Variables for the Height and width of the window
const GLint WIDTH = 800, HEIGHT = 800;



int main()
{
	//Initializes the glfw
	glfwInit();

	// Setting the required options for GLFW

	// Setting the OpenGL version, in this case 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Setting the Profile for the OpenGL.
	// Option of choosing between Compat and Core.
	// We choose core, because we won't be using any deprecated function from the previous versions of OpenGL
	// In other words, no backward compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Setting the forward compatibility of the application to true
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// We don't want the window to resize as of now.
	// Therefore we will set the resizeable window hint to false.
	// To make is resizeable change the value to GL_TRUE.
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create the window object
	// The first and second parameters passed in are WIDTH and HEIGHT of the window we want to create
	// The third parameter is the title of the window we want to create

	// NOTE: Fourth paramter is called monitor of type GLFWmonitor, used for the fullscreen mode.
	//		 Fifth paramter is called share of type GLFWwindow, here we can use the context of another window to create this window
	// Since we won't be using any of these two features for the current tutorial we will pass nullptr in those fields
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Shaders Tutorial", nullptr, nullptr);

	// We call the function glfwGetFramebufferSize to query the actual size of the window and store it in the variables.
	// This is useful for the high density screens and getting the window size when the window has resized.
	// Therefore we will be using these variables when creating the viewport for the window
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	// Check if the window creation was successful by checking if the window object is a null pointer or not
	if (window == nullptr)
	{
		// If the window returns a null pointer, meaning the window creation was not successful
		// we print out the messsage and terminate the glfw using glfwTerminate()
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		// Since the application was not able to create a window we exit the program returning EXIT_FAILURE
		return EXIT_FAILURE;
	}

	// Creating a window does not make it the current context in the windows.
	// As a results if the window is not made the current context we wouldn't be able the perform the operations we want on it
	// So we make the created window to current context using the function glfwMakeContextCurrent() and passing in the Window object
	glfwMakeContextCurrent(window);

	// Enable GLEW, setting glewExperimental to true.
	// This allows GLEW take the modern approach to retrive function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup OpenGL function pointers
	if (GLEW_OK != glewInit())
	{
		// If the initalization is not successful, print out the message and exit the program with return value EXIT_FAILURE
		std::cout << "Failed to initialize GLEW" << std::endl;

		return EXIT_FAILURE;
	}

	// Setting up the viewport
	// First the parameters are used to set the top left coordinates
	// The next two parameters specify the height and the width of the viewport.
	// We use the variables screenWidth and screenHeight, in which we stored the value of width and height of the window,
	glViewport(0, 0, screenWidth, screenHeight);

	//Initalizing the first entity - a simple triangle from the last example
	shape triangle;
	triangle.vertices = {
		// POSITION				
		-1.0f, -0.5f, 0.0f,
		0.0f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
	};

	//These steps are pretty standard for 
	//rendering objects as described in the last example
	glGenVertexArrays(1, &triangle.VAO);																					//Generating VAO
	glGenBuffers(1, &triangle.VBO);																							//Generating VBO
	glBindVertexArray(triangle.VAO);																						//Binding the VAO so we can manipulate it
	glBindBuffer(GL_ARRAY_BUFFER, triangle.VBO);																		    //Binding the VBO so we can manipulate it

	//Since we are using a vector to store our vertices, some of the parameters have to be changed
	glBufferData(GL_ARRAY_BUFFER, 
		sizeof(GLfloat)*triangle.vertices.size(), //The data size is the size of one GLfloat multiplied by the number of vertices
		&triangle.vertices[0],					  //We want to start at the first index of the vector, so we point to it
		GL_STATIC_DRAW);	

	//Defining our vertex data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0); //No need to make changes here as our data type (GLfloat) is the same. In later examples we will be changing it.

	//Unbinding both our OpenGL objects
	glBindBuffer(0, triangle.VBO);
	glBindVertexArray(0);


	//Initalizing the second entity, a simple square
	//This is done by drawing 2 sets of triangles
	shape square;

	//As you can see we repeat vertices 
	//In future examples, index buffers will be introduced
	//Index buffers make sure we don't load repeated vertices
	square.vertices = {
		// Triangle 1		
		0.0f, -0.5f, 0.0f,
		1.0f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		//Triangle 2
		0.0f, 0.5f, 0.0f,
		1.0f, -0.5f, 0.0f,
		1.0f, 0.5f, 0.0f
	};

	//Same as the above code
	glGenVertexArrays(1, &square.VAO);
	glGenBuffers(1, &square.VBO);
	glBindVertexArray(square.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, square.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*square.vertices.size(), &square.vertices[0], GL_STATIC_DRAW);;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(0, square.VBO);
	glBindVertexArray(0);

	
	// This is the game loop, the game logic and render part goes in here.
	// It checks if the created window is still open, and keeps performing the specified operations until the window is closed
	while (!glfwWindowShouldClose(window))
	{
		// Checking for events/inputs
		glfwPollEvents();

		// Specifies the RGBA values which will be used by glClear to clear the color buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		// Clears contents of a screen to a preset value, previously selected, by passing in what buffer we want to clear
		// In this case we are clearing the color buffer. Thus setting a background color to the color specified previously in glClearColor
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw OpenGL stuff

		//Drawing our triangle by binding it's VAO
		glBindVertexArray(triangle.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 vertices in the triangle
		glBindVertexArray(0);	//Unbind after we're finished drawing this entity.

		//Drawing our square by binding it's VAO
		glBindVertexArray(square.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6); // 6 vertices in triangle (2 sets of 3)
		glBindVertexArray(0); //Unbind after we're finished drawing this entity.

		// Swaps the front and back buffers of the specified window
		glfwSwapBuffers(window);
	}

	// Delete the vertex array object, passing in the number of the vertex arrays objects stored in the the array (VAO)
	glDeleteVertexArrays(1, &triangle.VAO);
	glDeleteVertexArrays(1, &square.VAO);

	// Delete the number of buffer objects passed in the array buffer.
	glDeleteBuffers(1, &triangle.VBO);
	glDeleteBuffers(1, &square.VBO);
	// Terminate all the stuff related to GLFW and exit the program using the return value EXIT_SUCCESS
	glfwTerminate();

	return EXIT_SUCCESS;
}
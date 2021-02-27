#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

const unsigned int window_width = 800;
const unsigned int window_height = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

int main () {

	// Instantiate the GLFW window
	glfwInit();
	// Version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// This window object holds all the windowing data and is required by most of GLFW's other functions.
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLAD before we call any OpenGL function.
	// We pass GLAD the function to load the address of the OpenGL function pointers
	// which is OS-specific. GLFW gives us glfwGetProcAddress that defines the correct function 
	// based on which OS we're compiling for.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/* Before we can start rendering we have to do one last thing. We have to tell OpenGL
	   the size of the rendering window so OpenGL knows how we want to display the data and coordinates
	   with respect to the window. We can set those dimensions via the glViewport funtion.

	   The first two parameters of glViewport set the location of the lower left corner of the window.
	   The third and fourth parameter set the width and height of the rendering window in pictures,
	   which we set equal to GLFW's window size.

	   We could actually set the viewport dimensions at values smaller than GLFW's dimensions;
	   then all the OpenGL rendering would be displayed in a smaller window and we could for example display other elements
	   outside the OpenGL viewport.

	   Behind the scenes OpenGl oses the data specified via glViewport to transform the 2D coordinates it processed
	   to coordinates on your screen. For example, a processed point of location (-0.5, 0.5) would, as its final transformation,
	   be mapped to (200, 450) in screen coordinates. Note that processed coordinates in OpenGL are between -1 and 1 
	   so we effectively map from the range (-1 to 1) to (0, 800) and (0, 600).
	*/
	glViewport(0, 0, window_width, window_height);

	/* However, the moment a user resizes the window the viewport should be adjusted as well.We can register a callback function
	   on the window that gets called each time the window is resized.

	   We do have to tell GLFW we want to call this function on every window resize by registering it:
	*/
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	/*
	  Loop
	*/
	while (!glfwWindowShouldClose(window)) {

		// input
		process_input(window);

		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		// glfwPollEvents checks if any events are triggered, like keyboard or mouse movement events.
		// It also updates the window state, and calls the corresponding functions (which we can register
		// via callback methods.
		glfwPollEvents();
	}

	// Clean/delete all of GLFW's resources that were allocated.
	glfwTerminate();
	return 0;
}

void process_input(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
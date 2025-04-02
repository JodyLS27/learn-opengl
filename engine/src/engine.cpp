#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>

#include "engine.hpp"

// TODO: Create a Second Fragment, Yellow
#pragma region Shaders
// Temp Data for testing
const char* vertex_shader_source = "#version 330 core\n"
"layout(location = 0) in vec3 aPos; \n"
"layout(location = 1) in vec3 aColour; \n"
"out vec3 myColour; \n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"	myColour = aColour; \n"
"}\0";

const char* fragment_shader_source = "#version 330 core\n"
"in vec3 myColour;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(myColour, 1.0); \n"
"}\n";

#pragma endregion Shaders

void engine::Engine::init()
{
}

int engine::Engine::start()
{
	// -- Windowing --
	m_engine_window.init();

	m_window = m_engine_window.getGLFWwindow();

	if (!m_window)
	{
		return -1;
	}


#pragma region Shading
	// Checking if shader comiliation was successful
	int success{};
	char info_log[512];


	// --- Vertex Shader ---
	unsigned int vertex_shader{};
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
	glCompileShader(vertex_shader);

	//Vertex Compiliation success
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILE FAILED\n" << info_log << "\n\n";
	}

	// --- Fragment Shader ---
	unsigned int fragment_shader_s{};
	fragment_shader_s = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment_shader_s, 1, &fragment_shader_source, nullptr);
	glCompileShader(fragment_shader_s);

	// Fragment Compilation success
	glGetShaderiv(fragment_shader_s, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragment_shader_s, 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILED FAILED\n" << info_log << "\n\n";
	}

	// --- Shader Program ---	
	unsigned int shader_program[1];
	shader_program[0] = glCreateProgram();


	glAttachShader(shader_program[0], vertex_shader);
	glAttachShader(shader_program[0], fragment_shader_s);

	glLinkProgram(shader_program[0]);

	glGetProgramiv(shader_program[0], GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shader_program[0], 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILE FAILED\n" << info_log << "\n\n";
	}

	// Cleanup Unneeded Shaders
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader_s);

#pragma endregion Shading

#pragma region Verticies and Indices
	// --- Vertex Data ---
	float vertices[] =
	{
		// Position				// Colour		
		-0.0f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 	// top
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,	// Left
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f	// Right
	};

	unsigned int indices[] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
#pragma endregion Verticies and Indices

#pragma region Vertex_Array_and_Buffers

	// for the amount of objects to create
	const unsigned int max_objects{ 1 };

	// Setup Vertex Buffer Object
	GLuint VBOs[max_objects];
	GLuint VAOs[max_objects];


	// Generate Buffers
	glGenVertexArrays(max_objects, VAOs);
	glGenBuffers(max_objects, VBOs);

	// Loop over the array
	for (int i = 0; i < max_objects; i++)
	{
		glBindVertexArray(VAOs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);

		// [i * 9] is the amount of data per row : TODO: do Some testing ?
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / max_objects, &vertices[i * 9], GL_STATIC_DRAW);

		// Position data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

	}

#pragma endregion Vertex_Array_and_Buffers


	// Main loop
	// ---------
	while (!glfwWindowShouldClose(m_window))
	{
		// Input handling
		m_engine_window.process_input(m_window);

		// Rendering: Clear the Back Buffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);



		for (int i = 0; i < max_objects; i++)
		{
			// Draw Triangle: On the Back Buffer
			glUseProgram(shader_program[i]);

			glBindVertexArray(VAOs[i]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		// Moving to Element Buffer, No longer needed

		// Swap the Front and Back Buffers
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	return 0;
}
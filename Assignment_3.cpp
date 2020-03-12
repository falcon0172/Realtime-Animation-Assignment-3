//-----------------------------------------------------------------------------
// Models_01.cpp by Steve Jones 
// Copyright (c) 2015-2019 Game Institute. All Rights Reserved.
//
// - Creates Mesh class
// - Loads and renders (3) OBJ models
//-----------------------------------------------------------------------------
#include <iostream>
#include <cstdint>
#include <algorithm>

#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#define GLEW_STATIC
#include "GL/glew.h"	// Important - this header must come before glfw3 header
#include "GLFW/glfw3.h"



#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "anttweakbar/AntTweakBar.h"

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Camera.h"
#include "Mesh.h"


// Global Variables
const char* APP_TITLE = "Introduction to Modern OpenGL - Loading OBJ Models";
int gWindowWidth = 1024;
int gWindowHeight = 768;
GLFWwindow* gWindow = NULL;
bool gWireframe = false;


FPSCamera fpsCamera(glm::vec3(0.0f, 3.0f, 10.0f));
const double ZOOM_SENSITIVITY = -3.0;
const float MOVE_SPEED = 5.0; // units per second
const float MOUSE_SENSITIVITY = 0.1f;
float happy_w = 0.0f;
float angry_w = 0.0f;
float neutral = 0.0f;
float angry_l_w;
float angry_r_w;
float happy_l_w;
float happy_r_w;
float suck_l_w;
float suck_r_w;
float suck_vp_w;
float jaw_open_w;
float pos1;
float pos2;
float pos3;
float pos4;
float pos5;
float pos6;
float pos7;
float pos8;
float pos9;
float pos10;
float pos11;
float pos12;
float pos13;
float pos14;
float pos15;
float pos16;

ShaderProgram shaderProgram;


int flag = 0;
int anim_flag = 0;
int j = 0;
glm::vec3 spherePos = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 0.0f);
glm::vec3 lightPos = glm::vec3(0.0f, 1.0f, 10.0f);

// Function prototypes
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height);
void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY);
void update(double elapsedTime);
void showFPS(GLFWwindow* window);
void initialiseexpression();
bool initOpenGL();
void playanimation();

void playanimation()
{
	anim_flag = 1;
	j = 0;
}

inline void TwEventMouseButtonGLFW3(GLFWwindow* window, int button, int action, int mods)
{
	TwEventMouseButtonGLFW(button, action);
}
inline void TwEventMousePosGLFW3(GLFWwindow* window, double xpos, double ypos)
{
	TwMouseMotion(int(xpos), int(ypos));
}
inline void TwEventMouseWheelGLFW3(GLFWwindow* window, double xoffset, double yoffset)
{
	glfw_onMouseScroll(window, xoffset, yoffset);
	TwEventMouseWheelGLFW(yoffset);
}
inline void TwEventKeyGLFW3(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	glfw_onKey(window, key,scancode, action, mods);
	TwEventKeyGLFW(key, action);
}
inline void TwEventCharGLFW3(GLFWwindow* window, int codepoint)
{
	TwEventCharGLFW(codepoint, GLFW_PRESS);
}
inline void TwWindowSizeGLFW3(GLFWwindow* window, int width, int height)
{
	TwWindowSize(width, height);

}



//-----------------------------------------------------------------------------
// Main Application Entry Point
//-----------------------------------------------------------------------------

void initialiseexpression()
{
	happy_w = 0.0f;
	angry_w = 0.0f;
	neutral = 1.0f;
	angry_l_w = 0.0f;
	angry_r_w = 0.0f;
	happy_l_w = 0.0f;
	happy_r_w = 0.0f;
	suck_l_w = 0.0f;
	suck_r_w = 0.0f;
	suck_vp_w = 0.0f;
	jaw_open_w = 0.0f;
	pos1 = 0.0f;
	pos2 = 0.0f;
	pos3 = 0.0f;
	pos4 = 0.0f;
	pos5 = 0.0f;
	pos6 = 0.0f;
	pos7 = 0.0f;
	pos8 = 0.0f;
	pos9 = 0.0f;
	pos10 = 0.0f;
	pos11 = 0.0f;
	pos12 = 0.0f;
	pos13 = 0.0f;
	pos14 = 0.0f;
	pos15 = 0.0f;
	pos16 = 0.0f;


}
void setexpression()
{
	shaderProgram.setUniform("neutral", neutral);
	shaderProgram.setUniform("happy_w", happy_w);
	shaderProgram.setUniform("angry_w", angry_w);
	shaderProgram.setUniform("angry_l_w", angry_l_w);
	shaderProgram.setUniform("angry_r_w", angry_r_w);
	shaderProgram.setUniform("happy_l_w", happy_l_w);
	shaderProgram.setUniform("happy_r_w", happy_r_w);
	shaderProgram.setUniform("suck_l_w", suck_l_w);
	shaderProgram.setUniform("suck_r_w", suck_r_w);
	shaderProgram.setUniform("suck_vp_w", suck_vp_w);
	shaderProgram.setUniform("jaw_open_w", jaw_open_w);

	shaderProgram.setUniform("pos1", pos1);
	shaderProgram.setUniform("pos2", pos2);
	shaderProgram.setUniform("pos3", pos3);
	shaderProgram.setUniform("pos4", pos4);
	shaderProgram.setUniform("pos5", pos5);
	shaderProgram.setUniform("pos6", pos6);
	shaderProgram.setUniform("pos7", pos7);
	shaderProgram.setUniform("pos8", pos8);
	shaderProgram.setUniform("pos9", pos9);
	shaderProgram.setUniform("pos10", pos10);
	shaderProgram.setUniform("pos11", pos11);
	shaderProgram.setUniform("pos12", pos12);
	shaderProgram.setUniform("pos13", pos13);
	shaderProgram.setUniform("pos14", pos14);
	shaderProgram.setUniform("pos15", pos15);
	shaderProgram.setUniform("pos16", pos16);
}


int main()
{
	initialiseexpression();
	if (!initOpenGL())
	{
		// An error occured
		std::cerr << "GLFW initialization failed" << std::endl;
		return -1;
	}


	shaderProgram.loadShaders("shaders/basic.vert", "shaders/basic.frag");

	ShaderProgram manipulator;
	manipulator.loadShaders("shaders/basic_model.vert", "shaders/basic_model.frag");

	


	// Load meshes and textures
	const int numModels = 30;
	Mesh mesh[numModels];
	Texture2D texture;

	mesh[0].loadOBJ("models/neutral.obj");
	mesh[1].loadOBJ("models/sad.obj");
	mesh[2].loadOBJ("models/smile.obj");
	mesh[3].loadOBJ("models/Mery_l_sad.obj");
	mesh[4].loadOBJ("models/Mery_r_sad.obj");
	mesh[5].loadOBJ("models/Mery_l_smile.obj");
	mesh[6].loadOBJ("models/Mery_r_smile.obj");
	mesh[7].loadOBJ("models/Mery_l_suck.obj");
	mesh[8].loadOBJ("models/Mery_r_suck.obj");
	mesh[9].loadOBJ("models/suck.obj");
	mesh[10].loadOBJ("models/Mery_jaw_open.obj");

	mesh[11].loadOBJ("models/pos1.obj");
	mesh[12].loadOBJ("models/pos2.obj");
	mesh[13].loadOBJ("models/pos3.obj");
	mesh[14].loadOBJ("models/pos4.obj");
	mesh[15].loadOBJ("models/pos5.obj");
	mesh[16].loadOBJ("models/pos6.obj");
	mesh[17].loadOBJ("models/pos7.obj");
	mesh[18].loadOBJ("models/pos8.obj");
	mesh[19].loadOBJ("models/pos9.obj");
	mesh[20].loadOBJ("models/pos10.obj");
	mesh[21].loadOBJ("models/pos11.obj");
	mesh[22].loadOBJ("models/pos12.obj");
	mesh[23].loadOBJ("models/pos13.obj");
	mesh[24].loadOBJ("models/pos14.obj");
	mesh[25].loadOBJ("models/pos15.obj");
	mesh[26].loadOBJ("models/pos16.obj");


	texture.loadTexture("textures/grey.png", true);

	// Model positions
	glm::vec3 modelPos = glm::vec3(0.0f, 0.0f, 0.0f);	// floor


	// Model scale
	glm::vec3 modelScale = glm::vec3(0.1f, 0.1f, 0.1f);


	//Mesh sphere;
	//sphere.loadOBJ("models/sphere.obj");

	Texture2D spheretex;
	spheretex.loadTexture("textures/grey.png", true);

//GUI
/*
	TwBar* bar;
	bar = TwNewBar("NameOfMyTweakBar");
	int wire = 0;
	float bgColor[] = { 0.1f, 0.2f, 0.4f };
	TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLFW and OpenGL.' "); // Message added to the help bar.
	// Add 'wire' to 'bar': it is a modifable variable of type TW_TYPE_BOOL32 (32 bits boolean). Its key shortcut is [w].
	TwAddVarRW(bar, "wire", TW_TYPE_BOOL32, &wire,
		" label='Wireframe mode' key=w help='Toggle wireframe display mode.' ");
	// Add 'bgColor' to 'bar': it is a modifable variable of type TW_TYPE_COLOR3F (3 floats color)
	TwAddVarRW(bar, "bgColor", TW_TYPE_COLOR3F, &bgColor, " label='Background color' ");
	TwAddButton(bar, "comment1", NULL, NULL, " label='Life is like a box a chocolates' ");
	glfwSetWindowSizeCallback(gWindow, (GLFWwindowposfun)TwWindowSizeGLFW3);

	glfwSetMouseButtonCallback(gWindow, (GLFWmousebuttonfun)TwEventMouseButtonGLFW3);
	glfwSetCursorPosCallback(gWindow, (GLFWcursorposfun)TwEventMousePosGLFW3);
	glfwSetScrollCallback(gWindow, (GLFWscrollfun)TwEventMouseWheelGLFW3);
	glfwSetKeyCallback(gWindow, (GLFWkeyfun)TwEventKeyGLFW3);
	glfwSetCharCallback(gWindow, (GLFWcharfun)TwEventCharGLFW3);
	*/
	double lastTime = glfwGetTime();
	// Rendering loop
	while (!glfwWindowShouldClose(gWindow))
	{
		showFPS(gWindow);
		  // draw the tweak bar(s)

	
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;

		// Poll for and process events
		glfwPollEvents();
		update(deltaTime);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model(1.0), view(1.0), projection(1.0);

		// Create the View matrix
		view = fpsCamera.getViewMatrix();

		// Create the projection matrix
		projection = glm::perspective(glm::radians(fpsCamera.getFOV()), (float)gWindowWidth / (float)gWindowHeight, 0.1f, 200.0f);

		// Must be called BEFORE setting uniforms because setting uniforms is done
		// on the currently active shader program.
		shaderProgram.use();

		// Pass the matrices to the shader
		
		shaderProgram.setUniform("view", view);
		shaderProgram.setUniform("projection", projection);
		shaderProgram.setUniform("lightColor", lightColor);
		shaderProgram.setUniform("lightPos", lightPos);
		setexpression();
		//spherePos.x = spherePos.x + 1.0f;
		//spherePos.y = spherePos.y + 1.5f;
		j++;
		if(anim_flag == 1)
		{ 
			std::cout << "Animation Begins" << std::endl;
			if (j < 10)
			{
				
				std::cout << "1 Begins" << std::endl; 
				std::cout << j << std::endl;
				pos1 = 1;
			}

			if (j >= 10 && j <= 20)
			{
				pos1 = 0;
				std::cout << "2 Begins" << std::endl;
				pos2 = 1;
			}

			if (j > 20 && j < 30)
			{
				pos2 = 0; 
				std::cout << "3 Begins" << std::endl;
				pos3 = 1;
			}

			if (j> 30 && j< 40)
			{
				pos3 = 0; 
				std::cout << "4 Begins" << std::endl;
				pos4 = 1;
			}

			if (j> 40 && j< 50)
			{
				pos4 = 0;
				std::cout << "5 Begins" << std::endl;
				pos5 = 1;
			}

			if (j> 60 && j< 70)
			{
				pos5 = 0;				
				std::cout << "6 Begins" << std::endl;
				pos6 = 1;
			}

			if (j> 80 && j< 90)
			{
				pos6 = 0;
				std::cout << "7 Begins" << std::endl;
				pos7 = 1;
			}

			if (j> 100 && j< 110)
			{
				pos7 = 0;
				std::cout << "8 Begins" << std::endl;
				pos8 = 1;
			}
			if (j> 120 && j< 130)
			{
				pos8 = 0;	
				std::cout << "9 Begins" << std::endl;
				pos9 = 1;
			}

			if (j> 140 && j< 150)
			{
				pos9 = 0;
				std::cout << "10 Begins" << std::endl;
				pos10 = 1;
			}

			if (j> 150 && j< 160)
			{
				pos10 = 0;
				std::cout << "11 Begins" << std::endl;
				pos11 = 1;
			}

			if (j> 160 && j< 170)
			{
				pos11 = 0;
				std::cout << "12 Begins" << std::endl;
				pos12 = 1;
			}

			if (j> 170 && j< 180)
			{
				pos12 = 0;
				std::cout << "13 Begins" << std::endl;
				pos13 = 1;
			}

			if (j> 180 && j< 190)
			{
				pos13 = 0;
				std::cout << "14 Begins" << std::endl;

				pos14 = 1;
			}

			if (j> 190 && j< 200)
			{
				pos14 = 0;
				std::cout << "15 Begins" << std::endl;
				pos15 = 1;
			}

			if (j> 210 && j< 220)
			{
				std::cout << "16 Begins" << std::endl;

				pos15 = 0;
				pos16 = 1;
			}

			else
			{
				//initialiseexpression();
				std::cout << "end" << std::endl;
				std::cout << j<< std::endl;
				//anim_flag = 0;
			}
		
		}
		

		//std::cout << j <<std::endl;
	
		// Render the scene
		for (int i = 0; i < numModels; i++)
		{
			shaderProgram.setUniform("flag", flag);

			model = glm::translate(glm::mat4(1.0), modelPos) * glm::scale(glm::mat4(1.0), modelScale);
			shaderProgram.setUniform("model", model);

			texture.bind(0);		// set the texture before drawing.  Our simple OBJ mesh loader does not do materials yet.
			mesh[i].draw();			// Render the OBJ mesh
			texture.unbind(0);
		//	std::cout <<"flag:" <<flag << std::endl;
			flag = flag + 1	;
		}
		flag = 0;/*
		manipulator.use();
		manipulator.setUniform("view", view);
		manipulator.setUniform("projection", projection);
		model = glm::translate(model, spherePos);
		manipulator.setUniform("model", model);
		
		spheretex.bind(0);
		sphere.draw();
		spheretex.unbind(0);

		
	
		neutral_w = 1.0 - happy_w - angry_w;
		if (neutral_w < 0.0f) { neutral_w = 0.0f; }
		if(neutral_w > 1.0f) { neutral_w = 1.0f; }
		sum_w = happy_w + angry_w + neutral_w;
		happy_f = happy_w / sum_w;
		angry_f = angry_w / sum_w;
		neutral_f = neutral_w / sum_w;
		std::cout << "Neutral:" << neutral_f << std::endl << "Angry:" << angry_f << std::endl << "Happy:" << happy_f << std::endl << "Sum:" << sum_w << std::endl;
		std::cout << "Neutral_w:" << neutral_w << std::endl;
		shaderProgram.setUniform("neutral_w", neutral_w);
		shaderProgram.setUniform("sum_w", sum_w);
		shaderProgram.setUniform("happy_f", happy_f);
		shaderProgram.setUniform("angry_f", angry_f);
		shaderProgram.setUniform("neutral_f", neutral_f); */


		// Swap front and back buffers
		glfwSwapBuffers(gWindow);
		//TwDraw();
		lastTime = currentTime;


	}
	TwTerminate();
	glfwTerminate();

	

	return 0;
}

//-----------------------------------------------------------------------------
// Initialize GLFW and OpenGL
//-----------------------------------------------------------------------------
bool initOpenGL()
{
	// Intialize GLFW 
	// GLFW is configured.  Must be called before calling any GLFW functions
	if (!glfwInit())
	{
		// An error occured
		std::cerr << "GLFW initialization failed" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
#ifdef __APPLE__ // TODO is it ok to use it on Windows and Linux?
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// forward compatible with newer versions of OpenGL as they become available but not backward compatible (it will not run on devices that do not support OpenGL 3.3
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	//TwInit(TW_OPENGL, NULL);

	// Create an OpenGL 3.3 core, forward compatible context window
	gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
	//TwWindowSize(gWindowWidth, gWindowHeight);

	if (gWindow == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// Make the window's context the current one
	glfwMakeContextCurrent(gWindow);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	// Set the required callback functions
	glfwSetKeyCallback(gWindow, glfw_onKey);
	glfwSetFramebufferSizeCallback(gWindow, glfw_onFramebufferSize);
	glfwSetScrollCallback(gWindow, glfw_onMouseScroll);

	// Hides and grabs cursor, unlimited movement
	glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(gWindow, gWindowWidth / 2.0, gWindowHeight / 2.0);

	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	// Define the viewport dimensions
	glViewport(0, 0, gWindowWidth, gWindowHeight);
	//TwWindowSize(gWindowWidth, gWindowWidth);
	glEnable(GL_DEPTH_TEST);

	return true;
}

//-----------------------------------------------------------------------------
// Is called whenever a key is pressed/released via GLFW
//-----------------------------------------------------------------------------
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		gWireframe = !gWireframe;
		if (gWireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//	glPolygonMode(GL_BACK, GL_FILL);
			glPointSize(5);
		}
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		std::cout << angry_w << std::endl;
		initialiseexpression();
		angry_w = angry_w + 1;
		spherePos = glm::vec3(0.0f, -1.5f, 0.0f);
	}
	if (key == GLFW_KEY_H && action == GLFW_PRESS)
	{
		std::cout << angry_w << std::endl;
		initialiseexpression();
		happy_w = happy_w + 1;
		spherePos = glm::vec3(1.0f, 1.5f, 0.0f);
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		std::cout << angry_w << std::endl;
		initialiseexpression();
		angry_l_w = angry_l_w + 1;
		spherePos = glm::vec3(0.0f, 0.0f, 0.0f);
	}  // sad left
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		std::cout << angry_w << std::endl;
		initialiseexpression();
		angry_r_w = angry_r_w + 1;
		spherePos = glm::vec3(0.0f, -1.5f, 0.0f);
	} //sad right.
	if (key == GLFW_KEY_U && action == GLFW_PRESS)
	{
		std::cout << angry_w << std::endl;
		initialiseexpression();
		happy_r_w = happy_r_w + 1;
		spherePos = glm::vec3(1.0f, 1.5f, 0.0f);
	} //happy right.
	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		std::cout << angry_w << std::endl;
		initialiseexpression();
		happy_l_w = happy_l_w + 1;
		spherePos = glm::vec3(0.0f, 0.0f, 0.0f);
	} //happy left.
	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		std::cout << angry_w << std::endl;
		initialiseexpression();
		suck_vp_w = suck_vp_w + 1;
		spherePos = glm::vec3(0.0f, -1.5f, 0.0f);
	} //suck.
	if (key == GLFW_KEY_Y && action == GLFW_PRESS)
	{
		std::cout << angry_w << std::endl;
		initialiseexpression();
		suck_l_w = suck_l_w + 1;
		spherePos = glm::vec3(0.0f, 0.0f, 0.0f);
	} //suck
	if (key == GLFW_KEY_V && action == GLFW_PRESS)
	{
		std::cout << happy_w << std::endl;
		initialiseexpression();
		suck_r_w = suck_r_w + 1;
		spherePos = glm::vec3(-1.5f, 1.5f, 0.0f);
	}
	if (key == GLFW_KEY_J && action == GLFW_PRESS)
	{
		std::cout << happy_w << std::endl;
		initialiseexpression();
		jaw_open_w = jaw_open_w + 1;
		spherePos = glm::vec3(-1.5f, 1.5f, 0.0f);
	}
	if (key == GLFW_KEY_N && action == GLFW_PRESS)
	{
		std::cout << happy_w << std::endl;
		initialiseexpression();
		neutral = neutral + 1;
		spherePos = glm::vec3(-1.5f, 1.5f, 0.0f);
	}
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		std::cout << "Playing Animation" << std::endl;
		initialiseexpression();
		playanimation();
	}
}

//-----------------------------------------------------------------------------
// Is called when the window is resized
//-----------------------------------------------------------------------------
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height)
{
	gWindowWidth = width;
	gWindowHeight = height;
	glViewport(0, 0, gWindowWidth, gWindowHeight);
}

//-----------------------------------------------------------------------------
// Called by GLFW when the mouse wheel is rotated
//-----------------------------------------------------------------------------
void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY)
{
	double fov = fpsCamera.getFOV() + deltaY * ZOOM_SENSITIVITY;

	fov = glm::clamp(fov, 1.0, 120.0);

	fpsCamera.setFOV((float)fov);
}

//-----------------------------------------------------------------------------
// Update stuff every frame
//-----------------------------------------------------------------------------
void update(double elapsedTime)
{
	// Camera orientation
	double mouseX, mouseY;

	// Get the current mouse cursor position delta
	glfwGetCursorPos(gWindow, &mouseX, &mouseY);

	// Rotate the camera the difference in mouse distance from the center screen.  Multiply this delta by a speed scaler
	fpsCamera.rotate((float)(gWindowWidth / 2.0 - mouseX) * MOUSE_SENSITIVITY, (float)(gWindowHeight / 2.0 - mouseY) * MOUSE_SENSITIVITY);

	// Clamp mouse cursor to center of screen
	glfwSetCursorPos(gWindow, gWindowWidth / 2.0, gWindowHeight / 2.0);

	// Camera FPS movement

	// Forward/backward
	if (glfwGetKey(gWindow, GLFW_KEY_W) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * fpsCamera.getLook());
	else if (glfwGetKey(gWindow, GLFW_KEY_S) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -fpsCamera.getLook());

	// Strafe left/right
	if (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -fpsCamera.getRight());
	else if (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * fpsCamera.getRight());

	// Up/down
	if (glfwGetKey(gWindow, GLFW_KEY_Z) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * fpsCamera.getUp());
	else if (glfwGetKey(gWindow, GLFW_KEY_X) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -fpsCamera.getUp());
}

//-----------------------------------------------------------------------------
// Code computes the average frames per second, and also the average time it takes
// to render one frame.  These stats are appended to the window caption bar.
//-----------------------------------------------------------------------------
void showFPS(GLFWwindow* window)
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime(); // returns number of seconds since GLFW started, as double float

	elapsedSeconds = currentSeconds - previousSeconds;

	// Limit text updates to 4 times per second
	if (elapsedSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		// The C++ way of setting the window title
		std::ostringstream outs;
		outs.precision(3);	// decimal places
		outs << std::fixed
			<< APP_TITLE << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << msPerFrame << " (ms)";
		glfwSetWindowTitle(window, outs.str().c_str());

		// Reset for next average.
		frameCount = 0;
	}

	frameCount++;
}

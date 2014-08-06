#include "main.hpp"


using namespace std;
 
GLFWwindow* mainWindow = NULL;


int main(int argc, char** argv)
{
#if defined(_WIN32)
	// Enable memory-leak reports
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
#endif

    g_camera.m_width = 800;
    g_camera.m_height = 600;
    
	if (glfwInit() == 0)
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	char title[64];
	sprintf(title, "Box2D Testbed Version %d.%d.%d", b2_version.major, b2_version.minor, b2_version.revision);

#if defined(__APPLE__)
	// Not sure why, but these settings cause glewInit below to crash.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    mainWindow = glfwCreateWindow(g_camera.m_width, g_camera.m_height, title, NULL, NULL);
	if (mainWindow == NULL)
	{
		fprintf(stderr, "Failed to open GLFW mainWindow.\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(mainWindow);
	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	glfwSetScrollCallback(mainWindow, sScrollCallback);
	glfwSetWindowSizeCallback(mainWindow, sResizeWindow);
	glfwSetKeyCallback(mainWindow, sKeyCallback);
	glfwSetMouseButtonCallback(mainWindow, sMouseButton);
	glfwSetCursorPosCallback(mainWindow, sMouseMotion);
	glfwSetScrollCallback(mainWindow, sScrollCallback);

#if defined(__APPLE__) == FALSE
	//glewExperimental = GL_TRUE;
    GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}
#endif
    
	g_debugDraw.Create();

	sCreateUI();

	testCount = 0;
	while (g_testEntries[testCount].createFcn != NULL)
	{
		++testCount;
	}

	testIndex = b2Clamp(testIndex, 0, testCount - 1);
	testSelection = testIndex;

	entry = g_testEntries + testIndex;
	test = entry->createFcn();

	// Control the frame rate. One draw per monitor refresh.
	glfwSwapInterval(1);

    double time1 = glfwGetTime();
    double frameTime = 0.0;
   
    glClearColor(0.3f, 0.3f, 0.3f, 1.f);
	
 	while (!glfwWindowShouldClose(mainWindow))
	{
 		glfwGetWindowSize(mainWindow, &g_camera.m_width, &g_camera.m_height);
		glViewport(0, 0, g_camera.m_width, g_camera.m_height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		unsigned char mousebutton = 0;
		int mscroll = ui.scroll;
		ui.scroll = 0;

		double xd, yd;
		glfwGetCursorPos(mainWindow, &xd, &yd);
		int mousex = int(xd);
		int mousey = int(yd);

		mousey = g_camera.m_height - mousey;
		int leftButton = glfwGetMouseButton(mainWindow, GLFW_MOUSE_BUTTON_LEFT);
		if (leftButton == GLFW_PRESS)
			mousebutton |= IMGUI_MBUT_LEFT;

		imguiBeginFrame(mousex, mousey, mousebutton, mscroll);

		sSimulate();
		sInterface();
        
        // Measure speed
        double time2 = glfwGetTime();
        double alpha = 0.9f;
        frameTime = alpha * frameTime + (1.0 - alpha) * (time2 - time1);
        time1 = time2;

        char buffer[32];
        snprintf(buffer, 32, "%.1f ms", 1000.0 * frameTime);
        AddGfxCmdText(5, 5, TEXT_ALIGN_LEFT, buffer, WHITE);
        
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
		RenderGLFlush(g_camera.m_width, g_camera.m_height);

		glfwSwapBuffers(mainWindow);

		glfwPollEvents();
	}

	g_debugDraw.Destroy();
	RenderGLDestroy();
	glfwTerminate();

	return 0;
}
 

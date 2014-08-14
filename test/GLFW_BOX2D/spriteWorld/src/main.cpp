#include "main.hpp"
#include "utils.hpp"

namespace
{
    static constexpr int32 velocityIterations = 8;
    static constexpr int32 positionIterations = 3;
    static constexpr float32 settingsHz = 60.0;
    static constexpr unsigned MAX_KEYS = 300;
    
	GLFWwindow* mainWindow = NULL;
	b2Vec2 lastp;
    b2World* world;
    
    std::map<std::string, usrdata_t*> objs;
    float32 timeStep = 0.0f;
    bool keys[MAX_KEYS];
}

static void sResizeWindow(GLFWwindow*, int width, int height)
{
	g_camera.m_width = width;
	g_camera.m_height = height;
}

static void acctions(void)
{
    b2Body* hero = NULL;
    static constexpr float32 vel = 8.0f;
    
    if (keys[GLFW_KEY_ESCAPE] == true)
    {
        glfwSetWindowShouldClose(mainWindow, GL_TRUE);
        return;
    }
    else if(keys[GLFW_KEY_LEFT] == true)
    {
        hero = utils::getBody("hero", world);
        hero->SetLinearVelocity(b2Vec2{-vel, 0.0f});
        
    }
    else if(keys[GLFW_KEY_RIGHT] == true)
    {
        hero = utils::getBody("hero", world);
        hero->SetLinearVelocity(b2Vec2{vel, 0.0f});
    }
    else if(keys[GLFW_KEY_DOWN] == true)
    {
        hero = utils::getBody("hero", world);
        hero->SetLinearVelocity(b2Vec2{0.0f, -vel});
    }
    else if(keys[GLFW_KEY_UP] == true)
    {
        hero = utils::getBody("hero", world);
        hero->SetLinearVelocity(b2Vec2{0.0f, vel});
    }
    else if(keys[GLFW_KEY_SPACE] == true)
    {
        
    }
    else
    {
        hero = utils::getBody("hero", world);
        hero->SetLinearVelocity(b2Vec2{0.0f, 0.0f});
    }
}

//
static void sKeyCallback(GLFWwindow* mainWindow, int key, int scancode, int action, int mods)
{
    B2_NOT_USED(key);
    B2_NOT_USED(mods);
    B2_NOT_USED(scancode);
    B2_NOT_USED(mainWindow);
    
    if (action == GLFW_PRESS)
        keys[key] = true;
    else if (action == GLFW_RELEASE)
        keys[key] = false;
}

static void sScrollCallback(GLFWwindow* window, double, double dy)
{
    B2_NOT_USED(window);
    B2_NOT_USED(dy);
}

static void sSimulate()
{
	glEnable(GL_DEPTH_TEST);
    timeStep = settingsHz > 0.0f ? 1.0f / settingsHz : float32(0.0f);
    uint32 flags = 0;
	flags += 1	* b2Draw::e_shapeBit;
	flags += 1	* b2Draw::e_jointBit;
	flags += 0	* b2Draw::e_aabbBit;
	flags += 0	* b2Draw::e_centerOfMassBit;
	g_debugDraw.SetFlags(flags);
    
    world->Step(timeStep, velocityIterations, positionIterations);
    acctions();
    world->DrawDebugData();
    
    g_debugDraw.Flush();
    
	glDisable(GL_DEPTH_TEST);
    
}

static void initPhysicsWorld(void)
{
    b2Vec2 gravity(0.0f, 0.0f);
	world = new b2World(gravity);
    
	world->SetDebugDraw(&g_debugDraw);
	//world->SetContactListener(&m_ContactListener);
}

void initScene(void)
{
    // Define the ground body.    
    utils::CreateRect(b2Vec2(-32.0f, 40.0f), b2Vec2(32.0f, 40.0f), CUD("gndUp", GND_UP, NULL, &objs), world);
	utils::CreateRect(b2Vec2(32.0f, 40.0f), b2Vec2(32.0f, -4.8f), CUD("gndRight", GND_RIGHT, NULL, &objs), world);
	utils::CreateRect(b2Vec2(32.0f, -4.8f), b2Vec2(-32.0f, -4.8f), CUD("gndDown", GND_DOWN, NULL, &objs), world);
	utils::CreateRect(b2Vec2(-32.0f, -4.8f), b2Vec2(-32.0f, 40.0f), CUD("gndLeft", GND_LEFT, NULL, &objs), world);
    
    // Rectangulo
	utils::CreateBox( -20.0f, 20.0f, 3.0f, 5.0f, CUD("caja0", BOX, NULL, &objs), world);
	utils::CreateBox( 10.0f, 20.0f, 15.0f, 0.5f, CUD("caja1", BOX, NULL, &objs), world);
    
	// Hero
	utils::CreateDynBox( -0.5f, -3.0f, 1.0f, 1.0f, 0.45f, 1.0f, 0.25f, CUD("hero", DYNBOX, new enemy_t(2, 1.0f), &objs), world);
     
}

int main(const int argc, const char* argv[])
{
    B2_NOT_USED(argc);
    B2_NOT_USED(argv);
#if defined(_WIN32)
	// Enable memory-leak reports
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
#endif

    g_camera.m_width = 1024;
    g_camera.m_height = 640;
    
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
    initPhysicsWorld();
    initScene();
    
	// Control the frame rate. One draw per monitor refresh.
	glfwSwapInterval(1);

    double time1 = glfwGetTime();
    double frameTime = 0.0;
   
    glClearColor(0.3f, 0.3f, 0.3f, 1.f);
    GLenum errCode = 0;
	
 	while (!glfwWindowShouldClose(mainWindow))
	{
 		glfwGetWindowSize(mainWindow, &g_camera.m_width, &g_camera.m_height);
		glViewport(0, 0, g_camera.m_width, g_camera.m_height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sSimulate();

        // Measure speed
        double time2 = glfwGetTime();
        double alpha = 0.9f;
        frameTime = alpha * frameTime + (1.0 - alpha) * (time2 - time1);
        time1 = time2;
        
		//glEnable(GL_BLEND);
        //glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_BLEND);
		RenderGLFlush(g_camera.m_width, g_camera.m_height);
        
		glfwSwapBuffers(mainWindow);
        
        errCode = glGetError();

		glfwPollEvents();
	}

	g_debugDraw.Destroy();
	RenderGLDestroy();
	glfwTerminate();

	return 0;
}
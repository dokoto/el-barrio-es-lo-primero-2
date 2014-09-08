#include "main.hpp"
#include "utils.hpp"
#include "imgui.h"
#include <SOIL2/SOIL2.h>

struct UIState
{
	bool showMenu;
	int scroll;
	int scrollarea1;
	bool mouseOverMenu;
	bool chooseTest;
};

namespace
{
    static constexpr int32 velocityIterations = 8;
    static constexpr int32 positionIterations = 3;
    static constexpr float32 settingsHz = 60.0;
    static constexpr unsigned MAX_KEYS = 300;
    
	GLFWwindow* mainWindow = NULL;
    UIState ui;
	b2Vec2 lastp;
    b2World* world;
    GLuint tex_2d;
    
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
    static constexpr float32 vel = 8.0f, camVel = 0.1f;
    
    if (keys[GLFW_KEY_ESCAPE] == true)
    {
        glfwSetWindowShouldClose(mainWindow, GL_TRUE);
        return;
    }
    else if(keys[GLFW_KEY_LEFT] == true)
    {
        hero = utils::getBody("hero", world);
        hero->SetLinearVelocity(b2Vec2{-vel, 0.0f});
        g_camera.m_center.x -= camVel;
        
    }
    else if(keys[GLFW_KEY_RIGHT] == true)
    {
        hero = utils::getBody("hero", world);
        hero->SetLinearVelocity(b2Vec2{vel, 0.0f});
        g_camera.m_center.x += camVel;
    }
    else if(keys[GLFW_KEY_DOWN] == true)
    {
        hero = utils::getBody("hero", world);
        hero->SetLinearVelocity(b2Vec2{0.0f, -vel});
        g_camera.m_center.y -= camVel;
    }
    else if(keys[GLFW_KEY_UP] == true)
    {
        hero = utils::getBody("hero", world);
        hero->SetLinearVelocity(b2Vec2{0.0f, vel});
        g_camera.m_center.y += camVel;
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

static void sCreateUI()
{
	ui.showMenu = true;
	ui.scroll = 0;
	ui.scrollarea1 = 0;
	ui.chooseTest = false;
	ui.mouseOverMenu = false;
    
	// Init UI
    const char* fontPath = "ttf/DroidSans.ttf";
    
	if (RenderGLInit(fontPath) == false)
	{
		fprintf(stderr, "Could not init GUI renderer.\n");
		assert(false);
		return;
	}
}

static void drawTexture_TEST(GLuint& id_tex_2d)
{
    glEnable( GL_TEXTURE_2D );
    glLoadIdentity();
    glTranslatef( 0, 0, 0.f );
    glBindTexture( GL_TEXTURE_2D, id_tex_2d );
    glBegin(GL_QUADS);                              // Draw A Quad
        glTexCoord2f(0,0);
        glVertex2f(0,0);
    
        glTexCoord2f(1,0);
        glVertex2f(500,0);
    
        glTexCoord2f(1,1);
        glVertex2f(500,500);
    
        glTexCoord2f(0,1);
        glVertex2f(0,500);
    glEnd();
}

void display() {
    int width, height;
    glfwGetFramebufferSize(mainWindow, &width, &height);
    float ratio = width / (float) height;
    glBegin(GL_TRIANGLES);
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-0.6f, -0.4f, 0.f);
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.6f, -0.4f, 0.f);
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.6f, 0.f);
    glEnd();
    
    GLenum errCode = glGetError();
	if (errCode != GL_NO_ERROR)
	{
		printf("display ERROR %d\n", errCode);
	}
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
//  drawTexture_TEST(tex_2d);
    display();
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

static void loadTexture_TEST(const char* path, GLuint& id_tex_2d)
{
    id_tex_2d = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

    if( 0 == tex_2d )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
}


void initScene(void)
{
    g_camera.m_center.x = 0.0f;
    g_camera.m_center.y = 0.0f;
    
    // Centre
    utils::CreateBox( 0.0f, 0.0f, 0.2f, 0.2f, CUD("caja0", BOX, NULL, &objs), world);
    
    // Player
    utils::CreateDynBox( -1.5f, -3.5f, 2.0f, 2.0f, 0.45f, 1.0f, 0.25f, CUD("hero", DYNBOX, new enemy_t(2, 1.0f), &objs), world);
    
    // Define the ground body.
    utils::CreateRect(b2Vec2(-10.0f, 10.0f), b2Vec2(10.0f, 10.0f), CUD("gndUp", GND_UP, NULL, &objs), world);
	utils::CreateRect(b2Vec2(10.0f, 10.0f), b2Vec2(10.0f, -10.0f), CUD("gndRight", GND_RIGHT, NULL, &objs), world);
	utils::CreateRect(b2Vec2(10.0f, -10.0f), b2Vec2(-10.0f, -10.0f), CUD("gndDown", GND_DOWN, NULL, &objs), world);
	utils::CreateRect(b2Vec2(-10.0f, -10.0f), b2Vec2(-10.0f, 10.0f), CUD("gndLeft", GND_LEFT, NULL, &objs), world);

    // Load texture TEST
    loadTexture_TEST("img/test_1.png", tex_2d);
}


void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error nº: %d - %s.\n", error, description);
}



int main(const int argc, const char* argv[])
{
    B2_NOT_USED(argc);
    B2_NOT_USED(argv);
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
	sprintf(title, "El Barrio es lo Primero - TEST GLFW");

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
    glfwSetErrorCallback(error_callback);

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
        
        char buffer[32];
        snprintf(buffer, 32, "%.1f ms", 1000.0 * frameTime);
        AddGfxCmdText(5, 5, TEXT_ALIGN_LEFT, buffer, WHITE);
        
        glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
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
#include "main.hpp"
#include <SOIL2/SOIL2.h>

#include <stdlib.h>
#include <stdio.h>


GLuint id_tex_2d;
GLenum errCode;

void loadTexture(const char* path, unsigned char*& data, GLuint& id_tex_2d, int& width, int& height, int& channels);
void setProjection2DInCentre(const int screenWidth, const int screenHeight);
void generateTexture(const int screenWidth, const int screenHeight, const int width, const int height, GLuint& id_tex_2d, void* data);


void drawTexture_TEST(const int width, const int height, GLuint& id_tex_2d);
void drawTriangle(GLFWwindow* window);
void renderTextureClip(const GLfloat x, const GLfloat y, const int imagewidth, const int imageheight, GLuint& mTextureID, LFRect* clip = NULL );
void drawTexture_TEST2(const int imagewidth, const int imageheight, GLuint& id_tex_2d);
void RenderSprite( GLuint spritesheet, unsigned spritex, unsigned spritey, unsigned texturew, unsigned textureh, int x, int y, int w, int h );




void loadTexture(const char* path, unsigned char*& data, GLuint& id_tex_2d, int& width, int& height, int& channels)
{
    data = SOIL_load_image( path, &width, &height, &channels, SOIL_LOAD_AUTO );
    
    if ( data )
    {
        id_tex_2d = SOIL_load_OGL_texture(path, SOIL_LOAD_RGBA,
                                          SOIL_CREATE_NEW_ID,
                                          SOIL_FLAG_TEXTURE_RECTANGLE | SOIL_FLAG_NTSC_SAFE_RGB);
        
        if( 0 == id_tex_2d )
        {
            printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        }
    }
}

void setProjection2DInCentre(const int screenWidth, const int screenHeight)
{
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-(screenWidth/2), screenWidth/2, -(screenHeight/2), screenHeight/2, -1, 1);
}


void generateTexture(const int screenWidth, const int screenHeight, const int imageWidth, const int imageHeight, GLuint& id_tex_2d, void* data)
{
    setProjection2DInCentre(screenWidth, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glGenTextures(1, &id_tex_2d);
    
    glBindTexture(GL_TEXTURE_2D, id_tex_2d);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    errCode = glGetError();
	if (errCode != GL_NO_ERROR)
	{
		printf("generateTexture_TEST ERROR %d\n", errCode);
	}
}



void drawTexture_TEST(const int imagewidth, const int imageheight, GLuint& id_tex_2d)
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    //Reset modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    glBindTexture(GL_TEXTURE_2D, id_tex_2d);
    
    GLint widthratio, heightratio;
    widthratio = imagewidth/5;
    heightratio = imageheight/5;
    
    glTranslatef(-(widthratio/2), -(heightratio/2), 0);
    
    glBegin(GL_QUADS);
    glTexCoord2i(0,0); glVertex2i(0, heightratio);
    glTexCoord2i(0,1); glVertex2i(0, 0);
    glTexCoord2i(1,1); glVertex2i(widthratio, 0);
    glTexCoord2i(1,0); glVertex2i(widthratio, heightratio);
    glEnd();
    
    errCode = glGetError();
	if (errCode != GL_NO_ERROR)
	{
		printf("drawTexture_TEST ERROR %d\n", errCode);
	}
}

void drawTexture_TEST2(const int imagewidth, const int imageheight, GLuint& id_tex_2d)
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    //Reset modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    glBindTexture(GL_TEXTURE_2D, id_tex_2d);
    
    GLint widthratio, heightratio;
    widthratio = imagewidth/3;
    heightratio = imageheight/3;
    
    //glTranslatef(-(widthratio/2), -(heightratio/2), 0);
    glTranslatef(0, 0, 0);
    
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, heightratio);                // BOTTOM-LEFT
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 0.0f);                       // TOP-LEFT
    glTexCoord2f(1.0f, 1.0f); glVertex2f(widthratio, 0.0f);                 // TOP-RIGHT
    glTexCoord2f(1.0f, 0.0f); glVertex2f(widthratio, heightratio);          // BOTTOM-RIGHT
    
    /*
     * SCALING DOWNSIZE AND VERTICAL FLIP
    glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);                // BOTTOM-LEFT
    glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, heightratio);         // TOP-LEFT
    glTexCoord2f(1.0f, 1.0f); glVertex2f(widthratio, heightratio);   // TOP-RIGHT
    glTexCoord2f(1.0f, 0.0f); glVertex2f(widthratio, 0.0f);          // BOTTOM-RIGHT
     */
    
    /*
     * SCALING DOWNSIZE AND NO CLIPPING
     glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, heightratio);                // BOTTOM-LEFT
     glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, 0.0f);                       // TOP-LEFT
     glTexCoord2f(1.0f, 1.0f); glVertex2f(widthratio, 0.0f);                 // TOP-RIGHT
     glTexCoord2f(1.0f, 0.0f); glVertex2f(widthratio, heightratio);          // BOTTOM-RIGHT
     */
    
    /*
     * Clipping LEFT-BOTTOM SIDE AND NO CLIPPING
     glTexCoord2f(0.0f, 0.5f); glVertex2f(0, heightratio);  // top-right
     glTexCoord2f(0.0f, 1.0f); glVertex2f(0, 0); // bottom-right
     glTexCoord2f(0.5f, 1.0f); glVertex2f(widthratio, 0); // bottom-left
     glTexCoord2f(0.5f, 0.5f); glVertex2f(widthratio, heightratio); // top-left
     */
    
    /* Clipping LEFT-BOTTOM SIDE AND HORIZONTAL CLIPPING
     glTexCoord2f(1.0f, 0.5f); glVertex2f(0, heightratio);  // top-right
     glTexCoord2f(1.0f, 1.0f); glVertex2f(0, 0); // bottom-right
     glTexCoord2f(0.5f, 1.0f); glVertex2f(widthratio, 0); // bottom-left
     glTexCoord2f(0.5f, 0.5f); glVertex2f(widthratio, heightratio); // top-left
     */
    
    glEnd();
    
    errCode = glGetError();
	if (errCode != GL_NO_ERROR)
	{
		printf("drawTexture_TEST ERROR %d\n", errCode);
	}
}


static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


int main(void)
{
    static constexpr int screnWidth = 800;
    static constexpr int screnHeight = 600;
    int textureWidth = 0, textureHeight = 0, channel = 0;
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    window = glfwCreateWindow(screnWidth, screnHeight, "TEST-1", NULL, NULL);
    glViewport(0, 0, screnWidth, screnHeight);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    id_tex_2d = 0;
    unsigned char* data = nullptr;
    
    loadTexture("img/test_1.png", data, id_tex_2d, textureWidth, textureHeight, channel);
    generateTexture(screnWidth, screnHeight, textureWidth, textureHeight, id_tex_2d, data);
    
    LFRect clip = {0, 0, 100, 100};
    while (!glfwWindowShouldClose(window))
    {
        //drawTriangle(window);
        drawTexture_TEST2(textureWidth, textureHeight, id_tex_2d);
        //renderTextureClip(-250, -250, textureWidth, textureHeight, id_tex_2d, &clip);
        //RenderSprite(id_tex_2d, 0, 0, textureWidth, textureHeight, 100, 100, 200, 200);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    if (data != nullptr)
        SOIL_free_image_data( data );
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
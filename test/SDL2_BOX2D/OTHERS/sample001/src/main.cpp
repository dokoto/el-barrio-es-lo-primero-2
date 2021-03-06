	

    //http://www.youtube.com/user/thecplusplusguy
    //The Box2D main program with SDL
    #include <iostream>
#include <string>
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>
#if defined(__APPLE__)
#include <OpenGL/gl3.h>
#else
#include <glew/glew.h>
#endif    
    #include <Box2D/Box2D.h>
     
    const int WIDTH=800;
    const int HEIGHT=600;
    const float M2P=20;
    const float P2M=1/M2P;
    b2World* world;
    SDL_Surface* screen;
     
    void putPixel(SDL_Surface* dest,int x,int y,int r,int g,int b)
    {
    //      std::cout << x << " " << y << std::endl;
            if(x>=0 && x<dest->w && y>=0 && y<dest->h)
                    ((Uint32*)dest->pixels)[y*dest->pitch/4+x]=SDL_MapRGB(dest->format,r,g,b);
    }
     
    void swapValue(int& a,int& b)
    {
            int tmp=a;
            a=b;
            b=tmp;
    }
     
    void drawLine(SDL_Surface* dest,int x0,int y0,int x1,int y1)
    {
            int tmp;
            bool step;
           
            step=abs(y1-y0)>abs(x1-x0);
            if(step)
            {
                    swapValue(x0,y0);
                    swapValue(x1,y1);
            }
           
            if(x0>x1)
            {
                    swapValue(x1,x0);
                    swapValue(y1,y0);
            }
            float error=0.0;
            float y=y0;
            float roundError=(float)abs(y1-y0)/(x1-x0);
            int ystep=(y1>y0 ? 1 : -1);
            for(int i=x0;i<x1;i++)
            {
                    if(step)
                            putPixel(dest,y,i,255,255,255);
                    else
                            putPixel(dest,i,y,255,255,255);
                    error+=roundError;
                    if(error>=0.5)
                    {
                            y+=ystep;
                            error-=1;
                    }
            }
    }
     
    void rotateTranslate(b2Vec2& vector,const b2Vec2& center,float angle)
    {
            b2Vec2 tmp;
            tmp.x=vector.x*cos(angle)-vector.y*sin(angle);
            tmp.y=vector.x*sin(angle)+vector.y*cos(angle);
            vector=tmp+center;
    }
     
     
    b2Body* addRect(int x,int y,int w,int h,char* name,bool dyn=true)
    {
            b2BodyDef bodydef;
            bodydef.position.Set(x*P2M,y*P2M);
            bodydef.userData = static_cast<void*>(name);
        
            if(dyn)
                    bodydef.type=b2_dynamicBody;
            b2Body* body=world->CreateBody(&bodydef);
           
            b2PolygonShape shape;
            shape.SetAsBox(P2M*w/2,P2M*h/2);
           
            b2FixtureDef fixturedef;
            fixturedef.shape=&shape;
            fixturedef.density=1.0;
            body->CreateFixture(&fixturedef);
           
    }
     
    void drawSquare(b2Vec2* points,b2Vec2 center,float angle)
    {
            for(int i=0;i<4;i++)
                    drawLine(screen,points[i].x*M2P,points[i].y*M2P,points[(i+1)>3 ? 0 : (i+1)].x*M2P,points[(i+1)>3 ? 0 : (i+1)].y*M2P);
    }
     
     
    void init()
    {
            world=new b2World(b2Vec2(0.0,9.81));
            //addRect(WIDTH/2,HEIGHT-50,WIDTH,30,false);
            addRect(WIDTH/2,HEIGHT-50,790,30,"base", false);
    }
     
    void display()
    {
            SDL_FillRect(screen,NULL,0);
            b2Body* tmp=world->GetBodyList();
            b2Vec2 points[4];
            while(tmp)
            {
                    for(int i=0;i<4;i++)
                    {
                            points[i]=((b2PolygonShape*)tmp->GetFixtureList()->GetShape())->GetVertex(i);
                            rotateTranslate(points[i],tmp->GetWorldCenter(),tmp->GetAngle());
                    }
                    char* usr1 = static_cast<char*>(tmp->GetFixtureList()->GetBody()->GetUserData());
                    if (std::string(usr1).compare("cuadrado") == 0)
//                        printf("[%f, %f][%f, %f][%f, %f][%f, %f]\n", points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y, points[3].x, points[3].y );
                
                    drawSquare(points,tmp->GetWorldCenter(),tmp->GetAngle());
                    tmp=tmp->GetNext();
            }
    }
     
    int main(int argc,char** argv)
    {
            SDL_Init(SDL_INIT_EVERYTHING);
            screen=SDL_SetVideoMode(WIDTH,HEIGHT,32,SDL_SWSURFACE);
            Uint32 start;
            SDL_Event event;
            bool running=true;
            init();
            while(running)
            {
                    start=SDL_GetTicks();
                    while(SDL_PollEvent(&event))
                    {
                            switch(event.type)
                            {
                                    case SDL_QUIT:
                                            running=false;
                                            break;
                                    case SDL_KEYDOWN:
                                            switch(event.key.keysym.sym)
                                            {
                                                    case SDLK_ESCAPE:
                                                            running=false;
                                                            break;
                                            }
                                            break;
                                    case SDL_MOUSEBUTTONDOWN:
                                            addRect(event.button.x,event.button.y,20,20,"cuadrado",true);
                                            break;
                                           
                            }
                    }
                    display();
                    world->Step(1.0/30.0,8,3);      //update
                    SDL_Flip(screen);
                    if(1000.0/30>SDL_GetTicks()-start)
                            SDL_Delay(1000.0/30-(SDL_GetTicks()-start));
            }
            SDL_Quit();
    }


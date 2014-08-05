#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <Box2D/Box2D.h>
#include <stdio.h>
#include <stdexcept>
 
#include "TextureManager.h"
 
SDL_Window* gameWindow;
SDL_Renderer* gameRenderer;
 
// Pixels Per Meter
static constexpr float PPM{400.0f};
static constexpr float FPS{60.f};
static constexpr float DELAY_TIME = 1000.f / FPS;
static constexpr float TIMESTEP = 1.f / 60.f;
 
static constexpr int WIDTH = 800;
static constexpr int HEIGHT = 600;
 
b2World* world;
b2Body* body;
 
b2Body* groundBody;
b2Fixture* bottomFixture;
 
class Ball 
{
private:
 
 
public:
    static constexpr int WIDTH{22};
    static constexpr int HEIGHT{22};
    static constexpr int RADIUS{11};
 
    b2Vec2 position;
    float angle;
    b2Vec2 linearVelocity;
 
    Ball();
    void init(b2World* world);
    void render(TextureManager& textureManager);
    void kick();
private:
    b2Body* body;
    b2BodyDef myBodyDef;
};
 
Ball::Ball()
{
}
 
void Ball::init(b2World* world)
{
    // setup dynamic body
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(100/PPM, 100/PPM);
    body = world->CreateBody(&myBodyDef);
 
    body->SetUserData(this);
    
    // add circle fixture
    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = RADIUS;
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &circleShape;
    myFixtureDef.density = 1;
    myFixtureDef.friction = 0.2f;
    myFixtureDef.restitution = 1.0f;
    body->CreateFixture(&myFixtureDef);
}
 
void Ball::kick()
{
    b2Vec2 force = b2Vec2(0, 10.0f);
    body->ApplyLinearImpulse(force, myBodyDef.position, true);
}
 
void Ball::render(TextureManager& textureManager)
{
    textureManager.render(position.x, position.y);
}
 
int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw std::runtime_error("Initialized failure");
    }
 
    if (SDL_ShowCursor(SDL_DISABLE) < 0) {
        throw std::runtime_error("Could not disable cursor");
    }
 
    // Draw main window
    gameWindow = SDL_CreateWindow("Box2D Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (gameWindow == nullptr) {
        throw std::runtime_error("gameWindow could not be created");
    }
    if (gameRenderer == nullptr) {
        throw std::runtime_error("gameRenderer could not be created");
    }
 
    SDL_SetRenderDrawColor(gameRenderer, 55, 55, 55, 255);
 
    TextureManager txtBall = { gameRenderer };
    txtBall.loadFromFile("img/ball.png");
 
    // Box2D
    b2Vec2 gravity = b2Vec2(0.0f, 10.0f);
    world = new b2World(gravity);
 
    // Create edges around entire screen
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0,HEIGHT/PPM);
    groundBody = world->CreateBody(&groundBodyDef);
 
    b2EdgeShape groundBox;
    b2FixtureDef groundBoxDef;
    groundBoxDef.shape = &groundBox;
  
    // ground 
    groundBox.Set(b2Vec2(0, HEIGHT/PPM), b2Vec2(WIDTH/PPM, HEIGHT/PPM));
    bottomFixture = groundBody->CreateFixture(&groundBoxDef); 
    // right wall
    groundBox.Set(b2Vec2(WIDTH - 11, 0), b2Vec2(WIDTH-11, HEIGHT/PPM));
    groundBody->CreateFixture(&groundBoxDef);
    // left wall
    groundBox.Set(b2Vec2(-11, 0), b2Vec2(-11, HEIGHT));
    groundBody->CreateFixture(&groundBoxDef);
    // top wall
    groundBox.Set(b2Vec2(0, -70), b2Vec2(WIDTH, -70));
    groundBody->CreateFixture(&groundBoxDef);
   
    Ball* ball = new Ball();
    ball->init(world);
    
    SDL_Event e;
 
    Uint32 lastTime, currentTime, frameTime;
    float deltaTime;
    currentTime = SDL_GetTicks();
 
    bool running = true;
    while (running) {
        lastTime = currentTime;
        currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.f;
 
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
 
        world->Step(TIMESTEP, 10, 10);
 
        b2Body* b = world->GetBodyList();
        while (b != nullptr) {
            Ball* ball = static_cast<Ball*>(b->GetUserData());
            if (ball != nullptr) {
                ball->position = b2Vec2(b->GetPosition().x * PPM, b->GetPosition().y * PPM);
                ball->linearVelocity = b->GetLinearVelocity();
                ball->angle = b->GetAngle();
            }
 
            b = b->GetNext();
        }
        
        ball->kick();
 
        // Clear screen
        SDL_RenderClear(gameRenderer);
        ball->render(txtBall);
 
        // Update screen
        SDL_RenderPresent(gameRenderer);
 
 
        frameTime = SDL_GetTicks() - currentTime;
        if (frameTime < DELAY_TIME) {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }
 
    world = nullptr;
    groundBody = nullptr;
    IMG_Quit();
    SDL_Quit();
    return 0;
}
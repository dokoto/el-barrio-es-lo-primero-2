#include "main.hpp"


SDL_Window* win = nullptr;
SDL_Renderer* ren = nullptr;
SDL_GLContext con;

 void DestroyAndQuit(SDL_Window* win, SDL_Renderer* ren, SDL_GLContext& con)
{
  if (ren)
    SDL_DestroyRenderer(ren);
  if (win)
    SDL_DestroyWindow(win);
  if (con)
    SDL_GL_DeleteContext(con);
  SDL_Quit();
}


int main(int argc, char **argv) try {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    throw std::runtime_error("SDL_Init failed.");
  }

  win = SDL_CreateWindow("SDL ENVIRONMENT TESTING", 0, 0, 640, 480, SDL_WINDOW_OPENGL);
  if (!win) {
    throw std::runtime_error("SDL_CreateWindow failed.");
  }

  ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
  if (!ren) {
    throw std::runtime_error("SDL_CreateRenderer failed.");
  }

  con = SDL_GL_CreateContext(win);
  if (!con) {
    throw std::runtime_error("SDL_GL_CreateContext failed.");
  }

  SDL_RenderClear(ren);
  SDL_RenderPresent(ren);

  glClearColor(0, 1, 1, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  SDL_GL_SwapWindow(win);

  SDL_Delay(2000);

  DestroyAndQuit(win, ren, con);

  return 0;
 } catch(std::exception& ex) {
  std::cerr << ex.what() << ": " << SDL_GetError() << "\n";
  DestroyAndQuit(win, ren, con);
  return 1;
 }
 
#ifndef EL_BARRIO_ES_LO_PRIMERO_FrameRate_h
#define EL_BARRIO_ES_LO_PRIMERO_FrameRate_h

#include "LTimer.hpp"

namespace barrio {
    namespace utls
    {
        class FrameRate
        {
        private:
            FrameRate(const FrameRate&){}
            FrameRate& operator=(const FrameRate&);
            
        private:
            int countedFrames;
            float avgFPS;
            LTimer fpsTimer;
            
        public:
            
            void start(void)
            {
                countedFrames = 0;
                avgFPS = 0.0f;
                fpsTimer.start();
            }
            
            float getFrameRate(void)
            {
                avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
                if( avgFPS > 2000000.0f )
                {
                    avgFPS = 0.0f;
                }
                
                return avgFPS;
            }
            
            void step(void)
            {
                ++countedFrames;
            }
            
            FrameRate(void) : countedFrames(0), avgFPS(0.0f) {}
            FrameRate(const FrameRate&& f): countedFrames(f.countedFrames), avgFPS(f.avgFPS) {}
            FrameRate& operator=(const FrameRate&& f)
            {
                countedFrames = f.countedFrames;
                avgFPS = f.avgFPS;
                
                return *this;
            }
        };
    }
}

#endif

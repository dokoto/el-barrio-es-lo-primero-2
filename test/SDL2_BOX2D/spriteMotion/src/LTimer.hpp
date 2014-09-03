#ifndef __EL_BARRIO_ES_LO_PRIMERO__LTimer__
#define __EL_BARRIO_ES_LO_PRIMERO__LTimer__

#include <SDL2/SDL.h>

namespace barrio {
    
    class LTimer
    {
    public:
        //Initializes variables
        LTimer();
        
        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();
        
        //Gets the timer's time
        Uint32 getTicks();
        
        //Checks the status of the timer
        bool isStarted();
        bool isPaused();
        
    private:
        //The clock time when the timer started
        Uint32 mStartTicks;
        
        //The ticks stored when the timer was paused
        Uint32 mPausedTicks;
        
        //The timer status
        bool mPaused;
        bool mStarted;
    };
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__LTimer__) */

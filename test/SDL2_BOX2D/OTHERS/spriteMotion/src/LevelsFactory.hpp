#ifndef EL_BARRIO_ES_LO_PRIMERO_Levels_hpp
#define EL_BARRIO_ES_LO_PRIMERO_Levels_hpp

#include "Level.hpp"
#include "Level_1.hpp"
#include "ErrorsCodes.hpp"

namespace barrio
{
    
    class LevelsFactory
    {
    public:
        enum Stage {LEVEL1};
        static Level* CreateIntance(Stage stage)
        {
            Level* level = nullptr;
            switch (stage)
            {
                case Stage::LEVEL1:
                    level = new Level_1();
                    break;
                default:
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Level not found");
                    throw error::LEVEL_NOT_FOUND;
                    break;
            }
            
            return level;
        }
    };
}

#endif

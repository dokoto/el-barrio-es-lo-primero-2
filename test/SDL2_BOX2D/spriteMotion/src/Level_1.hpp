#ifndef __EL_BARRIO_ES_LO_PRIMERO__Level_1__
#define __EL_BARRIO_ES_LO_PRIMERO__Level_1__

#include "Level.hpp"
#include "Furnitures.hpp"

namespace barrio
{
    
class Level_1 : public Level
{
public:
    void loadLevelWorld(void);
    void handleInput(void)
    {
        handleInputPlayer(playerA);
        handleInputPlayer(playerB);
    }
    void releaseClycleLiveTimeResources(void);
    
private:    
    Furnitures furnitures;
};
    
}

#endif /* defined(__EL_BARRIO_ES_LO_PRIMERO__Level_1__) */

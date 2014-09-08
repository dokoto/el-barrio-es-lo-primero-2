#ifndef EL_BARRIO_ES_LO_PRIMERO_Entities_hpp
#define EL_BARRIO_ES_LO_PRIMERO_Entities_hpp

namespace entity {
    
    enum TypeOfSprite
    {
        SPRT_CHARACTER,
        SPRT_FURNITURE,
        SPRT_BACKGROUND,
        SPRT_NONE
    };
    
    enum TypeOfShape
    {
        SHP_POLYGON,
        SHP_CIRCLE,
        SHP_CHAIN,
        SHP_NONE
    };
    
    enum TypeOfFixture
    {
        FIX_CHARACTER,
        FIX_ENEMY,
        FIX_FURNITURE,
        FIX_FOOT,
        FIX_HORIZON,
        FIX_WORLD_BUDARIES,
        FIX_NONE
    };
}
#endif



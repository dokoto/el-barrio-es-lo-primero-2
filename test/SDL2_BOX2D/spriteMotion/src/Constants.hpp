#ifndef EL_BARRIO_ES_LO_PRIMERO_Constants_hpp
#define EL_BARRIO_ES_LO_PRIMERO_Constants_hpp

namespace consts {
    static constexpr int CAMERA_WIDTH_PX = 800;
    static constexpr int CAMERA_MIDDLE_WIDTH_PX = CAMERA_WIDTH_PX / 2;
    
    static constexpr int CAMERA_HEIGHT_PX = 600;
    static constexpr int CAMERA_MIDDLE_HEIGHT_PX = CAMERA_HEIGHT_PX / 2;
    
    static constexpr int WORLD_WIDTH_PX = 1679;
    static constexpr int WORLD_MIDDLE_WIDTH_PX = WORLD_WIDTH_PX / 2;
    
    static constexpr int WORLD_HEIGHT_PX = 600;
    static constexpr int WORLD_MIDDLE_HEIGHT_PX = WORLD_HEIGHT_PX / 2;
    
    static constexpr int CAMERA_MARGIN_PX = 100;
    static constexpr int CAMERA_SHIFT_FACTOR = 1;
    
    static constexpr int DELAY_BETWEEN_ANIMATIONS = 10;
    static constexpr int RESUME_STATE_DELAY_IN_MS = 300;
    
    static constexpr bool QUIT_GAME = true;
    static constexpr bool CONTINUE_GAME = false;
    
    static constexpr bool DYNAMIC_BODY = true;
    static constexpr bool STATIC_BODY = false;
    
    static constexpr bool ENABLE_ROTATION = false;
    static constexpr bool DISABLE_ROTATION = true;
    
    static const char* FOOT_NAME = "_FOOT";
    static const char* WORLD_BUNDARIES_NAME = "WORLD_BUNDARIES";
    static const char* HORIZON_NAME = "HORIZON";
    static const char* MOVEMENT_STOP = "stop";
    static const char* MOVEMENT_WALKING = "walking";
    static const char* MOVEMENT_PUNCH = "punch";
    
    enum CLASSES {OBJECT, TEXTURE, SPRITE};
    
}

#endif

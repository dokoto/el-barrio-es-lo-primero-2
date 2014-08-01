#ifndef EL_BARRIO_ES_LO_PRIMERO_errorsCodes_hpp
#define EL_BARRIO_ES_LO_PRIMERO_errorsCodes_hpp

namespace error {
    
    enum {
        SYS_INIT_FAIL,
        LINEAR_TEXTURE_FAIL,
        WINDOW_INIT_FAIL,
        RENDER_CREATION_FAIL,
        SYS_IMAGE_INIT_FAIL,
        READ_SPRITESHEETS_JSON_FAIL,
        PHYSICS_INIT_FAIL,
        PHYSICS_BODY_NAME_NOT_FOUND,
        PHYSICS_BODY_NAME_DUPLICATE,
        PHYSICS_MANDATORY
    };
    
}
#endif

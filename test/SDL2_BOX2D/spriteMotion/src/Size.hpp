//
//  Size.h
//  EL_BARRIO_ES_LO_PRIMERO
//
//  Created by administrador on 21/08/14.
//
//

#ifndef EL_BARRIO_ES_LO_PRIMERO_Size_hpp
#define EL_BARRIO_ES_LO_PRIMERO_Size_hpp

template <typename T> class Size
{
private:
    Size(const Size&){}
    Size& operator=(const Size&);
    
public:
    T w, h;
    
    Size(void) {}
    Size(T widht, T height) : w(widht), h(height) {};
    Size(const Size&& s): w(s.w), h(s.h) {}
    Size& operator=(const Size&& s)
    {
        w = s.w;
        h = s.h;
        return *this;
    }
};

#endif

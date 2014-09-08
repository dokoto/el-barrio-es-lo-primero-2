#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstring>
#include <map>
#include <string>
#include <vector>

	enum  objT {CIRCLE_ENEMY, BOX_ENEMY, BOX, DYNBOX, EDGE, GND_UP, GND_RIGHT, GND_DOWN, GND_LEFT, BULLET, OBJT_NULL};
    enum typeCollisionT {CIRCLE_ENEMY_vs_GROND, CIRCLE_ENEMY_vs_BULLET, BOX_ENEMY_vs_BULLET,
        ANY_vs_BULLET, CIRCLE_ENEMY_vs_HERO, TYPECOLLISIONT_NULL};

    struct usrdata_t;
    typedef std::map<std::string, usrdata_t*> objects_t;
    typedef std::vector<std::pair<b2Fixture*, b2Fixture*> > CollisionedObjects_t;
    extern CollisionedObjects_t CollisionedObjects;
    struct usrdata_t
    {
        std::string idtxt;
        objT type;
        void* object;        
        
        usrdata_t(const char* IdTxt, objT Type, void* Object = NULL) :
            idtxt(IdTxt),
            type(Type),
            object(Object){}
	};

    struct enemy_t
    {
        size_t size;
        float32 radius;
        bool gameover;        
        
        enemy_t(size_t Size, float32 Radius) : size(Size), radius(Radius), gameover(false) {}
        void SplitBall(enemy_t*& newBallA, enemy_t*& newBallB)
        {
            newBallA = NULL; newBallB = NULL;
            if (--size == 0) return;
            newBallA = new enemy_t(size, radius - (radius / 4));
            newBallB = new enemy_t(size, radius - (radius / 4));
        }
    };

    struct enemyPoly_t
    {
        size_t size;
        b2Vec2 sizePoly;
        bool gameover;
        
        enemyPoly_t(const size_t Size, const b2Vec2 SizePoly) : size(Size), sizePoly(SizePoly), gameover(false) {}
        void SplitBall(enemyPoly_t*& newPolyA, enemyPoly_t*& newPolyB)
        {
            newPolyA = NULL; newPolyB = NULL;
            if (--size == 0) return;
            newPolyA = new enemyPoly_t(size, b2Vec2( sizePoly.x - (sizePoly.x / 4), sizePoly.y - (sizePoly.y / 4)) );
            newPolyB = new enemyPoly_t(size, b2Vec2( sizePoly.x - (sizePoly.x / 4), sizePoly.y - (sizePoly.y / 4)) );
        }
    };

    


#endif // TYPES_HPP
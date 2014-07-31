#include "main.hpp"

int main( void )
{
    try
    {
        barrio::Game ElBarrio;
        ElBarrio.gameLoop();
        
    } catch( int exceprionId)
    {
        return exceprionId;
    }
    
    return 0;
}

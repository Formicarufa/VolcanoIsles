#ifndef FireBallGraphics_H
#define FireBallGraphics_H
#include "GameEngine/Image.h"
#include "FireBall.h"


class FireBallGraphics : public  g::Image
{
public:


	FireBallGraphics(int x, int y)
		: Image(x, y, "fireBall" )
	{
		
	}

};


#endif // FireBallGraphics_H

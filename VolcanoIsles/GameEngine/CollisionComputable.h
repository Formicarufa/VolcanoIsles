#ifndef CollisionComputable_H
#define CollisionComputable_H
#include "Graphics.h"

namespace g
{

	class CollisionComputable : public Graphics
	{
		

	public:
		CollisionComputable()
			: mouse_over_(false)
		{
		}
		virtual ~CollisionComputable()
		{
		}

		virtual bool point_collision(int x, int y) = 0;

		bool is_mouse_over() const
		{
			return mouse_over_;
		}
		void set_mouse_over(bool value)
		{
			mouse_over_ = value;
		}
private:
	bool mouse_over_;
	};

}



#endif // CollisionComputable_H



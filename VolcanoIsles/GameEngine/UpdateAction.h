#ifndef UpdateAction_H
#define UpdateAction_H

namespace g
{
	class UpdateAction
	{
	public:
		virtual ~UpdateAction()
		{
		}

		virtual void updateAction() = 0;
	};

}


#endif // UpdateAction_H



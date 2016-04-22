#ifndef DelayTimer_H
#define DelayTimer_H

#include <ctime>
namespace g
{
	class DelayTimer
	{
	public:
		DelayTimer(): end_time_(0) {
		}
		void start(std::clock_t end_time)
		{
			end_time_ = end_time;
			active_ = true;
		}
		void start(std::size_t seconds)
		{
			start(static_cast<std::clock_t>(std::clock() + seconds*CLOCKS_PER_SEC));
		}
		bool time_elapsed() const
		{
			return std::clock() > end_time_;
		}
	private:
		std::clock_t end_time_;
		bool active_;
	};

	
}
#endif // DelayTimer_H

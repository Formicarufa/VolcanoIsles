#ifndef GameConstants_H
#define GameConstants_H

namespace gameconst
{
	///Sprite dimension
	const int island_size = 64;
	const int HEIGHT = 650;
	const int WIDTH = 850;
	const int fire_size = 36;
	const int medal_size = 36;
	const int player_icon_size = 64;
	const int button_size = 64;

	static const std::size_t THINKING_TIME = 2; // time in seconds.
	// maximum depth of the minimax algorithm, the higher number, the more clever the AI is and more time the computation takes.
	const int MAX_DEPTH = 6;


}

#endif // GameConstants_H

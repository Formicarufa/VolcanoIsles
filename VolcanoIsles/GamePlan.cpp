#include "GamePlan.h"
#include <fstream>
#include <sstream>

bool GamePlan::load(std::string filename)
{
	std::ifstream fstream;
	fstream.open(filename);
	std::string line;
	std::size_t index=0;
	while (std::getline(fstream, line))
	{
		std::istringstream line_stream(line);
		std::size_t num;
		int x, y;
		if (!(line_stream >> x)) {
			err_msg();
			return false;
		}
		if (!(line_stream >> y))
		{
			err_msg();
			return false;
		}
		std::vector<std::size_t> vec;
		while (line_stream >> num)
		{
			vec.push_back(num - 1); //1-based to 0-based
		}
		nodes_.emplace_back(std::move(vec), x, y, index);
		++index;
	}
	if (nodes_.size() <= 1)
	{
		err_msg();
		return false;
	}
	auto & base1 = nodes_[0];
	auto & base2 = nodes_[nodes_.size() - 1];
	base1.set_owner(Player::BLUE);
	base1.set_island_type(IslandType::BASE);
	base2.set_owner(Player::RED);
	base2.set_island_type(IslandType::BASE);
	set_random_pointing_to_directions();
	return true;

}

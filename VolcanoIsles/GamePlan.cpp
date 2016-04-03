#include "GamePlan.h"
#include <fstream>
#include <sstream>

void GamePlan::load(std::string filename)
{
	std::ifstream fstream;
	fstream.open(filename);
	std::string line;
	while (std::getline(fstream, line))
	{
		std::istringstream line_stream(line);
		std::size_t num;
		int x, y;
		if (!(line_stream >> x)) {
			err_msg();
			return;
		}
		if (!(line_stream >> y))
		{
			err_msg();
			return;
		}
		std::vector<std::size_t> vec;
		while (line_stream >> num)
		{
			vec.push_back(num - 1); //1-based to 0-based
		}
		auto node = std::make_unique<GameNode>(std::move(vec), x, y);
		nodes_.push_back(std::move(node));
	}
	if (nodes_.size() <= 1)
	{
		err_msg();
		return;
	}
	auto & base1 = nodes_[0];
	auto & base2 = nodes_[nodes_.size() - 1];
	base1->set_owner(PLAYER);
	base1->set_island_type(BASE);
	base2->set_owner(COMPUTER);
	base2->set_island_type(BASE);
	set_random_pointing_to_directions();

}

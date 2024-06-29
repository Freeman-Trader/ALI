
#include "lob-test.hpp"

int main(void)
{
	Brain Ali;

	for (size_t i = 0; i < 100; i++)
	{
			
		Ali.detemineChange();
	}

	std::string input, output;

	input.clear();
	input.append("Hello");

	Ali.followPathway(input, output);

	return 0;
}
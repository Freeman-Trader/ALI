
#include "Brain.hpp"

int main(void)
{
	Brain Ali;
	std::string Input;// = "9+7=";
	std::string desiredOutput;// = "16";
	std::string actualOutput;

	Ali.createDesiredPathway(Input, desiredOutput);

	/*for (int loop = 0; loop < 100; loop++)
	{
		Ali.followPathway(Input, actualOutput);
		std::cout << actualOutput << std::endl;
		actualOutput.clear();
	}*/

	for (int loop1 = 0; loop1 < 10; loop1++)
	{
		std::cout << "Loop: " << loop1 << std::endl;
		for (int loop2 = 0; loop2 <= loop1; loop2++)
		{
			Input = std::to_string(loop1);
			Input += '+';
			Input += std::to_string(loop2);
			//Input += '=';

			int tempInt = 0;
			tempInt = loop1 + loop2;
			desiredOutput = std::to_string(tempInt);

			Ali.createDesiredPathway(Input, desiredOutput);
		}
	}


	while (true)
	{
		std::cin >> Input;
		//Input = "4+3=";

		if (Input == "EXIT")
			return 0;
		
		Ali.followPathway(Input, actualOutput);
		std::cout << actualOutput << std::endl;
		Ali.resetBreakCount(Input);
		actualOutput.clear();
	}

	/*for(int loop = 0; loop < 1000; loop++)
	{
		Ali.createPathway("1+2", "2");
  		Ali.randomizePathway("1+1");
		Ali.followPathway("1+1");
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "------------------------------------------------------------" << std::endl;
	}*/

	return 0;
}
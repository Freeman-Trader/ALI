
#include "./Header Files/Cortex.hpp"

int main(void) {
	Cortex ALI;
    std::string str = "hi";
    
	ALI.train(str, str);

    std::cout << "Input: " << str;
    str = ALI.stimulate(str);
    std::cout << "Output: " << str;

	return 0;
}
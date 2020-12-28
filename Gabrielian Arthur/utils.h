#pragma once
#include <unordered_map>
#include <iostream>

template <typename T>
T proverka(T min, T max)
{
	T value;


	while ((std::cin >> value).fail() || value > max || value < min)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Incorrect value. Choose between (" << min << " - " << max << ")" << std::endl;
	}
	return value;
}

template <typename T>
void proverka2(T& input, std::string inputText)
{
	std::cout << inputText;
	while ((std::cin >> input).fail() || input < 0) {
		std::cout << "Incorrect value. Try again\n";
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	}
}
#pragma once
#include <unordered_map>
#include <iostream>

template <typename T>
T proverka(T min, T max, std::string text1, std::string text2)
{
	T value;

	std::cout << text1;
	while ((std::cin >> value).fail() || value > max || value < min)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << text2 << "Choose between (" << min << " - " << max << ")" << std::endl;
	}
	return value;
}
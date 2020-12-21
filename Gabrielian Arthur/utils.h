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
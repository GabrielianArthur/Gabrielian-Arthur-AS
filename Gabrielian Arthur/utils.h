#pragma once
#include <iostream>

template <typename T>
T proverka(T min, T max, std::string text1, std::string text2)
{
	T value;

	cout << text1;
	while ((cin >> value).fail() || value > max || value < min)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << text2 << "Choose between (" << min << " - " << max << ")" << endl;
	}
	return value;
}
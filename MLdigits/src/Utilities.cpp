/*
 * Utilities.cpp
 *
 *  Created on: Oct 11, 2020
 *      Author: avest
 */

#include "Utilities.hpp"
#include "climits"

std::string getString(unsigned int maxLength){
	std::string str = "";
	do{
		std::cout << "Please enter a string less than " << std::to_string(maxLength) << " characters" << std::endl;
		std::getline(std::cin, str);
		if(str.length() <= maxLength){
			return str;
		} else {
			std::cerr << "Invalid value, please try again" << std::endl;
		}//if/else
	}while(str.length() > maxLength);//do-while
	return "";
}//getString

void clearCin(void){
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
}//clearCin

int getInt(unsigned int min, unsigned int max){
	unsigned int num = 0;
	do{
		std::cout << "Please enter a number between " << std::to_string(min)
			<< " and " << std::to_string(max) << std::endl;
		std::cin >> num;
		clearCin();
		if((num >= min) | (num <= max)){
			return num;
		} else {
			std::cerr << "number out of range, please try again" << std::endl;
		}//if/else
	}while((num < min) || (num > max));//do-while
	return -1;
}//getInt


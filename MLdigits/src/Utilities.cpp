/*
 * Utilities.cpp
 *
 *  Created on: Oct 11, 2020
 *      Author: avest
 */

#include "Utilities.hpp"
#include "climits"
#include <cstring>

//std::string getString(unsigned int maxLength){
//	std::string str = "";
//	do{
//		std::cout << "Please enter a string less than " << std::to_string(maxLength) << " characters" << std::endl;
//		std::getline(std::cin, str);
//		if(str.length() <= maxLength){
//			return str;
//		} else {
//			std::cout << "Invalid value, please try again" << std::endl;
//		}//if/else
//	}while(str.length() > maxLength);//do-while
//	return "";
//}//getString

void clearCin(void){
	std::cin.clear();
	std::cin.ignore(INT_MAX, '\n');
}//clearCin

std::string getString(unsigned int min, unsigned int max) {
	std::string str = "";
	do{
		std::cout << "Please enter a string between " << std::to_string(min) <<
				" and " << std::to_string(max) << std::endl;
		std::getline(std::cin, str);
		if (str.length() < min || str.length() > max) {
			std::cout << "Invalid value, please try again" << std::endl;
		} else {
			const char *Whitespace = " \t\v\r\n";						//checks for, and removes leading/trailing whitespace
			size_t start = str.find_first_not_of(Whitespace);			//..
			size_t end = str.find_last_not_of(Whitespace);				//..
			return start == end ?										//..
					std::string() : str.substr(start, end - start + 1);	//..
		}//if/else
	}while(str.length() < min || str.length() > max);//do-while
	return "";
}//getString

int getInt(unsigned int min, unsigned int max){
	unsigned int num = 0;
	do{
		std::cout  << "Please enter a number between " << std::to_string(min)
			<< " and " << std::to_string(max) << ": ";
		std::cin >> num;
		std::cout << "\n";
		clearCin();
		if((num >= min) && (num <= max)){
			return num;
		} else {
			std::cout << "Invalid value, please try again" << std::endl;
		}//if/else
	}while((num < min) || (num > max));//do-while
	return -1;
}//getInt

char getChar(void) {
	char c_str[32];
	do{
		std::cin.getline(c_str, INT_MAX);
		if (strlen(c_str) > 1) {
			std::cout << "Invalid value, please enter a single character" << std::endl;
		} else {
			return c_str[0];
		}//if/else
	}while(strlen(c_str) > 1);//do-while
	return '0';
}//getChar

bool yn(void) {
	char choice;
	do{
		std::cout << "(y/n)" << std::endl;
		choice = getChar();
		if (toupper(choice) == 'Y') {
			return true;
		} else if (toupper(choice) == 'N') {
			return false;
		} else {
			std::cout << "Invalid input, please try again (y/n)" << std::endl;
		}//if/elif/else
	}while(toupper(choice) != 'Y' && toupper(choice) != 'N');//do-while
	return false;//should never reach
}//yn


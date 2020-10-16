/*
 * Utilities.hpp
 *
 *  Created on: Oct 11, 2020
 *      Author: avest
 */

#ifndef UTILITIES_HPP_
#define UTILITIES_HPP_

#include <iostream>
#include <string>

	//function pre-fix template
	//Desciption:
	//Preconditions:
	//Postconditions:

	//error struct for try/catch blocks
	struct error{
		int errorCode;
		std::string errorMSG;
	};

	//getString
	//Description:		gets a string from the user
	//						that's length is less than or
	//						equal to maxLength. Continues to ask
	//						until value is valid
	//Preconditions:	-maxLength is positive
	//Postconditions:	-a string is returned
	//					-returns "" as default
	//std::string getString(unsigned int maxLength);

	//getString
	//Description:		gets a string from the user
	//						that's length is between a min
	//						and max value. Continues to ask
	//						until value is valid
	//Preconditions:	-max is positive
	//					-min is positive
	//Postconditions:	-a string is returned
	//					-returns "" as default
	//					-leading/trailing whitespace removed
	std::string getString(unsigned int min, unsigned int max);

	//getInt
	//Description:		gets an integer from the user between
	//						the min and max values. Continues to ask
	//						until values are valid
	//Preconditions:	-none
	//Postconditions:	-integer returned
	//					-returns -1 as default
	int getInt(unsigned int min, unsigned int max);

	//clearCin
	//Description:		clears the cin
	//Preconditions:	-cin is not empty
	//Postconditions:	-cin is empty
	void clearCin(void);

	//getChar
	//Desciption:		gets and returns a single character
	//						input from the user
	//Preconditions:	-none
	//Postconditions:	-returns a char
	//					-returns '0' as default
	char getChar(void);

	//function yn
	//Desciption:		gets and returns a char of 'y' or 'n'
	//						from the user
	//Preconditions:	-none
	//Postconditions:	-returns true if y
	//					-false if n
	bool yn(void);

#endif /* UTILITIES_HPP_ */

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

	//getString
	//Description:		gets a string from the user
	//						that's length is less than or
	//						equal to maxLength. Continues to ask
	//						until value is valid
	//Preconditions:	-maxLength is positive
	//Postconditions:	-a string is returned
	//					-returns "" as default
	std::string getString(unsigned int maxLength);

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

#endif /* UTILITIES_HPP_ */

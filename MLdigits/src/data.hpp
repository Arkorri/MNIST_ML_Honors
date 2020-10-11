/*
 * data.hpp
 *
 *  Created on: Oct 10, 2020
 *      Author: avest
 */

#ifndef DATA_HPP_
#define DATA_HPP_
#include <vector>
#include "stdint.h"
#include "stdio.h"

//DATA CLASS
//Description:		An instance of this class holds the element
//						data read from the .idx1 and .idx3 files
//						the feature_vector holds an array of bytes
//						representing pixels. The labels are
//						identifiers that tell the program "what"
//						each piece of data is. i.e. a picture of a
//						"1" or "5".
class data {
public:
	data();
	virtual ~data();

	//set_feature_vector
	//Description:		sets the feature vector containing
	//						an array of bytes(pixels)
	//Precondition:		-none
	//Postconditions:	-feature_vector == argument passed
	void set_feature_vector(std::vector<uint8_t>*);

	//append_to_vector
	//Description:		Appends a byte to the end of the vector
	//Precondition:		-none
	//Postconditions:	-length+=1
	//					-byte appended
	void append_to_vector(uint8_t);

	//set_label
	//Description:		Sets an identifier for the class
	//Preconditions:	-none
	//Postconditions	-label is set
	void set_lable(uint8_t);

	//set_enum_label
	//Description:		Sets an enumerated label
	//Preconditions:	-none
	//Postconditions:	-enum_label set
	void set_enum_label(int);

	//get_feature_vector_size
	//Description:		Returns the length of the array
	//Preconditions:	-none
	//Postconditions:	-length returned
	int get_feature_vector_size();

	//get_label
	//Description:		Returns the label
	//Preconditions:	-none
	//Postconditions	-label returned
	uint8_t get_label();

	//get_enum_label
	//Description:		Returns the enum_label
	//Preconditions:	-none
	//Postconditions	-enum_label returned
	uint8_t get_enum_label();

	//get_feature_vector
	//Description:		Returns the array of bytes
	//Preconditions:	-none
	//Postconditions	-array returned
	std::vector<uint8_t> * get_feature_vector();

private:
	std::vector<uint8_t> * feature_vector;
	uint8_t label;
	int enum_label;

};//data

#endif /* DATA_HPP_ */

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


class data {
public:
	data();
	virtual ~data();

	void set_feature_vector(std::vector<uint8_t>*);
	void append_to_vector(uint8_t);
	void set_lable(uint8_t);
	void set_enum_label(int);

	int get_feature_vector_size();
	uint8_t get_label();
	uint8_t get_enum_label();
	std::vector<uint8_t> * get_feature_vector();

private:
	std::vector<uint8_t> * feature_vector;
	uint8_t label;
	int enum_label;

};//data

#endif /* DATA_HPP_ */

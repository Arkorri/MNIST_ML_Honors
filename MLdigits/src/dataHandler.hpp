/*
 * dataHandler.hpp
 *
 *  Created on: Oct 10, 2020
 *      Author: avest
 */

#ifndef DATAHANDLER_HPP_
#define DATAHANDLER_HPP_

#include <fstream>
#include "stdint.h"
#include "data.hpp"
#include <vector>
#include <string>
#include <map>
#include <unordered_set>

class dataHandler {
public:
	dataHandler();
	virtual ~dataHandler();

	void read_feature_vector(std::string path);
	void read_feature_labels(std::string path);
	void split_data();
	void count_classes();
	void shuffle_data();
	uint32_t convert_to_little_endian(const unsigned char* bytes);
	std::vector<data*> *get_training_data();
	std::vector<data*> *get_test_data();
	std::vector<data*> *get_validation_data();

private:
	std::vector<data *> *data_array;
	std::vector<data *> *training_data;
	std::vector<data *> *test_data;
	std::vector<data *> *validation_data;
	int num_classes;
	int vector_size;
	std::map<uint8_t, int> class_map;

	//used for data splits
	//double represents a % of data to be used for each set of data
	const double TRAINING_SPLIT = 0.75;
	const double TEST_SPLIT = 0.20;
	const double VALIDATION_SPLIT = 0.05;

};//dataHandler

#endif /* DATAHANDLER_HPP_ */

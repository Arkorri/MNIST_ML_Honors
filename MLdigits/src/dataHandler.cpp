/*
 * dataHandler.cpp
 *
 *  Created on: Oct 10, 2020
 *      Author: avest
 */

#include "dataHandler.hpp"
#include <iostream>
#include <ctime>
#include <algorithm>

dataHandler::dataHandler() {
	this->data_array = new std::vector<data *>;
	this->test_data = new std::vector<data *>;
	this->training_data = new std::vector<data *>;
	this->validation_data = new std::vector<data *>;
}//dataHandler

dataHandler::~dataHandler() {
	for(unsigned int i = 0; i < data_array->size(); i++){
		delete data_array->at(i);
	}
	delete this->data_array;
	delete this->test_data;
	delete this->training_data;
	delete this->validation_data;
}//~dataHandler

void dataHandler::read_feature_vector(std::string path){
	uint32_t header[4];// |MAGIC|NUM IMAGES|ROW SIZE|COLUMN SIZE|
	unsigned char bytes[4];
	FILE *file = fopen(path.c_str(), "rb");//read bytes only
	if(file){
		for(unsigned int i = 0; i < 4; i++){
			if(fread(bytes, sizeof(bytes), 1, file)){
				header[i] = convert_to_little_endian(bytes);
			}//if
		}//for
		std::cout << "Finished getting data file header" << std::endl;
		int image_size = header[2]*header[3];//rows * columns
		for(unsigned int i = 0; i < header[1]; i++){
			data *image = new data();
			uint8_t element[1];//need an array for fread to work properly
			for(int j = 0; j < image_size; j++){
				if(fread(element, sizeof(element), 1, file)){
					image->append_to_vector(element[0]);
				} else {
					std::cerr << "Error reading from file in dataHandler.read_feature_vector() \nending program" << std::endl;
					exit(1);
				}//if/else
			}//for
			this->data_array->push_back(image);
		}//for
		std::cout << "Successfully read file and stored data points. " << this->data_array->size() << std::endl;
	} else {
		std::cerr << "Unable to read file in dataHandler.read_feature_vector() \nending program" << std::endl;
		exit(1);
	}//if/else
}//read_feature_vector

void dataHandler::read_feature_labels(std::string path){
uint32_t header[2];// |MAGIC|NUM IMAGES|
	unsigned char bytes[4];
	FILE *file = fopen(path.c_str(), "rb");//read only
	if(file){
		for(unsigned int i = 0; i < 2; i++){
			if(fread(bytes, sizeof(bytes), 1, file)){
				header[i] = convert_to_little_endian(bytes);
			}//if
		}//for
		std::cout << "Finished getting label file header" << std::endl;
		for(unsigned int i = 0; i < header[1]; i++){
			uint8_t element[1];//need an array for fread to work properly
			if(fread(element, sizeof(element), 1, file)){
				this->data_array->at(i)->set_lable(element[0]);
			} else {
				std::cerr << "Error reading from file in dataHandler.read_feature_labels() \n ending program" << std::endl;
				exit(1);
			}//if/else
		}//for
		std::cout << "Successfully read file and stored labels. " << std::endl;
	} else {
		std::cerr << "Unable to read file in dataHandler.read_feature_labels() \n ending program" << std::endl;
		exit(1);
	}//if/else
}//read_feature_labels

void dataHandler::shuffle_data(){
	std::cout << "Shuffling data" << std::endl;
	int size = this->data_array->size();
	srand((unsigned)time(0));
	for(int i = 0; i < size - 1; i++){
		int j = i + ((2*rand()-1) % (size - i));
		if(j==i){
			j+=1;
		}else {
			//nothing
		}//if/else
		data* tempData = data_array->at(j);
		data_array->at(j) = data_array->at(i);
		data_array->at(i) = tempData;
	}//for
	std::cout << "Finished shuffling data" << std::endl;
}//dataHandler

void dataHandler::split_data(){
	std::unordered_set<int> used_indexes;
	int train_size = data_array->size() * this->TRAINING_SPLIT;
	int test_size = data_array->size() * this->TEST_SPLIT + train_size;
	int valid_size = data_array->size() * this->VALIDATION_SPLIT + test_size;
	this->shuffle_data();

	std::cout << "Splitting data" << std::endl;
	//Training data split
	int count = 0;
	while(count < train_size){
		training_data->push_back(data_array->at(count));
		count++;
	}//while
	std::cout << "Training data split successfully" << std::endl;
	std::cout << "Training data size: " << training_data->size() << std::endl;

	//Test data split
	while(count < test_size){
		test_data->push_back(data_array->at(count));
		count++;
	}//while
	std::cout << "Test data split successfully" << std::endl;
	std::cout << "Test data size: " << test_data->size() << std::endl;

	//Validation data split
	while(count < valid_size){
		validation_data->push_back(data_array->at(count));
		count++;
	}//while
	std::cout << "Validation data split successfully" << std::endl;
	std::cout << "Validation data size: " << validation_data->size() << std::endl;
	std::cout << "All splits were successful" << std::endl;
}//split_data

void dataHandler::count_classes(){
	int count = 0;
	for(unsigned int i = 0; i < data_array->size(); i++){
		if(class_map.find(data_array->at(i)->get_label()) == class_map.end()){
			class_map[data_array->at(i)->get_label()] = count;
			data_array->at(i)->set_enum_label(count);
			count++;
		}//if
	}//for
	num_classes = count;
	std::cout << "Successfully found " << num_classes << " unique classes" << std::endl;
}//count_classes

uint32_t dataHandler::convert_to_little_endian(const unsigned char* bytes){
	return(uint32_t) ((bytes[0] << 24) |
			(bytes[1] << 16) |
			(bytes[2] << 8) |
			(bytes[3]));
}

std::vector<data*> *dataHandler::get_training_data(){
	return training_data;
}

std::vector<data*> *dataHandler::get_test_data(){
	return test_data;
}

std::vector<data*> *dataHandler::get_validation_data(){
	return validation_data;
}


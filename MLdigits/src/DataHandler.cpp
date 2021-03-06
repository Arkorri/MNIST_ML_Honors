/*
 * dataHandler.cpp
 *
 *  Created on: Oct 10, 2020
 *      Author: avest
 */

#include <iostream>
#include <ctime>
#include <algorithm>
#include "DataHandler.hpp"

dataHandler::dataHandler() {//initialization of variables
	this->data_array = new std::vector<data *>;
	this->test_data = new std::vector<data *>;
	this->training_data = new std::vector<data *>;
	this->validation_data = new std::vector<data *>;
	this->featurePath = "";
	this->labelPath = "";
	this->num_classes = 0;
	this->loaded = false;
}//dataHandler

dataHandler::~dataHandler() {//de-allocate dynamic memory
	for(unsigned int i = 0; i < data_array->size(); i++){
		delete data_array->at(i);
	}//for
	delete this->data_array;
	delete this->test_data;
	delete this->training_data;
	delete this->validation_data;
}//~dataHandler

bool dataHandler::load(void){
	std::cout << "Loading data into dataHandler" << std::endl;
	if(this->read_feature_vector(featurePath)){
		if(this->read_feature_labels(labelPath)){
			this->split_data();
			this->count_classes();
			this->loaded = true;
			std::cout << "Finished loading" << std::endl;
			return true;
		} else {
			this->unload();
			return false;
		}//if/else
	} else {
		this->unload();
		return false;
	}//if/else
}//load

void dataHandler::unload(void){
	for(int i = data_array->size() - 1; i > -1; i--){
		delete data_array->at(i);
	}//for
	data_array->clear();
	test_data->clear();
	training_data->clear();
	validation_data->clear();
	class_map.clear();
	std::cout << "data has been unloaded" << std::endl;
	this->loaded = false;
}//clear

bool dataHandler::isLoaded(void){
	return this->loaded;
}//isLoaded

bool dataHandler::read_feature_vector(std::string path){
	uint32_t header[4];// |MAGIC|NUM IMAGES|ROW SIZE|COLUMN SIZE|
	unsigned char bytes[4];
	FILE *file = fopen(path.c_str(), "rb");//read bytes only
	if(file){
		for(unsigned int i = 0; i < 4; i++){
			if(fread(bytes, sizeof(bytes), 1, file)){
				if(isIntel){
					header[i] = convert_to_little_endian(bytes);
				} else {
					header[i] = (uint32_t)bytes;
				}//if/else
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
					std::cerr << "Error reading from file in dataHandler.read_feature_vector()" << std::endl;
					return false;
				}//if/else
			}//for
			this->data_array->push_back(image);
		}//for
		std::cout << "Successfully read file and stored data points. " << this->data_array->size() << std::endl;
	} else {
		std::cerr << "Unable to read file in dataHandler.read_feature_vector()" << std::endl;
		return false;
	}//if/else
	return true;
}//read_feature_vector

bool dataHandler::read_feature_labels(std::string path){
uint32_t header[2];// |MAGIC|NUM IMAGES|
	unsigned char bytes[4];
	FILE *file = fopen(path.c_str(), "rb");//read bytes only
	if(file){
		for(unsigned int i = 0; i < 2; i++){
			if(fread(bytes, sizeof(bytes), 1, file)){
				if(isIntel){
					header[i] = convert_to_little_endian(bytes);
				} else {
					header[i] = (uint32_t)bytes;
				}//if/else
			}//if
		}//for
		std::cout << "Finished getting label file header" << std::endl;
		for(unsigned int i = 0; i < header[1]; i++){
			uint8_t element[1];//need an array for fread to work properly
			if(fread(element, sizeof(element), 1, file)){
				this->data_array->at(i)->set_lable(element[0]);
			} else {
				std::cerr << "Error reading from file in dataHandler.read_feature_labels()" << std::endl;
				return false;
			}//if/else
		}//for
		std::cout << "Successfully read file and stored labels. " << std::endl;
	} else {
		std::cerr << "Unable to read file in dataHandler.read_feature_labels()" << std::endl;
		return false;
	}//if/else
	return true;
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
}//convert_to_little_endian

std::vector<data*> *dataHandler::get_training_data(){
	return training_data;
}//get_training_data

std::vector<data*> *dataHandler::get_test_data(){
	return test_data;
}//get_test_data

std::vector<data*> *dataHandler::get_validation_data(){
	return validation_data;
}//get_validation_data

bool dataHandler::setFeaturePath(void){
	std::string extension = ".idx3-ubyte";
	std::string path = "";
	do{
		path = getString(1,64);
		if(path.length() > extension.length()){
			if(0 == path.compare(path.length() - extension.length(), extension.length(), extension)){
				this->featurePath = path;
				return true;
			} else {
				std::cerr << "incorrect file type, please try again (must end in " << extension << ")" << std::endl;
			}//if/else
		}else {
			std::cerr << "incorrect file type, please try again (must end in " << extension << ")" << std::endl;
		}//if/else
	}while(true);//do-while
	return false;
}//setFeaturePath

bool dataHandler::setFeaturePath(std::string path){//overloaded for default
	this->featurePath = path;
	return true;
}//setFeaturePath

bool dataHandler::setLabelPath(void){
	std::string extension = ".idx1-ubyte";
	std::string path = "";
	do{
		path = getString(1,64);
		if(path.length() > extension.length()){
			if(0 == path.compare(path.length() - extension.length(), extension.length(), extension)){
				this->labelPath = path;
				return true;
			} else {
				std::cerr << "incorrect file type, please try again (must end in " << extension << ")" << std::endl;
			}//if/else
		}else {
			std::cerr << "incorrect file type, please try again (must end in " << extension << ")" << std::endl;
		}//if/else
	}while(true);//do-while
	return false;
}//setLabelPath

bool dataHandler::setLabelPath(std::string path){//overloaded for default
	this->labelPath = path;
	return true;
}//setLabelPath

void dataHandler::setIsIntel(bool x){
	this->isIntel = x;
}//setIsIntel


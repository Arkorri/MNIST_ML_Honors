/*
 * data.cpp
 *
 *  Created on: Oct 10, 2020
 *      Author: avest
 */

#include "Data.hpp"

data::data() {
	this->feature_vector = new std::vector<uint8_t>;
}//data

data::~data() {
	delete this->feature_vector;
}//~data


void data::set_feature_vector(std::vector<uint8_t>* vector){
	this->feature_vector = vector;
}//set_feature_vector

void data::append_to_vector(uint8_t byte){
	this->feature_vector->push_back(byte);
}//append_to_vector

void data::set_lable(uint8_t byte){
	this->label = byte;
}//set_label

void data::set_enum_label(int val){
	this->enum_label = val;
}//set_enum_label

int data::get_feature_vector_size(){
	return this->feature_vector->size();
}//get_feature_vector_size

uint8_t data::get_label(){
	return this->label;
}//get_label

uint8_t data::get_enum_label(){
	return this->enum_label;
}//get_enum_label

std::vector<uint8_t> * data::get_feature_vector(){
	return this->feature_vector;
}//get_feature_vector


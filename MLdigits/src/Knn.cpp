/*
 * Knn.cpp
 *
 *  Created on: Oct 13, 2020
 *      Author: avest
 */

#include "Knn.hpp"
#include <cmath>
#include <limits>
#include <map>
#include "stdint.h"
#include <iomanip>


Knn::Knn() {
	this->k = 1;	//default k value
	this->loaded = false;
}//Knn default

Knn::Knn(int k){
	this->k = k;
	this->loaded = false;
}//Knn

Knn::~Knn() {
	//empty
}

bool Knn::load(dataHandler* dh){
	if(dh->isLoaded()){
		this->set_test_data(dh->get_test_data());
		this->set_training_data(dh->get_training_data());
		this->set_validation_data(dh->get_validation_data());
		this->loaded = true;
		std::cout << "Loading data into knn" << std::endl;
		return true;
	} else {
		std::cerr << "Error: attempted to load data with an empty dataHandler" << std::endl;
		this->loaded = false;
		return false;
	}//if/else
}//load

bool Knn::isLoaded(){
	return this->loaded;
}//isLoaded

void Knn::find_knearest(data *query_point){
	neighbors = new std::vector<data *>;
	double min = std::numeric_limits<double>::max();
	double previous_min = min;
	int index = 0;
	for(int i = 0; i < k; i++){
		if(i == 0){
			for(unsigned int j = 0; j < training_data->size(); j++){
				double distance = calc_distance(query_point, training_data->at(j));
				training_data->at(j)->set_distance(distance);
				if(distance < min){
					min = distance;
					index = j;
				}//if
			}//for
			neighbors->push_back(training_data->at(index));
			previous_min = min;
			min = std::numeric_limits<double>::max();
		} else {
			for(unsigned int j = 0; j < training_data->size(); j++){
				double distance = calc_distance(query_point, training_data->at(j));
				training_data->at(j)->set_distance(distance);
				if(distance > previous_min && distance < min){
					min = distance;
					index = j;
				}//if
			}//for
			neighbors->push_back(training_data->at(index));
			previous_min = min;
			min = std::numeric_limits<double>::max();
		}//if/else
	}//for
}//find_knearest

void Knn::set_training_data(std::vector<data *> *split){
	this->training_data = split;
}//set_training_data

void Knn::set_test_data(std::vector<data *> *split){
	this->test_data = split;
}//set_test_data

void Knn::set_validation_data(std::vector<data *> *split){
	this->validation_data = split;
}//set_validation_data

void Knn::set_k(int num){
	if(num > 0){
		this->k = num;
	} else {
		std::cerr << "Invalid value, k must be greater than 0" << std::endl;
	}//if/else
}//set_k

int Knn::predict(){
	std::map<uint8_t, int> class_freq;
	for(unsigned int i = 0; i < neighbors->size(); i++){
		if(class_freq.find(neighbors->at(i)->get_label()) == class_freq.end()){
			class_freq[neighbors->at(i)->get_label()] = 1;
		} else {
			class_freq[neighbors->at(i)->get_label()]++;
		}//if/else
	}//for
	int best = 0;
	int max = 0;
	for(auto kv : class_freq){
		if(kv.second > max){
			max = kv.second;
			best = kv.first;
		}//if
	}//for each
	delete neighbors;
	return best;
}//predict

double Knn::calc_distance(data* query_point, data* input){
	double distance = 0.0;
	if(query_point->get_feature_vector_size() != input->get_feature_vector_size()){
		std::cerr << "feature size mismatch in Knn:calc_distance" << std::endl;
		exit(1);
	}//if
	for(unsigned int i = 0; i < query_point->get_feature_vector_size(); i++){
		//EUCLDIEAN distance formula
		distance += pow(query_point->get_feature_vector()->at(i)-input->get_feature_vector()->at(i), 2);
	}//for
	distance = sqrt(distance);
	return distance;
}//calc_distance

double Knn::validate_performance(){
	if(this->loaded){
		double current_performance = 0.0;
		int count = 0;
		int data_index = 0;
		for(data *query_point : *validation_data){
			find_knearest(query_point);
			int prediction = predict();
			if(prediction == (int)query_point->get_label()){
				count++;
			}//if
			data_index++;
			current_performance = ((double)count*100/(double)data_index);
			std::cout << prediction << "->" << (int)query_point->get_label() << std::endl;
			std::cout << "Performance = " << std::fixed << std::setprecision(3) << current_performance << "%" << "\n"
					<< "Index #" << data_index << "\n" <<std::endl;
		}//for each
		std::cout << "Validation Performance = " << std::fixed << std::setprecision(3) << current_performance
				<< "% When k = " << this->k << std::endl;
		return current_performance;
	} else {
		std::cerr << "Error: attempted to run algorithm without data" << std::endl;
		return -1;
	}//if/else
}//validate_performance

double Knn::test_performance(){
	if(this->loaded){
		double current_performance = 0.0;
		int count = 0;
		int data_index = 0;
		for(data *query_point : *test_data){
			find_knearest(query_point);
			int prediction = predict();
			if(prediction == (int)query_point->get_label()){
				count++;
			}//if
			current_performance = ((double)count*100/(double)data_index);
			std::cout << prediction << "->" << (int)query_point->get_label() << std::endl;
			std::cout << "Performance = " << std::fixed << std::setprecision(3) << current_performance << "%" << "\n"
					<< "Index #" << data_index << "\n" << std::endl;
		}//for each
		std::cout << "Test Performance = " << std::fixed << std::setprecision(3) << current_performance
				<< "% When k = " << this->k << std::endl;
		return current_performance;
	} else {
		std::cerr << "Error: attempted to run algorithm without data" << std::endl;
		return -1;
	}//if/else
}//test_performance

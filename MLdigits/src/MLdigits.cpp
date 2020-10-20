//============================================================================
// Name        : MLdigits.cpp
// Author      : Avery Kempton
// Version     :
// Copyright   : Your copyright notice
// Description : ML program to identifty handwritten digits pulled from MNIST
//============================================================================

#include <iostream>
#include "Data.hpp"
#include "DataHandler.hpp"
#include "Knn.hpp"

int main() {

	dataHandler *dh = new dataHandler();
	Knn *knear = new Knn();
	double performance = 0.0;
	int choice = 0;
//	double best_performance = 0.0;
//	unsigned int best_k = 1;

	do{
		std::cout << "Is your system using an Intel processor?" << std::endl;
		dh->setIsIntel(yn());
		std::cout << "Do you want to use default data or use custom data?" << std::endl;
		std::cout << "1. Default Data (recommended)" << std::endl;
		std::cout << "2. Custom Data" << std::endl;
		choice = getInt(1,2);
		if(choice == 1){
			std::cout << "Using default MNIST data files" << std::endl;
			dh->setFeaturePath("./train-images.idx3-ubyte");	//recommended file
			dh->setLabelPath("./train-labels.idx1-ubyte");		//recommended file
		} else {
			std::cout << "Please enter the image file path" << std::endl;
			dh->setFeaturePath();
			std::cout << "Please enter the label file path" << std::endl;
			dh->setLabelPath();
			std::cout << "Using custom data files" << std::endl;
		}//if/else
	}while(!dh->load());

	std::cout << "\nPlease enter a value for k (recommended between 1-5)" << std::endl;
	choice = getInt(1,99);
	knear->set_k(choice);
	if(knear->load(dh)){
		std::cout << "Running the KNN algorithm with a k of " << choice << "\n" <<std::endl;
		performance = knear->validate_performance();
	}

//	for(unsigned int i = 1; i < 4; i++){
//		if(i == 1){
//			knear->set_k(i);
//			performance = knear->validate_performance();
//			best_performance = performance;
//		} else {
//			knear->set_k(i);
//			performance = knear->validate_performance();
//			if(performance > best_performance){
//				best_performance = performance;
//				best_k = i;
//			}//if
//		}//if/else
//	}//for
//	knear->set_k(best_k);
//	knear->test_performance();

	delete dh;
	delete knear;
	std::cout << "end program" << std::endl;
	return 0;
}//main

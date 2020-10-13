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

int main() {

	dataHandler *dh = new dataHandler();
	std::cout << "Do you want to use default data or use custom data?" << std::endl;
	std::cout << "1. Default Data (recommended)" << std::endl;
	std::cout << "2. Custom Data" << std::endl;
	int choice = getInt(1,2);
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
	dh->load();

	delete dh;
	std::cout << "end program" << std::endl;
	return 0;
}//main

//============================================================================
// Name        : MLdigits.cpp
// Author      : Avery Kempton
// Version     :
// Copyright   : Your copyright notice
// Description : ML program to identifty handwritten digits pulled from MNIST
//============================================================================

#include <iostream>
#include "data.hpp"
#include "dataHandler.hpp"

int main() {

	dataHandler *dh = new dataHandler();
	dh->read_feature_vector("./train-images.idx3-ubyte");
	dh->read_feature_labels("./train-labels.idx1-ubyte");
	dh->split_data();
	dh->count_classes();

	std::cout << "end program" << std::endl;
	return 0;
}//main

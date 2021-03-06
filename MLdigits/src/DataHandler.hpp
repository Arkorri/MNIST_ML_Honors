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
#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include "Data.hpp"
#include "Utilities.hpp"

//DATAHANDLER CLASS
//Description:		This class handles all file operations as well as
//						is responsible for formatting the MNIST data for
//						use. the data_array is an vector of data class objects.

class dataHandler {
public:
	dataHandler();
	virtual ~dataHandler();

	//load
	//Description:		Calls all necessary functions for
	//					reading, converting, and formatting
	//					MNIST data
	//Preconditions:	-feature and label paths have been set
	//Postconditions:	-data read, converted, formatted, and split
	//					-if failed, unloads the data and returns false
	//					-returns true if successful
	bool load(void);

	//clear
	//Descriptions:		Empties data in the class so that
	//						new data can be loaded. (undoes
	//						the load function)
	//Preconditions:	-none
	//Postconditions:	-vectors, and map were emptied
	//					-does not clear the set paths
	void unload(void);

	//isLoaded
	//Descriptions:		returns a true or false depending on if
	//						the class has data loaded
	//Preconditions:	-none
	//Postconditions:	-none
	bool isLoaded(void);

	//read_feature_vector
	//Description:		reads a .idx3-ubyte file into an
	//						array holding data
	//Preconditions:	-provided path/file must exist
	//					-files MUST be in the same format as listed
	//						on the MNIST website
	//Postconditions:	-reads data into the data class
	//					-puts the data class into the data_array
	//					-input file is not altered
	//					-returns true if successful, false otherwise
	bool read_feature_vector(std::string path);

	//read_featire_labels
	//Description:		reads a .idx1-ubyte file into an
	//						array holding data
	//Preconditions:	-provided path/file must exist
	//					-files MUST be in the same format as listed
	//						on the MNIST website
	//Postconditions:	-updates the array_data with proper labels
	//					-input file is not altered
	//					-returns true if successful, false otherwise
	bool read_feature_labels(std::string path);

	//split_data
	//Description:		Splits the data into the training_data,
	//						test_data, and validation_data classes. Split
	//						percentages are determined by TRAINING_SPLIT,
	//						TEST_SPLIT, VALIDATION_SPLIT
	//Preconditions:	-data_array is not empty
	//					-TRAINING_SPLIT, TEST_SPLIT, and VALIDATION_SPLIT
	//						contain values between 0.0 and 1.0 that add
	//						up to 1.0
	//Postconditions:	-training_data, test_data, and validation_data are
	//						populated based on split percentages
	//					-data_array is shuffled
	void split_data();

	//count_classes
	//Description:		Determines how many different "classes" of data
	//						exist in the data_array
	//Preconditions:	-data_array is not empty
	//Postconditions:	-populates a map containing 1 data point from
	//						each class of data
	void count_classes();

	//shuffle_data
	//Description:		shuffles the data_array into a random order
	//Preconditions:	-data_array contains at least 2 values
	//Postconditions:	-data_array is randomized
	void shuffle_data();

	//convert_to_little_endian
	//Description:		converts big endian data into little endian
	//						data. This must be done for Intel
	//						processors because Intel uses
	//						little endian values
	//Preconditions:	-Data was read successfully
	//Postconditions:	-header data converted into little
	//						endian format
	uint32_t convert_to_little_endian(const unsigned char* bytes);

	//get_training_data
	//Description:		return the training_data array
	//Preconditions:	-none
	//Postconditions	-returned array successfully
	std::vector<data*> *get_training_data();

	//get_test_data
	//Description:		return the test_data array
	//Preconditions:	-none
	//Postconditions	-returned array successfully
	std::vector<data*> *get_test_data();

	//get_validation_data
	//Description:		return the validation_data array
	//Preconditions:	-none
	//Postconditions	-returned array successfully
	std::vector<data*> *get_validation_data();

	//setFeatuePath
	//Description:		sets the path to the image file
	//						and verifies file format
	//Preconditions:	-none
	//Postconditions:	-image file path is set and verified
	//					-returns true if successful, false if not
	bool setFeaturePath(void);

	//setLabelPath
	//Description:		sets the path to the label file
	//						and verifies file format
	//Preconditions:	-none
	//Postconditions:	-label file path is set and verified
	//					-returns true if successful, false if not
	bool setLabelPath(void);

	//setFeatuePath (overload)
	//Description:		sets the path to the image file
	//						and verifies file format.
	//						This overloaded version does not
	//						take user input and instead uses
	//						default values
	//Preconditions:	-none
	//Postconditions:	-image file path is set and verified
	//					-returns true if successful, false if not
	bool setFeaturePath(std::string);

	//setLabelPath (overload)
	//Description:		sets the path to the label file
	//						and verifies file format.
	//						This overloaded version does not
	//						take user input and instead uses
	//						default values
	//Preconditions:	-none
	//Postconditions:	-label file path is set and verified
	//					-returns true if successful, false if not
	bool setLabelPath(std::string);

	//setIsIntel
	//Desciption:		sets weather the system is using intel or not
	//Preconditions:	-none
	//Postconditions:	-isIntel is set as true or false
	void setIsIntel(bool);

private:
	std::vector<data *> *data_array;		//array holding all data from the file
	std::vector<data *> *training_data;		//array holding a portion of data_array
	std::vector<data *> *test_data;			//array holding a portion of data_array
	std::vector<data *> *validation_data;	//array holding a portion of data_array
	int num_classes;						//identifies how many different classes there are
	//int vector_size;
	std::map<uint8_t, int> class_map;		//
	std::string featurePath;				//directory path for the file holding class data
	std::string labelPath;					//directory path for the file holding class names
	bool loaded;							//keeps track of if the class is holding data
	bool isIntel;							//keeps track of if the system is using an Intel processor

	//used for data splits
	//double represents a % of data to be used for each set of data
	const double TRAINING_SPLIT = 0.75;
	const double TEST_SPLIT = 0.20;
	const double VALIDATION_SPLIT = 0.05;

};//dataHandler

#endif /* DATAHANDLER_HPP_ */

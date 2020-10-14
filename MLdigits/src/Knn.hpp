/*
 * Knn.hpp
 *
 *  Created on: Oct 13, 2020
 *      Author: avest
 */

#ifndef KNN_HPP_
#define KNN_HPP_

#include <vector>
#include "data.hpp"
#include "dataHandler.hpp"

class Knn {
public:
	Knn();
	Knn(int);
	virtual ~Knn();

	//load
	//Description:		calls all functions necessary to load
	//						feature data into the knn class
	//Preconditions:	-DataHandler.load() has been called
	//					-DataHandler.isLoaded returns true
	//Postconditions:	-vectors initialized
	//					-returns true if successful, false otherwise
	bool load(dataHandler*);

	//Descriptions:		returns a true or false depending on if
	//						the class has data loaded
	//Preconditions:	-none
	//Postconditions:	-none
	bool isLoaded();

	//find_knearest
	//Description:		finds the k nearest points to
	//						any given query_point
	//Preconditions:	-load as been called
	//Postconditions:	-nearest neighbors set for query_point
	void find_knearest(data *query_point);

	//set_training_data
	//Description:		sets the training_data recieved from
	//						DataHandler
	//Preconditions:	-DataHandler.load() has been called
	//Postconditions:	-training_data initialized
	void set_training_data(std::vector<data *> *split);

	//set_test_data
	//Description:		sets the test_data recieved from
	//						DataHandler
	//Preconditions:	-DataHandler.load() has been called
	//Postconditions:	-test_data initialized
	void set_test_data(std::vector<data *> *split);

	//set_validation_data
	//Description:		sets the validation_data recieved from
	//						DataHandler
	//Preconditions:	-DataHandler.load() has been called
	//Postconditions:	-validation_data initialized
	void set_validation_data(std::vector<data *> *split);

	//set_k
	//Description:		sets the k value
	//Preconditions:	-none
	//Postconditions	-k = num
	void set_k(int num);

	//predict
	//Description:		analyzes the nearest neighbors for
	//						any point and determines what
	//						class the data belongs to
	//Preconditions:	-find_knearest has been called
	//Postconditions:	-returns a guess of the data's label
	int predict();

	//calc_distance
	//Description:		calculates distance between two data points
	//						using the euclidean formula
	//Preconditions:	-load as been called
	//Postconditions:	-distance is returned
	double calc_distance(data* query_point, data* input);

	//validate_performance
	//Description:		goes through the validation_data and
	//						runs the knearest and predict functions
	//						to guess and calculate accuracy
	//Preconditions:	-load as been called and was successful
	//Postconditions:	-the final performance % is returned
	double validate_performance();

	//test_performance
	//Description:		goes through the test_data and
	//						runs the knearest and predict functions
	//						to guess and calculate accuracy. This
	//						function is intended to be run after
	//						a desirable % is returned from
	//						validate_performance. However, this is not
	//						necessary
	//Preconditions:	-load as been called and was successful
	//Postconditions:	-the final performance % is returned
	double test_performance();

private:
	int k;									//value to be used for KNN
	std::vector<data* > *neighbors;			//holds the k nearest neighbors to a data point
	std::vector<data *> *training_data;		//holds data passed from DataHandler
	std::vector<data *> *test_data;			//holds data passed from DataHandler
	std::vector<data *> *validation_data;	//holds data passed from DataHandler
	bool loaded;							//keeps track of if data was loaded
};//Knn

#endif /* KNN_HPP_ */

# MNIST_ML_Honors
##### CS20 LPC. ML program using the MNIST database to identify handwritten digits 0-9 written in C++ using the Eclipse IDE

**Developement System Specs**\
Microsoft Windows 10\
x64-based PC\
16.0 GB memory\
Intel(R) Core(TM) i7-10710U CPU @ 1.10GHz, 1608 Mhz, 6 Core(s), 12 Logical Processor(s)

## How to download
**Releases**\
-The source.zip file located in each release contains all necessary code and files.\
-If you are using eclipse, the zip file can be **imported** as an **existing project**

## How to use the provided main
**1. On program start it will ask if you are using an Intel processor, reply with a 'y' or 'n'**\
\
**2. It will then ask if you want to use custom data, or provided MNIST data**\
-It is highly recommended to use the provided data\
-If you want to use custom data, when the prompts you for the path you must input the full path starting from the directory in which the .exe is called\
-Custom file(s) must also have the extension idx3-ubyte (for image files) or idx1-ubyte (for label files)\
\
**2. Input the desired K value when prompted**\
-Note: higher k values substantially increase program runtime
## How to use the DataHandler and Knn classes
-Required preprocessor commands\
**#include "Data.hpp"**\
**#include "DataHandler.hpp"**\
**#include "Knn.hpp"**\
-Data.hpp requires no programmer or user interaction\
-Note: most functions are handled by the classes themselves\
\
**1. Create a new DataHandler object**\
\
**2. Use the DataHandler setIsIntel(bool) function to say whether or not an Intel processor is being used**\
\
**3. Set the file paths using the DataHandler setLabelPath(string) and setFeaturePath(string) function**\
-Paths must be defined from the location in which the program was launched\
-i.e. if launching from eclipse with the files in the project folder ("./filename")\
\
**4. Load the data with the DataHandler load() function**\
-This will return true if the load was successful, or false if it failed\
-If the load failed, the class will automatically unload data\
\
**5. Create a new Knn object**\
-This can be done with the default constructor, or can be given a k value by passing an integer\
-If the default constructor was called you must first call Knn->set_k(int) before step 5\
\
**6. Call the Knn .load(DataHandler) function by passing it a pointer to the previously created DataHandler object**\
-This will return true if successfull, or false if the load failed\
\
**7. You can now call the Knn validate_performance() and test_performance() functions**\
-These will run the algorithm and print results to the console.\
-After they finish they will return a double containing the overall performance as a percent\
-These functions take a long time to complete\
\
**8. If you wish to input new data into the classes you must call the unload() function for each object first**

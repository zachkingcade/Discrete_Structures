#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "Matrix.h"

int main() {
    std::string choice;
    int n,friends, numNames;

    srand(time(NULL));

	//open in and out file streams
    std::ofstream out;
    std::cout << "Name of the input file to make?\n";
    std::cin >> choice;
    out.open(choice);

	//file with a list of random names and a number at the top
	//detailing how many names are in the file
	std::ifstream names;
	names.open("Names.dat");

	//load up our options of names into an array for use later
	names >> numNames;
	std::string nameOptions[numNames];
	for (int i = 0; i < numNames; i++){
		names >> nameOptions[i];
	}

	//number of data sets between 4 and 10
    n = (rand() % 7) + 4;
    out << n << '\n';

	//for the number of data sets
	for (int i = 0; i < n; i++){
		//determine how many friends we have for this data set
		friends = (rand() % 5) + 3;
		//list number of friends
		out << friends << std::endl;

		//decide our "friends" names
		for (int j = 0; j < friends; j++){
			out << nameOptions[(rand() % numNames)] << ' ';
		}
		out << std::endl;

		//create our relationship matrix
		Matrix data(friends,friends);
		//load our relationship matrix with a sentinal value
		for (int j =0; j < friends; j++){
			for (int k = 0; k < friends; k++){
				data[j][k] = -1;
			}
		}

		//run through and decide who is friends and who is not
		for (int j =0; j < friends; j++){
			for (int k = 0; k < friends; k++){
				//make sure they know themselves
				if (j == k){
					data[j][k] = 1;
					//if a relationship status has not been decided give it a random value
				}else if (data[j][k] == -1){
					data[j][k] = data[k][j] = (rand() % 2);
				}
			}
		}

		//finally print our resulting data
		out << data << std::endl;
	}

	//close our in and out file streams
	names.close();
	out.close();
}
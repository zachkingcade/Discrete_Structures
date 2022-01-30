/*
Name: Zachary Kingcade
Date: 12/1/19
Assignment: Discrete Program 04
Purpose: To learn how to solve a problem using a graph
*/

//----------PreCompiler Directives----------
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Matrix.h"

//----------Prototypes----------
//Function to open input and output files
void openStreams(std::ifstream &infile, std::ofstream &outfile);
//function to check weather the user would like to process another file
bool anotherFile();
//Function to read a graph
void readInData (std::ifstream &infile, Matrix &Storage, std::vector <std::string> &names);
//Function to determine introductions
void processFriendMatrix(std::ofstream &outfile, Matrix Storage, std::vector <std::string>names);
//prints the header for the outfile
void printHeader(std::ofstream &outfile, Matrix Storage, std::vector <std::string>names, int setNumber);


//----------Main Program----------
int main() {
	int dataSets, numFriends;
	bool run = true;

	while(run){
		std::ifstream infile;
		std::ofstream outfile;
		openStreams(infile, outfile);

		//print header
		outfile << "Zachary Kingcade\nDiscrete Program 04\n";

		//read in the number of "Friends" we are processing
		infile >> dataSets;

		//---read in our data---
		for (int set = 0; set < dataSets; set++){
			//vector to store friends names
			std::vector <std::string>names;
			//read in number of friends we have
			infile >> numFriends;
			//create our Matrix
			Matrix relations(numFriends,numFriends);

			//read in our data
			readInData(infile,relations,names);

			//print header
			printHeader(outfile, relations, names, set);

			//process data
			processFriendMatrix(outfile, relations, names);

			//create break between data sets
			outfile << std::endl;

		}


		//make sure to close our streams
		infile.close();
		outfile.close();

		//check if they would like to process another file
		run = anotherFile();
}

} //-----end of main-----

//Name: Open Streams
//Input: the stream to be opened one input to file the other output to file
//Purpose: Function to open input and output files
void openStreams(std::ifstream &infile, std::ofstream &outfile){
	std::string choice;

	std::cout << "What file would you like to input data from?\n";
	std::cin >> choice;
	infile.open(choice);

	std::cout << "What would you like to name your file to output data to?\n";
	std::cin >> choice;
	outfile.open(choice);
}//-----end of openStream-----

//Name: another file
//output: a bool telling waether or not to run the loop again
//Purpose: function to check weather the user would like to process another file
bool anotherFile(){
	bool result;
    bool valid;
    std::string loopChoice;
    while(valid == false){
        std::cout << "would you like to process another input file?\n";
        std::cin >> loopChoice;
        if (loopChoice == "yes" || loopChoice  == "Yes" || loopChoice  == "YES"){
            result = true;
            valid = true;
        } else if (loopChoice  == "no" || loopChoice  == "No" || loopChoice  == "NO"){
            result = false;
            valid = true;
        } else {
            std::cout << "Error: Invalid Input, Please try Again:\n";
        }
    }
    return result;
}//----end of anotherFile()-----

//Name: read in data
//input: stream to read in data from and matrix to store read in data to,
//vector to put friends names into
//Function to read a graph
void readInData (std::ifstream &infile, Matrix &Storage, std::vector <std::string> &names){
	std::string tempName;
	int mSize = Storage.checkRows();
	//read in the names of our friends
	for(int i = 0; i < mSize; i++){
		infile >> tempName;
		names.push_back(tempName);
	}

	//read in our data
	for(int i = 0; i < mSize; i++){
		for(int j = 0; j < mSize; j++){
			infile >> Storage[i][j];
		}
	}
}//-----end of readInData()-----

//Name: process friend matrix
//Function to determine introductions; determines what introdutions to make to complete the gragh
//and then prints the introductions to the passed in outfile stream
void processFriendMatrix(std::ofstream &outfile, Matrix Storage, std::vector <std::string>names){
	int mSize = Storage.checkRows();

	//-----process data and print------
	for(int i = 0; i < mSize; i++){
		for(int j = 0; j < mSize; j++){
			if (i != j && Storage[i][j] == 0){
				//print that they need to be Introduced
				outfile << names[i] << " and " << names[j] << std::endl;
				//"introduce" them so we don't reprint the need to do so
				Storage[i][j] = Storage[j][i] = 1;
			}
		}
	}
}

//Name: print header
//Purpose: printes the header info and a the friend ship matrix used
void printHeader(std::ofstream &outfile, Matrix Storage, std::vector <std::string>names, int setNumber){
	//--pre-process info & header print--
	outfile << "Acquaintance Graph " << setNumber << ": " << Storage.checkRows() << "Friends: \n";
	for(int i = 0; i < Storage.checkRows(); i++){
		outfile << names[i] << ", ";
	}
	outfile << std::endl << Storage << std::endl;
	outfile << "Introductions to be made:\n";
}
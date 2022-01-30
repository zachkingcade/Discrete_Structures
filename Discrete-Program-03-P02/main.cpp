/*----------------------------------------
Name: Zachary Kingcade
Date:11/12/19
Purpose: This is the refined version of the "Sieve of
Eratosthen". It calculates the prime numbers between 2 and
a given number and outputs both the time this version the
algorithm took and the results
----------------------------------------*/
#include<iostream>
#include<cstdio>
#include<ctime>
#include<vector>
#include<fstream>

/*--------------------Changes Made from Original--------------------
+Changed from array to vector implementation
+no longer a need to process 0 and 1
+deleteing an element is faster then assigning it to 0
+no longer a need to run thru data structure to figure out number of
primes, vector simply keeps track of its size and what ever its size
is how many primes there are
+added 2 to set first then only loaded up odd numbers as primes cant
be even
+because vector internally use jumps over erased data until it resizes
it dosen't have to compare against the previous data like program 1 did
--------------------------------------------------------------------*/

int main() {
    //our varibles used to calculate run time of the Algorithm
    std::clock_t start;
    double duration;
    start = std::clock();
    
    //--------------------Algorithm--------------------
    //in this program we will be hard coding the size of our data 
    //set, for the sequence to work the set must start at 2
    int setEnd = 100000;
    std::ofstream out;
    out.open("P1_Output04.txt");

    //header for our outfile
    out << "Zach kingcade\nDiscrete Program 03 Output\n\n";

    //changed from array to vector
    std::vector <int>Storage;

    //Create our vector and load it will our data set
    Storage.push_back(2);
    for (int i = 3; i < setEnd; i += 2){
        Storage.push_back(i);
    }

    //Loop Logic: we run thru our data set deleting things divisible by the
    //number our loop is currently checking for. so i is the number we are 
    //checking against every other number in the loop and j is what we use to
    //check between i (not include i of coarse) and the end of our data set. 
    //we delete things that are divisable by i as they cannot be prime
    for (int i = 0; i < Storage.size(); i++){
        for (int j = i + 1; j < Storage.size(); j++){
            if(Storage[j]%Storage[i] == 0){
                Storage.erase(Storage.begin() + j);
            }
        }
    }

    //output our results
    out << "There are " << Storage.size() << " primes between 2 and " << setEnd << std::endl;
    //out << "They are: " << '\n';
    //for (int i = 0; i < Storage.size(); i++){
    //    out << Storage[i] << "\n";
    //}

    //here we display the time it took to run
    duration = ( std::clock() -start ) / (double) CLOCKS_PER_SEC;
    out << "Algorithm runtime: "<< duration << std::endl;}
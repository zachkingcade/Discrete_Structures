/*----------------------------------------
Name: Zachary Kingcade
Date:11/12/19
Discrete Program 03 - version 01
Purpose: This is the brute force version of the "Sieve of
Eratosthen". It calculates the prime numbers between 2 and
a given number and outputs both the time this version the
algorithm took and the results
----------------------------------------*/

#include<iostream>
#include<cstdio>
#include<ctime>
#include<vector>
#include<fstream>

int main() {
    //our varibles used to calculate run time of the Algorithm
    std::clock_t start;
    double duration;
    start = std::clock();
    
    //--------------------Algorithm--------------------
    //in this program we will be hard coding the size of our data 
    //set, for the sequence to work the set must start at 2
    int setStart = 2;
    int setEnd = 50000;
    int primeNum = 0;
    std::ofstream out;
    out.open("P1_Output03.txt");

    //header for our outfile
    out << "Zach kingcade\nDiscrete Program 03 Output\n\n";

    //we do setEnd + 1 so we can hold 0 thru setEnd without having to do -1 everytime
    //we would have to do that if we just set 0=1,1=2,2=3......
    //named Storage because I may not end up using a array in the end and
    //this makes it so less has to be gone back and changed
    int Storage[setEnd + 1];

    //load our array set 1 and 0--------------------------------------------
    for (int i = 0; i <= setEnd; i++){Storage[i] = i;}
    //make 0 and 1 = -1 since they are not prime numbers
    Storage[0] = -1;
    Storage[1] = -1;

    //Loop Logic: we run thru our data set setting elements to one when their 
    //divisible by the number our loop is currently on/checking for. so i is 
    //the numger we are checking against every other number in the loop
    //and j is what we used to check between i (not including i of coarse) 
    //and the end of our data set. we set things divisible by i to be -1 to
    //mark them as not prime
    for (int i = 2; i <= setEnd; i++){
        if (Storage[i] != -1){
            for (int j = i + 1; j <= setEnd; j++){
                if(Storage[j] % Storage[i] == 0){
                    Storage[j] = -1;
                }
            }
        }
    }

    //sum up the amount of primes
    for (int i = 0; i < setEnd; i++){
        if (Storage[i] != -1){
            primeNum++;
        }
    }

    //output our results
    out << "There are " << primeNum << " primes between 2 and " << setEnd << std::endl;
    //out << "They are: " << '\n';
    //for (int i = 0; i <= setEnd; i++){
    //    if (Storage[i] != -1){
    //        out << Storage[i] << "\n";
    //    }
    //}

    //here we display the time in scientific notation
    duration = ( std::clock() -start ) / (double) CLOCKS_PER_SEC;
    out << "Algorithm runtime: "<< duration << std::endl;}
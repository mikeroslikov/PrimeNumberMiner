#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <ctime>
#include <stdlib.h>


using namespace std;



int main() {
    //Previos prime number to see the distribution
    unsigned int prevPrime = 0;
    //current prime number
    unsigned int prime = 0;



    ofstream file_prime_distribution("prime_distribution.txt");
    ofstream file_primes("primes.txt");

    //The roof of the prime number search
    unsigned int prime_max  = 1000;


    cout << "Roof of prime number search range? (-1 to exit)\n";
    cin >> prime_max;

    //Record current time to see the duration
    time_t start_milli;
    time(&start_milli);


    //Don't proceed if file's aren't open, this avoids disaster
    if (file_prime_distribution.is_open() && file_primes.is_open()) {
        //Even numbers aren't prime number, except 2
        for (unsigned int i = 1; i < prime_max+1; i+=1) {
            //record the amount of divisors
            unsigned int divisors = 2;
            //check each number lower to see if it is a factor, except if you pass the halfway point
            for (unsigned int j = 2; j < ((i/2) + 2); j++) {
                if (i % j == 0) {
                    divisors++;
                    //If we already know it is a prime, just end the cycle
                    if (divisors > 2) j=i;
                }
            }
            //See if number is a prime
            if (divisors < 3) { //Because prime numbers divide into 1 and themselves
                prevPrime = prime;
                prime = i;
                cout << prime << "\n";
                //record into file
                file_prime_distribution << (prime - prevPrime) << "\n";
                file_primes << prime << "\n";
            }
        }
    } else {
        cout << "Unable to open file.";
    }

    //Don't forget to close your files, kids
    file_prime_distribution.close();
    file_primes.close();

    //record the current time
    time_t now;
    time(&now);
    //calculate duration
    double duration = difftime(now,start_milli);
    //inform user of duration
    cout << "Duration: " << duration << "\n";

    //press any key to continue
    system("pause");

    return 0;
}
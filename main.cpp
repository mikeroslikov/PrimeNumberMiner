#include <iostream>
#include <fstream>
#include <thread>
#include <stdlib.h>
#include "omp.h"


using namespace std;

inline bool IsPrime( int64_t number ) {
    if ( ( (!(number & 1)) && number != 2 ) || (number < 2) || (number % 3 == 0 && number != 3) )
        return (false);

    for( int64_t k = 1; 36*k*k-12*k < number;++k)
        if ( (number % (6*k+1) == 0) || (number % (6*k-1) == 0) )
            return (false);
    return true;
}


int main() {
    //Amount of primes found
    int64_t prime_count = 0;
    //Previous prime number to see the distribution
    int64_t prevPrime = 0;
    //current prime number
    int64_t prime = 0;



    ofstream file_prime_distribution("prime_distribution.txt");
    ofstream file_primes("primes.txt");

    //The roof of the prime number search
    int64_t prime_max  = 1000;


    cout << "Roof of prime number search range? (-1 to exit)\n";
    cin >> prime_max;

    if (prime_max == -1)
        return 0;

    //The floor of the prime number search
    int64_t prime_min  = 1;


    cout << "Floor of prime number search range?\n";
    cin >> prime_min;

    //Record current time to see the duration
    time_t start;
    time(&start);


    //Don't proceed if file's aren't open, this avoids disaster
    if (file_prime_distribution.is_open() && file_primes.is_open()) {
        //Even numbers aren't prime number, except 2
        #pragma omp parallel for reduction (+:prime_count)
        for (int64_t i = prime_min; i < prime_max+1; i+=1) {
            if (i % 1000000 == 0) { // every 1,000,000 prime checks print out status
            cout << "Prime Checks: " << i  << "\nNumber: " << prime_count << "\nValue: " << prime << "\nTime: " << difftime(time(0), start)/60.00 <<  " min\n\n";
        }
            //See if number is a prime
            if (IsPrime(i)) {
                ++prime_count;
                prevPrime = prime;
                prime = i;

                //record into file
                file_prime_distribution << endl <<(prime - prevPrime) << ";" << difftime(time(0), start);
                file_primes << "\n" << prime;
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

    //inform user of duration
    cout << "Duration: " << difftime(time(0), start)/60.00 <<  " min\n";

    //press any key to continue
    system("pause");

    return 0;
}
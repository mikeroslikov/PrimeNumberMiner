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

    //Record current time to see the duration
    time_t start;
    time(&start);


    //Don't proceed if file's aren't open, this avoids disaster
    if (file_prime_distribution.is_open() && file_primes.is_open()) {
        //Even numbers aren't prime number, except 2
        #pragma omp parallel for
        for (int64_t i = 1; i < prime_max+1; i+=1) {

            //See if number is a prime
            if (IsPrime(i)) {
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

    //inform user of duration
    cout << "Duration: " << difftime(time(0), start)/60.00 <<  " min\n";

    //press any key to continue
    system("pause");

    return 0;
}
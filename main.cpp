#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <ctime>
#include <stdlib.h>


using namespace std;

int main() {
    unsigned int prevPrime = 0;
    unsigned int prime = 0;



    ofstream file_prime_distribution("prime_distribution.txt");
    ofstream file_primes("primes.txt");

    unsigned int prime_max  = 1000;


    cout << "Roof of prime number search range? (-1 to exit)\n";
    cin >> prime_max;
    time_t start_milli;
    time(&start_milli);

    if (file_prime_distribution.is_open() && file_primes.is_open()) {
        for (unsigned int i = 1; i < prime_max+1; i+=1) {
            unsigned int divisors = 0;
            //cout << "Testing for Prime: " << i << "------------------------------------\n";
            for (unsigned int j = 1; j < i + 1; j++) {
                if (i % j == 0) {
                    //cout << "Found new divisor: " << j << "\n";
                    divisors++;
                    if (divisors > 2) j=i;
                }
            }
            if (divisors < 3) { //Because prime numbers divide into 1 and themselves
                prevPrime = prime;
                prime = i;
                cout << prime << "\n";
                file_prime_distribution << (prime - prevPrime) << "\n";
                file_primes << prime << "\n";
            }
        }
    } else {
        cout << "Unable to open file.";
    }

    file_prime_distribution.close();
    file_primes;

    time_t now;
    time(&now);

    double duration = difftime(now,start_milli);

    cout << "Duration: " << duration << "\n";

    system("pause");

    return 0;
}
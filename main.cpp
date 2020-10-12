#include <chrono>

#include <iostream>

#include <vector>
#include <map>
using namespace std;



map<int, bool> pf_generate_odd_non_prime_map(int pMaxOddNumberN) {

    map<int, bool> retNonPrimeOddNumberMap;
    int iFirstOddNumber = 3;
    int iSpaceBetweenOddNumber = 2;

    for (int c = iFirstOddNumber; c < 3+(2*(pMaxOddNumberN-1)); c += iSpaceBetweenOddNumber) {
        retNonPrimeOddNumberMap[c] = false;
    }

    int iNonPrimeOdd = 9;
    int iStartingNonPrimeOdd = 9;
    int iInitialDiff = 6;
    int iDiff = 6;
    int iDiffIncrement = 4;

    do {

        if (retNonPrimeOddNumberMap.count(iNonPrimeOdd) == 0) {
            iStartingNonPrimeOdd += iInitialDiff;
            iNonPrimeOdd = iStartingNonPrimeOdd;
            iDiff += iDiffIncrement;
        } else {
            retNonPrimeOddNumberMap[iNonPrimeOdd] = true;
            iNonPrimeOdd += iDiff;
        }

    } while(retNonPrimeOddNumberMap.count(iStartingNonPrimeOdd) != 0);

    return retNonPrimeOddNumberMap;
}

vector<int> pf_generate_odd_prime_list(int pMaxOddNumberN) {

    map<int, bool> oddNonPrimeMap = pf_generate_odd_non_prime_map(pMaxOddNumberN);
    vector<int> retPrimeList;

    for(map<int, bool>::iterator it = oddNonPrimeMap.begin(); it != oddNonPrimeMap.end(); ++it) {
        if (it->second == 0) {
            retPrimeList.insert(retPrimeList.end(), it->first);
        }
    }

    return retPrimeList;
}

vector<int> pf_generate_prime_list(int pMaxOddNumberN) {
    vector<int> oretPrimeList = pf_generate_odd_prime_list(pMaxOddNumberN);
    // Only even prime number is 2, insert at beginning of vector list
    oretPrimeList.insert(oretPrimeList.begin(), 2);
    return oretPrimeList;
}

void print_prime_numbers() {
    map<int, bool> nonPrimeOddMap = pf_generate_odd_non_prime_map(5000);
    for(map<int, bool>::iterator it = nonPrimeOddMap.begin(); it != nonPrimeOddMap.end(); ++it) {
        cout << it->first << " " << (it->second ? "Not Prime" : "Prime") << endl;
    }
    vector<int> primeList = pf_generate_prime_list(5000);

    cout << "Prime Number List: " << endl;
    for (int i = 0; i < primeList.size(); ++i) {
        if (i < primeList.size() - 1)
            cout << primeList[i] << ",";
        else
            cout << primeList[i];
    }
}

// https://stackoverflow.com/questions/2808398/easily-measure-elapsed-time
void time_generation_of_prime_numbers() {

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    pf_generate_prime_list(10000);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

}

int main()
{

    time_generation_of_prime_numbers();
    return 0;
}

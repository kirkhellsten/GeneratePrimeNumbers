#include <chrono>

#include <iostream>

#include <vector>
#include <map>
using namespace std;



map<int, bool> pf_generate_odd_composite_map(int pMaxOddNumber) {

    map<int, bool> retNonPrimeOddNumberMap;
    int iFirstOddNumber = 3;
    int iSpaceBetweenOddNumber = 2;


    for (int c = iFirstOddNumber; c <= pMaxOddNumber; c += iSpaceBetweenOddNumber) {
        retNonPrimeOddNumberMap[c] = false;
    }


    int iNonPrimeOdd = 9;
    int iStartingNonPrimeOdd = 9;
    int iInitialDiff = 6;
    int iDiff = 6;
    int iDiffIncrement = 4;

    do {

        if (iNonPrimeOdd > pMaxOddNumber) {

            iStartingNonPrimeOdd += iInitialDiff;

            if (iStartingNonPrimeOdd > pMaxOddNumber) break;

            iNonPrimeOdd = iStartingNonPrimeOdd;
            iDiff += iDiffIncrement;

        } else {
            retNonPrimeOddNumberMap[iNonPrimeOdd] = true;
            iNonPrimeOdd += iDiff;
        }

    } while(true);

    return retNonPrimeOddNumberMap;
}

vector<int> pf_generate_prime_list(int pMaxOddNumber) {

    map<int, bool> oIsCompositeNumberList;
    int iFirstOddNumber = 3;
    int iSpaceBetweenOddNumber = 2;


    for (int c = iFirstOddNumber; c <= pMaxOddNumber; c += iSpaceBetweenOddNumber) {
        oIsCompositeNumberList[c] = false;
    }


    int iNonPrimeOdd = 9;
    int iStartingNonPrimeOdd = 9;
    int iInitialDiff = 6;
    int iDiff = 6;
    int iDiffIncrement = 4;

    do {

        if (iNonPrimeOdd > pMaxOddNumber) {

            iStartingNonPrimeOdd += iInitialDiff;

            if (iStartingNonPrimeOdd > pMaxOddNumber) break;

            iNonPrimeOdd = iStartingNonPrimeOdd;
            iDiff += iDiffIncrement;

        } else {
            oIsCompositeNumberList[iNonPrimeOdd] = true;
            iNonPrimeOdd += iDiff;
        }

    } while(true);

    vector<int> retPrimeList = {2};

    for(map<int, bool>::iterator it = oIsCompositeNumberList.begin(); it != oIsCompositeNumberList.end(); ++it) {
        if (it->second == false) {
            retPrimeList.insert(retPrimeList.end(), it->first);
        }
    }

    return retPrimeList;
}

// Skipped starting numbers
// Created d and f lists, while doing this flag all 9 + 6n as composite, index set to i to skip this since already done
// Change do while condition to true, moved condition to inner block
vector<int> pf_generate_prime_list2(int pMaxOddNumber) {

    vector<int> d = {};
    vector<int> f = {};

    map<int, bool> oIsCompositeNumberList;
    int iFirstOddNumber = 3;
    int iSpaceBetweenOddNumber = 2;


    for (int c = iFirstOddNumber; c <= pMaxOddNumber; c += iSpaceBetweenOddNumber) {
        oIsCompositeNumberList[c] = false;
    }

    int iNonPrimeOdd = 9;
    int iStartingNonPrimeOdd = 9;
    int iInitialDiff = 6;
    int iDiff = 6;
    int iDiffIncrement = 4;

    int iDElement = iInitialDiff;

    for (int c = iStartingNonPrimeOdd; c <= pMaxOddNumber; c += iInitialDiff) {
        f.insert(f.end(), c);
        d.insert(d.end(), iDElement);
        iDElement += iDiffIncrement;
        oIsCompositeNumberList[c] = true;
    }

    int i = 1;
    iNonPrimeOdd = f[i];
    iDiff = d[i];
    int iSizeOfVectorContainers = f.size();

    do {

        if (iNonPrimeOdd > pMaxOddNumber) {
            iDiff = d[i];
            iNonPrimeOdd = f[i];
            ++i;
            if (i == iSizeOfVectorContainers) break;
        }
        oIsCompositeNumberList[iNonPrimeOdd] = true;
        iNonPrimeOdd += iDiff;

    } while(true);

    vector<int> retPrimeList = {2};

    for(map<int, bool>::iterator it = oIsCompositeNumberList.begin(); it != oIsCompositeNumberList.end(); ++it) {
        if (it->second == false) {
            retPrimeList.insert(retPrimeList.end(), it->first);
        }
    }

    return retPrimeList;
}

vector<int> pf_generate_prime_list_sieve_of_eratosthenes_method(int pMaxNumber) {
    int pMinNumber = 2;
    map<int, bool> oIsCompositeNumberList;
    vector<int> retPrimeList;
    oIsCompositeNumberList[pMinNumber] = false;
    int iPrimeNumber = pMinNumber;
    int iCompositeNumber = iPrimeNumber*2;
    do {

        if (iCompositeNumber > pMaxNumber) {
            iPrimeNumber++;
            if (iPrimeNumber > pMaxNumber) break;
            // Check if iPrimeNumber is prime using composite number list
            if (oIsCompositeNumberList[iPrimeNumber] == false) {
                iCompositeNumber = iPrimeNumber*2;
            }
        } else {
            oIsCompositeNumberList[iCompositeNumber] = true;
            iCompositeNumber += iPrimeNumber;
        }

    } while(true);


    for(map<int, bool>::iterator it = oIsCompositeNumberList.begin(); it != oIsCompositeNumberList.end(); ++it) {
        if (it->second == false) {
            retPrimeList.insert(retPrimeList.end(), it->first);
        }
    }

    return retPrimeList;
}

void print_prime_numbers(vector<int> oPrimeList) {
    cout << "Prime Number List: " << endl;
    for (int i = 0; i < oPrimeList.size(); ++i) {
        if (i < oPrimeList.size() - 1)
            cout << oPrimeList[i] << ",";
        else
            cout << oPrimeList[i];
    }
    cout << endl;
}

// https://stackoverflow.com/questions/2808398/easily-measure-elapsed-time
void time_generation_of_prime_numbers() {

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    vector<int> oFirstPrimeList = pf_generate_prime_list2(10000001);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    cout << "Number of Prime Numbers Found: " << oFirstPrimeList.size() << endl;
    //print_prime_numbers(oFirstPrimeList);

    begin = std::chrono::steady_clock::now();
    vector<int> oSecondPrimeList = pf_generate_prime_list_sieve_of_eratosthenes_method(10000001);
    end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    cout << "Number of Prime Numbers Found: " << oSecondPrimeList.size() << endl;
    //print_prime_numbers(oSecondPrimeList);

}

int main()
{
    //print_prime_numbers();
    time_generation_of_prime_numbers();
    return 0;
}

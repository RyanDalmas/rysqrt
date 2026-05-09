#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC optimize("Ofast,unroll-loops")
#endif

#include "rysqrt.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <cmath>

using namespace std;

const int TABLE_LENGTH = 25;
const int ITERATIONS = 1000000;

float TABLE[TABLE_LENGTH] = {
    391561.41058498000000, 432583.70418713900000, 298195.31059824700000,
    178869.95551225300000, 183174.37678647000000, 3748.45423702329000,
    40878.61578132590000, 25041.86474300950000, 4744.58092543514000,
    5316.33869281101000, 11030.15206403820000, 1963.64526827462000,
    369.76953787389300, 1813.06677791079000, 2835.66638448701000,
    1618.41976290003000, 240.47406526906700, 401.90670284082600,
    320.14292190673100, 364.40185732391700, 182.05477132466200,
    34.23080568118220, 9.75539070122294, 6.00454701819069,
    1.64281641935836,
};

volatile float SINK = 0.0f;

int main()
{
    cout << "Using " << TABLE_LENGTH << " Test Numbers" << endl;
    cout << "Using " << ITERATIONS << " Iterations Per Number" << endl << endl;

    cout << "FAST-SQRT" << endl;
    cout << left << setw(16) << "Number";
    cout << right << setw(14) << "Avg ns";
    cout << right << setw(14) << "Error %" << endl;

    for (int i = 0; i < TABLE_LENGTH; ++i)
    {
        volatile float number = TABLE[i];
        float ret = 0.0f;


        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        for (int j = 0; j < ITERATIONS; ++j)
        {
            ret += RySQRT::fast_sqrt(number);
        }
        chrono::steady_clock::time_point endT = chrono::steady_clock::now();
        asm volatile("" ::: "memory");

        SINK = ret;

        float result = RySQRT::fast_sqrt(TABLE[i]);
        double expected = sqrt((double)TABLE[i]);
        double elapsed = chrono::duration_cast<chrono::nanoseconds>(endT - start).count();
        double avg_time = elapsed / ITERATIONS;
        double error = fabs((result - expected) / expected) * 100.0;

        cout << fixed << setprecision(6) << left << setw(16) << TABLE[i];
        cout << fixed << setprecision(3) << right << setw(14) << avg_time;
        cout << fixed << setprecision(6) << right << setw(14) << error << endl;
    }

    cout << endl;
    cout << "ACC-SQRT" << endl;
    cout << left << setw(16) << "Number";
    cout << right << setw(14) << "Avg ns";
    cout << right << setw(14) << "Error %" << endl;

    for (int i = 0; i < TABLE_LENGTH; ++i)
    {
        volatile float number = TABLE[i];
        float ret = 0.0f;

        asm volatile("" ::: "memory");
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        for (int j = 0; j < ITERATIONS; ++j)
        {
            ret += RySQRT::acc_sqrt(number);
        }
        chrono::steady_clock::time_point endT = chrono::steady_clock::now();
        asm volatile("" ::: "memory");

        SINK = ret;

        float result = RySQRT::acc_sqrt(TABLE[i]);
        double expected = sqrt((double)TABLE[i]);
        double elapsed = chrono::duration_cast<chrono::nanoseconds>(endT - start).count();
        double avg_time = elapsed / ITERATIONS;
        double error = fabs((result - expected) / expected) * 100.0;

        cout << fixed << setprecision(6) << left << setw(16) << TABLE[i];
        cout << fixed << setprecision(3) << right << setw(14) << avg_time;
        cout << fixed << setprecision(6) << right << setw(14) << error << endl;
    }

    return 0;
}

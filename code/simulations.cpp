#include <bits/stdc++.h>

using namespace std;

void generateRandomSequence(long long N, int D, int S, vector<long long> &Y) {
    if(D>S) throw invalid_argument("S must be greater or equal to D");

    int it = N, x, dice; long long maxx = 0, nThrows;
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    while(it--) {
        dice = D; maxx = 0;
        while(dice--) {
            nThrows = 0; x = 0; 
            while(x!=S) {
                x = rand() % S + 1;
                nThrows++;
            } 
            maxx = max(maxx, nThrows);
        }
        Y[it] = maxx;
    }

    return ;
}

double estimateEV(long long N, vector<long long> &Y) {
    long long summ = 0;
    for(long long i=0; i<N; i++) summ += Y[i];
    return ((double) summ)/N;
}

double estimateVariance(long long N, double mu, vector<long long> &Y) {
    double num=0;
    for(long long i=0; i<N; i++) {
        num += (Y[i]-mu)*(Y[i]-mu);
    } 
    return num/N;
}

int main() {
    long long N; int D, S;
    double mu;
    cout << "Input N, D, S, Exact Expected Value\n";
    cin >> N >> D >> S >> mu;

    vector<long long> Y(N, -1);
    auto t1 = chrono::high_resolution_clock::now();
    generateRandomSequence(N, D, S, Y);
    auto t2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> ms_double = t2 - t1;
    cout << "\nGenerated a Random Sequence in: " << ms_double.count();

    t1 = chrono::high_resolution_clock::now();
    double ev = estimateEV(N, Y);
    t2 = chrono::high_resolution_clock::now();
    ms_double = t2 - t1;
    cout << "\nEstimated the EV in: " << ms_double.count();

    t1 = chrono::high_resolution_clock::now();
    double var = estimateVariance(N, mu, Y);
    t2 = chrono::high_resolution_clock::now();
    ms_double = t2 - t1;
    cout << "\nEstimated the Variance in: " << ms_double.count() << "\n";

    cout << "\nEstimated Expected Value: " << ev << '\n';
    cout << "Estimated Variance: " << var << '\n';
    return 0;
}
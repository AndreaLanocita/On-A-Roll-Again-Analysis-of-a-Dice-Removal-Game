#include <bits/stdc++.h>

using namespace std;

vector<float> power1S;
vector<float> power2S;

void calculatePower1S(int N, int S) {
    /*
    Calculates the powers of 1/S
    */
    power1S[0] = 1;
    for(int i=1; i<N+1; i++) power1S[i] = power1S[i-1]/S;
}

void calculatePower2S(int N, int S) {
    /*
    Calculates the powers of (S-1)/S
    */
    power2S[0] = 1;
    for(int i=1; i<N+1; i++) power2S[i] = (S-1)*power2S[i-1]/S;
}

float bin(long long n, long long k) { // might be int
    /*
    Calculates the binomial coefficient recursively in O(k).
    Should work in exact arithm and avoid overflowing
    source: https://math.stackexchange.com/a/927064
    */
  if(k >  n)
    throw(invalid_argument("n must be greater or equal to k"));
  if(k == 0)
    return 1;
  if(k > n/2)
    return bin(n,n-k);
  return n * bin(n-1,k-1) / k;
}

vector<float> EV;
float CalculateEV(int D, int S) {
    power1S.resize(D+1); power2S.resize(D+1); 
    calculatePower1S(D, S);
    calculatePower2S(D, S);
    EV.resize(D+1); EV[0] = 0;
    
    for(int j=1; j<=D; j++) {
        float num = 1;
        for(int i=1; i<j; i++) num += (((float) bin(j, i)) * power1S[i] * power2S[j-i] * EV[j-i]);
        EV[j] = num/(1-power2S[j]);
    }

    return EV[D];
}

float CalculateEVnonRec(int D, int S) {
    power2S.resize(D+1); 
    calculatePower2S(D, S);
    float res = 0;
    
    for(int i=1; i<=D; i++) {
        res += ((float) bin(D, i)) * pow(-1, (i+1)%2) / (1-power2S[i]);
    }

    return res;
}

vector<float> EV2;
float CalculateVariance(int D, int S) {
    power1S.resize(D+1); power2S.resize(D+1); 
    calculatePower1S(D, S);
    calculatePower2S(D, S);
    EV2.resize(D+1); EV2[0] = 0;
    
    for(int j=1; j<=D; j++) {
        float num = 2*power2S[j]*EV[j]-1;
        for(int i=1; i<j; i++) num += (((float) bin(j, i)) * power1S[i] * power2S[j-i] * EV2[j-i]);
        EV2[j] = num/(1-power2S[j])+2*EV[j];
    }

    return (EV2[D]-pow(EV[D], 2));
}

float CalculateVariancenonRec(int D, int S) {
    power2S.resize(D+1); 
    calculatePower2S(D, S);
    float res = 0;
    
    for(int i=1; i<=D; i++) {
        res += ((float) bin(D, i)) * pow(-1, (i+1)%2) * (1+power2S[i]) / pow((1-power2S[i]), 2);
    }

    return (res-pow(EV[D], 2));
}

int main() {
    int D, S;
    cout << "D, S\n";
    cin >> D >> S;

    float evex = CalculateEV(D, S);
    float evex2 = CalculateEVnonRec(D, S);
    float varex = CalculateVariance(D, S);
    float varex2 = CalculateVariancenonRec(D, S);

    cout << "Exact Expected Value Recursive Method: " << evex << '\n';
    cout << "Exact Expected Value non-Recursive Method: " << evex2 << '\n';
    cout << "Exact Variance Recursive Method: " << varex << '\n';
    cout << "Exact Variance non-Recursive Method: " << varex2 << '\n';
    return 0;
}
#include <string> 
#include <algorithm> 
#include <cfloat> 
#include <climits> 
#include <cmath> 
#include <complex> 
#include <cstdio> 
#include <cstdlib> 
#include <cstring> 
#include <functional> 
#include <iostream> 
#include <map> 
#include <memory> 
#include <queue> 
#include <set> 
#include <sstream> 
#include <stack> 
#include <utility> 
#include <vector> 

#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)
#define ALL(x) (x).begin(),(x).end() 
typedef long long ll;
using namespace std; 
const double eps = 1e-10;

const int MAX_M = 100010;
int m, a, b;

vector<int> isPrime;
vector<ll> prime;

vector<int> sieve_of_eratosthenes(ll n, vector<ll> &prime){
    vector<int> isPrime(n);
    for(ll i = 2; i < n; ++i)
        isPrime[i] = i;
    for(ll i = 2; i < n; ++i)
        if(isPrime[i]){
            prime.push_back(i);
            for(ll j = i * i; j < n; j += i)
                isPrime[j] = 0; 
        }
    return isPrime;
}
void solve(){
    int rp, rq, rm;
    rp = rq = rm = 0;
    for(int i = 0; i < prime.size() && prime[i] * prime[i] <= m; ++i){
        for(int j = i; j < prime.size() && prime[i] * prime[j] <= m; ++j){
            ll p = prime[i];
            ll q = prime[j];
            if(a * q <= p * b && p * q > rm){
                rp = p; rq = q; rm = p * q;
            }
        }
    }
    printf("%d %d\n", rp, rq);
}
int main(){
    isPrime = sieve_of_eratosthenes(MAX_M + 1, prime);
    while(scanf("%d%d%d", &m, &a, &b), m || a || b){
        solve();
    }
    return 0;
}

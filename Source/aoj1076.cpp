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

ll gcd(ll x, ll y){
    return y == 0 ? x: gcd(y, x % y);
}
ll lcm(ll x, ll y){
    return x / gcd(x, y) * y;
}

int n, m;
ll p[30];

void solve(){
    ll time;
    ll all;
    time = 0;
    all = 0;
    for(int s = 1; s < (1 << m); ++s){
        ll t = 1, bc = 0;
        for(int i = 0; i < m; ++i){
            if(((s >> i) & 1) != 0){
                t = lcm(t, p[i]);
                ++bc;
            }
        }
        time += (bc % 2 == 0 ? -1: 1) * (n + t) * (n / t) / 2;
        all += (bc % 2 == 0 ? -1: 1) * (n / t);
    }
    time = (long long)n * (n + 1) / 2 - time;
    all = n - all;
    double res = (double)time / all;
    if(all == 0)
        res = 0.0;
    printf("%.8f\n", res);
}

int main(){
    for(;;){
        cin >> n >> m;
        if(n == 0 && m ==0) return 0;
        for(int i = 0; i < m; ++i){
            cin >> p[i];
        }
        solve();
    }
}

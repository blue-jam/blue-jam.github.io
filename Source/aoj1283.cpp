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

typedef complex<double> P;

bool operator < (const P &a, const P &b){
    return a.real() != b.real() ? a.real() < b.real() : a.imag() < b.imag();
}
double dot(const P &a, const P &b){
    return real(conj(a) * b);
}
double cross(const P &a, const P &b){
    return imag(conj(a) * b);
}

struct Line : public vector<P> {
    Line(const P &a, const P &b) {
        push_back(a); push_back(b);
    }
    Line(double x1, double y1, double x2, double y2){
        push_back(P(x1, y1));
        push_back(P(x2, y2));
    }
};

typedef vector<P> Polygon;

P intersection(const Line &a, const Line &b){
    P va = a[1] - a[0], vb = b[1] - b[0];
    return a[0] + va * cross(vb, b[0] - a[0]) / cross(vb, va);
}

int ccw(P a, P b, P c){
    P ab = b - a, ac = c - a;
    if(cross(ab, ac) > eps)     return +1;      //counter clockwise
    if(cross(ab, ac) < -eps)    return -1;      //clockwise
    return 0;                                   //parallel
}
Polygon convex_cut(const Polygon &p, const Line &l){
    Polygon res;
    for(int i = 0; i < p.size(); ++i){
        P curr = p[i];
        P next = p[(i + 1) % p.size()];
        Line tl = Line(curr, next);
        if(ccw(l[0], l[1], curr) == -1) res.push_back(curr);
        if(ccw(l[0], l[1], curr) * ccw(l[0], l[1], next) < 0)
            res.push_back(intersection(Line(curr, next), l));
    }
    return res;
}

int N;
Polygon ply;

void solve(){
    vector<P> v;
    for(int i = 0; i < N; ++i){
        P p = (ply[(i + 1) % N] - ply[i]) * P(0, -1);
        v.push_back(p / abs(p));
    }
    double dl = 0, dh = 20000;
    for(int i = 0; i < 50; ++i){
        double d = (dl + dh) / 2;
        Polygon p(ply);
        for(int j = 0; j < N; ++j){
            p = convex_cut(p, Line(ply[j] + v[j] * d, ply[(j + 1) % N] + v[j] * d));
        }
        if(p.size() < 3){
            dh = d;
        }
        else{
            dl = d;
        }
    }
    printf("%.9lf\n", dl);
}

int main(){
    while(cin >> N, N){
        ply.clear();
        for(int i = 0; i < N; ++i){
            double x, y;
            cin >> x >> y;
            ply.push_back(P(x, y));
        }
        reverse(ALL(ply));
        solve();
    }
    return 0;
}

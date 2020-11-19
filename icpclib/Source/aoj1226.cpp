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

const int MAX_N = 30;

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

struct Circle{
    P p; double r;
    Circle(const P &p, double r) : p(p), r(r) { }
};

P intersection_ls(const Line &a, const Line &b){
    P vb = b[1] - b[0];
    double d1 = abs(cross(vb, a[0] - b[0]));
    double d2 = abs(cross(vb, a[1] - b[0]));
    double t = d1 / (d1 + d2);
    return a[0] + (a[1] - a[0]) * t;
}

int n;
double a[MAX_N], b[MAX_N], c[MAX_N], d[MAX_N];
void solve(){
    double res = 0.0;
    a[0] = b[0] = c[0] = d[0] = 0.0;
    a[n + 1] = b[n + 1] = c[n + 1] = d[n + 1] = 1.0;
    for(int i = 0; i <= n; ++i){
        for(int j = 0; j <= n; ++j){
            Line l1 = Line(a[i], 0, b[i], 1);
            Line l2 = Line(a[i + 1], 0, b[i + 1], 1);
            Line l3 = Line(0, c[j], 1, d[j]);
            Line l4 = Line(0, c[j + 1], 1, d[j + 1]);
            P p1 = intersection_ls(l1, l3);
            P p2 = intersection_ls(l1, l4);
            P p3 = intersection_ls(l2, l3);
            P p4 = intersection_ls(l2, l4);
            double tmp = (abs(cross(p2 - p1, p3 - p1)) + abs(cross(p3 - p4, p2 - p4))) / 2.0;
            res = max(res, tmp);
        }
    }
    printf("%.9f\n", res);
}
int main(){
    while(cin >> n, n){
        for(int i = 1; i <= n; ++i) cin >> a[i];
        for(int i = 1; i <= n; ++i) cin >> b[i];
        for(int i = 1; i <= n; ++i) cin >> c[i];
        for(int i = 1; i <= n; ++i) cin >> d[i];
        solve();
    }
    return 0;
}

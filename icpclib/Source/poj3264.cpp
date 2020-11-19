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

#define ALL(x) (x).begin(),(x).end() 
using namespace std; 
const double eps = 1e-10;

typedef pair<int, int> Data;
const Data Ignore_Data = make_pair(INT_MAX, 0);

struct SegmentTree{
    int n;
    vector<Data> dat;
    SegmentTree(int n_){
        for(n = 1; n < n_; n *= 2);
        dat = vector<Data>(n * 2 - 1, Ignore_Data);
    }
    Data init(vector<Data> &v){
        for(int i = 0; i < v.size(); ++i){
            dat[i + n - 1] = v[i];          //葉の要素に直接書き込む
        }
        for(int k = n - 2; k >= 0; --k){    //上に上りながら計算
            dat[k].first = min(dat[k * 2 + 1].first, dat[k * 2 + 2].first);
            dat[k].second = max(dat[k * 2 + 1].second, dat[k * 2 + 2].second);
        }
    }
    void update(int k, Data d){
        k += n - 1;     //葉の接点
        dat[k] = d;
        while(k > 0){   //上りながら更新
            k = (k - 1) / 2;
            /* 以下を適切な処理に書き換える． */
            dat[k].first = min(dat[k * 2 + 1].first, dat[k * 2 + 2].first);
            dat[k].second = max(dat[k * 2 + 1].second, dat[k * 2 + 2].second);
        }
    }
    Data get(int a, int b, int k, int l, int r){
        if(b <= l || r <= a)
            return Ignore_Data;     //区間が交差しない
        if(a <= l && r <= b){
            return dat[k];          //区間が完全に含まれる
        }
        else{
            Data vl = get(a, b, k * 2 + 1, l, (l + r) / 2);
            Data vr = get(a, b, k * 2 + 2, (l + r) / 2, r);
            /* 以下を適切な処理に書き換える */
            return make_pair(min(vl.first, vr.first), max(vl.second, vr.second));
        }
    }
    Data query(int a, int b){
        return get(a, b, 0, 0, n);
    }
};

const int MAX_N = 50000;
const int MAX_Q = 200000;

int N, Q;
int height[MAX_N];
int A[MAX_Q], B[MAX_Q];

void solve(){
    SegmentTree st = SegmentTree(N);
    vector<pair<int, int> > dat;
    for(int i = 0; i < N; ++i){
        dat.push_back(make_pair(height[i], height[i]));
    }
    st.init(dat);
    for(int i = 0; i < Q; ++i){
        pair<int, int> ret = st.query(A[i] - 1, B[i]);
        printf("%d\n", ret.second - ret.first);
    }
}

int main(){
    scanf("%d%d", &N, &Q);
    for(int i = 0; i < N; ++i){
        scanf("%d", &height[i]);
    }
    for(int i = 0; i < Q; ++i){
        scanf("%d%d", &A[i], &B[i]);
    }
    solve();
    return 0;
}

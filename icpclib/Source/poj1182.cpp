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

const int MAX_K = 100000;

int N, K, D[MAX_K], X[MAX_K], Y[MAX_K];

struct UnionFind{
    vector<int> parent, rank;
    UnionFind(int n){ parent = vector<int>(n, -1); rank = vector<int>(n, 0); }
    int find(int x){
        if(parent[x] == -1) return x;
        else return (parent[x] = find(parent[x]));
    }
    bool unite(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y) return true;
        if(rank[x] < rank[y])
            parent[y] = x;
        else
            parent[x] = y;
        if(rank[x] == rank[y])
            ++rank[x];
        return false;
    }
    bool same(int x, int y){
        return find(x) == find(y);
    }
};

void solve(){
    int ans = 0;
    UnionFind uf = UnionFind(N * 3);

    for(int i = 0; i < K; ++i){
        int x = X[i] - 1, y = Y[i] - 1;
        if(x < 0 || N <= x || y < 0 || N <= y){
            ++ans;
        }
        else if(D[i] == 1){
            if(uf.same(3 * x, 3 * y + 1) || uf.same(3 * x, 3 * y + 2))
                ++ans;
            else
                for(int j = 0; j < 3; ++j)
                    uf.unite(3 * x + j, 3 * y + j);
        }
        else{
            if(uf.same(3 * x, 3 * y + 2) || uf.same(3 * x, 3 * y))
                ++ans;
            else
                for(int j = 0; j < 3; ++j)
                    uf.unite(3 * x + j, 3 * y + (j + 1) % 3);
        }
    }
    printf("%d\n", ans);
}

int main(){
    scanf("%d%d", &N, &K);
    for(int i = 0; i < K; ++i){
        scanf("%d%d%d", &D[i], &X[i], &Y[i]);
    }
    solve();
    return 0;
}

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

typedef int Weight;
struct Edge{
    int from, to;
    Weight weight;
    Edge(int from, int to, Weight weight) :
        from(from), to(to), weight(weight) { }
};
bool operator < (const Edge &a, const Edge &b){
    if(a.weight != b.weight) return a.weight > b.weight;
    if(a.from != b.from) return a.from > b.from;
    return  a.to > b.to;
}
typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

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
        if(x == y) return false;
        if(rank[x] < rank[y])
            parent[y] = x;
        else
            parent[x] = y;
        if(rank[x] == rank[y])
            ++rank[x];
        return true;
    }
    bool same(int x, int y){
        return find(x) == find(y);
    }
};

pair<Weight, Edges> kruskal_e(Edges &edges, int n){
    sort(ALL(edges)); reverse(ALL(edges));  //a < b <-> a.weight > b.weight
    int sz = edges.size();

    UnionFind uf(n);
    Weight total = 0;
    Edges F;
    for(int i = 0; i < sz; ++i){
        if(uf.unite(edges[i].from, edges[i].to)){
            total = total + edges[i].weight;
            F.push_back(edges[i]);
        }
    }
    return make_pair(total, F);
}
pair<Weight, Edges> kruskal_g(const Graph &g){
    int n = g.size();
    vector<Edge> edges;
    for(int i = 0; i < n; ++i) edges.insert(edges.end(), ALL(g[i]));
    return kruskal_e(edges, n);
}

const int MAX_R = 50000;

int N, M, R;
int x[MAX_R], y[MAX_R], d[MAX_R];

void solve(){
    Edges es(R, Edge(-1, -1, -1));
    for(int i = 0; i < R; ++i){
        int tx = x[i], ty = N + y[i];
        es[i] = Edge(tx, ty, -d[i]);
    }
    pair<Weight, Edges> pwe = kruskal_e(es, N + M);
    int ans = 10000 * (N + M) + pwe.first;
    printf("%d\n", ans);
}

int main(){
    int T;
    scanf("%d", &T);
    for(int k = 0; k  < T;  ++k){
        scanf("%d%d%d", &N, &M, &R);
        for(int i = 0; i < R; ++i){
            scanf("%d%d%d", &x[i], &y[i], &d[i]);
        }
        solve();
    }
    return 0;
}

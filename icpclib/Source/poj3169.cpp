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

const int INF = 1000000000;

bool bellmanFord(const Graph &g, int s, vector<Weight> &dist, vector<int> &prev){
    int n = g.size();
    bool nagativeRoop = false;
    dist.assign(n, INF); dist[s] = 0;
    prev.assign(n, -1);
    for(int k = 0; k < n; ++k){
        for(int v = 0; v < n; ++v){
            //EACH(i, g[v]){
            for(Edges::const_iterator i=g[v].begin(); i != g[v].end(); ++i){
                if(dist[i -> from] != INF && dist[i -> to] > dist[i -> from] + i -> weight){
                    dist[i -> to] = dist[i -> from] + i-> weight;
                    prev[i -> to] = i -> from;
                    if(k == n - 1){
                        dist[i -> to] = -INF;
                        nagativeRoop = true;
                    }
                }
            }
        }
    }
    return nagativeRoop;
}
bool findNegativeRoop(const Graph &g){
    int n = g.size();
    vector<Weight> dist(n, 0);
    for(int k = 0; k < n; ++k){
        for(int v = 0; v < n; ++v){
            //EACH(i, g[v]){
            for(Edges::const_iterator i=g[v].begin(); i != g[v].end(); ++i){
                if(dist[i -> to] > dist[i -> from] + i -> weight){
                    dist[i -> to] = dist[i -> from] + i -> weight;
                    if(v == n - 1) return true;
                }
            }
        }
    }
    return false;
}

const int MAX_ML = 10000;
const int MAX_MD = 10000;

int N, ML, MD;
int AL[MAX_ML], BL[MAX_ML], DL[MAX_ML];
int AD[MAX_MD], BD[MAX_MD], DD[MAX_MD];

void solve(){
    Graph g(N);
    for(int i = 0; i < ML; ++i)
        g[AL[i] - 1].push_back(Edge(AL[i] - 1, BL[i] - 1, DL[i]));
    for(int i = 0; i < MD; ++i)
        g[BD[i] - 1].push_back(Edge(BD[i] - 1, AD[i] - 1, -DD[i]));
    for(int i = 0; i < N - 1; ++i)
        g[i + 1].push_back(Edge(i + 1, i, 0));
    vector<Weight> dist;
    vector<int> prev;
    bool nagativeRoop = bellmanFord(g, 0, dist, prev);
    if(nagativeRoop){
        printf("-1\n");
    }
    else if(dist[N - 1] == INF){
        printf("-2\n");
    }
    else{
        printf("%d\n", dist[N - 1]);
    }
}

int main(){
    scanf("%d%d%d", &N, &ML, &MD);
    for(int i = 0; i < ML; ++i){
        scanf("%d%d%d", &AL[i], &BL[i], &DL[i]);
    }
    for(int i = 0; i < MD; ++i){
        scanf("%d%d%d", &AD[i], &BD[i], &DD[i]);
    }
    solve();
    return 0;
}

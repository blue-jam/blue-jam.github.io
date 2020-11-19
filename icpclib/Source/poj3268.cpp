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

const int INF = 100000000;
void dijkstra(const Graph &g, int s, vector<Weight> &dist, vector<int> &prev){
    int n = g.size();
    dist.assign(n, INF);
    dist[s] = 0;
    prev.assign(n, -1);
    priority_queue<Edge> Q;     // a < b <-> a.weight > b.weight
    Q.push(Edge(-2, s, 0));
    while(!Q.empty()){
        Edge e = Q.top(); Q.pop();
        if(prev[e.to] != -1) continue;
        prev[e.to] = e.from;
        EACH(i, g[e.to]){
        //for(Edges::const_iterator i=g[e.to].begin(); i!=g[e.to].end(); ++i){
            if(dist[i -> to] > dist[i -> from] + i -> weight){
                dist[i -> to] = dist[i -> from] + i -> weight;
                Q.push(Edge(i -> from, i -> to, dist[i -> to]));
            }
        }
    }
}
vector<int> buildPath(const vector<int> &prev, int t){
    vector<int> path;
    for(int v = t; v >= 0; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

const int MAX_N = 1000;
const int MAX_M = 100000;

int N, M, X;
int A[MAX_M], B[MAX_M], T[MAX_M];

void solve(){
    Graph fwd(N + 1), rev(N + 1);
    vector<Weight> fdst(N + 1), rdst(N + 1);
    vector<int> fprv(N + 1), rprv(N + 1);
    for(int i = 0; i < M; ++i){
        fwd[A[i]].push_back(Edge(A[i], B[i], T[i]));
        rev[B[i]].push_back(Edge(B[i], A[i], T[i]));
    }
    dijkstra(fwd, X, fdst, fprv);
    dijkstra(rev, X, rdst, rprv);
    int ans = 0;
    for(int i = 1; i <= N; ++i){
        ans = max(ans, fdst[i] + rdst[i]);
    }
    printf("%d\n", ans);
}

int main(){
    scanf("%d%d%d", &N, &M, &X);
    for(int i = 0; i < M; ++i){
        scanf("%d%d%d", &A[i], &B[i], &T[i]);
    }
    solve();
    return 0;
}

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

#define EACH(i,c) for(__typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)
#define ALL(x) (x).begin(),(x).end() 
typedef long long ll;
using namespace std; 
const double eps = 1e-10;
const int INF = 500000000;

typedef int Weight;
struct Edge{
    Weight weight;
    int from, to;
    Edge(int f, int t, Weight w) :
        from(f), to(t), weight(w) { }
};
bool operator < (const Edge &a, const Edge &b){
    if(a.weight != b.weight) return a.weight > b.weight;
    if(a.from != b.from) return a.from > b.from;
    return a.to > b.to;
}
typedef vector<Edge> Edges;
typedef vector<Edges> Graph;

void dijkstra(const Graph &g, int s, vector<Weight> &dist, vector<int> &prev){
    int n = g.size();
    dist.assign(n, INF);
    dist[s] = 0;
    prev.assign(n, -1);
    priority_queue<Edge> Q;
    Q.push(Edge(-2, s, 0));
    while(!Q.empty()){
        Edge e = Q.top(); Q.pop();
        if(prev[e.to] != -1) continue;
        prev[e.to] = e.from;
        EACH(i, g[e.to]){
            if(dist[i -> to] > dist[i -> from] + i -> weight){
                dist[i -> to] = dist[i -> from] + i -> weight;
                Q.push(Edge(i -> from, i -> to, dist[i -> to]));
            }
        }
    }
}

void calcDepth(const Graph &g, int s, vector<int> &depth){
    vector<int> prev(g.size());
    dijkstra(g, s, depth, prev);
}
int check(int v, vector<int> &ancestor){
    if(ancestor[v] != -1){
        ancestor[v] = check(ancestor[v], ancestor);
        return ancestor[v];
    }
    else{
        return v;
    }
}

void initLCA(vector<int> &parent, vector<vector<int> > &ancestor){
    int n = parent.size();
    int tn = 1;
    int maxLog = 0;
    for(maxLog = 0; tn < n; ++maxLog) tn *= 2;
    ancestor.resize(maxLog, vector<int>(n, -1));
    for(int i = 0; i < n; ++i)
        ancestor[0][i] = parent[i];
    for(int i = 0; i + 1 < maxLog; ++i){
        for(int j = 0; j < n; ++j){
            if(ancestor[i][j] < 0)
                ancestor[i + 1][j] = -1;
            else
                ancestor[i + 1][j] = ancestor[i][ancestor[i][j]];
        }
    }
}
int lowestCommonAncestor(int u, int v, vector<int> &depth, vector<vector<int> > &ancestor){
    int maxLog = ancestor.size();
    if(depth[u] > depth[v]) swap(u, v);
    for(int k = 0; k < maxLog; ++k){
        if((depth[v] - depth[u]) >> k & 1){
            v = ancestor[k][v];
        }
    }
    if(u == v) return u;
    for(int k = maxLog - 1; k >= 0; --k){
        if(ancestor[k][u] != ancestor[k][v]){
            u = ancestor[k][u];
            v = ancestor[k][v];
        }
    }
    return ancestor[0][u];
}

int N, M, K, Q;

int main(){
    scanf("%d%d%d%d", &N, &M, &K, &Q);
    Graph g(N + 1);
    vector<Weight> dist;
    vector<int> prev;

    for(int i = 0; i < M; ++i){
        int a, b, l;
        scanf("%d%d%d", &a, &b, &l);
        g[a].push_back(Edge(a, b, l));
        g[b].push_back(Edge(b, a, l));
    }
    for(int i = 0; i < K; ++i){
        int f;
        scanf("%d", &f);
        g[0].push_back(Edge(0, f, 0));
    }
    //cerr << "input end..." << endl;

    dijkstra(g, 0, dist, prev);
    //cerr << "dijkstra end..." << endl;

    vector<pair<int, int> > vp(N);
    for(int i = 1; i <= N; ++i){
        vp[i - 1] = make_pair(dist[i], i);
    }
    sort(ALL(vp), greater<pair<int, int> >());

    Graph tree(N + 1);
    vector<int> depth(N + 1, -1);
    vector<int> parent(N + 1, -1);
    vector<int> anc(N + 1, -1);
    for(int i = 0; i < N; ++i){
        int v = vp[i].second;
        EACH(j, g[v]){
            int to = j -> to;
            to = check(to, anc);
            if(dist[to] > dist[v] || dist[to] == dist[v] && v < to){
                anc[to] = parent[to] = v;
                tree[v].push_back(Edge(v, to, 1));
            }
        }
    }
    depth[vp[N - 1].second] = 0;
    calcDepth(tree, vp[N - 1].second, depth);
    /*
    for(int i = 1; i <= N; ++i){
        printf("[%d,%d,%d]", i, dist[i], parent[i]);
    }
    printf("\n");
    */
    //cerr << "tree end..." << endl;

    vector<vector<int> > ancestor;
    initLCA(parent, ancestor);
    //cerr << "initLCA end..." << endl;
    /*
    int maxLog = ancestor.size();
    for(int i = 0; i < maxLog; ++i){
        for(int j = 0; j <= N; ++j){
            printf("[%2d]", ancestor[i][j]);
        }
        printf("\n");
    }
    */
    for(int i = 0; i < Q; ++i){
        int u, v;
        scanf("%d%d", &u, &v);
        int res = lowestCommonAncestor(u, v, depth, ancestor);
        printf("%d\n", dist[res]);
    }
    return 0;
}

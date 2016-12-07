#include <bits/stdc++.h>
using namespace std;
using ll=long long; using ld=long double;
#define rep(i,s,e) for (int i=(s),__ee=(e);i<__ee;++i)
#define all(x) begin(x),end(x)
#define clr(x,y) memset(x,y,sizeof x)
int dx[]={0,0,1,-1,1,-1,1,-1}, dy[]={-1,1,0,0,1,-1,-1,1};

int n, a, b;
double p[2222], u[2222], eps=1e-7;

const int MAXN = 2010;
struct edge { int dest, cap; double cost; int rev; };
vector<edge> adj[MAXN];
double dis[MAXN], cost;
int source, target, iter, cap;
edge* pre[MAXN];

void addedge(int x, int y, int cap, double cost) {
  adj[x].push_back(edge {y, cap, cost, (int)adj[y].size()});
  adj[y].push_back(edge {x, 0, -cost, (int)adj[x].size() - 1});
}

bool spfa() { // optimization: use dijkstra here and do Johnson reweighting before
    fill(dis, dis + MAXN, 1e12);
  queue<int> q;
  pre[source] = pre[target] = 0;
  dis[source] = 0;
  q.emplace(source);
  while (!q.empty()) {
    int x = q.front();
        double d = dis[x];
    q.pop();
    for (auto& e : adj[x]) {
      int y = e.dest;
            double w = d + e.cost;
      if (e.cap < cap || dis[y] < w + eps) continue;
      dis[y] = w;
      pre[y] = &e;
      q.push(y);  // optimization: only push if not in queue yet
    }
  }
  edge* e = pre[target];
  if (!e || dis[target] > -eps) return 0;  // to minimize (cost, -flow): return also if dis[target] > 0
  while (e) {
    edge& rev = adj[e->dest][e->rev];
    e->cap -= cap;
    rev.cap += cap;
    cost += cap * e->cost;
    e = pre[rev.dest];
  }
  return 1;
}

double mincost(int S, int T) {
  cap = 1, source = S, target = T, cost = 0;
    while(spfa()) {}
  return cost;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> a >> b;
    for (int i = 0; i < n; ++i) cin >> p[i];
    for (int i = 0; i < n; ++i) cin >> u[i];
    int S = n + 1, T = n + 2, P = n + 3, U = n + 4;
    addedge(S, P, a, 0);
    addedge(S, U, b, 0);
    for (int i = 0; i < n; ++i) {
        addedge(P, i, 1, -p[i]);
        addedge(U, i, 1, -u[i]);
        addedge(i, T, 1, 0);
        addedge(i, T, 1, p[i]*u[i]);
    }
    cout << setprecision(20) << fixed << -mincost(S, T) << endl;
}

//SPFA for MCMF Algo
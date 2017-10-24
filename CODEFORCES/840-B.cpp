#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜

#define Foreach(i, c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define For(i,a,b) for(int (i)=(a);(i) < (b); ++(i))
#define rof(i,a,b) for(int (i)=(a);(i) > (b); --(i))
#define rep(i, c) for(auto &(i) : (c))
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define PB pop_back()
#define iOS ios_base::sync_with_stdio(false)
#define sqr(a) (((a) * (a)))
#define all(a) a.begin() , a.end()
#define error(x) cerr << #x << " = " << (x) <<endl
#define Error(a,b) cerr<<"( "<<#a<<" , "<<#b<<" ) = ( "<<(a)<<" , "<<(b)<<" )\n";
#define Error3(a,b,c) cerr<<"("<<#a<<" , "<<#b<<" , "<<#c<<" ) = ( "<<(a)<<" , "<<(b)<<" , "<<(c)<<")\n";
#define Error4(a,b,c,d) cerr<<"("<<#a<<" , "<<#b<<" , "<<#c<<" , "<<#d<<" ) = ( "<<(a)<<" , "<<(b)<<" , "<<(c)<<" , "<<(d)<<")\n";
#define Error5(a,b,c,d,e) cerr<<"("<<#a<<" , "<<#b<<" , "<<#c<<" , "<<#d<<" , "<<#e<<" ) = ( "<<(a)<<" , "<<(b)<<" , "<<(c)<<" , "<<(d)<<" , "<<(e)<<")\n";
#define errop(a) cerr<<#a<<" = ( "<<((a).x)<<" , "<<((a).y)<<" )\n";
#define coud(a,b) cout<<fixed << setprecision((b)) << (a)
#define L(x) (((x)<<1)+1)
#define R(x) (((x)<<1)+2)
#define umap unordered_map
//#define double long double
#define mod 1000000007
#define mod1 1000000009
#define LIMIT 10000000000000000LL
#define INF 10000000000LL
#define MAX1 1000000000
const int inf=0x3f3f3f3f;
const long double pi=acos(-1.0);
#define MAX 50010
// #define N 100010
const string debug_line="yolo";
#define debug error(debug_line)
#define read() freopen("mergedoutput.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
//template <typename T> using os =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef unsigned long long ull;
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);
const long double eps=1e-6;
ull getRand(){return ((ull)rand()<<40)+((ull)rand()<<20)+((ull)rand());}

int d[300010];
int par[300010];
bool visited[300010];
vi Adj[300010]; 
vi Adj1[300010];
int d1[300010];
map<pii,int> edgeMap;
vector<pii> edges;
int n, m;

bool check() {
    int currentVal = 0;
    bool canBeChanged = false;
    for (int i=1; i<=n; i++) {
        if (d[i] != -1) {
            currentVal ^= d[i];
        }
        else {
            canBeChanged = true;
        }
    }

    if (currentVal && !canBeChanged) {
        return false;
    }
    return true;
}

void changeD() {
    int currentVal = 0;
    for(int i=1; i<=n; i++) {
        if (d[i]!=-1) {
            currentVal ^= d[i];
        }
    }

    for(int i=1; i<= n; i++) {
        if (d[i] == -1) {
            if (currentVal == 0) {
                d[i] = 0;
            } else {
                d[i] = 1;
                currentVal = 0;
            }
        }
    }
}

void DFS(int u,int p) {
    par[u] = p;
    visited[u] = true;
    for(auto v: Adj[u]) {
        if (!visited[v]) {
            // Adj1[u].pb(v);
            DFS(v, u);
        }
    }
}

void DFS1(int u, int p) {
    visited[u] = true;
    for (auto v: Adj[u]) {
        if (!visited[v]) {
            DFS1(v, u);
        }
    }

    if (d1[u] != d[u]) {
        Adj1[u].pb(par[u]);
        d1[par[u]] ^= 1;
    }
}

void getAllEdges() {
    for (int i=1; i<= n; i++) {
        for (auto v : Adj1[i]) {
            edges.pb(mp(min(i,v), max(i,v)));
        }
    }
    sort(all(edges), [](pii &t1, pii &t2) {
        return edgeMap[t1] < edgeMap[t2];
    });
}

int main() {
    scanf("%d%d", &n, &m);

    for(int i=1; i<=n; i++) {
        scanf("%d", &d[i]);
    }

    for(int i=1; i<=m; i++) {
        int u1, v1;
        scanf("%d%d", &u1, &v1);
        Adj[u1].pb(v1);
        Adj[v1].pb(u1);
        edgeMap[mp(min(u1,v1), max(u1,v1))] = i;
    }

    if (!check()) {
        printf("-1\n");
        return 0;
    }
    changeD();
    DFS(1, -1);
    memset(visited, 0, sizeof(visited));
    DFS1(1, -1);
    getAllEdges();
    int size1 = edges.size();
    printf("%d\n", size1);
    for (auto edge_: edges) {
        printf("%d\n", edgeMap[edge_]);
    }
    return 0;
}
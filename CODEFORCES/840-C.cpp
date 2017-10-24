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

ll a[310];
ll dp[310][310];
ll nCr[310][310];
vi Adj[310];
int visited[310];
int groupSize = 0;
vi groupSizes;

void calc() {
    for (int i=0;i<300; i++) {
        nCr[i][0] = 1LL;
    }

    for (int i=1; i<300; i++) {
        for (int j =1 ; j<=i;j++) {
            nCr[i][j] = (nCr[i-1][j-1] + nCr[i][j-1]) %mod;
        }
    }
}

bool check(int i, int j) {
    ll val = (1LL * a[i] * 1LL * a[j]);
    ll val1 = sqrt(val);
    if (val1 * val1 == val) {
        return true;
    }
    return false;
}

void DFS(int u, int p) {
    visited[u] = true;
    groupSize++;
    for (auto v: Adj[u]) {
        if (!visited[v]) {
            DFS(v, u);
        }
    }
}

int main() {
    calc();
    int n;
    scanf("%d", &n);

    for(int i=0; i<n; i++) {
        scanf("%d", &a[i]);
    }

    for(int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            if (check(i, j)) {
                Adj[i].pb(j);
                Adj[j].pb(i);
            }
        }
    }

    for (int i=0; i<n; i++) {
        if (!visited[i]) {
            groupSize = 0;
            DFS(i, -1);
            groupSizes.pb(groupSize);
        }
    }

    error(groupSizes.size());

    dp[0][0] = 1LL;
    int total1 = 0;
    for (int i= 1; i<= groupSizes.size(); i++) {
        total1 += groupSizes[i-1];
        for (int j = 0; j < total1; j++) {
            for (int k = 1; k<= min(total1 - groupSizes[i-1]+1, groupSizes[i-1]); k++) {
                for (int l = 0; l <= min(total1 - groupSizes[i-1], k) ;l++) {
                    int change1 = j-groupSizes[i-1]+k+l;
                    if (change1 < 0 || total1 - groupSizes[i-1] + 1 - change1 < 0) {
                        continue;
                    }
                    ll val1 = 1LL*dp[i-1][change1]*nCr[l][change1] %mod;
                    val1 = val1 * nCr[k-l][total1-groupSizes[i-1] + 1-change1];
                    val1 = val1 * nCr[groupSizes[i-1]][0]%mod;
                    val1 = val1 * nCr[k-1][groupSizes[i-1]-1]%mod;
                    dp[i][j] = ( dp[i][j] + val1) % mod;
                }
            }
        }
    }

    printf("%lld\n", dp[groupSizes.size()][0]);
    return 0;
}
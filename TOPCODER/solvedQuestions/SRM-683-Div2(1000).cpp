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
#define x first
#define y second
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
//#define si(n) scanf("%d",&n)
//#define sii(n,m) scanf("%d%d",&n,&m)
//#define pi(n) printf("%d\n",n)
const int inf=0x3f3f3f3f;
const long double pi=acos(-1.0);
#define MAX 50010
// #define N 100000
const string debug_line="yolo";
#define debug error(debug_line)
const double PI=4*atan(1);
#define read() freopen("mergedoutput.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
//template <typename T> using os =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef complex<double> point;

class SubtreesCounting
{
public:
	ll answer1;
	vi Adj[100010];
	vector<ll> sumTrees[100010];
	vector<ll> countTrees[100010];
	int size1[100010];
	bool deleted[100010];

	void generate(int n,ll a0,ll b,ll c,ll m){
		vector<ll> vals;
		vals.resize(n);
		vals[0]=a0;
		For(i,1,n-1){
			vals[i]=(((ll)b%m*(ll)vals[i-1])%m+(ll)c)%m;
			// Error(i,vals[i]);
		}
		For(i,1,n){
			// Adj[i].pb(vals[i-1]%i);
			Adj[vals[i-1]%i].pb(i);
			// Error(i,vals[i-1]%i);
		}
	}

	void DFS(int u,int p){
		countTrees[u].resize(Adj[u].size()+1);
		sumTrees[u].resize(Adj[u].size()+1);
		For(t,0,Adj[u].size()+1){
			if(t==Adj[u].size() && t==0){
				countTrees[u][0]=1;
				sumTrees[u][0]=1;
				break;
			}
			else{
				if(t==0){
					sumTrees[u][0]=1;
					countTrees[u][0]=1;
				}
				else{
					DFS(Adj[u][t-1],u);
					int v=Adj[u][t-1];
					ll a=countTrees[u][t-1];
					ll b=sumTrees[u][t-1];
					ll c=1+countTrees[v][Adj[v].size()];
					ll d=sumTrees[v][Adj[v].size()];
					countTrees[u][t]=(countTrees[u][t-1]*(c))%mod;
					sumTrees[u][t]=((a*d)%mod+(b*c)%mod)%mod;
				}
			}
		}
		answer1=(answer1+sumTrees[u][Adj[u].size()])%mod;
	}

	int sumOfSizes(int n,int a0,int b,int c,int m){
		For(i,0,n){
			Adj[i].clear();
			size1[i]=0;
			deleted[i]=false;
		}
		generate(n,a0,b,c,m);
		answer1=0;
		DFS(0,-1);
		return answer1;
	}
};

// int main(){
// 	SubtreesCounting sc;
// 	int n,a0,b,c,m;
// 	scanf("%d%d%d%d%d",&n,&a0,&b,&c,&m);
// 	error(sc.sumOfSizes(n,a0,b,c,m));
// }
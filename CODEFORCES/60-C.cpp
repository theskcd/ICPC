#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

#pragma comment(linker, "/STACK:16777216")

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
#define errop(a) cerr<<#a<<" = ( "<<((a).x)<<" , "<<((a).y)<<" )\n";
#define coud(a,b) cout<<fixed << setprecision((b)) << (a)
#define L(x) (((x)<<1)+1)
#define R(x) (((x)<<1)+2)
#define umap unordered_map
//#define double long double
#define mod 1000000007
// #define mod1 1000000009
#define LIMIT 1000000000000000000LL
#define INF 10000000000LL
#define MAX1 1000000000
//#define si(n) scanf("%d",&n)
//#define sii(n,m) scanf("%d%d",&n,&m)
//#define pi(n) printf("%d\n",n)
const int inf=0x3f3f3f3f;
const long double pi=acos(-1.0);
#define MAX 50010
#define N 5010
#define M 2000010
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

struct edge{
	int u;int v;int gcd1;int lcm1;
	edge(){};
	edge(int _u,int _v,int _gcd1,int _lcm1){
		u=_u;
		v=_v;
		gcd1=_gcd1;
		lcm1=_lcm1;
	};
};

vector<edge> edges;
vector<edge> fEdges[1000010];
vi factors[1000010];
bool isPrime[1000010];
ll answer1[101];
bool poss=true;
bool visited[101];
vector<pair<pair<ll,ll>,ll> > Adj[101];

void clear(){
	memset(visited,0,sizeof(visited));
}

bool DFS(int u,int p,ll val){
	visited[u]=true;
	answer1[u]=val;
	// Error(u,answer1[u]);

	rep(t1,Adj[u]){
		if(!visited[t1.x.x] && t1.x.x!=p){
			if(((t1.x.y)*t1.y)%answer1[u]!=0){
				// error("wrong");
				return false;
			}
			else{
				ll temp1=((t1.x.y*t1.y)/answer1[u]);
				if(__gcd(temp1,answer1[u])!=t1.x.y){
					return false;
				}
				else if(!DFS(t1.x.x,u,temp1)){
					return false;
				}
			}
		}
		else if(visited[t1.x.x]){
			if(!(__gcd(answer1[u],answer1[t1.x.x])==t1.x.y && (answer1[u]*answer1[t1.x.x])==(t1.x.y*t1.y))){
				return false;
			}
		}
	}
	// Error3("DFS",u,val);
	return true;
}

int main(){
	// calc();
	int n,m;
	scanf("%d%d",&n,&m);
	// debug;

	For(i,0,n+1){
		answer1[i]=1LL;
	}

	For(i,0,m){
		int a,b,x1,y1;
		scanf("%d%d%d%d",&a,&b,&x1,&y1);
		edge temp1(a,b,x1,y1);
		edge temp2(b,a,x1,y1);
		edges.pb(temp1);
		edges.pb(temp2);
		Adj[a].pb(mp(mp(b,x1),y1));
		Adj[b].pb(mp(mp(a,x1),y1));
		if(y1%x1!=0){
			poss=false;
		}
	}

	// error(poss);

	For(i,1,n+1){
		if(!visited[i] && (int)Adj[i].size()!=0){
			ll num1=Adj[i][0].y;
			// Error(i,num1);
			bool poss1=false;
			for(ll j=1;j*j<=num1;j++){
				if(num1%j==0){
					// Error4("DFS with",i,j,num1/j);
					clear();
					// Error("DFS",j);
					if(DFS(i,0,j)){
						poss1=true;
						break;
					}
					clear();
					// Error("DFS",num1/j);
					if(DFS(i,0,num1/j)){
						poss1=true;
						break;
					}
					clear();
				}
			}

			if(!poss1){
				poss=false;
			}
		}
		else if((int)Adj[i].size()==0){
			answer1[i]=1LL;
		}
	}

	if(!poss){
		printf("NO\n");
	}
	else{
		printf("YES\n");
		For(i,1,n+1){
			printf("%lld ",answer1[i]);
		}
		printf("\n");
	}
return 0;}
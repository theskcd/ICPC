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

vector<pair<pii,int> > edges;
vector<pii> Adj[N];
int orignalSize[N];
ll size1[N];
ll dp[N];
ll dp1[N];

void DFSOrg(int u,int p){
	rep(t1,Adj[u]){
		if(t1.x!=p){
			DFSOrg(t1.x,u);
			orignalSize[u]+=orignalSize[t1.x];
		}
	}
	orignalSize[u]++;
}

void DFS(int u,int p){
	rep(t1,Adj[u]){
		if(t1.x!=p){
			DFS(t1.x,u);
			size1[u]+=size1[t1.x];
			dp1[u]+=dp1[t1.x]+t1.y;
		}
	}
	size1[u]++;
}

void DFSAllPair(int u,int p,int root,ll &allPairSum){
	rep(t1,Adj[u]){
		if(t1.x!=p){
			DFSAllPair(t1.x,u,root,allPairSum);
			allPairSum=allPairSum+((ll)t1.y)*((ll)size1[root]-size1[t1.x])*((ll)size1[t1.x]);
		}
	}
}

void DFSDirectedSum(int u,int p){
	rep(t1,Adj[u]){
		if(t1.x!=p){
			DFSDirectedSum(t1.x,u);
			dp[u]+=dp[t1.x]+((ll)t1.y)*((ll)size1[t1.x]);
		}
	}
}

void getAnswer(int u,int p,ll prev,ll prevSize,ll prevEdge,ll &answer){
	answer=min(answer,dp[u]+prev+prevEdge*prevSize);
	// Error3(u,dp[u],dp[u]+prev+prevEdge*prevSize);
	ll temp1=1;
	ll temp2=0;
	rep(t1,Adj[u]){
		if(t1.x!=p){
			temp1=temp1+size1[t1.x];
			temp2=temp2+dp[t1.x];
		}
	}

	rep(t1,Adj[u]){
		if(t1.x!=p){
			getAnswer(t1.x,u,prev+prevSize*prevEdge+dp[u]-((ll)t1.y)*((ll)size1[t1.x])-dp[t1.x],prevSize+size1[u]-size1[t1.x],t1.y,answer);
		}
	}
}

void resetAll(){
	memset(size1,0,sizeof(size1));
	memset(dp,0,sizeof(dp));
}

int main(){
	int n;
	scanf("%d",&n);

	For(i,1,n){
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		edges.pb(mp(mp(a,b),w));
		Adj[a].pb(mp(b,w));
		Adj[b].pb(mp(a,w));
	}

	DFSOrg(1,0);
	ll answerFinal=LIMIT;

	For(i,0,edges.size()){
		ll allPairSum1=0;
		ll allPairSum2=0;
		ll answerFirst=LIMIT;
		ll answerSecond=LIMIT;
		ll sizeX=0;
		ll sizeY=0;
		// Error(edges[i].x.x,edges[i].x.y);
		DFS(edges[i].x.x,edges[i].x.y);
		DFSAllPair(edges[i].x.x,edges[i].x.y,edges[i].x.x,allPairSum1);
		DFSDirectedSum(edges[i].x.x,edges[i].x.y);
		getAnswer(edges[i].x.x,edges[i].x.y,0LL,0LL,0LL,answerFirst);
		sizeX=size1[edges[i].x.x];
		
		resetAll();
		
		DFS(edges[i].x.y,edges[i].x.x);
		DFSAllPair(edges[i].x.y,edges[i].x.x,edges[i].x.y,allPairSum2);
		DFSDirectedSum(edges[i].x.y,edges[i].x.x);
		getAnswer(edges[i].x.y,edges[i].x.x,0LL,0LL,0LL,answerSecond);
		sizeY=size1[edges[i].x.y];

		ll answer1=0;
		answer1=answerFirst*sizeY+answerSecond*sizeX+(ll)(edges[i].y)*sizeX*sizeY;
		answer1+=allPairSum1+allPairSum2;
		// Error4(i,answer1,allPairSum1,allPairSum2);
		// Error4(sizeX,sizeY,answerFirst,answerSecond);
		answerFinal=min(answerFinal,answer1);

		resetAll();
	}
	printf("%lld\n",answerFinal);
return 0;}
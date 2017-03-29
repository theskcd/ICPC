#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

// using namespace __gnu_pbds;
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
const int inf=0x3f3f3f3f;
const long double pi=acos(-1.0);
#define MAX 810
// #define N 100010
const string debug_line="yolo";
#define debug error(debug_line)
#define read() freopen("mergedoutput.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef unsigned long long ull;
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);
const long double eps=1e-6;
// typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> os;
ull getRand(){return ((ull)rand()<<40)+((ull)rand()<<20)+((ull)rand());}

vector<pii> Adj[1][1000010];
int id1[100010];
const int pivot=300000;
bool visited[1000010];
ll dist[1000010];

void build(int node,int b,int e){
	if(b>e){
		return ;
	}
	else if(b==e){
		Adj[0][node].pb(mp(pivot+b,0));
		Adj[0][pivot+b].pb(mp(2*pivot+node,0));
	}
	else{
		build(2*node,b,(b+e)/2);
		build(2*node+1,(b+e)/2+1,e);
		Adj[0][node].pb(mp(2*node,0));
		Adj[0][node].pb(mp(2*node+1,0));
		Adj[0][2*node+2*pivot].pb(mp(node+2*pivot,0));
		Adj[0][2*node+1+2*pivot].pb(mp(node+2*pivot,0));
	}
}

void update(int node,int b,int e,int i,int j,int w,int n,int t){
	if(b>e || i>e || j<b){
		return ;
	}
	else if(i<=b && e<=j){
		if(t==2){
			Adj[0][pivot+n].pb(mp(node,w));
		}
		else{
			Adj[0][2*pivot+node].pb(mp(pivot+n,w));
		}
	}
	else{
		update(2*node,b,(b+e)/2,i,j,w,n,t);
		update(2*node+1,(b+e)/2+1,e,i,j,w,n,t);
	}
}

void fill(){
	For(i,0,1000010){
		dist[i]=LIMIT;
		visited[i]=false;
	}
}

int main(){
	int n,q,s;
	scanf("%d%d%d",&n,&q,&s);
	build(1,1,n);
	fill();

	while(q--){
		int t;
		scanf("%d",&t);
		if(t==1){
			int v,u,w;
			scanf("%d%d%d",&v,&u,&w);
			Adj[0][pivot+v].pb(mp(pivot+u,w));
		}
		else{
			int v,l,r,w;
			scanf("%d%d%d%d",&v,&l,&r,&w);
			update(1,1,n,l,r,w,v,t);
		}
	}

	debug;

	priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>> > Q1;
	dist[pivot+s]=0;
	Q1.push(mp(0LL,pivot+s));
	while(!Q1.empty()){
		pii u=Q1.top();
		// Error(u.x,u.y);
		Q1.pop();
		if(visited[u.y]){
			continue;
		}
		visited[u.y]=true;
		rep(edge,Adj[0][u.y]){
			// Error3("0",edge.x,edge.y);
			if(dist[edge.x]>dist[u.y]+edge.y){
				dist[edge.x]=dist[u.y]+edge.y;
				Q1.push(mp(dist[u.y]+edge.y,edge.x));
			}
		}
	}

	For(i,1,n+1){
		if(!visited[pivot+i]){
			printf("-1 ");
		}
		else{
			printf("%lld ",dist[pivot+i]);
		}
	}
	printf("\n");
return 0;}
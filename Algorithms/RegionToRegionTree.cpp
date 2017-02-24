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

vector<pii> e;
vi Adj[200010];
int n,m;
map<pii,int> ids;
vector<pii> membs[200010];
set<int> fadj[100010];
int col[100010];
int size1[100010];
int nn=0;

void makeTree(){
	For(i,1,n+1){
		sort(all(Adj[i]),[=](const int x,const int y){
			if(x>i && y<i) return true;
			if(x<i && y>i) return false;
			return x<y;
		});
	}
	For(i,1,n+1){
		reverse(all(Adj[i]));
	}
	For(i,1,n+1){
		error(i);
		rep(t1,Adj[i]){ printf("%d ",t1);}
		printf("\n");
	}
	rof(u,n,0){
		error(u);
		For(i,1,Adj[u].size()){
			int v=Adj[u][i-1];int w=Adj[u][i];
			swap(w,v);
			Error3(u,v,w);
			if(!ids.count({u,v})){
				Error3("checking for",u,v);
				ids[{u,v}]=++nn;
				membs[nn].pb({u,v});
			}
			int me=ids[{u,v}];
			if(!ids.count({w,u})){
				Error3("checking for 1",w,u);
				membs[me].pb({w,u});
			}
			ids[{w,u}]=me;
		}
	}

	For(i,1,nn+1){
		rep(t1,membs[i]){
			Error(i,ids[mp(t1.y,t1.x)]);
			fadj[i].insert(ids[{t1.y,t1.x}]);
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);

	For(i,0,m){
		int a1,b1;
		scanf("%d%d",&a1,&b1);
		Adj[a1].pb(b1);Adj[b1].pb(a1);
	}

	For(i,1,n){
		Adj[i].pb(i+1);
		Adj[i+1].pb(i);
	}
	Adj[n].pb(1);Adj[1].pb(n);

	makeTree();
}
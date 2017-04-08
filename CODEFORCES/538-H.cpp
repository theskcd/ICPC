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

int color[100010];
vi Adj[100010];
bool visited[100010];
pii limits[100010];
bool poss;

void DFS(int u,int col){
	if(visited[u]){
		if(color[u]!=col){
			puts("IMPOSSIBLE"); exit(0);
		}
		else{
			return ;
		}
	}
	visited[u]=true;
	color[u]=col;
	// Error(u,color[u]);
	rep(t1,Adj[u]){
		DFS(t1,1-col);
	}
}

bool inside(int id,int x){
	if(limits[id].F<=x && limits[id].S>=x){
		return true;
	}
	else{
		return false;
	}
}

int main(){
	int t,T;
	scanf("%d%d",&t,&T);
	int n,m;
	scanf("%d%d",&n,&m);
	int n1=-1;
	int n2=INT_MAX;
	swap(n1,n2);

	For(i,1,n+1){
		int l1,r1;
		scanf("%d%d",&l1,&r1);
		limits[i]=mp(l1,r1);
		n2=max(n2,l1);
		n1=min(n1,r1);
	}

	For(i,0,m){
		int x1,y1;
		scanf("%d%d",&x1,&y1);
		Adj[x1].pb(y1);Adj[y1].pb(x1);
	}
	// Error(n1,n2);

	if(n1+n2<t){
		n2=t-n1;
	}
	if(n1+n2>T){
		n1=T-n2;
	}
	// Error(n1,n2);
	if(n1<0 || n2<0){
		puts("IMPOSSIBLE");
		return 0;
	}
	else{
		For(i,1,n+1){
			if(inside(i,n1)){
				if(!inside(i,n2)){
					DFS(i,0);
				}
			}
			else if(inside(i,n2)){
				DFS(i,1);
			}
			else{
				puts("IMPOSSIBLE"); return 0;
			}
		}

		// debug;

		For(i,1,n+1){
			if(!visited[i]){
				DFS(i,0);
			}
		}

		printf("POSSIBLE\n%d %d\n",n1,n2);
		For(i,1,n+1){
			printf("%d",color[i]+1);
		}
		printf("\n");
	}
return 0;}
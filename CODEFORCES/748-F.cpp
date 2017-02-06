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

int count1[200010];
int dp1[200010];
int dp2[200010];
vi nodes;
int size1[200010];
vi Adj[200010];
bool deleted[200010];

void calcSize(int u,int p){
	size1[u]=1;
	dp1[u]+=count1[u];
	rep(t1,Adj[u]){
		if(t1!=p && !deleted[t1]){
			calcSize(t1,u);
			size1[u]+=size1[t1];
			dp1[u]+=dp1[t1];
		}
	}
}

int getCentriod(int u,int p,int compSize){
	rep(t1,Adj[u]){
		if(t1!=p && !deleted[t1]){
			if(2*dp1[t1]>compSize){
				return getCentriod(t1,u,compSize);
			}
		}
	}
	return u;
}

void DFS(int u,int p){
	rep(t1,Adj[u]){
		if(t1!=p){
			DFS(t1,u);
		}
	}
	while(count1[u]!=0){
		nodes.pb(u);count1[u]--;
	}
}

int main(){
	int n,k;
	scanf("%d%d",&n,&k);

	For(i,1,n){
		int a1,b1;
		scanf("%d%d",&a1,&b1);
		Adj[a1].pb(b1);
		Adj[b1].pb(a1);
	}

	For(j,0,2*k){
		int temp;scanf("%d",&temp);
		count1[temp]++;
	}

	calcSize(1,0);
	int root1=getCentriod(1,0,2*k);
	DFS(root1,0);

	printf("%d\n%d\n",1,root1);

	For(i,0,k){
		printf("%d %d %d\n",nodes[i],nodes[i+k],root1);
	}
return 0;}
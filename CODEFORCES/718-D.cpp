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
#define N 100010
const string debug_line="yolo";
#define debug error(debug_line)
#define read() freopen("mergedoutput.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
//template <typename T> using os =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);
const long double eps=1e-6;

vi Adj[100010];
bool visited[100010];
int counter1=0;
int b[100010];
int a[100010];
map<vi,int> mp1;

void DFS(int u,int p){
	visited[u]=true;
	vi res;
	rep(t1,Adj[u]){
		if(t1!=p){
			DFS(t1,u);
			res.pb(a[t1]);
		}
	}
	while(res.size()!=4){
		res.pb(-1);
	}
	sort(all(res));
	if(mp1.count(res)==0){
		mp1[res]=counter1++;
	}
	// Error(u,mp1[res]);
	a[u]=mp1[res];
}

void revDFS(int u,int p,int prev1){
	// error(u);
	visited[u]=true;
	vi res;
	rep(t1,Adj[u]){
		if(t1!=p){
			res.pb(a[t1]);
		}
	}
	if(u!=1){
		res.pb(prev1);
	}
	while(res.size()<4){
		res.pb(-1);
	}
	// error(u);
	// rep(t1,res){
	// 	printf("%d ",t1);
	// }
	// printf("\n");
	sort(all(res));
	if(mp1.count(res)==0){
		mp1[res]=counter1++;
	}
	b[u]=mp1[res];
	rep(t1,Adj[u]){
		if(t1!=p){
			vi res1;
			rep(t2,Adj[u]){
				if(t2!=t1 && t2!=p){
					res1.pb(a[t2]);
				}
				else if(t2!=t1 && t2==p){
					res1.pb(prev1);
				}
			}
			while(res1.size()<4){
				res1.pb(-1);
			}
			sort(all(res1));
			if(mp1.count(res1)==0){
				mp1[res1]=counter1++;
			}
			revDFS(t1,u,mp1[res1]);
		}
	}
}

int main(){
	int n;
	scanf("%d",&n);

	For(i,1,n){
		int u1,v1;
		scanf("%d%d",&u1,&v1);
		Adj[u1].pb(v1);
		Adj[v1].pb(u1);
	}

	DFS(1,0);
	memset(visited,0,sizeof(visited));
	// error(counter1);
	debug;
	revDFS(1,0,-1);
	debug;
	int answer1=0;
	set<int> s1;
	For(i,1,n+1){
		if(Adj[i].size()<=3){
			s1.insert(b[i]);
		}
	}
	printf("%d\n",(int)s1.size());
return 0;}
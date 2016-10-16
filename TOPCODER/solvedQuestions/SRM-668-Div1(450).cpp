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

class WalkingToSchool
{
public:
	int n;
	vi Adj[2010];
	vi rAdj[2010];
	vi from0;
	vi from1;
	vi rfrom1;
	vi primes;
	bool isPrime[2010];
	vi color;

	void DFS(int u,vi &visited){
		visited[u]=true;
		// error(u);
		rep(t1,Adj[u]){
			if(!visited[t1]){
				DFS(t1,visited);
			}
		}
	}

	void DFS1(int u,vi &visited){
		visited[u]=true;
		rep(t1,rAdj[u]){
			if(!visited[t1]){
				DFS1(t1,visited);
			}
		}
	}

	void calc(){
		For(i,2,2010){
			isPrime[i]=true;
		}
		For(i,2,2010){
			if(isPrime[i]){
				primes.pb(i);
				for(int j=i+i;j<2010;j=j+i){
					isPrime[j]=false;
				}
			}
		}
	}

	bool ifColor(int u,int col,int p){
		if(!from0[u] || !rfrom1[u]){
			return true;
		}
		if(color[u]==-1){
			color[u]=col;
			rep(t1,Adj[u]){
				if(color[t1]==-1){
					if(!ifColor(t1,(col+1)%p,p)){
						return false;
					}
				}
				else if((color[u]+1)%p!=color[t1]){
					return false;
				}
			}
			return true;
		}
		else{
			if(color[u]==col){
				return true;
			}
			else{
				return false;
			}
		}
	}

	bool tryColor(int u,int p){
		color.clear();
		color.resize(n,-1);
		return ifColor(u,0,p);
	}

	string canWalkExactly(int n,vi from,vi to){
		this->n=n;
		For(i,0,n){
			Adj[i].clear();
			rAdj[i].clear();
		}
		assert(from.size()==to.size());
		error(from.size());
		from0.clear();
		from1.clear();
		rfrom1.clear();
		from0.resize(n,0);
		from1.resize(n,0);
		rfrom1.resize(n,0);
		For(i,0,from.size()){
			// Error(from[i],to[i]);
			Adj[from[i]].pb(to[i]);
			rAdj[to[i]].pb(from[i]);
		}
		DFS(0,from0);
		DFS(1,from1);
		DFS1(1,rfrom1);
		calc();
		Error(from0[1],from1[0]);
		debug;
		if(!(from0[1] && from1[0])){
			return "Chores";
		}
		else{
			rep(prime,primes){
				if(tryColor(0,prime)){
					// error(prime);
					return "Chores";
				}
			}
			return "Freedom";
		}
	}
};

// int main(){
// 	int n=5;
// 	vi from={0,2,3,0,4,1};
// 	vi to={2,3,2,4,1,0};
// 	WalkingToSchool wts;
// 	error(wts.canWalkExactly(n,from,to));
// }
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
#define errop(a) cerr<<#a<<" = ( "<<((a).x)<<" , "<<((a).y)<<" )\n";
#define coud(a,b) cout<<fixed << setprecision((b)) << (a)
#define L(x) (((x)<<1)+1)
#define R(x) (((x)<<1)+2)
#define umap unordered_map
//#define double long double
#define mod 1000000007
// #define mod1 1000000009
#define LIMIT 10000000000000000LL
#define INF 10000000000LL
#define MAX1 1000000000
//#define si(n) scanf("%d",&n)
//#define sii(n,m) scanf("%d%d",&n,&m)
//#define pi(n) printf("%d\n",n)
const int inf=0x3f3f3f3f;
const long double pi=acos(-1.0);
#define MAX 50010
#define N 100000
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

class SubtreeSum
{
public:
	bool visited[101];
	vi Adj[101];
	int w[101];
	bool deleted[101];
	int bitIndex=0;
	bool color[101];

	ll size1(int node,int p=-1){
		ll answer1=1;
		rep(t1,Adj[node]){
			if(!visited[t1] && !deleted[t1] && t1!=p){
				answer1=(answer1*(1+size1(t1,node)))%mod;
			}
		}
		return answer1;
	}

	ll recurse(int node){
		ll answer1=1;
		deleted[node]=true;
		rep(t1,Adj[node]){
			if(!visited[t1] && !deleted[t1]){
				answer1=(answer1*(1+size1(t1)))%mod;
			}
		}
		rep(t1,Adj[node]){
			if(!visited[t1] && !deleted[t1]){
				answer1=(answer1+recurse(t1))%mod;
			}
		}
		return answer1;
	}

	ll getAll(int node){
		ll answer1=1;
		deleted[node]=true;
		rep(t1,Adj[node]){
			if(!visited[t1] && !deleted[t1]){
				answer1=(answer1*(1+size1(t1)))%mod;
			}
		}
		rep(t1,Adj[node]){
			if(!visited[t1] && !deleted[t1]){
				answer1=(answer1+getAll(t1))%mod;
			}
		}
		return answer1;
	}

	ll tryAll(int index,int n){
		ll answer1=0;
		For(i,0,n){
			if(w[i] & (1<<index)){
				color[i]=true;
			}
			else{
				color[i]=false;
			}
		}
		For(i,0,n){
			if(color[i]==1){
				deleted[i]=true;
			}
		}
		For(i,0,n){
			if(!deleted[i] && !visited[i]){
				answer1=(answer1+recurse(i))%mod;
			}
		}
		return answer1;
	}


	int getSum(vector<int> p,vector<int> x){
		ll answer1=0;
		int n=x.size();
		For(i,0,n){
			w[i]=x[i];
		}

		For(i,0,n-1){
			Adj[i+1].pb(p[i]);
			Adj[p[i]].pb(i+1);
		}

		For(i,0,n+1){
			color[i]=false;
			visited[i]=false;
		}

		ll allSub=getAll(0);

		For(i,0,32){
			bitIndex=i;
			ll temp1=(1LL<<i);
			For(j,0,n+1){
				visited[j]=false;
				deleted[j]=false;
				color[j]=false;
			}
			// Error(i,allSub);
			//get all the subtrees in the tree
			ll temp2=tryAll(i,n);
			temp2=((allSub-temp2)%mod+mod)%mod;
			answer1=(answer1+(temp1*temp2)%mod)%mod;
			// Error(i,answer1);
		}
		return answer1;
	}
};

int main(){
	SubtreeSum *sum=new SubtreeSum();
	vi p={0,0,1,0,2,2,3,0,0,2,1};
	vi x={4,5,6,7,0,8,9,5,1,2,3,6};
	assert((int)p.size()+1==(int)x.size());
	error((*sum).getSum(p,x));
}
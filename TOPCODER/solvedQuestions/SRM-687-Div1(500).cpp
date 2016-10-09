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

//https://en.wikipedia.org/wiki/Gomory%E2%80%93Hu_tree
class AllGraphCuts
{
public:
	vi parent;
	vi child;
	vector<pii> Adj[51];
	int countNodes;

	int parent1(int index){
		while(parent[index]!=index){
			index=parent[index];
		}
		return index;
	}

	void DFS(int u,int p,vi &res){
		rep(t1,Adj[u]){
			if(t1.x!=p){
				res.pb(t1.y*countNodes*countNodes+t1.x*countNodes+u);
				DFS(t1.x,u,res);
			}
		}
	}

	void merge(int x2,int y2,int cost1){
		int x1=parent1(x2);
		int y1=parent1(y2);
		assert(x1!=y1);
		Adj[x1].pb(mp(y1,cost1));
		Adj[y1].pb(mp(x1,cost1));
		if(child[x1]>child[y1]){
			child[x1]+=child[y1];
			parent[y1]=parent[x1];
		}
		else{
			child[y1]+=child[x1];
			parent[x1]=parent[y1];
		}
	}

	void DFS1(int u,int v,vi &minEdges,int &minEdge,int p=-1){
		if(u==v){
			int minNow=INT_MAX;
			rep(t1,minEdges){
				minNow=min(minNow,t1);
			}
			minEdge=minNow;
		}
		rep(t1,Adj[u]){
			if(t1.x!=p){
				minEdges.pb(t1.y);
				DFS1(t1.x,v,minEdges,minEdge,u);
				minEdges.PB;
			}
		}
	}

	bool isPoss(int u,int v,int cost1){
		int minEdge=INT_MAX;
		vi minEdges;
		DFS1(u,v,minEdges,minEdge,-1);
		if(minEdge!=cost1){
			return false;
		}
		else{
			return true;
		}
	}

	vector<int> findGraph(vector<int> x){
		int n=x.size();
		n=sqrt(n);
		countNodes=n;
		vector<pair<pii,int> > edges;
		For(i,0,n){
			For(j,0,n){
				edges.pb(mp(mp(x[i*n+j],i),j));
			}
		}
		sort(all(edges));
		reverse(all(edges));
		parent.resize(countNodes+1);
		child.resize(countNodes+1);
		For(i,0,n){
			parent[i]=i;
			child[i]=1;
		}

		rep(edge,edges){
			int cost1=edge.x.x;
			int u=edge.x.y;
			int v=edge.y;
			if(parent1(u)!=parent1(v)){
				merge(u,v,cost1);
			}
		}

		bool poss=true;

		For(i,0,n){
			For(j,0,n){
				if(i==j){
					if(x[i*n+j]!=0){
						poss=false;
					}
				}
				else{
					poss=poss & isPoss(i,j,x[i*n+j]);
				}
			}
		}
		vector<int> res;
		if(!poss){
			res={-1};
			return res;
		}
		else{
			DFS(0,-1,res);
			return res;
		}
	}
};

int main(){
	AllGraphCuts agc;
	vi x={0,0,0,0};
	vi temp=agc.findGraph(x);
	rep(t1,temp){
		error(t1);
	}
}
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

struct edge{
	int x1,y1;
	ll w1,p1;

	edge(int _x1,int _y1,ll _w1,ll _p1){
		x1=_x1;y1=_y1;w1=_w1;p1=_p1;
	}
};

vector<edge> e;
vi Adj[200010];
ll totalWeight;
int outEdges[200010];
ll f[200010];
int size1[200010];
int dfs_timer=1;
int begin1[200010];
int discover[200010];
bool poss=true;
int n;
deque<int> Q1[200010];

void update(int index,ll val){
	for(;index<=n;index+=index&(-index)){
		f[index]+=val;
	}
}

ll query(int index){
	ll answer1=0;
	for(;index>0;index-=index&(-index)){
		answer1+=f[index];
	}
	return answer1;
}

ll query(int a,int b){
	ll answer1=query(b)-query(a-1);
	return answer1;
}

void DFS0(int u,int p){
	begin1[u]=dfs_timer++;
	size1[u]=1;
	rep(t1,Adj[u]){
		if(e[t1].y1!=p){
			// Error(u,e[t1].y1);
			DFS0(e[t1].y1,u);
			size1[u]+=size1[e[t1].y1];
		}
	}
}

void mergeAll(int from,int to){
	while(!Q1[from].empty()){
		Q1[to].push_back(Q1[from].front());
		Q1[from].pop_front();
	}
}

void DFS(int u,int p){
	// Error(u,p);
	int bigChild=-1;
	int currSize=0;
	bool isLeaf=true;
	rep(t1,Adj[u]){
		if(e[t1].y1!=p){
			isLeaf=false;
			DFS(e[t1].y1,u);
			// Error3(u,e[t1].y1,Q1[e[t1].y1].size());
			if(size1[e[t1].y1]>currSize){
				currSize=size1[e[t1].y1];bigChild=e[t1].y1;
			}
			// Q1[e[t1].y1].push_back(t1);
		}
	}

	if(isLeaf){
		return;
	}

	rep(t1,Adj[u]){
		if(e[t1].y1!=p){
			totalWeight=query(begin1[e[t1].y1],begin1[e[t1].y1]+size1[e[t1].y1]-1);
			ll needToReduce=totalWeight-e[t1].p1;
			while(needToReduce>0){
				if(Q1[e[t1].y1].empty()){
					break;
				}
				edge e1=e[Q1[e[t1].y1].front()];
				ll from=e1.y1;ll cap=e1.p1;ll w1=e1.w1;
				ll subTree=query(begin1[from],begin1[from]+size1[from]-1);
				ll canReduce=min(needToReduce,min(w1-1,max(0LL,cap-subTree)));
				if(canReduce==0){
					Q1[e[t1].y1].pop_front();
				}
				else{
					needToReduce-=canReduce;
					int index=Q1[e[t1].y1].front();
					e[index].w1-=canReduce;e[index].p1-=canReduce;
					update(begin1[e[t1].x1],-canReduce);
				}
			}
			if(needToReduce>0){
				poss=false;
			}
		}
	}

	rep(t1,Adj[u]){
		if(e[t1].y1!=p && e[t1].y1!=bigChild){
			mergeAll(e[t1].y1,bigChild);
		}
	}
	Q1[u]=Q1[bigChild];
	rep(t1,Adj[u]){
		if(e[t1].y1!=p){
			Q1[u].push_back(t1);
		}
	}
	// Error(u,Q1[u].size());
}

int main(){
	scanf("%d",&n);
	For(i,1,n){
		int x1,y1,w1,p1;
		scanf("%d%d%d%d",&x1,&y1,&w1,&p1);
		edge e1={x1,y1,(ll)w1,(ll)p1};
		Adj[x1].pb((int)e.size());
		outEdges[x1]++;
		e.pb(e1);
	}

	DFS0(1,0);

	// For(i,1,n+1){
	// 	Error3(i,begin1[i],begin1[i]+size1[i]-1);
	// }

	rep(edge,e){
		update(begin1[edge.x1],edge.w1);
	}

	DFS(1,0);
	if(!poss){
		printf("-1\n");
	}
	else{
		printf("%d\n",n);
		// printf("%lld\n",query(begin1[1],begin1[1]+size1[1]-1));
		rep(edge,e){
			printf("%d %d %lld %lld\n",edge.x1,edge.y1,edge.w1,edge.p1);
		}
	}
return 0;}
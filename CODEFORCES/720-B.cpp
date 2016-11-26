#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・

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

vector<pii> Adj[10010];
stack<pii> s1;
bool visited[10010];
bool inStack[10010];
int edge1[1000010];
bool inCycle[1000010];
bool canSelect[1000010];
bool addToAnswer[1000010];
vector<vi> groups;

void printStack(){
	vector<pii> entreis;
	while(!s1.empty()){
		entreis.pb(s1.top());
		s1.pop();
	}
	rep(t1,entreis){
		Error(t1.x,t1.y);
	}
	printf("\n");
	reverse(all(entreis));
	rep(t1,entreis){
		s1.push(t1);
	}
}

void DFS(int u,int p){
	// error(u);
	// printStack();
	visited[u]=true;
	rep(t1,Adj[u]){
		if(!visited[t1.x]){
			s1.push(mp(u,t1.y));
			inStack[u]=true;
			DFS(t1.x,u);
			inStack[u]=false;
			s1.pop();
		}
		else if(visited[t1.x] && inStack[t1.x]){
			int nowEdge=t1.y;
			int nowNode=t1.x;
			vi edges;
			vi nodes;
			// debug;
			if(s1.empty()){
				printf("error");
				assert(false);
			}
			assert(!s1.empty());
			// debug;
			// Error(s1.top().y,nowEdge);
			if(s1.top().y==nowEdge){
				continue;
			}
			else{
				// Error4("found cycle with",u,t1.x,t1.y);
				// printStack();
				while(true){
					nodes.pb(s1.top().x);
					edges.pb(s1.top().y);
					if(s1.top().x==t1.x){
						s1.pop();
						break;
					}
					s1.pop();
				}
				reverse(all(edges));
				reverse(all(nodes));
				For(i,0,edges.size()){
					s1.push(mp(nodes[i],edges[i]));
				}
				edges.pb(nowEdge);
				// error("cycle");
				// rep(t1,edges){
				// 	printf("%d ",t1);
				// }
				// printf("\n");
				groups.pb(edges);
			}
		}
	}
}

struct edge {
   int x, y, cap, flow;
};
 
struct DinicFlow {
   vector <edge> e;
   vector <int> cur, d;
   vector < vector <int> > adj;
   int n, source, sink;
 
   DinicFlow() {}
 
   DinicFlow(int v) {
       n = v;
       cur = vector <int> (n + 1);
       d = vector <int> (n + 1);
       adj = vector < vector <int> > (n + 1);
   }
 
   void addEdge(int from, int to, int cap) {
       edge e1 = {from, to, cap, 0};
       edge e2 = {to, from, 0, 0};
       adj[from].push_back(e.size()); e.push_back(e1);
       adj[to].push_back(e.size()); e.push_back(e2);
   }
 
   int bfs() {
       queue <int> q;
       for(int i = 0; i <= n; ++i) d[i] = -1;
       q.push(source); d[source] = 0;
       while(!q.empty() and d[sink] < 0) {
           int x = q.front(); q.pop();
           for(int i = 0; i < (int)adj[x].size(); ++i) {
               int id = adj[x][i], y = e[id].y;
               if(d[y] < 0 and e[id].flow < e[id].cap) {
                   q.push(y); d[y] = d[x] + 1;
               }
           }
       }
       return d[sink] >= 0;
   }
 
   int dfs(int x, int flow) {
       if(!flow) return 0;
       if(x == sink) return flow;
       for(;cur[x] < (int)adj[x].size(); ++cur[x]) {
           int id = adj[x][cur[x]], y = e[id].y;
           if(d[y] != d[x] + 1) continue;
           int pushed = dfs(y, min(flow, e[id].cap - e[id].flow));
           if(pushed) {
               e[id].flow += pushed;
               e[id ^ 1].flow -= pushed;
               return pushed;
           }
       }
       return 0;
   }
 
   int maxFlow(int src, int snk) {
       this->source = src; this->sink = snk;
       int flow = 0;
       while(bfs()) {
           for(int i = 0; i <= n; ++i) cur[i] = 0;
           while(int pushed = dfs(source, inf)) {
               flow += pushed;
           }
       }
       return flow;
   }
};
int main(){
	int n,m;
	scanf("%d%d",&n,&m);

	For(i,0,m){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		edge1[i]=c;
		Adj[a].pb(mp(b,i));
		Adj[b].pb(mp(a,i));
	}

	DFS(1,0);
	int nodes=200000+100;
	// debug;
	DinicFlow df(nodes);
	int src=0;
	int snk=nodes-1;
	int currentCycle=1;
	For(i,1,m+1){
		// Error3(i+(int)groups.size(),snk,1);
		df.addEdge(i+m+(int)groups.size()+10,snk,1);
	}
	rep(cycle,groups){
		// Error3(src,,currentCycle,(int))
		df.addEdge(src,m+currentCycle+10,(int)cycle.size()-1);
		rep(t1,cycle){
			// printf("%d ",edge1[t1]);
			inCycle[t1]=true;
			df.addEdge(m+currentCycle+10,edge1[t1]+(int)groups.size()+m+10,1);
		}
		// printf("\n");
		currentCycle++;
	}
	For(i,0,m){
		if(!inCycle[i]){
			df.addEdge(src,i+1,1);
			df.addEdge(i+1,(int)groups.size()+m+10+edge1[i],1);
		}
	}
	int answer1=df.maxFlow(src,snk);
	
	// For(i,0,m){
	// 	if(!inCycle[i]){
	// 		canSelect[edge1[i]]=true;
	// 		// Error("color ",edge1[i]);
	// 	}
	// }

	// For(i,0,df.e.size()){
	// 	if(df.e[i].y==snk && df.e[i].flow!=1 && canSelect[df.e[i].x-(int)groups.size()]){
	// 		addToAnswer[df.e[i].x-(int)groups.size()]=true;
	// 		// error(df.e[i].x-30000);
	// 	}
	// }

	// For(i,1,m+1){
	// 	if(addToAnswer[i]){
	// 		answer1++;
	// 	}
	// }
	
	printf("%d\n",answer1);
return 0;}

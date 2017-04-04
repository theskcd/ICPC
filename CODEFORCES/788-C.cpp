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

bool marked[1010];
vi colNum;
vi Adj[2010];
bool visited[2010];
int SHIFT=1000;
int dist[2010];
int answer1;

void BFS(){
	answer1=INT_MAX;
	// visited[SHIFT]=true;
	For(i,0,2010){
		visited[i]=false;dist[i]=INT_MAX;
	}

	priority_queue<pii,vector<pii>,greater<pii> > Q1;
	Q1.push(mp(0,SHIFT));
	while(!Q1.empty()){
		pii u=Q1.top();
		// Error(u.F,u.S);
		Q1.pop();
		if(!visited[u.S]){
			visited[u.S]=true;
			dist[u.S]=u.F;
			rep(goTo,Adj[u.S]){
				if(!visited[goTo] && dist[goTo]>dist[u.S]+1){
					dist[goTo]=dist[u.S]+1;
					Q1.push(mp(dist[goTo],goTo));
				}
				else{
					if(goTo==SHIFT){
						answer1=min(answer1,dist[u.S]+1);
					}
				}
			}
		}
	}
}

int main(){
	int n,k;
	scanf("%d%d",&n,&k);

	For(i,0,k){
		int temp1;
		scanf("%d",&temp1);
		marked[temp1]=true;
	}

	For(i,0,1010){
		if(marked[i]){
			colNum.pb(i-n);
		}
	}

	For(i,0,2010){
		rep(edge,colNum){
			if(i+edge>=0 && i+edge<=2001){
				Adj[i].pb(i+edge);
			}
		}
	}

	BFS();
	if(answer1!=INT_MAX){
		printf("%d\n",answer1);
	}
	else{
		printf("-1\n");
	}
return 0;}
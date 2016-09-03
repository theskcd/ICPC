#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

#pragma comment(linker, "/STACK:16777216")

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

struct query{
	int type;
	int i,j;
	int index;
	query(int _type,int _index,int _i,int _j){
		type=_type;
		index=_index;
		i=_i;
		j=_j;
	};
};

bitset<1001> shelf[1001];
int answer1[100010];
vi Adj[100010];
vector<query> queries;
int parent1[100010];
int currAnswer=0;
int n,m;

int parent(int u){
	while(parent1[u]!=u){
		u=parent1[u];
	}
	return u;
}

void DFS(int u,int p){
	// Error(u,p);
	bitset<1001> temp1;
	int prevAns=currAnswer;
	if(queries[u].type==1){
		temp1=shelf[queries[u].i];
		if(shelf[queries[u].i][queries[u].j]==0){
			currAnswer++;
			shelf[queries[u].i][queries[u].j]=1;
		}
		answer1[u]=currAnswer;
		rep(t1,Adj[u]){
			if(t1!=p){
				DFS(t1,u);
			}
		}
		shelf[queries[u].i]=temp1;
		currAnswer=prevAns;
	}
	else if(queries[u].type==2){
		temp1=shelf[queries[u].i];
		if(shelf[queries[u].i][queries[u].j]==1){
			currAnswer--;
			shelf[queries[u].i][queries[u].j]=0;
		}
		answer1[u]=currAnswer;
		rep(t1,Adj[u]){
			if(t1!=p){
				DFS(t1,p);
			}
		}
		shelf[queries[u].i]=temp1;
		currAnswer=prevAns;
	}
	else if(queries[u].type==3){
		temp1=shelf[queries[u].i];
		For(j,0,m){
			if(shelf[queries[u].i][j]==1){
				currAnswer--;
			}
			else{
				currAnswer++;
			}
		}
		For(j,0,m){
			shelf[queries[u].i][j]=!shelf[queries[u].i][j];
		}
		answer1[u]=currAnswer;
		rep(t1,Adj[u]){
			if(t1!=p){
				DFS(t1,u);
			}
		}
		shelf[queries[u].i]=temp1;
		currAnswer=prevAns;
	}
	else{
		if(queries[u].type==-1){
			rep(t1,Adj[u]){
				DFS(t1,u);
			}
		}
		else{
			assert(false);
		}
	}
}

int main(){
	int q;
	scanf("%d%d%d",&n,&m,&q);
	queries.pb(query(-1,-1,-1,-1));
	int root=0;

	For(i,1,q+1){
		parent1[i]=i;
	}

	For(i,1,q+1){
		int type;
		scanf("%d",&type);
		// Error(root,i);
		if(type==1){
			int i1,j1;
			scanf("%d%d",&i1,&j1);
			query newQuery(type,i,i1,j1-1);
			queries.pb(newQuery);
			Adj[root].pb(i);
			root=i;
		}
		else if(type==2){
			int i1,j1;
			scanf("%d%d",&i1,&j1);
			query newQuery(type,i,i1,j1-1);
			queries.pb(newQuery);
			Adj[root].pb(i);
			root=i;
		}
		else if(type==3){
			int i1;
			scanf("%d",&i1);
			query newQuery(type,i,i1,0);
			queries.pb(newQuery);
			Adj[root].pb(i);
			root=i;
		}
		else if(type==4){
			int i1;
			scanf("%d",&i1);
			int temp1=parent(i1);
			query newQuery(type,i,temp1,0);
			queries.pb(newQuery);
			parent1[i]=temp1;
			root=temp1;
		}
	}

	DFS(0,0);

	For(j,1,q+1){
		if(queries[j].type!=4){
			printf("%d\n",answer1[j]);
		}
		else{
			printf("%d\n",answer1[queries[j].i]);
		}
	}
return 0;}
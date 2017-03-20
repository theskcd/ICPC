#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

// using namespace __gnu_pbds;
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
#define MAX 810
// #define N 100010
const string debug_line="yolo";
#define debug error(debug_line)
#define read() freopen("mergedoutput.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef unsigned long long ull;
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);
const long double eps=1e-6;
// typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> os;
ull getRand(){return ((ull)rand()<<40)+((ull)rand()<<20)+((ull)rand());}

struct node1{
	int val1[5];
	ll delta;
	int lazyp;
};
int n,k;
node1 tree[800040];
int level1[200010];
bool visited[200010];
vi Adj[200010];
ll permaAnswer=0;
ll answer1=0;
int discover[200010];
int begin1[200010];
int size1[200010];
int timer=1;

void merge(int n1,int n2,int n3){
	For(i,0,k){
		tree[n1].val1[i]=tree[n2].val1[i]+tree[n3].val1[i];
	}
	tree[n1].delta=tree[n2].delta+tree[n3].delta;
}

void initialise(int node,int b,int e){
	if(b>e){
		return ;
	}
	else if(b==e){
		tree[node].val1[level1[discover[b]]%k]++;
		tree[node].delta=0;
		if(discover[b]==1){
			tree[node].cZero=1;
		}
	}
	else{
		initialise(2*node,b,(b+e)/2);
		initialise(2*node+1,(b+e)/2+1,e);
		For(i,0,k){
			tree[node].val1[i]=(tree[2*node].val1[i]+tree[2*node+1].val1[i]);
		}
		tree[node].delta=0;
		tree[node].cZero=tree[2*node].cZero+tree[2*node+1].cZero;
	}
}

// check if this works >.< 
void updateLazyNode(int node,int b,int e){
	if(tree[node].lazyp!=0){
		Error5("updateLazyNode",node,b,e,tree[node].lazyp);
		For(i,0,k){
			printf("%d ",tree[node].val1[i]);
		}
		printf("\n");
		ll delta1=tree[node].lazyp/k;ll answer2=0;
		ll modulo=tree[node].lazyp%k;
		if(modulo<0){
			For(i,0,-modulo){
				answer2-=tree[node].val1[i];
			}
		}
		else if(modulo>0){
			For(i,k-modulo,k){
				answer2+=tree[node].val1[i];
			}
		}
		For(i,0,k){
			answer2=answer2+delta1*(ll)tree[node].val1[i];
		}
		error(answer2);
		tree[node].delta+=answer2;
		vector<int> temp1;temp1.resize(k+1,0);
		For(i,0,k){
			temp1[((i+tree[node].lazyp)%k+k)%k]=tree[node].val1[i];
		}
		For(i,0,k){
			tree[node].val1[i]=temp1[i];
		}
		if(b!=e){
			tree[2*node].lazyp+=tree[node].lazyp;
			tree[2*node+1].lazyp+=tree[node].lazyp;
		}
		tree[node].lazyp=0;
	}
}

void update(int node,int b,int e,int i,int j,bool increment){
	updateLazyNode(node,b,e);
	if(b>e || i>e || j<b){
		return ;
	}
	else if(i<=b && e<=j){
		if(increment){
			tree[node].lazyp++;
		}
		else{
			tree[node].lazyp--;
		}
		updateLazyNode(node,b,e);
	}
	else{
		update(2*node,b,(b+e)/2,i,j,increment);
		update(2*node+1,(b+e)/2+1,e,i,j,increment);
		merge(node,2*node,2*node+1);
	}
}

ll query(int node,int b,int e,int i,int j){
	updateLazyNode(node,b,e);
	if(b>e || i>e || j<b){
		return 0;
	}
	else if(i<=b && e<=j){
		updateLazyNode(node,b,e);
		return tree[node].delta;
	}
	else{
		return query(2*node,b,(b+e)/2,i,j)+query(2*node+1,(b+e)/2+1,e,i,j);
	}
}

void DFS(int u,int p,int level){
	level1[u]=level;
	begin1[u]=timer++;
	discover[begin1[u]]=u;
	size1[u]=1;
	rep(t1,Adj[u]){
		if(t1!=p){
			DFS(t1,u,level+1);
			size1[u]+=size1[t1];
		}
	}
}

void revDFS(int u,int p){
	error(u);
	For(i,0,k){
		printf("%d ",tree[1].val1[i]);
	}
	printf("\n");
	answer1=answer1+permaAnswer+query(1,1,n,1,n);
	error(tree[1].delta);
	rep(t1,Adj[u]){
		if(t1!=p){
			update(1,1,n,begin1[t1],begin1[t1]+size1[t1]-1,0);
			Error3(begin1[t1],begin1[t1]+size1[t1]-1,0);
			update(1,1,n,1,begin1[t1]-1,1);
			Error3(1,begin1[t1]-1,1);
			update(1,1,n,begin1[t1]+size1[t1],n,1);
			Error3(begin1[t1]+size1[t1],n,1);
			revDFS(t1,u);
			update(1,1,n,begin1[t1]+size1[t1],n,0);
			update(1,1,n,1,begin1[t1]-1,0);
			update(1,1,n,begin1[t1],begin1[t1]+size1[t1]-1,1);
		}
	}
}

int main(){
	scanf("%d%d",&n,&k);

	For(i,1,n){
		int a1,b1;
		scanf("%d%d",&a1,&b1);
		Adj[a1].pb(b1);
		Adj[b1].pb(a1);
	}

	DFS(1,0,0);
	initialise(1,1,n);
	For(i,1,n+1){
		Error(i,level1[i]);
		Error3(i,begin1[i],begin1[i]+size1[i]-1);
		permaAnswer=permaAnswer+(ll)level1[i]/k;
		if(level1[i]%k!=0){
			permaAnswer++;
		}
	}
	error(permaAnswer);
	revDFS(1,0);
	error(answer1);
	assert(answer1%2==0);
	printf("%lld\n",answer1/2);
return 0;}
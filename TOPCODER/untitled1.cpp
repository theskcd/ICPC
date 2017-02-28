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

struct Trie{
	Trie *next1[26];
	int size1;
	int occur;
	Trie(){
		size1=1;
		occur=1;
		For(i,0,26){
			next1[i]=NULL;
		}
	}
};

vector<pii> Adj[300010];
int level1[300010];
int size1[300010];
int delta1[300010];
Trie *madeTries[300010];
bool visited[300010];

void DFS(int u,int p){
	visited[u]=true;
	madeTries[u]=new Trie();
	size1[u]=1;
	level1[u]=level1[p]+1;
	rep(t1,Adj[u]){
		if(!visited[t1.x]){
			DFS(t1.x,u);
			madeTries[u]->next1[t1.y]=madeTries[t1.x];
			madeTries[u]->occur+=madeTries[t1.x]->occur;
			madeTries[u]->size1+=madeTries[t1.x]->size1;
			size1[u]+=size1[t1.x];
		}
	}
	// Error(u,madeTries[u]->size1);
}


//TODO: fix size and occur to clear the trie and reset it
int mergeNode(Trie *trie1,int node1){
	// trie1->size1=1;
	int newNodesAdded=0;
	rep(t1,Adj[node1]){
		if(trie1->next1[t1.y]==NULL){
			trie1->next1[t1.y]=new Trie();
			newNodesAdded++;
			newNodesAdded+=mergeNode(trie1->next1[t1.y],t1.x);
			trie1->size1+=trie1->next1[t1.y]->size1;
		}
		else{
			trie1->next1[t1.y]->occur++;
			newNodesAdded+=mergeNode(trie1->next1[t1.y],t1.x);
			trie1->size1+=trie1->next1[t1.y]->size1;
		}
	}
	trie1->size1+=newNodesAdded;
	return newNodesAdded;
}

int removeNode(Trie *trie1,int node1){
	int removeNodes=0;
	rep(t1,Adj[node1]){
		removeNodes+=removeNode(trie1->next1[t1.y],t1.x);
		trie1->next1[t1.y]->occur--;
		if(trie1->next1[t1.y]->occur==0){
			trie1->next1[t1.y]=NULL;
			trie1->size1--;
		}
	}
}

void check(Trie *trie,int node){
	// Error("entering check",node);
	rep(t1,Adj[node]){
		check(trie->next1[t1.y],t1.x);
	}
	// Error("exiting check",node);
}

void DFS1(int u,int p){
	// Error(u,p);
	int maxSize1=-1;
	int maxNode=-1;
	rep(t1,Adj[u]){
		if(t1.x!=p){
			if(madeTries[t1.x]->size1>maxSize1){
				maxSize1=madeTries[t1.x]->size1;
				maxNode=t1.x;
			}
		}
	}
	// Error(u,maxNode);
	if(maxNode==-1){
		return ;
	}
	Error3(u,maxNode,maxSize1);
	rep(t1,Adj[u]){
		if(t1.x!=p && t1.x!=maxNode){
			// Error3("merging",t1.x,maxNode);
			mergeNode(madeTries[maxNode],t1.x);
		}
	}
	Error4(u,level1[u],madeTries[maxNode]->size1,size1[u]);
	delta1[level1[u]]+=size1[u]-madeTries[maxNode]->size1;
	// Error(u,delta1[u]);
	rep(t1,Adj[u]){
		if(t1.x!=p && t1.x!=maxNode){
			removeNode(madeTries[maxNode],t1.x);
		}
	}
	check(madeTries[maxNode],maxNode);
	rep(t1,Adj[u]){
		if(t1.x!=p){
			DFS1(t1.x,u);
			// Error3("returned from",u,t1.x);
		}
	}
}

int main(){
	int n;
	scanf("%d",&n);
	For(i,1,n){
		int a1,b1;
		char c1[2];
		scanf("%d%d%s",&a1,&b1,c1);
		// Error3(a1,b1,c1[0]-'a');
		Adj[a1].pb(mp(b1,c1[0]-'a'));
		// getchar();
	}

	DFS(1,0);
	DFS1(1,0);
	// debug;
	int min1=INT_MAX;
	int levelVal=-1;
	// Error(1,size1[1]);
	For(i,0,n+1){
		// Error(i,delta1[i]);
		if(size1[1]-delta1[i]<min1){
			// Error3(size1[1],delta1[i],size1[1]+delta1[i]);
			min1=size1[1]-delta1[i];
			levelVal=i;
		}
	}
	// Error3(size1[1],min1,levelVal);
	printf("%d\n",min1);
	printf("%d\n",levelVal);
	// debug;
return 0;}

//TODO http://codeforces.com/contest/778/problem/C
// http://codeforces.com/problemset/problem/521/E
// http://codeforces.com/problemset/problem/478/E editorial http://codeforces.com/blog/entry/14307#comment-192751
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

typedef struct node2{
	int minVal;
	vi nums;
}node1;

node1 tree[400040];
vector<pii> Adj[100010];
int a1[100010];
int answerQ[300010];
int rlm=1;
int answer1;
int n,m;

void initialise(int node,int b,int e){
	if(b==e){
		tree[node].nums.pb(a1[b]);
		tree[node].minVal=(1<<30);
	}
	else{
		initialise(2*node,b,(b+e)/2);
		initialise(2*node+1,(b+e)/2+1,e);
		For(i,b,e+1){
			tree[node].nums.pb(a1[i]);
		}
		sort(all(tree[node].nums));
		tree[node].minVal=(1<<30);
	}
}

void update(int node,int b,int e){
	if(b>e){
		return ;
	}
	if(b==e){
		if(e>=rlm){return ;}
		tree[node].minVal=min(tree[node].minVal,abs(a1[b]-a1[rlm]));
		// Error3(b,rlm,tree[node].minVal);
		answer1=min(answer1,tree[node].minVal);
		return ;
	}
	// Error4(node,b,e,answer1);
	if(e<rlm){
		vi::iterator pos=lower_bound(tree[node].nums.begin(),tree[node].nums.end(),a1[rlm]);
		if((pos==tree[node].nums.begin() || a1[rlm]>=*(pos-1) + answer1) && 
			(pos==tree[node].nums.end() || a1[rlm]<=*pos - answer1)){
			// assert(tree[node].minVal!=0);
			answer1=min(answer1,tree[node].minVal);
			return ;
		}
	}
	if(rlm>=(b+e)/2+1){
		update(2*node+1,(b+e)/2+1,e);
	}
	update(2*node,b,(b+e)/2);
	tree[node].minVal=min(tree[2*node].minVal,tree[2*node+1].minVal);
	// Error4(node,b,e,answer1);
}

int query(int node,int b,int e,int i,int j){
	if(b>e || i>e || j<b){
		return (1<<30);
	}
	else if(i<=b && e<=j){
		return tree[node].minVal;
	}
	else{
		int answer1=(1<<30);
		answer1=min(query(2*node,b,(b+e)/2,i,j),answer1);
		answer1=min(query(2*node+1,(b+e)/2+1,e,i,j),answer1);
		return answer1;
	}
}

int main(){
	scanf("%d",&n);
	For(i,1,n+1){
		int temp;scanf("%d",&temp);a1[i]=temp;
	}
	scanf("%d",&m);
	For(i,1,m+1){
		int a1,b1;scanf("%d%d",&a1,&b1);
		Adj[b1].pb(mp(a1,i));
	}
	initialise(1,1,n);
	// debug;
	For(i,1,n+1){
		// error(i);
		while(rlm<i){
			rlm++;
			// Error(rlm,i);
			answer1=(1<<30);update(1,1,n);
		}
		// error(i);
		rep(query1,Adj[i]){
			answerQ[query1.y]=query(1,1,n,query1.x,i-1);
		}
		// error(i);
	}
	For(i,1,m+1){
		printf("%d\n",answerQ[i]);
	}
return 0;}
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
#define N 100010
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

ull seed[300010];
vi Adj[100010];
ull h1[200010];
ull h2[200010];
ull h11[200010];
ull h22[200010];
int father[200010];
int counter1=0;
unordered_map<ull,int> mp1;
unordered_map<ull,int> mp2;

void DFS(int u,int p){
	father[u]=p;
	ull hash1=seed[0];
	rep(t1,Adj[u]){
		if(t1!=p){
			DFS(t1,u);
			hash1+=seed[h1[t1]];
		}
	}
	if(mp1.find(hash1)==mp1.end()){
		mp1[hash1]=counter1++;
	}
	h11[u]=hash1;
	h1[u]=mp1[hash1];
}

void revDFS(int u,int p){
	ll hash1=h11[u];
	if(u!=1){
		hash1+=seed[h2[u]];
	}
	rep(t1,Adj[u]){
		if(t1!=p){
			hash1=hash1-seed[h1[t1]];
			if(mp1.find(hash1)==mp1.end()){
				mp1[hash1]=counter1++;
			}
			h22[t1]=hash1;
			h2[t1]=mp1[hash1];
			revDFS(t1,u);
			hash1=hash1+seed[h1[t1]];
		}
	}
	// if(mp1.find(hash1)==mp1.end()){
	// 	mp1[hash1]=counter1++;
	// }
	// h2[u]=mp1[hash1];
}

int currAnswer=0;
int maxAnswer=0;
int answer1=1;

void calDFS(int u,int p){
	// Error(u,currAnswer);
	if(currAnswer>maxAnswer){
		maxAnswer=currAnswer;answer1=u;
	}
	rep(t1,Adj[u]){
		if(t1==p) continue;
		currAnswer-=!(--mp2[h1[t1]]);
		// Error(t1,h2[t1]);
		currAnswer+=!(mp2[h2[t1]]++);
		// Error(t1,currAnswer);
		calDFS(t1,u);
		currAnswer-=!(--mp2[h2[t1]]);
		currAnswer+=!(mp2[h1[t1]]);
	}
}

int main(){
	int n;
	scanf("%d",&n);
	For(i,0,2*n+2){
		seed[i]=(getRand());
	}
	For(i,1,n){
		int a1,b1;
		scanf("%d%d",&a1,&b1);
		Adj[a1].pb(b1);Adj[b1].pb(a1);
	}

	DFS(1,0);
	revDFS(1,0);
	For(i,2,n+1){
		mp2[h1[i]]++;
		// Error(i,h1[i]);
	}
	maxAnswer=currAnswer=(int)mp2.size();
	calDFS(1,0);
	// error(maxAnswer);
	printf("%d\n",answer1);
return 0;}
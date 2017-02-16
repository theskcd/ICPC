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

ll answer1=0;
vi Adj[100010];
ll a1[100010];
int dp1[100010][20][2];

void addAnswer(int u,int c,int val1){
	For(i,0,20){
		if(val1 & (1<<i)){
			dp1[u][i][0]+=dp1[c][i][1];
			dp1[u][i][1]+=dp1[c][i][0];
		}
		else{
			dp1[u][i][0]+=dp1[c][i][0];
			dp1[u][i][1]+=dp1[c][i][1];
		}
	}
}

void addVal(int u,int val1){
	For(i,0,20){
		if(val1 & (1<<i)){
			dp1[u][i][1]++;
		}
		else{
			dp1[u][i][0]++;
		}
	}
}

void DFS(int u,int p){
	rep(t1,Adj[u]){
		if(t1!=p){
			DFS(t1,u);
			addAnswer(u,t1,a1[u]);
		}
	}
	addVal(u,a1[u]);
}

void assignValue(vector<vi>& arr,int u){
	For(i,0,20){
		For(j,0,2){
			arr[i][j]=dp1[u][i][j];
		}
	}
}

void addValue(vector<vi> &nowAnwer,vector<vi> p,int val1){
	For(i,0,20){
		if(val1 & (1<<i)){
			swap(p[i][0],p[i][1]);
		}
	}
	For(i,0,20){
		For(j,0,2){
			nowAnwer[i][j]+=p[i][j];
		}
	}
}

void modifyAnswer(vector<vi> &nowAnwer,int c,int val1,int sign){
	For(i,0,20){
		if((1<<i) & val1){
			nowAnwer[i][0]+=dp1[c][i][1]*sign;
			nowAnwer[i][1]+=dp1[c][i][0]*sign;
		}
		else{
			nowAnwer[i][0]+=dp1[c][i][0]*sign;
			nowAnwer[i][1]+=dp1[c][i][1]*sign;
		}
	}
}

ll getAns(int u,vector<vi> prev){
	ll answer1=0;
	For(i,0,20){
		if(a1[u] & (1<<i)){
			answer1=answer1+(1<<i)*(ll)prev[i][0];
		}
		else{
			answer1=answer1+(1<<i)*(ll)prev[i][1];
		}
	}
	For(i,0,20){
		answer1+=(1<<i)*(ll)dp1[u][i][1];
	}
	// Error(u,answer1);
	return answer1;
}

void revDFS(int u,int p,vector<vi> prev){
	answer1+=getAns(u,prev);
	// Error(u,answer1);
	vector<vi> nowAnswer;nowAnswer.resize(20,vector<int>(2,0));
	assignValue(nowAnswer,u);
	addValue(nowAnswer,prev,a1[u]);
	rep(t1,Adj[u]){
		if(t1!=p){
			modifyAnswer(nowAnswer,t1,a1[u],-1);
			revDFS(t1,u,nowAnswer);
			modifyAnswer(nowAnswer,t1,a1[u],+1);
		}
	}
}

int main(){
	int n;
	scanf("%d",&n);

	For(i,1,n+1){
		ll temp;scanf("%lld",&temp);
		a1[i]=temp;
	}

	For(i,1,n){
		int a1,b1;
		scanf("%d%d",&a1,&b1);
		Adj[a1].pb(b1);Adj[b1].pb(a1);
	}

	DFS(1,0);
	// For(i,0,3){
	// 	Error4(i,(1<<i),dp1[1][i][0],dp1[1][i][1]);
	// }
	vector<vi> prev;
	prev.resize(20,vi(2,0));
	revDFS(1,0,prev);
	For(i,1,n+1){
		answer1-=(ll)a1[i];
	}
	answer1=answer1/2;
	For(i,1,n+1){
		answer1+=(ll)a1[i];
	}
	printf("%lld\n",answer1);
return 0;}
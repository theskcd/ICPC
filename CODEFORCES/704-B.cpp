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

int a1[5010];
int b1[5010];
int c1[5010];
int d1[5010];
int x1[5010];
int n,e,s;
ll dp[5010][5010];
bool visited[5010][5010];

ll solve(int i,int j,int k){
	if(visited[i][j]){
		return dp[i][j];
	}
	else{
		if(i>=n){
			return (j||k)?LIMIT:0;
		}
		if(j==0 && k==0 && i){
			return LIMIT;
		}
		ll &res=dp[i][j];
		visited[i][j]=true;
		res=LIMIT;
		if(i==s){
			if(j){
				res=min(res,solve(i+1,j-1,k)+x1[i]+c1[i]);
			}
			res=min(res,solve(i+1,j,k+1)-x1[i]+d1[i]);
			return res;
		}
		if(i==e){
			if(k){
				res=min(res,solve(i+1,j,k-1)+x1[i]+a1[i]);
			}
			res=min(res,solve(i+1,j+1,k)-x1[i]+b1[i]);
			return res;
		}
		if(j && k){
			res=min(res,solve(i+1,j-1,k-1)+2*x1[i]+a1[i]+c1[i]);
		}
		if(k){
			res=min(res,solve(i+1,j,k)+a1[i]+d1[i]);
		}
		if(j){
			res=min(res,solve(i+1,j,k)+b1[i]+c1[i]);
		}
		res=min(res,solve(i+1,j+1,k+1)-2*x1[i]+b1[i]+d1[i]);
		return res;
	}
}

int main(){
	scanf("%d%d%d",&n,&s,&e);
	s--,e--;
	For(i,0,n){
		scanf("%d",&x1[i]);
	}
	For(i,0,n){
		scanf("%d",&a1[i]);
	}
	For(i,0,n){
		scanf("%d",&b1[i]);
	}
	For(i,0,n){
		scanf("%d",&c1[i]);
	}
	For(i,0,n){
		scanf("%d",&d1[i]);
	}
	printf("%lld\n",solve(0,0,0));
return 0;}
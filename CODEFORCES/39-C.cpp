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
typedef vector<ll> vll;
typedef unsigned long long ull;
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);
const long double eps=1e-6;
ull getRand(){return ((ull)rand()<<40)+((ull)rand()<<20)+((ull)rand());}

map<int,int> mp1,mp2;
vi ans,v[100010];
int dp[4010][4010][2];
pii e[4010];
vi answer1;

int f(int x1,int y1,bool t1){
	// Error(x1,y1);
	if(x1>y1){
		return 0;
	}
	int &r=dp[x1][y1][t1];
	if(r!=-1){
		return r;
	}
	r=f(x1+1,y1,0);
	rep(t2,v[x1]){
		if(e[t2].y<=y1-t1){
			// Error4(x1,e[t1].y,y1,t1);
			r=max(r,1+f(x1,e[t2].y,1)+f(e[t2].y,y1,0));
		}
	}
	return r;
}

void print(int x1,int y1,bool t1){
	// Error3(x1,y1,t1);
	if(x1>y1){
		return ;
	}
	int &r=dp[x1][y1][t1];
	if(f(x1+1,y1,0)==r){
		print(x1+1,y1,0);return ;
	}
	rep(t2,v[x1]){
		if(e[t2].y<=(y1-t1)){
			if(r==1+f(x1,e[t2].y,1)+f(e[t2].y,y1,0)){
				if(t2){
					answer1.pb(t2);
				}
				print(x1,e[t2].y,1);print(e[t2].y,y1,0);
				break;
			}
		}
	}
}

int main(){
	int n;
	scanf("%d",&n);
	mp1[2*-inf]=mp1[2*inf]=1;
	e[0]=mp(2*-inf,2*inf);
	For(i,1,n+1){
		int a1,b1;
		scanf("%d%d",&a1,&b1);
		int l1=a1-b1;int r1=a1+b1;
		e[i]=mp(l1,r1);
		mp1[l1]=mp1[r1]=1;
	}
	int counter1=0;
	rep(t1,mp1){
		mp2[t1.x]=++counter1;
		// Error(t1.x,mp1[t1.x]);
	}
	For(i,0,n+1){
		e[i]=mp(mp2[e[i].x],mp2[e[i].y]);
		// Error(e[i].x,e[i].y);
		if(i){
			// Error3("v",e[i].x,i);
			v[e[i].x].pb(i);
		}
	}

	memset(dp,-1,sizeof(dp));
	printf("%d\n",f(1,counter1,0));
	print(1,counter1,0);
	sort(all(answer1));
	rep(t1,answer1){
		printf("%d ",t1);
	}
	printf("\n");
return 0;}
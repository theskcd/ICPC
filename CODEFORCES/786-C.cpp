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

int a[500000];
unordered_map<int,int> mp1;
int answer1[500000];
int f[500000];
int lastOccur[500000];
vi Adj[500000];

void update(int p,int v){
	for(;p<(500000);p+=p&(-p)){
		f[p]+=v;
	}
}

int search(int k){
	int res=0;
	rof(j,16,-1){
		int shift=(1<<j);
		if(f[res+shift]<=k){
			k-=f[res+shift];
			res+=shift;
		}
	}
	return ++res;
}

int main(){
	memset(lastOccur,-1,sizeof(lastOccur));
	int n;
	scanf("%d",&n);
	For(i,1,n+1){
		int temp;
		scanf("%d",&temp);
		a[i]=temp;
	}
	rof(i,n,0){
		if(mp1[a[i]]){
			lastOccur[i]=mp1[a[i]];
		}
		mp1[a[i]]=i;
	}
	rep(t1,mp1){
		update(t1.y,1);
	}
	For(i,1,n+1){
		Adj[1].pb(i);
	}
	For(i,1,n+1){
		rep(query,Adj[i]){
			answer1[query]++;
			// debug;
			int nextPoint=search(query);
			// Error(nextPoint,query);
			Adj[nextPoint].pb(query);
		}
		update(i,-1);
		// Error(i,lastOccur[i]);
		if(lastOccur[i]!=-1){
			update(lastOccur[i],1);
		}
	}

	For(i,1,n+1){
		printf("%d ",answer1[i]);
	}
	printf("\n");
return 0;}
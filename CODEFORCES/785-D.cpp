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
#define MAX 810
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

char s[200010];
ll answer1=0;
ll f[200010];
ll invf[200010];
int val1[200010];
int val2[200010];

ll power(ll b,ll e){
	if(e==1){
		return b%mod;
	}
	else{
		ll p=power(b,e/2);
		if(e%2==0){
			return (p*p)%mod;
		}
		else{
			p=(p*p)%mod;
			p=(p*b)%mod;
			return p;
		}
	}
}

ll nCr(int n,int r){
	if(r>n){
		return 0LL;
	}
	else{
		ll val1=f[n];
		val1=(val1*invf[r])%mod;
		val1=(val1*invf[n-r])%mod;
		return val1;
	}
}

void calc(){
	f[0]=1LL;
	For(i,1,200010){
		f[i]=(f[i-1]*i)%mod;
	}
	invf[200009]=power(f[200009],mod-2);
	rof(i,200008,-1){
		invf[i]=(invf[i+1]*((ll)i+1))%mod;
	}
}

int main(){
	calc();
	scanf("%s",s+1);
	int n=strlen(s+1);
	For(i,1,n+1){
		if(s[i]=='('){
			val1[i]=val1[i-1]+1;
		}
		else{
			val1[i]=val1[i-1];
		}
	}
	rof(i,n,0){
		if(s[i]==')'){
			val2[i]=val2[i+1]+1;
		}
		else{
			val2[i]=val2[i+1];
		}
	}
	For(i,1,n+1){
		if(s[i]=='('){
			answer1=(answer1+nCr(val1[i-1]+val2[i+1],val2[i+1]-1))%mod;
		}
	}
	printf("%lld\n",answer1);
return 0;}
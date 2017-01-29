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
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);
const long double eps=1e-6;

ll dp[100010][3];
ll a[100010][3];

int main(){
	int n;
	scanf("%d",&n);
	For(j,0,3){
		For(i,0,n){
			int temp;
			scanf("%d",&temp);
			a[i][j]=temp;
		}
	}
	dp[0][0]=a[0][0];
	dp[0][1]=dp[0][0]+a[0][1];
	dp[0][2]=dp[0][1]+a[0][2];

	For(i,1,n){
		dp[i][0]=max(max(dp[i-1][0],dp[i-1][1]+a[i][1]),dp[i-1][2]+a[i][2]+a[i][1])+a[i][0];
		dp[i][1]=max(max(dp[i-1][1],dp[i-1][0]+a[i][0]),dp[i-1][2]+a[i][2])+a[i][1];
		dp[i][2]=max(max(dp[i-1][2],dp[i-1][1]+a[i][1]),dp[i-1][0]+a[i][0]+a[i][1])+a[i][2];

		ll sum1=0;
		For(j,0,3){
			sum1+=a[i][j]+a[i-1][j];
		}
		if(i>1){
			dp[i][0]=max(dp[i][0],dp[i-2][2]+sum1);
			dp[i][2]=max(dp[i][2],dp[i-2][0]+sum1);
			dp[i][0]=max(dp[i][0],dp[i-2][0]+sum1);
			dp[i][2]=max(dp[i][2],dp[i-2][2]+sum1);
		}
		if(i==1){
			dp[i][2]=max(dp[i][2],sum1);
			dp[i][0]=max(dp[i][0],sum1);
		}
	}

	printf("%lld\n",dp[n-1][2]);
}
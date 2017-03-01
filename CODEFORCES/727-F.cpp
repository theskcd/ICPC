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

vll query;
int n;
int a[751];
ll dp[751][751];
vll breakPoints;
unordered_map<ll,int> mp1;
unordered_map<ll,vll> mp2;

bool trySolve(int tries,int n,ll h1){
	priority_queue<ll,vector<ll>,greater<ll> > Q1;
	For(i,1,n+1){
		if(a[i]+h1>=0){
			h1+=a[i];
			Q1.push(a[i]);
		}
		else{
			h1+=a[i];Q1.push(a[i]);
			while(!Q1.empty() && tries>0 && h1<0){
				tries--;
				h1-=Q1.top();
				// Error4("removing",Q1.top(),h1,i);
				Q1.pop();
			}
			if(h1<0){
				return false;
			}
		}
	}
	assert(h1>=0);
	return true;
}

// bool trySolve(int tries,int n,ll h1){
// 	int tries1=tries;
// 	tries=n;
// 	if(mp2.find(h1)!=mp2.end()){
// 		if(mp2[h1][tries1]>=0){
// 			return true;
// 		}
// 		else{
// 			return false;
// 		}
// 	}
// 	For(i,0,n+1){
// 		For(j,0,tries+1){
// 			dp[i][j]=-1;
// 		}
// 	}
// 	dp[0][0]=h1;
// 	For(i,1,tries+1){
// 		dp[0][i]=-1;
// 	}
// 	For(i,1,n+1){
// 		if(dp[i-1][0]>=0){
// 			dp[i][0]=max(dp[i-1][0]+(ll)a[i],-1LL);
// 		}
// 		else{
// 			dp[i][0]=-1;
// 		}
// 		For(j,1,tries+1){
// 			if(dp[i-1][j]>=0){
// 				dp[i][j]=max(dp[i][j],max(dp[i-1][j]+(ll)a[i],-1LL));
// 			}
// 			dp[i][j]=max(dp[i][j],dp[i-1][j-1]);
// 		}
// 	}
// 	vll lastCol;
// 	For(i,0,tries+1){
// 		lastCol.pb(dp[n][i]);
// 	}
// 	if(mp2.find(h1)==mp2.end()){
// 		mp2[h1]=lastCol;
// 	}
// 	if(dp[n][tries1]>=0){
// 		// Error4(n,tries,h1,dp[n][tries]);
// 		return true;
// 	}
// 	else{
// 		return false;
// 	}
// }

void compute(){
	For(i,0,n+1){
		ll l1=0;
		ll h1=1000000000000000LL;
		while(l1<h1){
			ll mid=(l1+h1)/2;
			// Error3(l1,mid,h1);
			if(l1+1==h1){
				// error("here");
				if(trySolve(i,n,l1)){
					h1=l1;break;
				}
				else{
					l1=h1;break;
				}
			}
			if(trySolve(i,n,mid)){
				h1=mid;
			}
			else{
				l1=mid+1;
			}
		}
		// Error(i,l1);
		if(mp1.find(l1)==mp1.end()){
			breakPoints.pb(l1);
			mp1[l1]=i;
		}
		// Error(l1,mp1[l1]);
	}
}

int main(){
	int m;
	scanf("%d%d",&n,&m);
	
	For(i,1,n+1){
		int temp;scanf("%d",&temp);
		a[i]=temp;
	}

	compute();
	reverse(all(breakPoints));
	// rep(t1,breakPoints){
	// 	error(t1);
	// }
	// printf("\n");
	
	while(m--){
		ll temp1;
		scanf("%lld",&temp1);
		if(temp1>breakPoints.back()){
			printf("%d\n",mp1[breakPoints[breakPoints.size()-1]]);
			continue;
		}
		vll::iterator it=lower_bound(all(breakPoints),temp1);
		if(it!=breakPoints.begin() && *it>temp1){
			it--;
		}
		printf("%d\n",mp1[(*it)]);
	}
return 0;}
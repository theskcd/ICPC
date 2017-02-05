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

ll a[30010];
ll dp[30010][210][2][2][2];
bool visited[30010][210][2][2][2];
int N,K;

//0 ==> -
//1 ==> +

ll recurse(int index,int k,bool c1,bool c2,bool open){
	// Error5(index,k,c1,c2,open);
	if(k==K){
		return 0;
	}
	if(index==N){
		// if(k!=K){
		// 	return -LIMIT;
		// }
		return -LIMIT;
	}
	if(visited[index][k][c1][c2][open]){
		return dp[index][k][c1][c2][open];
	}
	else{
		ll &ans=dp[index][k][c1][c2][open];
		ans=-LIMIT;
		if(!open){
			//keep closed
			ans=max(ans,recurse(index+1,k,c1,c2,0));
			//open now
			ans=max(ans,recurse(index,k,c1,c2,1));
		}
		else{
			//close it maybe
			For(c3,0,2){
				// Error(index,index+1);
				// Error4(c1,c2,c2,c3);
				ll temp=recurse(index+1,k+1,c2,c3,0);
				ans=max(ans,temp);
			}
			//keep it open
			ans=max(ans,recurse(index+1,k,c1,c2,1));
			// Error3(index,c1,c2);
			if(k!=0){
				if(c1==0){ 
					ans-=a[index];
					}
				else{ ans+=a[index]; }
			}
			if(k!=K-1){
				if(c2==0){ ans+=a[index];} else {ans-=a[index];}
			}
		}
		visited[index][k][c1][c2][open]=true;
		// Error(open,ans);
		// Error5(index,k,c1,c2,dp[index][k][c1][c2][open]);
		return ans;
	}
}

int main(){
	scanf("%d%d",&N,&K);

	memset(visited,0,sizeof(visited));
	For(i,0,N){
		int temp;
		scanf("%d",&temp);
		a[i]=temp;
	}
	ll answer1=max(recurse(0,0,0,1,0),recurse(0,0,0,0,0));
	printf("%lld\n",answer1);
return 0;}
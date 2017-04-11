#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;
#pragma comment(linker, "/STACK:102400000,102400000")

// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・゜

#define Foreach(i, c) for(__typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define For(i,a,b) for(int (i)=(a);(i) < (b); ++(i))
#define rof(i,a,b) for(int (i)=(a);(i) > (b); --(i))
#define rep(i, c) for(auto &(i) : (c))
#define F first
#define S second
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

short a[1010];
short b[1010];
short dp[1002][51][1002][2];
short sum1[1010];
short n,p,k;

short getCumSum(int index1,int index2){
	assert(index1>=index2);
	index1=min(index1,(int)n);
	// Error3(index1,index2,sum1[index1]-sum1[index2-1]);
	return sum1[index1]-sum1[index2-1];
}

void solve(short index,short remainLength,short remain,bool who){
	if(index>=n+1){
		dp[index][remainLength][remain][who]=0;
		return ;
	}
	else{
		if(dp[index][remainLength][remain][who]!=-1){
			return ;
		}
		else{
			short addNow=0;
			if(who){
				addNow=a[index];
			}
			else{
				addNow=b[index];
			}
			short &res=dp[index][remainLength][remain][who];
			res=0;
			if(remain>0){
				if(remainLength==k){
					solve(index+1,remainLength,remain,who);
					solve(index+1,remainLength,remain,!who);
					if(index==4){
						Error5(index+1,remainLength,remain,who,dp[index+1][remainLength][remain][who]);
						Error5(index+1,remainLength,remain,who,dp[index+1][remainLength][remain][!who]);
					}
					res=max(res,max(dp[index+1][remainLength][remain][who],dp[index+1][remainLength][remain][!who]));
				}
				if(remainLength>=1){
					short finalVal=0;
					if(remain>1){
						solve(index+1,k,remain-1,who);
						solve(index+1,k,remain-1,!who);
						if(index==4){
							Error5(index+1,k,remain-1,who,addNow+dp[index+1][k][remain-1][who]);
							Error5(index+1,k,remain-1,!who,addNow+dp[index+1][k][remain-1][!who]);
						}
						finalVal=max(finalVal,(short)(addNow + max(dp[index+1][k][remain-1][who],dp[index+1][k][remain-1][!who])));
					}
					if(remainLength>1){
						{
							solve(index+1,remainLength-1,remain,who);
							if(index==4){
								Error5(index+1,remainLength-1,remain,who,dp[index+1][remainLength-1][remain][who]);
							}
							finalVal=max(finalVal,(short)(addNow+dp[index+1][remainLength-1][remain][who]));
						}
					}
					if(k-remainLength==0){
						if(remain>=2){
							solve(min(index+remainLength,n+1),(remain==2)?0:k,remain-2,who);
							solve(min(index+remainLength,n+1),(remain==2)?0:k,remain-2,!who);
							if(index==4){
								Error5(min(index+remainLength,n+1),(remain==2)?0:k,remain-2,who,getCumSum(index+remainLength-1,index)+dp[min(index+remainLength,n+1)][(remain==2)?0:k][remain-2][who]);
								Error5(min(index+remainLength,n+1),(remain==2)?0:k,remain-2,!who,getCumSum(index+remainLength-1,index)+dp[min(index+remainLength,n+1)][(remain==2)?0:k][remain-2][!who]);
							}
							finalVal=max(finalVal,(short)(getCumSum(index+remainLength-1,index) + dp[min(index+remainLength,n+1)][(remain==2)?0:k][remain-2][!who]));
							finalVal=max(finalVal,(short)(getCumSum(index+remainLength-1,index) + dp[min(index+remainLength,n+1)][(remain==2)?0:k][remain-2][who]));
						}
					}
					else{
						if(remain>=2){
							solve(min(index+remainLength,n+1),k-remainLength,remain-1,who);
							solve(min(index+remainLength,n+1),k-remainLength,remain-1,!who);
							if(who){
								// Error4(remain,getCumSum(index+remainLength-1,index),index+remainLength-1,index);
								finalVal=max(finalVal,(short)(getCumSum(index+remainLength-1,index) + dp[min(index+remainLength,n+1)][k-remainLength][remain-1][!who]));
							}
							else{
								// Error4(remain,getCumSum(index+remainLength-1,index),index+remainLength-1,index);
								finalVal=max(finalVal,(short)(getCumSum(index+remainLength-1,index) + dp[min(index+remainLength,n+1)][k-remainLength][remain-1][who]));
							}
						}
					}
					res=max(finalVal,res);
				}
				// Error5(index,remainLength,remain,who,dp[index][remainLength][remain][who]);
			}
			return ;
		}
	}
}

int main(){
	memset(dp,-1,sizeof(dp));
	// scanf("%d%d%d",&n,&p,&k);
	cin>>n>>p>>k;
	int r;
	scanf("%d",&r);
	For(i,0,r){
		int temp;
		scanf("%d",&temp);a[temp]=1;
	}

	int s;
	scanf("%d",&s);
	For(i,0,s){
		int temp;
		scanf("%d",&temp);b[temp]=1;
	}


	For(i,1,n+1){
		int temp=0;
		if(a[i] || b[i]){
			temp=1;
		}
		sum1[i]=sum1[i-1]+temp;
	}
	// For(i,1,n+1){
	// 	Error4(i,a[i],b[i],sum1[i]);
	// }

	solve(1,k,p,0);
	solve(1,k,p,1);
	cout<<max(dp[1][k][p][0],dp[1][k][p][1])<<"\n";
return 0;}
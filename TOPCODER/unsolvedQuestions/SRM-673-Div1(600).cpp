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
//#define si(n) scanf("%d",&n)
//#define sii(n,m) scanf("%d%d",&n,&m)
//#define pi(n) printf("%d\n",n)
const int inf=0x3f3f3f3f;
const long double pi=acos(-1.0);
#define MAX 50010
// #define N 100000
const string debug_line="yolo";
#define debug error(debug_line)
const double PI=4*atan(1);
#define read() freopen("mergedoutput.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
//template <typename T> using os =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef complex<double> point;

ll dp[110][110][110];
ll dp1[110][110];

class BearPermutations
{
public:
	int n,s;
	ll MOD;
	ll nCr[110][110];

	void calc(){
		nCr[0][0]=1LL;
		For(i,0,110){
			nCr[i][0]=1LL;
		}
		For(i,1,110){
			For(j,1,i+1){
				nCr[i][j]=(nCr[i-1][j-1]+nCr[i-1][j])%MOD;
			}
		}
		// error(nCr[5][2]);
	}

	int countPermutations(int N,int S,ll MOD){
		this->n=N;
		this->s=S;
		this->MOD=MOD;
		memset(nCr,0,sizeof(nCr));
		calc();
		memset(dp,0,sizeof(dp));
		memset(dp1,0,sizeof(dp1));
		dp[0][0][0]=1LL;
		dp[0][1][0]=1LL;
		For(n,1,N+1){
			if(n>1){
				For(i,0,n){
					int leftRemain=i;
					int rightRemain=n-1-i;
					For(s,0,S+1){
						dp[i][n][s]=0;
						if(leftRemain==0){
							For(j,0,rightRemain){
								dp[i][n][s]=(dp[i][n][s]+dp[j][rightRemain][s]);
							}
							dp[i][n][s]%=MOD;
						}
						else if(rightRemain==0){
							For(j,0,leftRemain){
								dp[i][n][s]=(dp[i][n][s]+dp[j][leftRemain][s]);
							}
							dp[i][n][s]%=MOD;
						}
						else{
							ll temp1=0;
							For(j,0,leftRemain+1){
								For(s1,0,s+1){
									int requiredSum=s-(s1+(i+1-j));
									// Error5(n,j,leftRemain,s1,rightRemain);
									temp1=(temp1+dp[j][leftRemain][s1]*dp1[rightRemain][requiredSum]);
									if(temp1>MOD){
										temp1=temp1%MOD;
									}
								}
							}
							assert(leftRemain<=n-1);
							temp1=(temp1%MOD*nCr[n-1][leftRemain])%MOD;
							dp[i][n][s]=temp1;
						}
						// Error4(i,n,s,dp[i][n][s]);
					}
				}
			}
			For(s,0,S+1){
				dp1[n][s]=0;
				For(pos,0,min(s+1,n)){
					dp1[n][s]=(dp1[n][s]+dp[pos][n][s-pos]);
				}
				dp1[n][s]=dp1[n][s]%MOD;
				// Error3(n,s,dp1[n][s]);
			}
		}

		ll answer1=0;
		For(s,0,S+1){
			For(i,0,N){
				answer1=(answer1+dp[i][n][s])%MOD;
			}
		}
		return answer1;
	}
};

int main(){
	int n,s,MOD;
	scanf("%d%d%d",&n,&s,&MOD);
	BearPermutations bp;
	error(bp.countPermutations(n,s,MOD));
}
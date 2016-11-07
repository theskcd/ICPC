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
// #define N 100010
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

int dp[50100];
int dp1[50100];
int index1[(1<<11)];

class PartisanGame
{
public:
	string getWinner(int n,vi a,vi b){
		dp[0]=0;
		dp1[0]=0;
		For(j,0,(1<<11)){
			index1[j]=-1;
		}
		For(i,1,50100){
			dp[i]=0;
			dp1[i]=0;
			rep(t1,a){
				if(t1<=i && !dp1[i-t1]){
					dp[i]=1;
				}
			}
			rep(t1,b){
				if(t1<=i && !dp[i-t1]){
					dp1[i]=1;
				}
			}
		}
		if(n<50100){
			if(dp[n]){
				return "Alice";
			}
			else{
				return "Bob";
			}
		}
		else{
			For(i,100,50100){
				//getMask
				int curMask=0;
				For(j,0,5){
					curMask=curMask*2;
					if(i-j>=0){
						curMask=curMask+dp[i-j];
					}
					curMask=curMask*2;
					if(i-j>=0){
						curMask=curMask+dp1[i-j];
					}
				}
				// if(i<20){
				// 	Error(i,curMask);
				// 	Error3(i,dp[i],dp1[i]);
				// }
				// Error(i,curMask);
				if(index1[curMask]==-1){
					index1[curMask]=i;
				}
				else{
					int length1=i-index1[curMask];
					// Error3(n,i,index1[curMask]);
					int newIndex=(n-i)-((n-i)/length1)*length1+index1[curMask];
					if(dp[newIndex]){
						return "Alice";
					}
					else{
						return "Bob";
					}
				}
			}
			assert(false);
		}
	}
};

// int main(){
// 	PartisanGame pg;
// 	int n=158260522;
// 	vi a={2,4};
// 	vi b={4};
// 	error(pg.getWinner(n,a,b));
// }
// 
//828191, {2}, {1, 5}}
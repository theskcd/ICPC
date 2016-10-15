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

ll dp[210][210][210];

class BearCries
{
public:
	string message;

	void tryAll(int index,int open,int paired){
		if(dp[index][open][paired]!=-1){
			return ;
		}
		if(index==message.size()){
			if(open==0 && paired==0){
				dp[index][open][paired]=1;
			}
			else{
				dp[index][open][paired]=0;
			}
		}
		else{
			dp[index][open][paired]=0;
			if(message[index]==';'){
				//open another bracket
				tryAll(index+1,open+1,paired);
				dp[index][open][paired]=(dp[index][open][paired]+dp[index+1][open+1][paired])%mod;
				//close one of the paired bracket
				if(open>0 && paired>0){
					tryAll(index+1,open-1,paired-1);
					dp[index][open][paired]=(dp[index][open][paired]+dp[index+1][open-1][paired-1]*(ll)paired)%mod;
				}
			}
			else{
				//pair one of the open bracket
				if(open>paired){
					tryAll(index+1,open,paired+1);
					dp[index][open][paired]=(dp[index][open][paired]+dp[index+1][open][paired+1]*(ll)(open-paired))%mod;
				}
				//do nothing to pair the previous
				if(open>0){
					tryAll(index+1,open,paired);
					dp[index][open][paired]=(dp[index][open][paired]+dp[index+1][open][paired]*(ll)paired)%mod;
				}
			}
		}
	}

	int count(string message){
		this->message=message;
		memset(dp,-1,sizeof(dp));
		tryAll(0,0,0);
		return dp[0][0][0];
	}
};

// int main(){
// 	string message;
// 	cin>>message;
// 	BearCries bc;
// 	error(bc.count(message));
// }
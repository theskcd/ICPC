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

class LinenCentreEasy
{
public:
	string s;
	int n;
	int k;
	bool invalid[101];
	int aut[101][26];
	ll dp[51][51][51];
	bool visited[51][51][51];
	int pre[101];

	ll tryAll(int pos,int n,int k){
		if(visited[pos][n][k]){
			return dp[pos][n][k];
		}
		else if(pos==s.size()){
			dp[pos][n][k]=0;
			return 0;
		}
		else{
			ll temp1=0;
			if(k==0){
				temp1=1;
			}
			For(j,0,26){
				if(n<=0){
					break;
				}
				tryAll(aut[pos][j],n-1,k);
				temp1=(temp1+dp[aut[pos][j]][n-1][k])%mod1;
			}
			if(k>0 && !invalid[pos]){
				tryAll(0,n,k-1);
				temp1=(temp1+dp[0][n][k-1])%mod1;
			}
			dp[pos][n][k]=temp1%mod1;
			visited[pos][n][k]=true;
			return dp[pos][n][k];
		}
	}

	int countString(string S,int N,int K){
		s=S,n=N,k=K;
		int l=s.size();
		For(i,0,l){
			string temp1=(s.substr(0,i)+s).substr(0,s.size());
			if(temp1==s){
				invalid[i]=true;
			}
			if(i==0){
				invalid[i]=false;
			}
			For(j,0,26){
				string temp2=s.substr(0,i)+(char)(j+'a');
				aut[i][j]=0;
				rof(k,temp2.size(),-1){
					if(s.substr(0,k)==temp2.substr(temp2.size()-k)){
						aut[i][j]=k;
						break;
					}
				}
			}
		}
		tryAll(0,n,k);
		return dp[0][n][k];
	}
};

// int main(){
// 	LinenCentreEasy *lce=new LinenCentreEasy();
// 	string s;
// 	int n,k;
// 	cin>>s>>n>>k;
// 	error((*lce).countString(s,n,k));
// }
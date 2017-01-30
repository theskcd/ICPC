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

string s;
ll dp[5010][27];
ll f[10020];
ll invf[10020];

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

void calc(){
	f[0]=1LL;
	For(i,1,10020){
		f[i]=(f[i-1]*i)%mod;
	}
	invf[10020-1]=power(f[10020-1],mod-2);
	rof(i,10020-2,-1){
		invf[i]=(invf[i+1]*(i+1))%mod;
	}
}

ll nCr(int n,int r){
	ll answer1=1LL;
	answer1=f[n];
	answer1=(answer1*invf[r])%mod;
	answer1=(answer1*invf[n-r])%mod;
	return answer1;
}

void compress(string &s){
	int n=s.size();
	string temp="";
	int pt=0;
	while(pt<n){
		int index=pt;
		temp+=(char)(s[index]);
		while(pt<n && s[index]==s[pt]){
			pt++;
		}
	}
	s=temp;
}

int main(){
	calc();
	int n;
	scanf("%d",&n);
	int n1=n;
	cin >> s;
	compress(s);
	n=s.size();
	// error(s);
	// error(nCr(5,2));
	dp[0][0]=1LL;

	For(i,1,n+1){
		// error(i);
		char c=s[i-1];
		For(j,1,i+1){
			ll temp1=0;
			// assert(c-'a'+1>=0 && c-'a'+1<=27);
			For(z,0,27){
				if(z!=c-'a'+1){
					temp1=(temp1+dp[j-1][z]);
					if(temp1>=mod){
						temp1=temp1-mod;
					}
				}
			}
			dp[j][c-'a'+1]=(temp1);
			if(dp[j][c-'a'+1]>=mod){
				dp[j][c-'a'+1]=dp[j][c-'a'+1]-mod;
			}
			// Error3(j,c-'a'+1,dp[j][c-'a'+1]);
		}
		// error(i);
		// For(k,1,26){
		// 	printf("%c: ",'a'+k-1);
		// 	For(j,1,i+1){
		// 		printf("%lld ",dp[j][k]);
		// 	}
		// 	printf("\n");
		// }
	}

	// For(j,0,4){
	// 	For(k,0,27){
	// 		printf("%lld ",dp[j][k]);
	// 	}
	// 	printf("\n");
	// }

	ll answer1=0;
	For(j,1,n+1){
		ll temp1=0;
		For(k,1,27){
			temp1=temp1+dp[j][k];
			if(temp1>=mod){
				temp1=temp1-mod;
			}
		}
		// Error(j,temp1);	
		temp1=(temp1*nCr(n1-1,j-1))%mod;
		answer1=(answer1+temp1)%mod;
	}
	printf("%lld\n",answer1);
return 0;}
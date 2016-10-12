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

class GCDLCM2
{
public:
	vi nums;
	unordered_map<int,int> mp1;
	vi smallestPrime;
	unordered_map<int,vi> mp2;

	void sieve(){
		int MAXN=10000000;
		smallestPrime.clear();
		smallestPrime.resize(MAXN+1,-1);
		For(i,2,MAXN+1){
			if(smallestPrime[i]==-1){
				for(int j=i;j<=MAXN;j=j+i){
					smallestPrime[j]=i;
				}
			}
		}
	}

	int getMaximumSum(vi start,vi d,vi count){
		int n=start.size();
		nums.clear();
		mp1.clear();
		mp2.clear();
		int totN=0;
		For(i,0,n){
			For(j,0,count[i]){
				totN++;
				int number=start[i]+d[i]*j;
				nums.pb(number);
				// Error(totN,number);
				mp1[number]++;
			}
		}
		debug;
		sieve();
		debug;
		rep(t1,mp1){
			int num1=t1.x;
			vector<pii> res;
			while(num1>1){
				int fact=smallestPrime[num1];
				int count1=0;
				int num2=1;
				while(num1%fact==0){
					num1=num1/fact;
					num2=num2*fact;
					count1++;
				}
				res.pb(mp(fact,num2));
			}
			int count2=t1.y;
			For(j,0,count2){
				rep(t1,res){
					// Error(t1.x,t1.y);
					mp2[t1.x].pb(t1.y);
				}
			}
		}
		debug;
		rep(t1,mp2){
			sort(all(t1.y));
			rep(t2,t1.y){
				// Error(t1.x,t2);
			}
		}
		debug;

		ll answer1=0;
		For(i,0,totN){
			ll temp1=1;
			vi eraseThem;
			rep(t1,mp2){
				// Error("inside the factors",t1.x);
				// Error(t1.x,t1.y.size());
				assert(t1.y.size()!=0);
				temp1=(temp1*t1.y[t1.y.size()-1])%mod;
				t1.y.PB;
				if(t1.y.size()==0){
					eraseThem.pb(t1.x);
				}
			}
			rep(eraseNum,eraseThem){
				mp2.erase(eraseNum);
			}
			// Error(i,temp1);
			answer1=(answer1+temp1)%mod;
		}
		debug;
		return answer1;
	}
};

// int main(){
// 	GCDLCM2 gl2;
// 	vi start={5,6};
// 	vi d={23,45};
// 	vi cnt={50000,50000};
// 	error(gl2.getMaximumSum(start,d,cnt));
// }
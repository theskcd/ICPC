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

bool isPrime[1000010];
int fact[1000010];
ll answer1[1000010];
vector<pair<ll,ll> > Adj[1000010];

void sieve(){
	For(i,2,1000010){
		isPrime[i]=true;
	}

	For(i,2,1000010){
		if(!isPrime[i]){
			continue;
		}
		fact[i]=i;
		for(int j=i+i;j<1000010;j=j+i){
			isPrime[j]=false;
			fact[j]=i;
		}
	}
}

void solve(){
	int n;
	sieve();
	scanf("%d",&n);

	For(i,0,n){
		int p1;
		scanf("%d",&p1);
		ll a1;scanf("%lld",&a1);
		Adj[p1].pb(mp(0,a1-1));
	}

	ll k;scanf("%lld",&k);

	rof(i,1000000,1){
		if(!Adj[i].empty()){
			vector<pair<ll,ll> > temp;
			temp.clear();
			sort(all(Adj[i]));
			rep(extent,Adj[i]){
				if(temp.empty()){
					temp.pb(extent);
				}
				else{
					if(temp.back().y+1>=extent.x){
						temp.back().y+=extent.y-extent.x+1;
					}
					else{
						temp.pb(extent);
					}
				}
			}
			Adj[i].clear();
			rep(extent,temp){
				if(extent.x>=k){
					answer1[i]+=extent.y-extent.x+1;
				}
				else if(extent.y>=k){
					answer1[i]+=extent.y-k+1;
					Adj[i].pb(mp(extent.x,k-1));
				}
				else{
					Adj[i].pb(extent);
				}
			}
			rep(extent,Adj[i]){
				int temp1=i-1;
				while(temp1>1){
					Adj[fact[temp1]].pb(mp(extent.x+1,extent.y+1));
					temp1=temp1/fact[temp1];
				}
			}
		}
	}

	vector<pair<ll,ll> > answerFinal;answerFinal.clear();

	For(i,0,1000010){
		if(answer1[i]!=0){
			answerFinal.pb(mp(i,answer1[i]));
		}
	}
	error(answerFinal.size());
	printf("%d\n",(int)answerFinal.size());
	rep(t1,answerFinal){
		printf("%lld %lld\n",t1.x,t1.y);
	}

}

int main(){
	solve();
}
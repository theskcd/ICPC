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

ll c[100010];
ll w[100010];
bool marked[100010];

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	For(i,0,n){
		int temp;scanf("%d",&temp);c[i]=temp;
	}

	For(i,0,n){
		int temp;scanf("%d",&temp);w[i]=temp;
	}

	ll anger1=0;
	ll cost1=0;
	priority_queue<pair<pair<ll,ll>,ll>,vector<pair<pair<ll,ll>,ll> >,greater<pair<pair<ll,ll>,ll> > >Q1;
	For(i,0,n){
		// Error(i,Q1.size());
		ll req1=c[i]%100;
		// Error(m,req1);
		if(m>=req1){
			// Error(i,"here");
			if(100-req1!=0 && req1%100!=0){
				Q1.push(mp(mp(w[i]*(100LL-req1),100-req1),i));
			}
			m-=req1;
		}
		else{
			// Error(i,Q1.size());
			bool poss=false;
			m-=req1;
			Q1.push(mp(mp(w[i]*(100LL-req1),100-req1),i));
			// Error3(w[i],req1,i);
			while(m<0){
				pair<pair<ll,ll>,ll> t1=Q1.top();Q1.pop();
				// Error4(t1.y,t1.x.x,t1.x.y,t1.x.x*(100-t1.x.y));
				anger1+=t1.x.x;
				marked[t1.y]=true;
				m+=100;
			}
		}
		// Error3(i,m,anger1);
	}

	printf("%lld\n",anger1);

	For(i,0,n){
		if(marked[i]){
			printf("%lld 0\n",c[i]/100+1);
		}
		else{
			printf("%lld %lld\n",c[i]/100,c[i]%100);
		}
	}

return 0;}
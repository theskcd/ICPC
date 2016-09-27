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

class FromToDivisible
{
public:
	vi Adj[1001];
	int dist[1001];
	int dist1[1001];
	bool visited[1001];

	bool lcm(int a,int b,int n){
		ll a1=a;
		ll b1=b;
		ll n1=n;
		a1=(a1*b1)/__gcd(a1,b1);
		if(a1<=n){
			return true;
		}
		else{
			return false;
		}
	}

	int shortest(int N,int S,int T,vector<int> a,vector<int> b){
		int m=a.size();
		int n=N;
		int s=S;
		int t=T;
		if(s==t){
			return 0;
		}
		queue<pii> Q1;

		For(i,0,m){
			dist[i]=INT_MAX;
		}

		For(i,0,m){
			if(s%a[i]==0){
				Q1.push(mp(1,i));
				dist[i]=1;
				visited[i]=1;
			}
		}

		while(!Q1.empty()){
			pii u=Q1.front();
			// Error(u.x,u.y);
			Q1.pop();
			For(i,0,m){
				if(!visited[i] && lcm(b[u.y],a[i],n)){
					visited[i]=true;
					dist[i]=dist[u.y]+1;
					Q1.push(mp(dist[i],i));
				}
			}
		}

		int answer1=INT_MAX;
		For(i,0,m){
			if(t%b[i]==0){
				answer1=min(answer1,dist[i]);
			}
		}
		if(answer1==INT_MAX){
			answer1=-1;
		}
		return answer1;
	}
};

// int main(){
// 	int n,s,t;
// 	n=100;
// 	s=90;
// 	t=40;
// 	vi a={20,30,100,99,100};
// 	vi b={10,30,100,100,99};
// 	FromToDivisible *ftd=new FromToDivisible();
// 	error((*ftd).shortest(n,s,t,a,b));
// }
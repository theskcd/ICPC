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

// TUTTES Theorem for k-edge disconnected spanning trees
class FoxAirline2
{
public:
	vi Adj[101];
	bool poss;

	void tryAll(int index,int n,vector<vi> &groups){
		if(index==n){
			vi groupId;
			groupId.resize(n);
			For(i,0,groups.size()){
				rep(t1,groups[i]){
					groupId[t1]=i;
				}
			}
			int count1=2*(groups.size()-1);
			int count2=0;
			For(i,0,n){
				rep(t1,Adj[i]){
					if(groupId[i]!=groupId[t1]){
						count2++;
					}
				}
			}
			count2/=2;
			if(count2<count1){
				poss=false;
			}
		}
		else{
			For(i,0,groups.size()){
				vi temp1=groups[i];
				groups[i].pb(index);
				tryAll(index+1,n,groups);
				groups[i]=temp1;
			}
			vi temp1={index};
			groups.pb(temp1);
			tryAll(index+1,n,groups);
			groups.PB;
		}
	}

	string isPossible(int n,vector<int> a,vector<int> b){
		poss=true;
		For(i,0,n){
			Adj[i].clear();
		}
		int m=a.size();
		For(i,0,m){
			Adj[a[i]].pb(b[i]);
			Adj[b[i]].pb(a[i]);
		}
		vector<vi> curr;
		tryAll(0,n,curr);

		if(poss){
			return "Possible";
		}
		else{
			return "Impossible";
		}
	}
};

int main(){
int n=5;
vi a={0,0,0,1,1,2,2,3};
vi b={1,2,4,2,4,3,4,4};

	FoxAirline2 fal2;
	error(fal2.isPossible(n,a,b));
}
#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

#pragma comment(linker, "/STACK:16777216")

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
#define errop(a) cerr<<#a<<" = ( "<<((a).x)<<" , "<<((a).y)<<" )\n";
#define coud(a,b) cout<<fixed << setprecision((b)) << (a)
#define L(x) (((x)<<1)+1)
#define R(x) (((x)<<1)+2)
#define umap unordered_map
//#define double long double
#define mod 1000000007
// #define mod1 1000000009
#define LIMIT 10000000000000000LL
#define INF 10000000000LL
#define MAX1 1000000000
//#define si(n) scanf("%d",&n)
//#define sii(n,m) scanf("%d%d",&n,&m)
//#define pi(n) printf("%d\n",n)
const int inf=0x3f3f3f3f;
const long double pi=acos(-1.0);
#define MAX 50010
#define N 100000
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

struct query{
	int x1;
	int y1;
	int x2;
	int y2;
	int index;
	query(int _x1,int _y1,int _x2,int _y2,int _index){
		x1=_x1;
		y1=_y1;
		x2=_x2;
		y2=_y2;
		index=_index;
	};
};

vector<pair<pii,int> > Adj[2010];
vector<pii> events[2010];
vector<query> queries;
unordered_map<int,int> hash1;
map<pii,ll> valAt;
vector<pii> eve[2010];
ll f[2010];
ll answer1[2010];

void updateVal(int index,ll val){
	for(;index<=2000;index=index+(index&(-index))){
		f[index]+=val;
	}
}

ll queryVal(int index){
	ll answer1=0;
	for(;index>0;index=index-(index&(-index))){
		answer1+=f[index];
	}
	return answer1;
}

int main(){
	int n,m,k;
	scanf("%d%d%d",&n,&m,&k);

	For(i,1,k+1){
		int len;
		scanf("%d",&len);
		For(i,0,len){
			int x1,y1,w1;
			scanf("%d%d%d",&x1,&y1,&w1);
			Adj[i].pb(mp(mp(y1,x1),w1));
		}
		sort(all(Adj[i]));
	}

	int q;
	scanf("%d",&q);
	For(i,1,q+1){
		string type;
		cin>>type;
		if(type=="SWITCH"){
			int index;
			scanf("%d",&index);
			events[index].pb(mp(i,0));
		}
		else if(type=="ASK"){
			int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			query temp(x1,y1,x2,y2,i);
			queries.pb(temp);
			hash1[i]=queries.size()-1;
			For(i,1,k+1){
				events[i].pb(mp(hash1[i],1));
			}
		}
	}

	For(i,1,k+1){
		int currCount=1;
		vi active;
		valAt.clear();
		For(i,0,2010){
			f[i]=0;
			eve[i].clear();
		}
		rep(eve1,events[i]){
			if(eve1.y==0){
				currCount=1-currCount;
			}
			else{
				if(currCount){
					active.pb(eve1.x);
				}
			}
		}
		For(j,0,Adj[i].size()){
			eve[Adj[i][j].x.x].pb(mp(Adj[i][j].x.y,Adj[i][j].y));
		}
		rep(activePoints,active){
			query temp=queries[activePoints];
			int x1=temp.x1;
			int y1=temp.y1;
			int x2=temp.x2;
			int y2=temp.y2;
			eve[y2].pb(mp(x2,-1));
			eve[y1-1].pb(mp(x1-1,-1));
			eve[y2].pb(mp(x1-1,-1));
			eve[y1-1].pb(mp(x2,-1));
		}
		// sort(all(eve));
		For(i,1,m+1){
			rep(t1,eve[i]){
				if(t1.y!=-1){
					updateVal(t1.x,t1.y);
				}
			}
			rep(t1,eve[i]){
				if(t1.y==-1){
					ll answer1=queryVal(t1.x);
					valAt[mp(t1.x,i)]=answer1;
				}
			}
		}

		rep(activePoints,active){
			error(activePoints);
			query temp=queries[activePoints];
			int x1=temp.x1;
			int y1=temp.y1;
			int x2=temp.x2;
			int y2=temp.y2;
			Error4(x1,y1,x2,y2);
			Error3(valAt[mp(x2,y2)],x2,y2);
			answer1[activePoints]+=valAt[mp(x2,y2)]+valAt[mp(x1-1,y1-1)]-valAt[mp(x1-1,y2)]-valAt[mp(x2,y1-1)];
		}
		error(queries.size());
		For(i,0,queries.size()){
			printf("%lld\n",answer1[i]);
		}
	}
return 0;}
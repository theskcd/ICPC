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
#define N 100010
#define M 2000010
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

typedef struct node2{
	int val1;
}node1;

node1 tree[4*N];
int a[N];
map<int,int> mp1;
vi Adj[N];
int n;

void initialise(int node,int b,int e){
	if(b>e){
		return ;
	}
	else if(b==e){
		tree[node].val1=a[b];
		return ;
	}
	else{
		initialise(2*node,b,(b+e)/2);
		initialise(2*node+1,(b+e)/2+1,e);
		tree[node].val1=min(tree[2*node].val1,tree[2*node+1].val1);
		return ;
	}
}

void query(node1 &res,int node,int b,int e,int i,int j){
	if(b>e || i>e || j<b){
		return ;
	}
	else if(i<=b && e<=j){
		res=tree[node];
		return ;
	}
	else{
		node1 l,r;
		l.val1=r.val1=INT_MAX;
		query(l,2*node,b,(b+e)/2,i,j);
		query(r,2*node+1,(b+e)/2+1,e,i,j);
		res.val1=min(l.val1,r.val1);
		return ;
	}
}

int findMin(int b,int e){
	node1 res;
	res.val1=INT_MAX;
	query(res,1,0,n-1,b,e);
	return res.val1;
}

vector<pii> getIntervals(int b,int e,int val1){
	vector<int>::iterator itl=lower_bound(Adj[mp1[val1]].begin(),Adj[mp1[val1]].end(),b);
	vector<int>::iterator itu=upper_bound(Adj[mp1[val1]].begin(),Adj[mp1[val1]].end(),e);
	vi seperations;
	vector<pii> answer1;
	seperations.pb(b);
	for(;itl!=itu;itl++){
		seperations.pb((*itl));
	}
	while(!seperations.empty() && seperations.back()>e){
		seperations.pop_back();
	}
	if(seperations.back()!=e){
		seperations.pb(e);
	}
	For(i,1,seperations.size()){
		if(i==1){
			answer1.pb(mp(seperations[i-1],seperations[i]-1));
		}
		else if(i==seperations.size()-1){
			answer1.pb(mp(seperations[i-1]+1,seperations[i]));
		}
		else{
			answer1.pb(mp(seperations[i-1]+1,seperations[i]-1));
		}
	}
	return answer1;
}

ll solve(int b,int e,ll prev){
	// Error4(b,e,prev,findMin(b,e));
	if(b>e){
		return 0;
	}
	else if(b==e){
		// assert(a[b]>prev);
		return a[b]-prev;
	}
	else{
		ll min1=findMin(b,e);
		ll answer1=(min1-prev);
		vector<pii> intervals=getIntervals(b,e,min1);
		rep(interval,intervals){
			answer1=answer1+solve(interval.x,interval.y,min1);
		}
		return answer1;
	}
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		int counter1=0;

		For(i,0,n){
			int temp;
			scanf("%d",&temp);
			a[i]=temp;
			if(mp1.count(a[i])==0){
				mp1[a[i]]=++counter1;
			}
			Adj[mp1[a[i]]].pb(i);
		}
		
		initialise(1,0,n-1);
		ll min1=findMin(0,n-1);
		ll answer1=solve(0,n-1,min1);
		printf("%lld\n",answer1);
		
		mp1.clear();
		For(i,0,counter1+1){
			Adj[i].clear();
		}
	}
return 0;}
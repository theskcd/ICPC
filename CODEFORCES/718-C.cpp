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

struct node1{
	ll f1;ll f0;ll lazyp;
};

node1 tree[400040];
int a[100010];

void initMat(vector<vector<ll> > &res){
	res.resize(2,vector<ll>(2,0));
	res[0][0]=res[0][1]=res[1][0]=1LL;
}

void mul(vector<vector<ll> > &res,vector<vector<ll> > a,vector<vector<ll> > b){
	For(i,0,2){
		For(j,0,2){
			ll sum1=0;
			For(k,0,2){
				sum1=(a[i][k]*(ll)b[k][j]+sum1)%mod;
			}
			// Error3(i,j,sum1);
			res[i][j]=(sum1)%mod;
		}
	}
}

void power(vector<vector<ll> > &res,ll e){
	// Error("power",e);
	if(e==0){
		res.pb({1,0});
		res.pb({0,1});
		// initMat({{1,0},{-1,-1}});
	}
	else if(e==1){
		initMat(res);
	}
	else{
		vector<vector<ll> > res11;
		power(res11,e/2);
		vector<vector<ll> > res22;
		if(e%2==0){
			res.resize(2,vector<ll>(2,0));
			mul(res,res11,res11);
		}
		else{
			initMat(res22);
			res.resize(2,vector<ll>(2,0));
			mul(res,res11,res11);
			// Error5(e,res[0][0],res[0][1],res[1][0],res[1][1]);
			// Error4(res22[0][0],res22[0][1],res22[1][0],res22[1][1]);
			res11=res;
			mul(res,res11,res22);
			// Error5(e,res[0][0],res[0][1],res[1][0],res[1][1]);
		}
	}
}

pair<ll,ll> findVal(ll index){
	vector<vector<ll> > res;
	if(index<0){
		return {-1,-1}; 
	}
	power(res,index);
	return {res[0][0],res[0][1]};
}

void printVal(){
	For(i,0,11){
		pii t1=findVal(i);
		// Error3(i,t1.x,t1.y);
	}
}

void merge(node1 &res,node1 a,node1 b){
	res.f1=(a.f1+b.f1)%mod;
	res.f0=(a.f0+b.f0)%mod;
}

void initialise(int node,int b,int e){
	if(b>e){
		return ;
	}
	else if(b==e){
		pii t1=findVal(a[b]);
		tree[node].f1=t1.x;tree[node].f0=t1.y;tree[node].lazyp=0;
	}
	else{
		initialise(2*node,b,(b+e)/2);
		initialise(2*node+1,(b+e)/2+1,e);
		tree[node].lazyp=0;
		merge(tree[node],tree[2*node],tree[2*node+1]);
	}
}

void solve(node1 &res,ll val1){
	pii t1=findVal(val1-1);
	pii t2=findVal(val1);
	// Error5(val1,t1.x,t1.y,t2.x,t2.y);
	ll temp1=res.f1;ll temp0=res.f0;
	res.f1=((temp0*t1.x)%mod+(temp1*t2.x)%mod)%mod;
	res.f0=((temp0*t1.y)%mod+(temp1*t2.y)%mod)%mod;
}

void updateNode(node1 &res,ll val1){
	res.lazyp+=val1;
}

void init(node1 &res){
	res.f1=res.f0=res.lazyp=0;
}

void update(int node,int b,int e,int i,int j,ll val1){
	// Error4(b,e,i,j);
	if(tree[node].lazyp!=0){
		solve(tree[node],tree[node].lazyp);
		if(b!=e){
			updateNode(tree[2*node],tree[node].lazyp);
			updateNode(tree[2*node+1],tree[node].lazyp);
		}
		tree[node].lazyp=0;
	}
	if(b>e || i>e || j<b){
		return ;
	}
	else if(i<=b && e<=j){
		solve(tree[node],val1);
		// Error5(b,e,val1,tree[node].f1,tree[node].f0);
		if(b!=e){
			updateNode(tree[2*node],val1);
			updateNode(tree[2*node+1],val1);
		}
	}
	else{
		update(2*node,b,(b+e)/2,i,j,val1);
		update(2*node+1,(b+e)/2+1,e,i,j,val1);
		merge(tree[node],tree[2*node],tree[2*node+1]);
		// Error4(b,e,tree[node].f1,tree[node].f0);
	}
}

void query(node1 &res,int node,int b,int e,int i,int j){
	if(tree[node].lazyp!=0){
		solve(tree[node],tree[node].lazyp);
		if(b!=e){
			updateNode(tree[2*node],tree[node].lazyp);
			updateNode(tree[2*node+1],tree[node].lazyp);
		}
		tree[node].lazyp=0;
	}
	if(b>e || i>e || j<b){
		return ;
	}
	else if(i<=b && e<=j){
		res=tree[node];
		return ;
	}
	else{
		node1 l,r;
		init(l);init(r);
		query(l,2*node,b,(b+e)/2,i,j);
		query(r,2*node+1,(b+e)/2+1,e,i,j);
		merge(res,l,r);
		return ;
	}
}

int main(){
	printVal();
	int n,m;
	scanf("%d%d",&n,&m);

	For(i,0,n){
		int temp;
		scanf("%d",&temp);
		temp--;
		a[i]=temp;
	}

	initialise(1,0,n-1);
	// Error(tree[1].f1,tree[1].f0);

	while(m--){
		// error("begin");
		int tp;
		scanf("%d",&tp);
		if(tp==1){
			int l1,r1,x1;
			scanf("%d%d%d",&l1,&r1,&x1);
			update(1,0,n-1,l1-1,r1-1,x1);
		}
		else{
			int l1,r1;
			scanf("%d%d",&l1,&r1);
			node1 res;init(res);
			query(res,1,0,n-1,l1-1,r1-1);
			printf("%lld\n",res.f1);
		}
		// Error(tree[1].f1,tree[1].f0);
		// error("end");
	}
return 0;}
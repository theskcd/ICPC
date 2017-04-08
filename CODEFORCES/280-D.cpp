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
#define F first
#define S second
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

struct node1{
	ll maxL;
	ll maxR;
	ll sumC;
	ll ans;
	int lef,rig;
	int ansL,ansR;
	int maxLL;int maxRR;
	void init(int l,int val){
		maxL=maxR=sumC=ans=val;
		lef=rig=maxLL=maxRR=ansL=ansR=l;
	}
};

struct data{
	node1 mi,mx;
	bool flag;
	int l,r,a,b;
	void init(int val){
		flag=0;
		mi.init(l,-val);
		mx.init(l,val);
	}
};

data tree[400010];
int a[100010];

void initMerge(node1 &res,node1 &val1,node1 &val2){
	res.maxL=max(val1.maxL,val1.sumC+val2.maxL);
	if(res.maxL==val1.maxL){
		res.maxLL=val1.maxLL;
	}
	else{
		res.maxLL=val2.maxLL;
	}
	res.maxR=max(val2.maxR,val2.sumC+val1.maxR);
	if(res.maxR==val2.maxR){
		res.maxRR=val2.maxRR;
	}
	else{
		res.maxRR=val1.maxRR;
	}
	res.sumC=val1.sumC+val2.sumC;
	res.ans=max(val1.ans,max(val2.ans,val1.maxR+val2.maxL));
	if(res.ans==val1.ans){
		res.ansL=val1.ansL;res.ansR=val1.ansR;
	}
	else if(res.ans==val2.ans){
		res.ansL=val2.ansL;res.ansR=val2.ansR;
	}
	else if(res.ans==val1.maxR+val2.maxL){
		res.ansL=val1.maxRR;res.ansR=val2.maxLL;
	}
	// Error4(val1.maxLL,val1.maxRR,val1.ansL,val1.ansR);
	assert(res.ansL!=0 && res.ansR!=0 && res.maxLL!=0 && res.maxRR!=0);
}

void initialise(int node,int b,int e){
	tree[node].l=b;tree[node].r=e;
	if(b>e){
		return ;
	}
	else if(b==e){
		tree[node].init(a[b]);
		return ;
	}
	else{
		initialise(2*node,b,(b+e)/2);
		initialise(2*node+1,(b+e)/2+1,e);
		// tree[node].lef=b;tree[node].rig=e;
		initMerge(tree[node].mi,tree[2*node].mi,tree[2*node+1].mi);
		initMerge(tree[node].mx,tree[2*node].mx,tree[2*node+1].mx);
		// Error3(b,e,tree[node].ans);
	}
}

void pushDown(int node){
	// Error4("pushdown",tree[node].l,tree[node].r,tree[node].flag);
	if(tree[node].l==tree[node].r){
		return ;
	}
	if(tree[node].flag){
		// error("==========");
		// error(tree[node].flag);
		swap(tree[2*node].mi,tree[2*node].mx);
		swap(tree[2*node+1].mx,tree[2*node+1].mi);
		tree[2*node].flag^=1;
		tree[2*node+1].flag^=1;
		tree[node].flag^=1;
		// Error(tree[2*node+1].mx.ans,tree[2*node+1].mi);
	}
}

void update(int node,int b,int e,int index,int val1){
	pushDown(node);
	if(b==e && e==index){
		tree[node].init(val1);
		return ;
	}
	else{
		if(index<=(b+e)/2){
			update(2*node,b,(b+e)/2,index,val1);
		}
		else{
			update(2*node+1,(b+e)/2+1,e,index,val1);
		}
		initMerge(tree[node].mi,tree[2*node].mi,tree[2*node+1].mi);
		initMerge(tree[node].mx,tree[2*node].mx,tree[2*node+1].mx);
	}
}

void unfix(int node,int b,int e,int i,int j){
	// Error4("unfix",b,e,tree[node].flag);
	// Error(i,j);
	// error(tree[node].flag);
	pushDown(node);
	if(i==b && e==j){
		// error(tree[node].flag);
		swap(tree[node].mx,tree[node].mi);
		tree[node].flag^=1;
		// Error4("change",tree[node].flag,tree[node].mx.ans,tree[node].mi.ans);
		return ;
	}
	else{
		if(i>(b+e)/2){
			unfix(2*node+1,(b+e)/2+1,e,i,j);	
		}
		else if(j<=(b+e)/2){
			unfix(2*node,b,(b+e)/2,i,j);
		}
		else{
			unfix(2*node,b,(b+e)/2,i,(b+e)/2);
			unfix(2*node+1,(b+e)/2+1,e,(b+e)/2+1,j);
		}
		initMerge(tree[node].mx,tree[2*node].mx,tree[2*node+1].mx);
		initMerge(tree[node].mi,tree[2*node].mi,tree[2*node+1].mi);
	}

}

void query(data &res,int node,int b,int e,int i,int j){
	// Error5("query",i,j,b,e);
	// error(tree[node].flag);
	pushDown(node);
	if(i==b && e==j){
		res=tree[node];
		return ;
	}
	else{
		data l;
		data r;
		if(j<=(b+e)/2){
			query(l,2*node,b,(b+e)/2,i,j);
			res=l;
			return ;
		}
		else if(i>(b+e)/2){
			query(r,2*node+1,(b+e)/2+1,e,i,j);
			res=r;
			return ;
		}
		else{
			query(l,2*node,b,(b+e)/2,i,(b+e)/2);
			query(r,2*node+1,(b+e)/2+1,e,(b+e)/2+1,j);
			initMerge(res.mx,l.mx,r.mx);
			return ;
			// initMerge(res.mi,l.mi,r.mi);
		}
		// Error4(b,e,res.mx.ansL,res.mx.ansR);
	}
}

ll findAnswer(int l1,int r1,int k1,int n){
	ll finalAnswer=0;
	vector<pii> makeWays;
	For(i,1,k1+1){
		data currAnswer;
		query(currAnswer,1,1,n,l1,r1);
		if(currAnswer.mx.ans>=0){
			finalAnswer=finalAnswer+currAnswer.mx.ans;
			// Error3(currAnswer.mx.ans,currAnswer.mx.ansL,currAnswer.mx.ansR);
			unfix(1,1,n,currAnswer.mx.ansL,currAnswer.mx.ansR);
			// error("========");
			makeWays.pb(mp(currAnswer.mx.ansL,currAnswer.mx.ansR));
		}
		else{
			break;
		}
	}
	rep(ways,makeWays){
		unfix(1,1,n,ways.F,ways.S);
	}
	return finalAnswer;
}

int main(){
	int n,m;
	scanf("%d",&n);
	For(i,1,n+1){
		int temp;
		scanf("%d",&temp);
		a[i]=temp;
	}
	initialise(1,1,n);
	scanf("%d",&m);
	while(m--){
		int tp;
		scanf("%d",&tp);
		if(tp==0){
			int index,val;
			scanf("%d%d",&index,&val);
			update(1,1,n,index,val);
		}
		else{
			int l1,r1,k;
			scanf("%d%d%d",&l1,&r1,&k);
			ll final=findAnswer(l1,r1,k,n);
			printf("%lld\n",final);
		}
	}
return 0;}
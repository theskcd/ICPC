#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

// (づ°ω°)づﾐe★゜・。。・゜゜・。。・゜☆゜・。。・゜゜・。。・

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
#define N 300010
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

ll a[N];
ll num[N];

template<class T>
int sign(T x){
	if(x>0){
		return 1;
	}
	else if(x<0){
		return -1;
	}
	else{
		return 0;
	}
}

typedef struct node2{
	ll answer1;
	ll lval;
	ll rval;
}node1;

node1 tree[4*N];

void merge(int node,int b,int e){
	int mid=(b+e)/2;
	int node1=2*node;
	tree[node].answer1=max(tree[2*node].answer1,tree[2*node+1].answer1);
	if(!num[mid] || !num[mid+1] || sign(num[mid])<sign(num[mid+1])){
		tree[node].lval=tree[2*node].lval;
		tree[node].rval=tree[2*node+1].rval;
	}
	else{
		tree[node].answer1=max(tree[node].answer1,tree[2*node].rval+tree[2*node+1].lval);
		if(tree[2*node].answer1==mid-b+1){
			tree[node].lval=tree[2*node].lval+tree[2*node+1].lval;
		}
		else{
			tree[node].lval=tree[2*node].lval;
		}
		if(tree[2*node+1].answer1==e-mid){
			tree[node].rval=tree[2*node+1].rval+tree[2*node].rval;
		}
		else{
			tree[node].rval=tree[2*node+1].rval;
		}
		tree[node].answer1=max(tree[node].answer1,max(tree[node].rval,tree[node].lval));
	}
}

void initialise(int node,int b,int e){
	if(b>e){
		return ;
	}
	else if(b==e){
		int temp1=!!a[b];
		tree[node]={temp1,temp1,temp1};
		return ;
	}
	else{
		initialise(2*node,b,(b+e)/2);
		initialise(2*node+1,(b+e)/2+1,e);
		merge(node,b,e);
	}
}

void update(int node,int b,int e,int index,ll val1){
	if(b>e){
		return ;
	}
	if(b==e && e==index){
		num[index]+=val1;
		int temp1=!!a[index];
		tree[node]={temp1,temp1,temp1};
		return ;
	}
	else{
		if((b+e)/2>=index){
			update(2*node,b,(b+e)/2,index,val1);
		}
		else{
			update(2*node+1,(b+e)/2+1,e,index,val1);
		}
		merge(node,b,e);
		return ;
	}
}

int main(){
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif
	int n;
	scanf("%d",&n);

	For(i,0,n){
		int temp;
		scanf("%d",&temp);
		a[i]=temp;
	}

	For(i,0,n-1){
		num[i]=a[i+1]-a[i];
	}

	if(n>1){
		initialise(1,0,n-2);
	}

	int q;
	scanf("%d",&q);
	while(q--){
		int l1,r1,d1;
		scanf("%d%d%d",&l1,&r1,&d1);
		if(n==1){
			puts("1");
			continue;
		}
		if(l1!=1){
			update(1,0,n-2,l1-2,d1);
		}
		if(r1!=n){
			update(1,0,n-2,r1-1,-d1);
		}
		printf("%lld\n",tree[1].answer1+1);
	}
return 0;}
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
	int lson;
	int rson;
	int sum1;
}tree[4000400];

int maxx=1000000000;
vector<pii> Adj[10110];
vector<pair<pii,int> > v1;
unordered_map<int,int> mp1;
set<int> s1;
int totalVert=0;
int rt[10010];

int query(int node,int b,int e,int i,int j){
	if(node==0){
		return 0;
	}
	else if(i<=b && e<=j){
		return tree[node].sum1;
	}
	else{
		int temp1=query(tree[node].lson,b,(b+e)/2,i,j);
		temp1+=query(tree[node].rson,(b+e)/2+1,e,i,j);
		return temp1;
	}
}

// int query(int v,int l,int r,int x,int y){
// 	if (v==0) return 0;
// 	if (l==x && r==y) return tree[v].sum1;
// 	int mid=(l+r) >> 1;
// 	if (y<=mid) return query(tree[v].lson,l,mid,x,y);
// 	else if (x>mid) return query(tree[v].rson,mid+1,r,x,y);
// 	else return query(tree[v].lson,l,mid,x,mid)+query(tree[v].rson,mid+1,r,mid+1,y);
// }

void update(int &node,int b,int e,int index){
	totalVert++;
	tree[totalVert]=tree[node];
	node=totalVert;
	tree[totalVert].sum1++;
	if(b==e){
		return ;
	}
	else{
		if(index<=(b+e)/2){
			update(tree[node].lson,b,(b+e)/2,index);
		}
		else{
			update(tree[node].rson,(b+e)/2+1,e,index);
		}
	}
}

int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	For(i,0,n){
		int x1,r1,f1;
		scanf("%d%d%d",&x1,&r1,&f1);
		v1.pb(mp(mp(r1,x1),f1));
	}
	sort(all(v1));
	reverse(all(v1));
	ll answer1=0;
	int golbIndex=0;

	rep(tower,v1){
		int currentX=tower.x.y;
		int freq=tower.y;
		int range1=tower.x.x;
		For(j,max(freq-k,1),freq+k+1){
			answer1=answer1+query(rt[j],1,maxx,max(1,currentX-range1),min(maxx,currentX+range1));
		}
		update(rt[freq],1,maxx,currentX);
	}

	printf("%lld\n",answer1);
return 0;}
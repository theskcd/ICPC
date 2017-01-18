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

typedef struct node2{
	int dp[5][5];
}node1;

node1 tree[800040];
char s1[200010];

void init(int node,char c){
	For(i,0,5){
		For(j,0,5){
			tree[node].dp[i][j]=mod;
		}
	}

	For(i,0,5){
		tree[node].dp[i][i]=0;
	}

	if(c=='2'){
		tree[node].dp[0][1]=0;
		tree[node].dp[0][0]=1;
	}
	else if(c=='0'){
		tree[node].dp[1][2]=0;
		tree[node].dp[1][1]=1;
	}
	else if(c=='1'){
		tree[node].dp[2][3]=0;
		tree[node].dp[2][2]=1;
	}
	else if(c=='6'){
		tree[node].dp[3][3]=1;
		tree[node].dp[4][4]=1;
	}
	else if(c=='7'){
		tree[node].dp[3][4]=0;
	}
}

int add(int x1,int y1){
	int answer1=x1+y1;
	return min(answer1,mod);
}

void merge(node1 &res,node1 &l,node1 &r){
	For(i,0,5){
		For(j,0,5){
			res.dp[i][j]=mod;
		}
	}
	For(i,0,5){
		For(j,i,5){
			For(k,j,5){
				res.dp[i][k]=min(res.dp[i][k],add(l.dp[i][j],r.dp[j][k]));
			}
		}
	}
}

void printAll(node1 node){
	For(i,0,5){
		For(j,0,5){
			printf("%d ",node.dp[i][j]);
		}
		printf("\n");
	}
}

void makeStable(node1 &res){
	For(i,0,5){
		For(j,0,5){
			res.dp[i][j]=mod;
		}
		// res.dp[i][i]=0;
	}
}

void initialise(int node,int b,int e){
	if(b>e){
		return ;
	}
	else if(b==e){
		init(node,s1[b]);
	}
	else{
		initialise(2*node,b,(b+e)/2);
		initialise(2*node+1,(b+e)/2+1,e);
		merge(tree[node],tree[2*node],tree[2*node+1]);
		// printAll(tree[node]);
	}
}


bool check(node1 node){
	For(i,0,5){
		For(j,0,5){
			if(node.dp[i][j]!=mod){
				return true;
			}
		}
	}
	return false;
}

void query(node1 &res,int node,int b,int e,int i,int j){
	// Error(b,e,i,j);
	if(b>e || i>e || j<b){
		return ;
	}
	else if(i<=b && e<=j){
		res=tree[node];
		return ;
	}
	else{
		node1 l,r;
		makeStable(l);
		makeStable(r);
		query(l,2*node,b,(b+e)/2,i,j);
		query(r,2*node+1,(b+e)/2+1,e,i,j);
		bool useL=check(l);
		bool useR=check(r);
		if(useL && !useR){
			res=l;
		}
		else if(!useL && useR){
			res=r;
		}
		else if(useL && useR){
			merge(res,l,r);
		}
		// printAll(res);
		return ;
	}
}

int main(){
	int n,q;
	scanf("%d%d",&n,&q);
	scanf("%s",s1);
	initialise(1,0,n-1);
	// error(tree[1].dp[0][4]);
	while(q--){
		int x1,y1;
		scanf("%d%d",&x1,&y1);
		x1--,y1--;
		node1 res;
		makeStable(res);
		query(res,1,0,n-1,x1,y1);
		if(res.dp[0][4]!=mod){
			printf("%d\n",res.dp[0][4]);
		}
		else{
			printf("-1\n");
		}
	}
return 0;}
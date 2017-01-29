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

string a,b;
int minPos[100010];
int maxPos[100010];
int tree[400010];

void update(int node,int b,int e,int index,int val1){
	if(b>e){
		return ;
	}
	else if(b==e && e==index){
		tree[node]=min(val1,tree[node]);
		// Error3(b,e,tree[])
	}
	else{
		if(index<=(b+e)/2){
			update(2*node,b,(b+e)/2,index,val1);
		}
		else{
			update(2*node+1,(b+e)/2+1,e,index,val1);
		}
		tree[node]=min(tree[2*node],tree[2*node+1]);
		// Error3(b,e,tree[node]);
	}
}

void initialise(int node,int b,int e){
	if(b>e){
		return ;
	}
	else if(b==e){
		tree[node]=INT_MAX;
	}
	else{
		initialise(2*node,b,(b+e)/2);
		initialise(2*node+1,(b+e)/2+1,e);
		tree[node]=INT_MAX;
	}
}

void query(int& res,int node,int b,int e,int i,int j){
	if(b>e || i>e || j<b){
		return ;
	}
	else if(i<=b && e<=j){
		res=tree[node];
		return ;
	}
	else{
		int l,r;
		l=r=INT_MAX;
		query(l,2*node,b,(b+e)/2,i,j);
		query(r,2*node+1,(b+e)/2+1,e,i,j);
		res=min(l,r);
		return ;
	}
}

int main(){
	cin>>a;
	cin>>b;
	swap(a,b);
	int n=a.size();
	int m=b.size();
	int pointer=0;
	initialise(1,0,m);
	For(i,0,n){
		minPos[i]=-1;
		maxPos[i]=-1;
	}
	For(i,0,n){
		while(pointer<m && a[i]!=b[pointer]){
			pointer++;
		}
		if(pointer<m){
			minPos[i]=pointer;
		}
		// Error(i,minPos[i]);
		pointer++;
	}
	pointer=m-1;
	rof(i,n-1,-1){
		while(pointer>=0 && a[i]!=b[pointer]){
			pointer--;
		}
		if(pointer>=0){
			maxPos[i]=pointer;
		}
		// Error(i,maxPos[i]);
		pointer--;
	}
	int answer1=n;
	int mode1=-1;
	pii poss;
	For(i,0,n){
		if(minPos[i]!=-1){
			// answer1=min(answer1,n-1-i);
			if(n-1-i<answer1){
				answer1=n-1-i;
				mode1=0;
				poss={i+1,n};
			}
		}
	}
	rof(i,n-1,-1){
		if(maxPos[i]!=-1){
			// answer1=min(answer1,i);
			if(i<answer1){
				answer1=i;
				mode1=1;
				poss={0,i-1};
			}
		}
	}

	// debug;
	// error(answer1);
	// Error(poss.x,poss.y);
	
	rof(i,n-1,-1){
		// error(i);
		int res=INT_MAX;
		if(minPos[i]!=-1){
			query(res,1,0,m,minPos[i]+1,m);
			// Error3(i,res,minPos[i]+1);
			if(res!=INT_MAX){
				// Error(answer1,res-i-1);
				if(res-i-1<answer1){
					answer1=res-i-1;
					mode1=2;
					poss={i+1,res-1};
				}
			}
		}
		if(maxPos[i]!=-1){
			update(1,0,m,maxPos[i],i);
		}
	}

	if(mode1==-1){
		printf("-\n");
	}
	else{
		For(i,0,n){
			if(!(i>=poss.x && i<=poss.y)){
				printf("%c",a[i]);
			}
		}
		printf("\n");
	}
return 0;}
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

int r[20];
int b[20];
bool color[20];
int dp[(1<<16)][2][300];
int redC[(1<<16)];
int blueC[(1<<16)];
int n;

int solve(int mask,bool whichColor,int tokens){
	// Error3(mask,whichColor,tokens);
	tokens=min(tokens,n*n);
	if(mask==(int)((1<<n)-1)){
		dp[mask][whichColor][tokens]=0;
		return 0;
	}
	else if(dp[mask][whichColor][tokens]!=-1){
		return dp[mask][whichColor][tokens];
	}
	else{
		int getR=redC[mask];
		int getB=blueC[mask];
		// Error3(mask,getR,getB);
		int currR=0;
		int currB=0;
		if(whichColor==0){
			currR=tokens;
		}
		else{
			currB=tokens;
		}
		int currCost=INT_MAX;	
		For(i,0,n){
			if(!((1<<i) & mask)){
				// Error(i,mask);
				int reqR=max(r[i]-getR-currR,0);
				int reqB=max(b[i]-getB-currB,0);
				int needMore=max(reqR,reqB);
				if(needMore+currR-max(0,r[i]-getR)==0){
					currCost=min(currCost,needMore+solve(mask | (1<<i),1,needMore+currB-max(0,b[i]-getB)));
				}
				if(needMore+currB-max(0,b[i]-getB)==0){
					currCost=min(currCost,needMore+solve(mask | (1<<i),0,needMore+currR-max(0,r[i]-getR)));
				}
			}
		}
		dp[mask][whichColor][tokens]=currCost;
		// Error4(mask,whichColor,tokens,currCost);
		return dp[mask][whichColor][tokens];
	}
}

void clearAll(){
	For(i,0,(1<<16)){
		For(j,0,2){
			For(k,0,300){
				dp[i][j][k]=-1;
			}
		}
	}
}

int main(){
	scanf("%d",&n);
	int excessRCost=0;
	int excessBCost=0;
	For(i,0,n){
		string s;
		int r1,b1;
		cin>>s>>r1>>b1;
		r[i]=r1;b[i]=b1;
		if(s[0]=='R'){
			color[i]=1;
		}
		else{
			color[i]=0;
		}
		if(r[i]>=n){
			excessRCost+=r[i]-n;
			r[i]=n;
		}
		if(b[i]>=n){
			excessBCost+=b[i]-n;
			b[i]=n;
		}
	}

	For(i,0,(1<<n)){
		int redCount=0;int blueCount=0;
		For(j,0,n){
			if(i & (1<<j)){
				if(color[j]==0){
					blueCount++;
				}
				else{
					redCount++;
				}
			}
		}
		redC[i]=redCount;blueC[i]=blueCount;
		// Error3(i,redC[i],blueC[i]);
	}

	clearAll();

	int answer1=max(excessRCost,excessBCost)+n;
	// error(answer1);
	// Error(excessRCost,excessBCost);
	if(excessRCost>excessBCost){
		answer1=answer1+solve(0,1,excessRCost-excessBCost);
	}
	else{
		answer1=answer1+solve(0,0,excessBCost-excessRCost);
	}
	printf("%d\n",answer1);
return 0;}
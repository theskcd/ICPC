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

char s[101];
int stepsV[101][101];
int stepsK[101][101];
ll dp[101][101][101][3];
bool visited[101][101][101][3];
// int findChar[101][101][101][3];
int n;
int normieC;
int countV;
int countK;
int timesCalled=0;
bool visited1[101];

int findChar(int normie,int v,int k,int charType){
	// error(++timesCalled);

	For(i,0,101) visited1[i]=false;
	int countNormie=0;
	int countVe=0;
	int countKe=0;
	For(i,1,n+1){
		if(s[i]!='V' && s[i]!='K'){
			if(countNormie==normie){
				continue;
			}
			countNormie++;
			visited1[i]=true;
		}
		else if(s[i]=='V'){
			if(countVe==v){
				continue;
			}
			countVe++;
			visited1[i]=true;
		}
		else if(s[i]=='K'){
			if(countKe==k){
				continue;
			}
			countKe++;visited1[i]=true;
		}
	}
	int movesNeeded=0;
	if(charType==0){
		For(i,1,n+1){
			if(!visited1[i] && s[i]!='V'){
				movesNeeded++;
			}
			else if(s[i]=='V' && !visited1[i]){
				return movesNeeded;
			}
		}
	}
	else if(charType==1){
		For(i,1,n+1){
			if(!visited1[i] && s[i]!='K'){
				movesNeeded++;
			}
			else if(s[i]=='K' && !visited1[i]){
				return movesNeeded;
			}
		}
	}
	else if(charType==2){
		For(i,1,n+1){
			if(!visited1[i] && (s[i]=='V' || s[i]=='K')){
				movesNeeded++;
			}
			else if((s[i]!='V' && s[i]!='K') && !visited1[i]){
				return movesNeeded;
			}
		}
	}
	return INT_MAX;
}

void solve(int index,int v,int k,int lastChar){
	// Error4(index,v,k,lastChar);
	if(index>n){
		visited[index][v][k][lastChar]=true;
		dp[index][v][k][lastChar]=INT_MAX;
		return ;
	}
	if(index==n){
		visited[index][v][k][lastChar]=true;
		if(v==countV && k==countK){
			dp[index][v][k][lastChar]=0;
			return ;
		}
		else{
			dp[index][v][k][lastChar]=INT_MAX;
			return ;
		}
	}
	else{
		if(visited[index][v][k][lastChar]){
			return ;
		}
		else{
			ll res=INT_MAX;
			int posN=findChar(index-(v+k),v,k,2);
			int posV=findChar(index-(v+k),v,k,0);
			int posK=findChar(index-(v+k),v,k,1);
			// Error4(index,v,k,lastChar);
			// Error3(posN,posV,posK);
			int min1=-1;
			// if(index==0 && v==0 && k==0){
			// 	posN = posV = posK = 0;
			// }
			if(lastChar==0){
				if(posN!=INT_MAX){
					// Error4(index,v,k,lastChar);
					// error("going to");
					// Error4(index+1,v,k,2);
					solve(index+1,v,k,2);assert(visited[index+1][v][k][2]);
					//shift moves add here
					res=min(res,posN + dp[index+1][v][k][2]);
					if(res==posN + dp[index+1][v][k][2]){
						min1=2;
					}
				}
				if(posV!=INT_MAX){
					// Error4(index,v,k,lastChar);
					// error("going to");
					// Error4(index+1,v+1,k,0);
					solve(index+1,v+1,k,0);assert(visited[index+1][v+1][k][0]);
					//shift moves add here
					res=min(res,posV + dp[index+1][v+1][k][0]);
					if(res==posV + dp[index+1][v+1][k][0]){
						min1=0;
					}
				}
			}
			else{
				if(posN!=INT_MAX){
					// Error4(index,v,k,lastChar);
					// error("going to");
					// Error4(index+1,v,k,2);					
					solve(index+1,v,k,2);assert(visited[index+1][v][k][2]);
					//shift moves add here
					res=min(res,posN + dp[index+1][v][k][2]);
					if(res==posN + dp[index+1][v][k][2]){
						min1= 2;
					}
				}
				if(posV!=INT_MAX){
					// Error4(index,v,k,lastChar);
					// error("going to");
					// Error4(index+1,v+1,k,0);
					solve(index+1,v+1,k,0);assert(visited[index+1][v+1][k][0]);
					res=min(res,posV + dp[index+1][v+1][k][0]);
					if(res==posV + dp[index+1][v+1][k][0]){
						min1=0;
					}
				}
				if(posK!=INT_MAX){
					// Error4(index,v,k,lastChar);
					// error("going to");
					// Error4(index+1,v,k+1,1);
					solve(index+1,v,k+1,1);assert(visited[index+1][v][k+1][1]);
					res=min(res,posK + dp[index+1][v][k+1][1]);
					if(res==posK + dp[index+1][v][k+1][1]){
						min1=1;
					}
				}
			}
			dp[index][v][k][lastChar]=res;
			// Error5(index,v,k,lastChar,min1);
			// error(dp[index][v][k][lastChar]);
			// Error3(posN,posK,posV);
			// Error4(index,v,k,lastChar);
			visited[index][v][k][lastChar]=true;
			return ;
		}
	}
}

int main(){
	scanf("%d",&n);
	scanf("%s",s+1);
	For(i,1,n+1){
		if(s[i]=='V'){
			countV++;
		}
		else if(s[i]=='K'){
			countK++;
		}
		else{
			normieC++;
		}
	}
	// error(findChar(0,0,0,2));
	// error(findChar(0,0,0,1));
	// error(findChar(0,0,0,0));
	solve(0,0,0,2);
	printf("%lld\n",dp[0][0][0][2]);
return 0;}
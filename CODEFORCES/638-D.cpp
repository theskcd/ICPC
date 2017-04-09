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

char state[111][111][111];
int state1[111][111][111];
int n,m,k;
int groups=0;
pair<pii,int> max1;
pair<pii,int> min1;

bool checkBounds(int i1,int j1,int k1){
	if(i1<n && j1<m && k1<k && i1>=0 && j1>=0 && k1>=0){
		return true;
	}
	else{
		return false;
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&k);

	For(i,0,n){
		For(j,0,m){
			scanf("%s",state[i][j]);
			For(k1,0,k){
				state1[i][j][k1]=state[i][j][k1]-'0';
			}
		}
	}

	int answer1=0;

	For(i,0,n){
		For(j,0,m){
			For(k1,0,k){
				if(state1[i][j][k1]){
					int inclueThis=0;
					// if(i && j+1<m && state1[i-1][j][k1] && state1[i][j+1][k] && !state1[i-1][j+1][k1]) inclueThis=1;
					// if(i && k1+1<k && state1[i-1][j][k1] && state1[i][j][k1+1] && !state1[i-1][j][k1+1]) inclueThis=1;
					// if(j && i+1<n && state1[i][j-1][k1] && state1[i+1][j][k1] && !state1[i+1][j-1][k1]) inclueThis=1;
					// if(j && k1+1<k && state1[i][j-1][k1] && state1[i][j][k1+1] && !state1[i][j-1][k1+1]) inclueThis=1;
					// if(k1 && i+1<n && state1[i][j][k1-1] && state1[i+1][j][k1] && !state1[i+1][j][k1-1]) inclueThis=1;
					// if(k1 && j+1<m && state1[i][j][k1-1] && state1[i][j+1][k1] && !state1[i][j+1][k1-1]) inclueThis=1;
			       if (i && i+1 < n && state1[i-1][j][k1] && state1[i+1][j][k1]) inclueThis=1;
			       if (j && j+1 < m && state1[i][j-1][k1] && state1[i][j+1][k1]) inclueThis=1;
			       if (k1 && k1+1 < k && state1[i][j][k1-1] && state1[i][j][k1+1]) inclueThis=1;

			       if (i && j+1 < m && state1[i-1][j][k1] && state1[i][j+1][k1] && !state1[i-1][j+1][k1]) inclueThis=1;
			       if (i && k1+1 < k && state1[i-1][j][k1] && state1[i][j][k1+1] && !state1[i-1][j][k1+1]) inclueThis=1;

			       if (j && i+1 < n && state1[i][j-1][k1] && state1[i+1][j][k1] && !state1[i+1][j-1][k1]) inclueThis=1;
			       if (j && k1+1 < k && state1[i][j-1][k1] && state1[i][j][k1+1] && !state1[i][j-1][k1+1]) inclueThis=1;

			       if (k1 && i+1 < n && state1[i][j][k1-1] && state1[i+1][j][k1] && !state1[i+1][j][k1-1]) inclueThis=1;
			       if (k1 && j+1 < m && state1[i][j][k1-1] && state1[i][j+1][k1] && !state1[i][j+1][k1-1]) inclueThis=1;

					answer1=answer1+inclueThis;
				}
			}
		}
	}

	printf("%d\n",answer1);
return 0;}
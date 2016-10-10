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
//#define si(n) scanf("%d",&n)
//#define sii(n,m) scanf("%d%d",&n,&m)
//#define pi(n) printf("%d\n",n)
const int inf=0x3f3f3f3f;
const long double pi=acos(-1.0);
#define MAX 50010
// #define N 100000
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

class DiameterOfRandomTree
{
public:
	vi Adj[101];
	vi Adj1[101];
	double dp[101][101][101];

	void DFS(int u,int p){
		rep(t1,Adj1[u]){
			if(t1!=p){
				Adj[u].pb(t1);
				DFS(t1,u);
			}
		}
	}

	void tryAll(int u,int maxDepth,int maxDiameter){
		double res=dp[u][maxDepth][maxDiameter];
		if(res!=-1){
			return ;
		}
		else if(Adj[u].size()==0){
			dp[u][maxDepth][maxDiameter]=1;
			// Error4(u,maxDepth,maxDiameter,dp[u][maxDepth][maxDiameter]);
			return ;
		}
		else{
			res=0;
			For(m,1,min(maxDiameter,maxDepth)+1){
				For(i,0,Adj[u].size()){
					int v=Adj[u][i];
					For(edge,1,min(2,m)+1){
						double res1=0;
						tryAll(v,m-edge,maxDiameter);
						if(m-edge>0){
							tryAll(v,m-edge-1,maxDiameter);
						}
						res1=dp[v][m-edge][maxDiameter];
						if(m-edge>0){
							res1=res1-dp[v][m-edge-1][maxDiameter];
						}
						// Error4(u,m,maxDiameter,res1);
						For(j,0,Adj[u].size()){
							double res2=0;
							if(j!=i){
								if(j<i){
									int maxPossible=maxDiameter-m;
									maxPossible=min(maxPossible,m-1);
									For(k,1,min(maxPossible,2)+1){
										tryAll(Adj[u][j],maxPossible-k,maxDiameter);
									}
									For(k,1,min(maxPossible,2)+1){
										res2=res2+dp[Adj[u][j]][maxPossible-k][maxDiameter];
									}
								}
								else{
									int maxPossible=maxDiameter-m;
									maxPossible=min(maxPossible,m);
									For(k,1,min(maxPossible,2)+1){
										tryAll(Adj[u][j],maxPossible-k,maxDiameter);
									}
									For(k,1,min(maxPossible,2)+1){
										res2=res2+dp[Adj[u][j]][maxPossible-k][maxDiameter];
									}
								}
								res1=res1*res2;
							}
						}
						// Error4(u,m,maxDiameter,res);
						res=res+res1;
					}
				}
			}
			// Error4(u,maxDepth,maxDiameter,res);
			dp[u][maxDepth][maxDiameter]=res;
			return ;
		}
	}

	double getExpectation(vi a,vi b){
		For(i,0,101){
			Adj[i].clear();
			Adj1[i].clear();
		}

		assert(a.size()==b.size());
		
		For(i,0,a.size()){
			Adj1[a[i]].pb(b[i]);
			Adj1[b[i]].pb(a[i]);
			Error(a[i],b[i]);
		}

		DFS(0,-1);
		
		For(i,0,101){
			For(j,0,101){
				For(k,0,101){
					dp[i][j][k]=-1;
				}
			}
		}

		double answer1=0;
		double prev=0;
		double pow2=1;
		For(i,0,a.size()){
			pow2=pow2*2.0;
		}
		For(i,0,2*a.size()+1){
			tryAll(0,2*a.size(),i);
			double temp1=dp[0][2*a.size()][i];
			Error(i,temp1);
			temp1=temp1-prev;
			answer1=answer1+(i*temp1)/pow2;
			prev=dp[0][2*a.size()][i];
		}
		return answer1;
	}
};

// int main(){
// 	DiameterOfRandomTree drt;
// 	vi a={1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49} ;
// 	vi b={0, 0, 1, 3, 1, 1, 5, 5, 7, 8, 10, 6, 9, 8, 4, 4, 9, 14, 9, 0, 4, 0, 14, 2, 2, 3, 18, 27, 2, 22, 13, 31, 27, 18, 32, 16, 14, 19, 34, 39, 20, 38, 34, 17, 0, 36, 7, 10, 37};

// 	error(drt.getExpectation(a,b));
// }
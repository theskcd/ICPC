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

vi Adj[3010];
vi Adj1[3010];
bool visited[3010];
int dis[3010][3010];
int dis1[3010][3010];
vector<pii> far[3010];
vector<pii> far1[3010];

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	For(i,0,m){
		int a1,b1;
		scanf("%d%d",&a1,&b1);
		Adj[a1].pb(b1);
		Adj1[b1].pb(a1);
	}

	For(i,1,n+1){
		For(j,1,n+1){
			dis[i][j]=10e8;
			dis1[i][j]=10e8;
		}
	}

	For(i,1,n+1){
		For(j,1,n+1){
			visited[j]=false;
		}
		queue<pii> Q1;
		dis[i][i]=0;
		Q1.push(mp(dis[i][i],i));
		while(!Q1.empty()){
			pii t1=Q1.front();Q1.pop();
			if(visited[t1.S]){
				continue;
			}
			visited[t1.S]=true;
			rep(t2,Adj[t1.S]){
				if(dis[i][t2]>dis[i][t1.S]+1){
					dis[i][t2]=dis[i][t1.S]+1;
					Q1.push(mp(dis[i][t2],t2));
				}
			}
		}

		For(j,1,n+1){
			if(!visited[j]){
				dis[i][j]=-10e8;
			}
		}

		For(j,1,n+1){
			far[i].pb(mp(dis[i][j],j));
		}

		sort(all(far[i]));reverse(all(far[i]));
	}

	For(i,1,n+1){
		For(j,1,n+1){
			visited[j]=false;
		}
		queue<pii> Q1;
		dis1[i][i]=0;
		Q1.push(mp(dis1[i][i],i));
		while(!Q1.empty()){
			pii t1=Q1.front();Q1.pop();
			if(visited[t1.S]){
				continue;
			}
			visited[t1.S]=true;
			rep(t2,Adj1[t1.S]){
				if(dis1[i][t2]>dis1[i][t1.S]+1){
					dis1[i][t2]=dis1[i][t1.S]+1;
					Q1.push(mp(dis1[i][t2],t2));
				}
			}
		}

		For(j,1,n+1){
			if(visited[j]){
				far1[i].pb(mp(dis1[i][j],j));
			}
		}

		sort(all(far1[i]));reverse(all(far1[i]));
		// For(k,0,3){
		// 	Error3(i,far1[i][k].S,far1[i][k].F);
		// }
	}

	int maxAnswer=0;
	vi answerList;

	For(i,1,n+1){
		For(j,1,n+1){
			if(i==j) continue;
			For(k,0,min((int)far1[i].size(),3)){
				For(l,0,min((int)far[j].size(),3)){
					if(far1[i][k].S==far[j][l].S) continue;
					if(i==far[j][l].S) continue;
					if(j==far1[i][k].S) continue;
					if(j==far[j][l].S) continue;
					if(i==far1[i][k].S) continue;
					vi currAnswer;
					currAnswer={far1[i][k].S,i,j,far[j][l].S};
					if(true){
						int nowAnswer=dis[far1[i][k].S][i]+dis[i][j]+dis[j][far[j][l].S];
						// Error4(far1[i][k].S,i,j,far[j][l].S);
						// Error3(dis[far1[i][k].S][i],dis[i][j],dis[j][far[j][l].S]);
						if(nowAnswer>maxAnswer){
							maxAnswer=nowAnswer;
							answerList=currAnswer;
						}
					}
				}
			}
		}
	}

	error(maxAnswer);
	rep(t1,answerList){
		printf("%d ",t1);
	}
	printf("\n");
return 0;}
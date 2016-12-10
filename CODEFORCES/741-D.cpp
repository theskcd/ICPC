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
#define MAX1 1000000000
const int inf=0x3f3f3f3f;
const long double pi=acos(-1.0);
#define MAXN 500010
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
const double InfCost = 1e99;

vector<pii> Adj[MAXN];
int val1[MAXN];
bool visited[MAXN];
int height1[MAXN];
int answer1[MAXN];
int size1[MAXN];
int f[(1<<22)];
int start1[MAXN];
int end1[MAXN];
int discover[MAXN];
int dfs_timer=0;

void DFS(int u,int mask,int h){
	visited[u]=true;
	val1[u]=mask;
	height1[u]=h;
	size1[u]=1;
	start1[u]=dfs_timer;
	discover[dfs_timer]=u;
	dfs_timer++;

	rep(t1,Adj[u]){
		if(!visited[t1.x]){
			DFS(t1.x,mask ^ (1<<t1.y),h+1);
			size1[u]+=size1[t1.x];
		}
	}
	// Error(u,height1[u]);
}

void DFS1(int u,int p,bool keep){
	// Error(u,p);
	visited[u]=true;
	int bigChild=-1;
	int maxSize=-1;
	int maxAnswer=-1;
	rep(t1,Adj[u]){
		if(size1[t1.x]>maxSize){
			maxSize=size1[t1.x];
			bigChild=t1.x;
		}
	}

	rep(t1,Adj[u]){
		if(t1.x!=p && t1.x!=bigChild){
			DFS1(t1.x,u,0);
		}
	}
	if(bigChild!=-1){
		DFS1(bigChild,u,1);
		rep(t1,Adj[u]){
			if(t1.x!=p && t1.x!=bigChild){
				For(i,start1[t1.x],start1[t1.x]+size1[t1.x]){
					int maskNow=val1[discover[i]];
					int part1=height1[discover[i]];
					For(i,0,22){
						if(maskNow & (1<<i)){
							int tempMask=(maskNow^(1<<i));
							if(f[tempMask]!=-1e9){
								maxAnswer=max(maxAnswer,part1+f[tempMask]-2*height1[u]);
							}
						}
						else{
							int tempMask=(maskNow^(1<<i));
							if(f[tempMask]!=-1e9){
								maxAnswer=max(maxAnswer,part1+f[tempMask]-2*height1[u]);
							}
						}
						if(f[maskNow]!=-1e9){
							maxAnswer=max(maxAnswer,part1+f[maskNow]-2*height1[u]);
						}
					}
				}
				For(i,start1[t1.x],start1[t1.x]+size1[t1.x]){
					f[val1[discover[i]]]=max(f[val1[discover[i]]],height1[discover[i]]);
				}
			}
		}
		int maskNow=val1[u];
		For(i,0,22){
			if(maskNow & (1<<i)){
				int tempMask=(maskNow^(1<<i));
				if(f[tempMask]!=-1e9){
					maxAnswer=max(maxAnswer,f[tempMask]-height1[u]);
				}
			}
			else{
				int tempMask=(maskNow^(1<<i));
				if(f[tempMask]!=-1e9){
					maxAnswer=max(maxAnswer,f[tempMask]-height1[u]);
				}
			}
		}
		if(f[maskNow]!=-1e9){
			maxAnswer=max(maxAnswer,f[maskNow]-height1[u]);
		}
		f[maskNow]=max(f[maskNow],height1[u]);
		if(!keep){
			For(i,start1[u],start1[u]+size1[u]){
				f[val1[discover[i]]]=-1e9;
			}
		}
		answer1[u]=maxAnswer;
	}
	else{
		f[val1[u]]=max(f[val1[u]],height1[u]);
		if(!keep){
			For(i,start1[u],start1[u]+size1[u]){
				f[val1[discover[i]]]=-1e9;
			}
		}
	}
	// Error3(u,answer1[u],(int)mp1[u].size());
	// rep(mask,mp1[u]){
	// 	Error(mask.x,mask.y);
	// }
}

void DFS2(int u,int p){
	rep(t1,Adj[u]){
		if(t1.x!=p){
			DFS2(t1.x,u);
			answer1[u]=max(answer1[u],answer1[t1.x]);
		}
	}
}

int main(){
	int n;
	scanf("%d",&n);

	For(i,1,n){
		int temp;
		string s;
		cin>>temp>>s;
		Adj[temp-1].pb(mp(i,s[0]-'a'));
	}

	For(i,0,(int)(1<<22)){
		f[i]=-1e9;
	}

	DFS(0,0,0);
	debug;
	DFS1(0,-1,0);
	debug;
	DFS2(0,-1);
	debug;

	For(i,0,n){
		printf("%d ",answer1[i]);
	}
	printf("\n");
return 0;}
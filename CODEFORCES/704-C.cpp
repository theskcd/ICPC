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

vi vertexClause[200010];
vector<pii> clauseClause[200010];
vi clause[200010];
bool visited[200010];
vector<pair<ll,ll> > numWays;
vector<pii> group;
bool marked[200010];
ll answer1=1LL;
set<pii> s1;

void DFS(int clauseId,int prev=-1){
	// Error(clauseId,prev);
	group.pb(mp(clauseId,prev));
	error(group.size());
	visited[clauseId]=true;

	rep(t1,clauseClause[clauseId]){
		if(t1.x!=clauseId && !visited[t1.x]){
			DFS(t1.x,t1.y);
		}
	}
}

void iterateOverGroup(vector<vector<ll> >&dp,bool mode=0){
	int prev;
	For(i,1,group.size()-mode){
		if(i==0){
			if(clause[group[i].x].size()==1){
				dp[0][0]=1LL;dp[1][1]=1LL;
			}
			else{
				dp[1][1]=2LL;dp[0][0]=1LL;dp[1][0]=1LL;
			}
		}
		else{
			vector<vector<ll> > dp1=dp;
			dp.clear();
			dp.resize(2,vector<ll>(2,0));
			if(clause[group[i].x].size()==1){
				if(group[i].y==-1){
					dp[0][0]=dp1[1][1];dp[1][0]=dp1[0][1];
					dp[0][1]=dp1[1][0];dp[1][1]=dp1[0][0];
				}
				else if(group[i].y==1){
					dp[0][0]=dp1[0][0];dp[1][0]=dp1[1][0];
					dp[0][1]=dp1[1][1];dp[1][1]=dp1[0][1];
				}
			}
			else{
				if(group[i].y==-1){
					dp[0][0]+=(dp1[1][0]+dp1[0][1])%mod;
					dp[0][1]+=(dp1[1][0]+dp1[1][1])%mod;
					dp[1][0]+=(dp1[1][1]+dp1[0][0])%mod;
					dp[1][1]+=(dp1[0][0]+dp1[0][1])%mod;
				}
				else if(group[i].y==1){
					dp[0][0]+=(dp1[0][0]+dp1[1][1])%mod;
					dp[0][1]+=(dp1[1][0]+dp1[1][1])%mod;
					dp[1][0]+=(dp1[1][0]+dp1[0][1])%mod;
					dp[1][1]+=(dp1[0][1]+dp1[0][0])%mod;
				}
			}
			Error4(dp[0][0],dp[0][1],dp[1][0],dp[1][1]);
		}
	}
}

void findAnswer(bool mode){
	if(mode==1){
		//start with 0
		vector<vector<ll> > dp;dp.resize(2,vector<ll>(2,0));
		if(clause[group[0].x].size()==1){
			dp[0][0]=1LL;
		}
		else{
			dp[1][1]=1LL;dp[0][0]=1LL;
		}
		debug;
		iterateOverGroup(dp,1);
		vector<vector<ll> > dp1=dp;
		For(i,0,2)For(j,0,2)dp[i][j]=0;
		if(group[group.size()-1].y==-1){
			dp[0][0]=dp1[1][0];dp[1][0]=dp1[1][1];
			dp[0][0]+=dp1[0][1];dp[1][0]=+dp1[0][0];
		}
		else{
			dp[1][0]+=dp1[1][0];dp[0][0]+=dp1[1][1];
			dp[1][0]+=dp1[0][1];dp[0][0]+=dp1[0][0];
		}
		debug;
		//start with 1
		vector<vector<ll> > dp2;dp2.resize(2,vector<ll>(2,0));
		Error(group[0].x,clause[group[0].x].size());
		if(clause[group[0].x].size()==1){
			dp2[1][1]=1LL;
		}
		else{
			dp2[1][1]=1LL;dp2[1][0]=1LL;
		}
		Error4(dp2[0][0],dp2[0][1],dp2[1][0],dp2[1][1]);
		// debug;
		iterateOverGroup(dp2,1);
		Error4(dp2[0][0],dp2[0][1],dp2[1][0],dp2[1][1]);
		vector<vector<ll> > dp3=dp2;
		For(i,0,2)For(j,0,2)dp2[i][j]=0;
		if(group[group.size()-1].y==-1){
			dp2[0][1]+=dp3[1][0]+dp3[1][1];
			dp2[1][1]+=dp3[0][1]+dp3[0][0];
		}
		else{
			dp2[0][1]+=dp3[1][0]+dp3[1][1];
			dp2[1][1]+=dp3[0][1]+dp3[0][0];
		}
		Error4(dp2[0][0],dp2[0][1],dp2[1][0],dp2[1][1]);
		// debug;
		//done
		numWays.pb(mp(dp[0][0]+dp[0][1]+dp2[0][1]+dp2[0][0],
			dp[1][0]+dp[1][1]+dp2[1][0]+dp2[1][1]));
		Error(numWays[numWays.size()-1].x,numWays[numWays.size()-1].y);
	}
	else{
		vector<vector<ll> > dp;dp.clear();dp.resize(2,vector<ll>(2,0));
		int clauseIds=group[0].x;
		if(clause[group[0].x].size()==1){
			dp[0][0]=1LL;dp[1][1]=1LL;
		}
		else{
			dp[1][1]=2LL;dp[0][0]=1LL;dp[1][0]=1LL;
		}
		iterateOverGroup(dp,0);
		Error3("findAnswer",dp[0][0]+dp[0][1],dp[1][0]+dp[1][1]);
		numWays.pb(mp(dp[0][0]+dp[0][1],dp[1][1]+dp[1][0]));
	}
}

void insertToComp(int var,int id){
	if(var<0){
		vertexClause[-var].pb(-id);
		clause[id].pb(-var);
	}
	else{
		vertexClause[var].pb(id);
		clause[id].pb(var);
	}
}

void findWays(){
	error(answer1);
	vector<ll> dp={1,1};
	error(numWays.size());
	dp[0]=numWays[0].x;dp[1]=numWays[0].y;
	For(i,1,numWays.size()){
		vector<ll> dp1=dp;dp.clear();
		dp.resize(2,0);assert(dp[0]==0 && dp[1]==0);
		Error4(dp1[0],dp1[1],numWays[i].x,numWays[i].y);
		dp[0]=((dp1[1]*numWays[i].y)%mod+(dp1[0]*numWays[i].x)%mod)%mod;
		dp[1]=((dp1[0]*numWays[i].y)%mod+(dp1[1]*numWays[i].x)%mod)%mod;
		Error(dp[0],dp[1]);
	}
	Error(answer1,dp[1]);
	answer1=(answer1*dp[1])%mod;
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	vector<pii> v1;
	For(i,0,n){
		int k1;scanf("%d",&k1);
		if(k1==1){
			int t1;scanf("%d",&t1);
			s1.insert(mp(t1,t1));
			v1.pb(mp(t1,t1));
		}
		else{
			int t1,t2;scanf("%d%d",&t1,&t2);
			int min1=min(t1,t2);int max1=max(t1,t2);
			s1.insert(mp(min1,max1));
			if(min1==max1){
				numWays.pb(mp(1,1));
				marked[max1]=true;
			}
			else if(min1==-max1){
				numWays.pb(mp(0,2));
				marked[max1]=true;
			}
			else{
				v1.pb(mp(min1,max1));
			}
		}
	}
	// n=(int)s1.size();
	n=v1.size();
	int counter1=1;
	rep(t1,v1){
		if(t1.x==t1.y){
			numWays.pb(mp(1,1));
			// insertToComp(t1.x,counter1);
		}
		else if(t1.x==-t1.y){
			numWays.pb(mp(0,2));
		}
		else{
			insertToComp(t1.x,counter1);insertToComp(t1.y,counter1);
		}
		// Error3(counter1,t1.x,t1.y);
		counter1++;
	}
	error(n);
	// For(i,0,n){
	// 	int k1;
	// 	scanf("%d",&k1);
	// 	if(k1==1){
	// 		int t1;
	// 		scanf("%d",&t1);
	// 		if(s1.find(mp(t1,t1))==s1.end()){
	// 			numWays.pb(mp(1,1));
	// 		}
	// 	}
	// 	else{
	// 		int t1,t2;
	// 		scanf("%d%d",&t1,&t2);
	// 		clause[i]={t1,t2};
	// 		int min1=min(t1,t2);int max1=max(t1,t2);
	// 		if(s1.find(mp(t1,t2))==s1.end()){
	// 			insertToComp(t1,i);insertToComp(t2,i);
	// 		}
	// 	}
	// }

	For(i,1,m+1){
		if(vertexClause[i].size()==0 && !marked[i]){
			answer1=(answer1*2LL)%mod;
		}
		else if(vertexClause[i].size()==1){
			continue;
		}
		else if(vertexClause[i].size()==2){
			int count1=0;
			count1+=(vertexClause[i][0]>0)?1:0;
			count1+=(vertexClause[i][1]>0)?1:0;
			int ver1=abs(vertexClause[i][0]);
			int ver2=abs(vertexClause[i][1]);
			Error4(i,ver1,ver2,count1);
			Error(vertexClause[i][0],vertexClause[i][1]);
			if(count1==2 || count1==0){
				clauseClause[ver1].pb(mp(ver2,1));
				clauseClause[ver2].pb(mp(ver1,1));
			}
			else{
				clauseClause[ver1].pb(mp(ver2,-1));
				clauseClause[ver2].pb(mp(ver1,-1));
			}
		}
	}

	For(i,1,n+1){
		if(clauseClause[i].size()==0 && !visited[i]){
			visited[i]=true;
			Error("emptyVal",i);
			numWays.pb(mp(1,1));
		}
		else if(clauseClause[i].size()==1 && !visited[i]){
			group.clear();
			Error("DFS1",i);
			DFS(i);findAnswer(0);
			rep(t1,group){
				printf("(%d,%d) ",t1.x,t1.y);
			}
			printf("\n");
			Error("size1",numWays.size());
			// error(group.size());
		}
	}

	error(numWays.size());

	For(i,1,n+1){
		if(!visited[i]){
			group.clear();
			Error("DFS2",i);
			DFS(i);
			// Error("done",group.size());
			// rep(t1,group){
			// 	printf("%d %d\n",t1.x,t1.y);
			// 	printf("(%d,%d) ",t1.x,t1.y);
			// }
			// debug;
			findAnswer(1);
			// printf("\n");
			Error("size1",numWays.size());
			// error(group.size());
		}
	}

	error(numWays.size());

	findWays();
	printf("%lld\n",answer1);
return 0;}
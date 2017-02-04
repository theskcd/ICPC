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
typedef unsigned long long ull;
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);
const long double eps=1e-6;
ull getRand(){return ((ull)rand()<<40)+((ull)rand()<<20)+((ull)rand());}

struct change{
	int x1;
	int y1;
	int cx1;
	int cy1;
	change(int _x1,int _y1,int _cx1,int _cy1){
		x1=_x1;y1=_y1;cx1=_cx1;cy1=_cy1;
	}
};

struct node2{
	int delGroup;
	vector<change> changes;
	vi eventsH;
};

node2 tree[1200040];
map<pii,int> mp1;
unordered_map<int,pii> mp2;
vector<pair<pii,int> > events;
int startTime[300010];
int endTime[300010];
int timer=0;
int groups;
int answer1[300010];
int parent1[300010];
bool hasEnded[300010];
bool hasQuestion[300010];
int child1[300010];

int parent(int u){
	while(parent1[u]!=u){
		u=parent1[u];
	}
	return u;
}

void makeChanges(int node){
	rep(index1,tree[node].eventsH){
		pii t1=mp2[index1];
		int x1=parent(t1.x);
		int y1=parent(t1.y);
		if(x1!=y1){
			if(child1[x1]>child1[y1]){
				change c1={parent1[x1],parent1[y1],child1[x1],child1[y1]};
				tree[node].changes.pb(c1);
				child1[x1]+=child1[y1];
				parent1[y1]=parent1[x1];
			}
			else{
				change c1={parent1[y1],parent1[x1],child1[y1],child1[x1]};
				tree[node].changes.pb(c1);
				child1[y1]+=child1[x1];
				parent1[x1]=parent1[y1];
			}
			groups--;
		}
	}
	tree[node].delGroup=groups;
}

void revertBack(int node){
	reverse(all(tree[node].changes));
	rep(change,tree[node].changes){
		int x1=change.x1;
		int y1=change.y1;
		int cx1=change.cx1;
		int cy1=change.cy1;
		parent1[x1]=x1;
		parent1[y1]=y1;
		child1[x1]=cx1;
		child1[y1]=cy1;
		groups++;
	}
}

void update(int node,int b,int e,int i,int j,int index1){
	if(b>e || i>e || j<b){
		return ;
	}
	else if(i<=b && e<=j){
		tree[node].eventsH.pb(index1);
		return ;
	}
	else{
		update(2*node,b,(b+e)/2,i,j,index1);
		update(2*node+1,(b+e)/2+1,e,i,j,index1);
	}
}

void DFS(int node,int b,int e){
	if(b>e){
		return ;
	}
	else if(b==e){
		makeChanges(node);
		answer1[b]=groups;
		revertBack(node);
	}
	else{
		makeChanges(node);
		DFS(2*node,b,(b+e)/2);
		DFS(2*node+1,(b+e)/2+1,e);
		revertBack(node);
	}
}

int main(){
	freopen("connect.in","r",stdin);
	freopen("connect.out","w",stdout);
	int n,k;
	scanf("%d%d",&n,&k);
	groups=n;
	For(i,0,n+1){
		parent1[i]=i;
		child1[i]=1;
	}
	int counter1=0;

	For(i,0,k){
		char s[2];
		int u1,v1;
		scanf("%s",s);getchar();
		if(s[0]=='?'){
			hasQuestion[i]=true;
		}
		else if(s[0]=='+'){
			scanf("%d%d",&u1,&v1);
			int u22=u1;int v22=v1;
			u1=min(u22,v22);v1=max(u22,v22);
			mp1[mp(u1,v1)]=++counter1;
			mp2[mp1[mp(u1,v1)]]=mp(u1,v1);
			startTime[mp1[mp(u1,v1)]]=i;
		}
		else if(s[0]=='-'){
			scanf("%d%d",&u1,&v1);
			int u22=u1;int v22=v1;
			u1=min(u22,v22);v1=max(u22,v22);
			int eventNum=mp1[mp(u1,v1)];
			if(startTime[eventNum]!=i){
				events.pb(mp(mp(startTime[eventNum],i),eventNum));
			}
			hasEnded[eventNum]=true;
		}
	}

	rep(t1,mp1){
		if(!hasEnded[t1.y]){
			events.pb(mp(mp(startTime[t1.y],k),t1.y));
		}
	}

	rep(eventNow,events){
		// Error3(eventNow.x.x,eventNow.x.y,eventNow.y);
		update(1,0,k,eventNow.x.x,eventNow.x.y,eventNow.y);
	}

	DFS(1,0,k);

	For(i,0,k+1){
		if(hasQuestion[i]){
			printf("%d\n",answer1[i]);
		}
	}
return 0;}
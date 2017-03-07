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
#define MAX 810
// #define N 100010
const string debug_line="yolo";
#define debug error(debug_line)
#define read() freopen("mergedoutput.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
//template <typename T> using os =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef unsigned long long ull;
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);
const long double eps=1e-6;
ull getRand(){return ((ull)rand()<<40)+((ull)rand()<<20)+((ull)rand());}

int parent1[100010];
int child1[100010];
vector<pii> Adj[100010];
vector<pair<pair<pii,int>,int> > e;
ll val1[100010];
vi indices;
ll max1;
bool visited[100010];
int size1[100010];
ll totalSize;

int parent(int index1){
    while(parent1[index1]!=index1){
        index1=parent1[index1];
    }
    return index1;
}

void DFS(int u,int p){
    visited[u]=true;
    size1[u]=child1[u];
    rep(t1,Adj[u]){
        if(!visited[t1.x] && t1.x!=p){
            DFS(t1.x,u);
            size1[u]+=size1[t1.x];
        }
    }
}

void DFS1(int u,int p){
    rep(t1,Adj[u]){
        if(t1.x!=p){
            ll valNow=(ll)size1[t1.x]*(totalSize-size1[t1.x]);
            // Error(valNow,t1.y);
            if(valNow>max1){
                max1=valNow;indices.clear();indices.pb(t1.y);
            }
            else if(valNow==max1){
                indices.pb(t1.y);
            }
            DFS1(t1.x,u);
        }
    }
}

void union1(int x1,int y1){
    if(child1[x1]>child1[y1]){
        child1[x1]+=child1[y1];parent1[y1]=parent1[x1];
    }
    else{
        child1[y1]+=child1[x1];parent1[x1]=parent1[y1];
    }
}

void resolve(vi& edgeIndex){
    set<int> s1;
    rep(index1,edgeIndex){
        int x1=e[index1].x.y;
        int y1=e[index1].y;
        x1=parent(x1);y1=parent(y1);
        Adj[x1].pb(mp(y1,e[index1].x.x.y));
        Adj[y1].pb(mp(x1,e[index1].x.x.y));
        // Error3(x1,y1,e[index1].x.x.y);
        s1.insert(x1);
        s1.insert(y1);
    }
    rep(t1,s1){
        if(!visited[t1]){
            DFS(t1,-1);
            totalSize=size1[t1];
            DFS1(t1,-1);
        }
    }
    rep(index1,edgeIndex){
        int x1=e[index1].x.y;
        int y1=e[index1].y;
        x1=parent(x1);y1=parent(y1);
        union1(x1,y1);
    }
    rep(t1,s1){
        Adj[t1].clear();
        visited[t1]=false;
        size1[t1]=0;
    }
}

int main(){
    int n;
    scanf("%d",&n);
    For(i,1,n){
        int a1,b1,t1;
        scanf("%d%d%d",&a1,&b1,&t1);
        e.pb(mp(mp(mp(t1,i),a1),b1));
    }
    For(i,1,n+1){
        parent1[i]=i;child1[i]=1;
    }
    sort(all(e));
    int currentPoint=0;
    while(currentPoint<e.size()){
        int index1=currentPoint;
        vi edgeIndex;
        while(index1<e.size() && e[index1].x.x.x==e[currentPoint].x.x.x){
            edgeIndex.pb(index1);
            index1++;
        }
        currentPoint=index1;
        resolve(edgeIndex);
    }
    sort(all(indices));
    printf("%lld %d\n",2*max1,(int)indices.size());
    rep(t1,indices){
        printf("%d ",t1);
    }
    printf("\n");
return 0;}
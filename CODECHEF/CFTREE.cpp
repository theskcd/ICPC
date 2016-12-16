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
#define LIMIT 1000000000000000000LL
#define MAX1 1000000000
const int inf=0x3f3f3f3f;
const long double pi=acos(-1.0);
#define MAXN 123456
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

typedef struct node2{
    ll val1;
    ll val0;
    ll lazyp1;
    ll lazyp0;
}node1;

node1 tree[4*MAXN];
ll fib[3*MAXN];
int begin1[MAXN];
int size1[MAXN];
int discover[MAXN];
bool visited[MAXN];
int dfs_timer=0;
int offset=100005;
vi Adj[MAXN];
vector<vector<ll> > baseCase;
int level1[MAXN];

void calc(){
    level1[0]=-1;
    baseCase.resize(2,vector<ll>(2,0));
    baseCase[0][0]=baseCase[0][1]=baseCase[1][0]=1LL;
    fib[offset]=0;
    fib[offset+1]=1;
    For(i,2,MAXN){
        fib[offset+i]=(fib[offset+i-1]+fib[offset+i-2])%mod;
    }
    rof(i,offset-1,-1){
        fib[i]=((fib[i+2]-fib[i+1])%mod+mod)%mod;
    }
    // Error(fib[offset-6],fib[+5]);
}

void DFS(int u,int p){
    visited[u]=true;
    begin1[u]=dfs_timer;
    dfs_timer++;
    size1[u]++;
    level1[u]=level1[p]+1;
    rep(t1,Adj[u]){
        if(!visited[t1]){
            DFS(t1,u);
            size1[u]+=size1[t1];
        }
    }
    // Error4(u,begin1[u],begin1[u]+size1[u]-1,level1[u]);
}

void putZeros(int node){
    tree[node].val0=tree[node].val1=tree[node].lazyp0=tree[node].lazyp1=0;
}

void initialise(int node,int b,int e){
    if(b>e){
        return ;
    }
    else if(b==e){
        putZeros(node);
    }
    else{
        initialise(2*node,b,(b+e)/2);
        initialise(2*node+1,(b+e)/2+1,e);
        putZeros(node);
    }
}

void pushValues(int node,ll val1,ll val0){
    tree[node].lazyp1=((tree[node].lazyp1+val1)%mod+mod)%mod;
    tree[node].lazyp0=((tree[node].lazyp0+val0)%mod+mod)%mod;
}

void update(int node,int b,int e,int i,int j,int level1){
    if(tree[node].lazyp1!=0 || tree[node].lazyp0!=0){
        if(b!=e){
            pushValues(2*node,tree[node].lazyp1,tree[node].lazyp0);
            pushValues(2*node+1,tree[node].lazyp1,tree[node].lazyp0);
        }
        tree[node].val1=((tree[node].val1+tree[node].lazyp1)%mod+mod)%mod;
        tree[node].val0=((tree[node].val0+tree[node].lazyp0)%mod+mod)%mod;
        tree[node].lazyp0=tree[node].lazyp1=0;
    }
    if(b>e || i>e || j<b){
        return ;
    }
    else if(i<=b && e<=j){
        // Error3("update",fib[offset+level1],fib[offset+level1-1]);
        tree[node].val1=((tree[node].val1+fib[offset+level1])%mod+mod)%mod;
        tree[node].val0=((tree[node].val0+fib[offset+level1-1])%mod+mod)%mod;
        if(b!=e){
            pushValues(2*node,fib[offset+level1],fib[offset+level1-1]);
            pushValues(2*node+1,fib[offset+level1],fib[offset+level1-1]);
        }
    }
    else{
        update(2*node,b,(b+e)/2,i,j,level1);
        update(2*node+1,(b+e)/2+1,e,i,j,level1);
    }
}

void query(node1 &res,int node,int b,int e,int index){
    if(tree[node].lazyp0!=0 || tree[node].lazyp1!=0){
        if(b!=e){
            pushValues(2*node,tree[node].lazyp1,tree[node].lazyp0);
            pushValues(2*node+1,tree[node].lazyp1,tree[node].lazyp0);
        }
        tree[node].val1=((tree[node].val1+tree[node].lazyp1)%mod+mod)%mod;
        tree[node].val0=((tree[node].val0+tree[node].lazyp0)%mod+mod)%mod;
        tree[node].lazyp0=tree[node].lazyp1=0;
    }
    if(b>e){
        return ;
    }
    else if(b==e && e==index){
        // Error(tree[node].val0,tree[node].val1);
        res=tree[node];
        return ;
    }
    else{
        if(index<=(b+e)/2){
            query(res,2*node,b,(b+e)/2,index);
        }
        else{
            query(res,2*node+1,(b+e)/2+1,e,index);
        }
    }
}

void multiply(vector<vector<ll> > &res,vector<vector<ll> > a,vector<vector<ll> > b){
    res.resize(2,vector<ll>(2,0));
    For(i,0,2){
        For(j,0,2){
            ll sum1=0;
            For(k,0,2){
                sum1=(sum1+a[i][k]*b[k][j])%mod;
            }
            res[i][j]=sum1;
        }
    }
    return ;
}

void power(vector<vector<ll> > &mat,int e){
    if(e==1){
        mat.resize(2,vector<ll>(2,0));
        mat=baseCase;
        return ;
    }
    else{
        power(mat,e/2);
        if(e%2==0){
            vector<vector<ll> > res;
            multiply(res,mat,mat);
            mat=res;
            return ;
        }
        else{
            vector<vector<ll> > res;
            multiply(res,mat,mat);
            vector<vector<ll> > res1;
            res1=res;
            multiply(res,res1,baseCase);
            mat=res;
            return ;
        }
    }
}

ll getFib(int e,ll f1,ll f0){
    if(e==0){
        return f1;
    }
    else{
        vector<vector<ll> > mat;
        power(mat,e);
        assert(mat.size()==2 && mat[0].size()==2 && mat[1].size()==2);
        ll answer1=(mat[0][0]*f1+mat[0][1]*f0)%mod;
        return answer1;
    }
}

int main(){
    calc();
    int n,m,k;
    scanf("%d%d",&n,&m);
    For(i,2,n+1){
        int temp;
        scanf("%d",&temp);
        Adj[temp].pb(i);
        Adj[i].pb(temp);
        // Error(i,temp);
    }
    initialise(1,0,n-1);
    DFS(1,0);
    while(m--){
        string query1;
        cin>>query1;
        if(query1[0]=='U'){
            int x1,k1;
            scanf("%d%d",&x1,&k1);
            pii range1={begin1[x1],begin1[x1]+size1[x1]-1};
            update(1,0,n-1,range1.x,range1.y,k1-level1[x1]);
        }
        else{
            int x1;
            scanf("%d",&x1);
            node1 res;
            res.val0=res.val1=0;
            query(res,1,0,n-1,begin1[x1]);
            ll answer1=getFib(level1[x1],res.val1,res.val0);
            printf("%lld\n",answer1);
        }
    }
return 0;}
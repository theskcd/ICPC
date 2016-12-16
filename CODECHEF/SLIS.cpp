#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
#include <time.h>

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
    int maxn;
    ll sum0;
    ll sum1;
}node1;

node1 tree[4*MAXN];

node1 merge(const node1 &a,const node1 &b){
    node1 res;
    res.maxn=max(a.maxn,b.maxn);
    res.sum0=res.sum1=0;
    if(a.maxn==res.maxn){
        res.sum0=(res.sum0+a.sum0)%mod;
        res.sum1=(res.sum1+a.sum1)%mod;
    }
    else if(a.maxn==res.maxn-1){
        res.sum0=(res.sum0+a.sum1)%mod;
    }
    if(b.maxn==res.maxn){
        res.sum0=(res.sum0+b.sum0)%mod;
        res.sum1=(res.sum1+b.sum1)%mod;
    }
    else if(b.maxn==res.maxn-1){
        res.sum0=(res.sum0+b.sum1)%mod;
    }
    return res;
}

void initialise(int node,int b,int e){
    if(b>e){
        return ;
    }
    else if(b==e){
        tree[node].maxn=tree[node].sum0=tree[node].sum1=0;
        return ;
    }
    else{
        initialise(2*node,b,(b+e)/2);
        initialise(2*node+1,(b+e)/2+1,e);
        tree[node].maxn=tree[node].sum0=tree[node].sum1=0;
        return ;
    }
}

void update(int node,int b,int e,int index,node1 &val){
    if(b>e){
        return ;
    }
    else if(b==e && e==index){
        tree[node]=merge(tree[node],val);
        return ;
    }
    else{
        if(index<=(b+e)/2){
            update(2*node,b,(b+e)/2,index,val);
        }
        else{
            update(2*node+1,(b+e)/2+1,e,index,val);
        }
        tree[node]=merge(tree[2*node],tree[2*node+1]);
        return ;
    }
}

void query(node1 &res,int node,int b,int e,int i,int j){
    if(b>e || i>e || j<b){
        return ;
    }
    else if(i<=b && e<=j){
        res=tree[node];
        return ;
    }
    else{
        node1 l,r;
        l.sum1=l.sum0=l.maxn=r.sum0=r.sum1=r.maxn=0;
        query(l,2*node,b,(b+e)/2,i,j);
        query(r,2*node+1,(b+e)/2+1,e,i,j);
        res=merge(l,r);
        return ;
    }
}

void solve(){
    int n;
    scanf("%d",&n);
    set<int> s1;
    map<int,int> mp1;
    vi values;
    For(i,0,n){
        int temp;
        scanf("%d",&temp);
        values.pb(temp);
        s1.insert(temp);
    }
    int counter1=1;
    rep(t1,s1){
        mp1[t1]=counter1++;
    }
    node1 temp;
    temp.maxn=0;
    temp.sum1=1;
    temp.sum0=0;
    initialise(1,0,(int)s1.size());
    update(1,0,(int)s1.size(),0,temp);
    For(i,0,n){
        node1 res;
        res.maxn=res.sum0=res.sum1=0;
        // Error3(i,0,mp1[values[i]]-1);
        query(res,1,0,(int)s1.size(),0,mp1[values[i]]-1);
        res.maxn++;
        update(1,0,(int)s1.size(),mp1[values[i]],res);
    }
    printf("%lld\n",tree[1].sum0);
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
return 0;}
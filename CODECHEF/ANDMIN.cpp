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
#define MAXN 150010
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
    int maxVal;
    int mask1;
}node1;

node1 tree[4*MAXN];
int completeMask;
int a[MAXN];

void initialise(int node,int b,int e){
    if(b>e){
        return ;
    }
    else if(b==e){
        tree[node].maxVal=a[b];
        tree[node].mask1=0;
        return ;
    }
    else{
        initialise(2*node,b,(b+e)/2);
        initialise(2*node+1,(b+e)/2+1,e);
        tree[node].maxVal=min(tree[2*node].maxVal,tree[2*node+1].maxVal);
        return ;
    }
}

void fill(vector<bool> &mask1,int val1){
    For(i,0,32){
        if(val1 & (1<<i)){
            mask1.pb(1);
        }
        else{
            mask1.pb(0);
        }
    }
}

bool isNeed(int val1,int val2){
    // Error(val1,val2);
    vector<bool> mask1;
    vector<bool> mask2;
    fill(mask1,val1);
    fill(mask2,val2);
    // Error(mask1.size(),mask2.size());
    For(i,0,32){
        if(mask2[i]==1 && mask1[i]==0){
            return true;
        }
    }
    return false;
}

void update(int node,int b,int e,int i,int j,int val1){
    // Error5(b,e,i,j,val1);
    if(b>e || i>e || j<b){
        return ;
    }
    else if(i<=b && e<=j && b!=e){
        if(isNeed(tree[node].mask1,(completeMask ^ val1))){
            update(2*node,b,(b+e)/2,i,j,val1);
            update(2*node+1,(b+e)/2+1,e,i,j,val1);
            tree[node].maxVal=min(tree[2*node].maxVal,tree[2*node+1].maxVal);
            tree[node].mask1=tree[2*node].mask1 & tree[2*node+1].mask1;
        }
    }
    else if(b==e){
        tree[node].maxVal=tree[node].maxVal & val1;
        tree[node].mask1=(tree[node].mask1 | (completeMask ^ val1));
    }
    else{
        update(2*node,b,(b+e)/2,i,j,val1);
        update(2*node+1,(b+e)/2+1,e,i,j,val1);
        tree[node].maxVal=min(tree[2*node].maxVal,tree[2*node+1].maxVal);
        tree[node].mask1=tree[2*node].mask1 & tree[2*node+1].mask1;
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
        l.maxVal=INT_MAX;
        r.maxVal=INT_MAX;
        query(l,2*node,b,(b+e)/2,i,j);
        query(r,2*node+1,(b+e)/2+1,e,i,j);
        res.maxVal=min(l.maxVal,r.maxVal);
        return ;
    }
}

int main(){
    completeMask=INT_MAX;
    int n,q;
    scanf("%d%d",&n,&q);

    For(i,1,n+1){
        int temp;
        scanf("%d",&temp);
        a[i]=temp;
    }

    initialise(1,1,n);

    while(q--){
        int type;
        scanf("%d",&type);
        if(type==0){
            int l1,r1;
            scanf("%d%d",&l1,&r1);
            node1 res;
            res.maxVal=INT_MAX;
            query(res,1,1,n,l1,r1);
            printf("%d\n",res.maxVal);
        }
        else{
            int l1,r1,x1;
            scanf("%d%d%d",&l1,&r1,&x1);
            update(1,1,n,l1,r1,x1);
        }
    }
return 0;}
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

int parent1[MAXN];
int child1[MAXN];
ll total1=0;
ll total2=0;
ll total3=0;
ll currCost;
vector<pair<ll,pii> > edges;

int parent(int index1){
    while(index1!=parent1[index1]){
        index1=parent1[index1];
    }
    return index1;
}

void merge(int x1,int y1){
    x1=parent(x1);
    y1=parent(y1);
    total1=total1+currCost*(ll)child1[x1]*(ll)child1[y1];
    total2=total2+(ll)child1[x1]*(ll)child1[y1];
    total3=total3+currCost;
    if(child1[x1]<child1[y1]){
        child1[y1]+=child1[x1];
        parent1[x1]=parent1[y1];
    }
    else{
        child1[x1]+=child1[y1];
        parent1[y1]=parent1[x1];
    }
    return ;
}

int main(){
    int n;
    scanf("%d",&n);

    For(i,1,n){
        int a1,b1,c1;
        scanf("%d%d%d",&a1,&b1,&c1);
        edges.pb(mp(c1,mp(a1,b1)));
    }

    For(i,1,n+1){
        parent1[i]=i;
        child1[i]=1;
    }

    sort(all(edges));
    rep(edge,edges){
        currCost=edge.x;
        merge(edge.y.x,edge.y.y);
    }
    // Error3(total3,total2,total1);
    double answer1=total3-(double)(total1)/(double)total2;
    printf("%.6lf\n",answer1);
return 0;}
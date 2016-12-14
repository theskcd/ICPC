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

vector<pair<ll,ll> > scores;
ll p[MAXN];
ll t[MAXN];
int n;

bool poss(double mid){
    sort(all(scores),[](const pii &a,const pii &b){
        return (ll)a.x*(ll)b.y>(ll)a.y*(ll)b.x;
    });
    ll sum1=0;
    ll totalTime=0;
    
    For(i,0,scores.size()){
        totalTime+=scores[i].y;
    }
    vector<pair<int,pair<double,double> > > points;

    for(int i=0;i<scores.size();){
        int j=i;
        while(j<scores.size() && scores[i].x*scores[j].y==scores[i].y*scores[j].x){
            j++;
        }
        double timeNow=0;
        For(k,i,j){
            timeNow+=scores[k].y;
        }
        For(k,i,j){
            double max1=(double)scores[k].x*(double)(1-mid*(double)(sum1+scores[k].y)/(double)totalTime);
            double max2=(double)scores[k].x*(double)(1-mid*(double)(sum1+timeNow)/(double)totalTime);
            points.pb(mp(scores[k].x,mp(max2,max1)));
        }
        // Error(i,j);
        i=j;
        sum1+=timeNow;
    }

    // debug;

    sort(all(points));
    double max1=-1;
    bool poss=true;
    for(int i=0;i<n;){
        int j=i;
        while(j<n && points[i].x==points[j].x){
            j++;
        }
        For(k,i,j){
            if(max1>points[k].y.x){
                poss=false;
            }
        }
        For(k,i,j){
            max1=max(max1,points[k].y.y);
        }
        i=j;
    }

    return poss;
}

int main(){
    scanf("%d",&n);

    For(i,0,n){
        int temp1;
        scanf("%d",&temp1);
        p[i]=temp1;
    }

    For(i,0,n){
        int temp1;
        scanf("%d",&temp1);
        t[i]=temp1;
    }

    For(i,0,n){
        scores.pb(mp(p[i],t[i]));
    }

    double l1=0;
    double h1=1;
    For(times,0,101){
        double mid1=(l1+h1)/2;
        // Error(l1,h1);
        if(poss(mid1)){
            l1=mid1;
        }
        else{
            h1=mid1;
        }
    }
    printf("%.6lf\n",l1);
return 0;}
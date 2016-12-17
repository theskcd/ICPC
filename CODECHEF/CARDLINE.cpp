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

int dp[2010][2010];
vi Adj[2010];
bool visited[2010];
vi cycleLength;
int a1[2010];
int b1[2010];
int posB[2010];
bool inStack[2010];

void calc(){
    For(i,2,2010){
        For(j,1,i+1){
            if(i-j-1>=0){
                dp[i][j]=max(dp[i][j],j+dp[i-j-1][j]);
            }
            if(i-j-2>=0){
                dp[i][j]=max(dp[i][j],j+1+dp[i-j-2][j]);
            }
        }
    }
}

void solve(){
    int n;
    scanf("%d",&n);
    For(i,0,n+1){
        visited[i]=false;
    }
    cycleLength.clear();
    For(i,1,n+1){
        int temp1;
        scanf("%d",&temp1);
        a1[i]=temp1;
    }

    For(i,1,n+1){
        int temp1;
        scanf("%d",&temp1);
        b1[i]=temp1;
        posB[temp1]=i;
    }

    int answer1=0;

    For(i,1,n+1){
        if(!visited[i]){
            int size1=0;
            int currNum=i;
            int curA=a1[i];
            while(1){
                if(visited[currNum]){
                    break;
                }
                visited[currNum]=true;
                size1++;
                currNum=posB[curA];
                curA=a1[currNum];
            }
            cycleLength.pb(size1);
            if(size1==1){
                answer1++;
            }
            // error(size1);
        }
    }

    For(i,1,n+1){
        int tempAnswer=0;
        rep(t1,cycleLength){
            tempAnswer+=dp[t1][i];
        }
        answer1=max(answer1,tempAnswer);
    }
    printf("%d\n",answer1);
}

int main(){
    calc();
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
}
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
const int BASE1=31;
const int BASE2=37;

ll f[MAXN];
ll pow1[MAXN];
ll pow2[MAXN];
ll invpow1[MAXN];
ll invpow2[MAXN];
ll hash1[MAXN];
ll hash2[MAXN];
ll revHash1[MAXN];
ll revHash2[MAXN];
char s[MAXN];
int n;

ll power(ll b,ll e){
    if(e==0){
        return 1LL;
    }
    else if(e==1){
        return b%mod;
    }
    else{
        ll p=power(b,e/2);
        if(e%2==0){
            return (p*p)%mod;
        }
        else{
            p=(p*p)%mod;
            p=(p*b)%mod;
            return p;
        }
    }
}

void calc(){
    f[1]=1;
    For(i,2,MAXN){
        f[i]=(f[i-2]+(ll)i);
    }
    pow1[0]=pow2[0]=1LL;
    pow1[1]=BASE1;
    pow2[1]=BASE2;
    For(i,2,MAXN){
        pow1[i]=(pow1[i-1]*BASE1)%mod;
        pow2[i]=(pow2[i-1]*BASE2)%mod;
    }
    invpow1[MAXN-1]=power(pow1[MAXN-1],mod-2);
    invpow2[MAXN-1]=power(pow2[MAXN-1],mod-2);
    rof(i,MAXN-2,-1){
        invpow1[i]=(invpow1[i+1]*BASE1)%mod;
        invpow2[i]=(invpow2[i+1]*BASE2)%mod;
    }
}

void prep(){
    int l1=strlen(s);
    For(i,0,l1){
        if(i==0){
            hash1[i]=pow1[i]*(s[i]-'a');
            hash2[i]=pow2[i]*(s[i]-'a');
        }
        else{
            hash1[i]=(hash1[i-1]+pow1[i]*(s[i]-'a'))%mod;
            hash2[i]=(hash2[i-1]+pow2[i]*(s[i]-'a'))%mod;
        }
    }
    rof(i,l1-1,-1){
        if(i==l1-1){
            revHash1[i]=pow1[l1-1-i]*(s[i]-'a');
            revHash2[i]=pow2[l1-1-i]*(s[i]-'a');
        }
        else{
            revHash1[i]=(revHash1[i+1]+pow1[l1-1-i]*(s[i]-'a'))%mod;
            revHash2[i]=(revHash2[i+1]+pow2[l1-1-i]*(s[i]-'a'))%mod;
        }
    }
}

pair<ll,ll> getHash(int l1,int r1){
    ll val1=((hash1[r1]-hash1[l1]+(s[l1]-'a')*pow1[l1])%mod+mod)%mod;
    ll val2=((hash2[r1]-hash2[l1]+(s[l1]-'a')*pow2[l1])%mod+mod)%mod;
    val1=(val1*invpow1[l1])%mod;
    val2=(val2*invpow2[l1])%mod;
    return {val1,0};
}

pair<ll,ll> getRHash(int l1,int r1){
    ll val1=((revHash1[l1]-revHash1[r1]+(s[r1]-'a')*pow1[n-1-r1])%mod+mod)%mod;
    ll val2=((revHash2[l1]-revHash2[r1]+(s[r1]-'a')*pow2[n-1-r1])%mod+mod)%mod;
    val1=(val1*invpow1[n-1-r1])%mod;
    val2=(val2*invpow2[n-1-r1])%mod;
    return {val1,0};
}

bool sameHash(int l1,int r1,int l2,int r2){
    pair<ll,ll> forH=getHash(l1,r1);
    pair<ll,ll> revH=getRHash(l2,r2);
    if(forH.x==revH.x && forH.y==revH.y){
        return true;
    }
    else{
        return false;
    }
}

ll calcForCenter(int k,int l1,int r1){
    if(k<0){
        return 0;
    }
    else{
        For(i,0,k+1){
            int left=1;
            int right=n;
            int shift=0;
            while(left<=right){
                int middle=(left+right)/2;
                if(0<=l1-middle && r1+middle<n && sameHash(l1-middle,l1-1,r1+1,r1+middle)){
                    shift=middle;
                    left=middle+1;
                }
                else{
                    right=middle-1;
                }
            }
            l1=l1-shift;
            r1=r1+shift;
            if(l1==0 || r1==n-1){
                break;
            }
            if(i<k){
                l1--;
                r1++;
            }
        }
        // Error3(l1,r1,f[r1-l1+1]);
        return f[r1-l1+1];
    }
}

void solve(){
    int k;
    scanf("%d%d",&n,&k);
    scanf("%s",s);
    prep();
    ll answer1=0;
    For(i,0,n){
        answer1=answer1+calcForCenter(k,i,i);
        if(i+1<n){
            answer1=answer1+calcForCenter(k-(s[i]!=s[i+1]),i,i+1);
        }
    }
    printf("%lld\n",answer1);
}

int main(){
    calc();
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
    cerr<<(double)clock() / CLOCKS_PER_SEC<<endl;
return 0;}
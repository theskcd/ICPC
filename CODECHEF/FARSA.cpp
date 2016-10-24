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
//#define si(n) scanf("%d",&n)
//#define sii(n,m) scanf("%d%d",&n,&m)
//#define pi(n) printf("%d\n",n)
const int inf=0x3f3f3f3f;
const long double pi=acos(-1.0);
#define MAX 50010
// #define N 100000
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

ll a[200200];
unordered_map<ll,int> mp1;

void fft(vector <complex_t>& a, int s = 1) {
    int n = (int)a. size();
 
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1 ;
        for (; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if (i < j)
            swap (a[i], a[j]);
    }
 
    for (int len = 2; len <= n; len <<= 1) {
        long double ang = 2 * s * PI / len;
        complex_t wlen(cos(ang), sin(ang));
        for (int i = 0 ; i < n ; i += len) {
            complex_t w(1);
            for (int j = 0 ; j < len / 2 ; ++ j) {
                complex_t u = a[i + j] ,  v = a[i + j + len / 2] * w ;
                a[i + j] = u + v ;
                a[i + j + len / 2] = u - v ;
                w *= wlen ;
            }
        }
    }
    if (s == -1)
        for (int i = 0; i < n; ++i)
            a[i] /= n;
}
 
const int N = 200200;
const int MOD = 104857601;
 
typedef long long ll;
// change ll to complex_t if needed
vi multiply (const vi& a, const vi& b) {
    vector <complex_t> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < max(a.size(), b.size()))
        n <<= 1;
    n <<= 1;
    fa.resize(n), fb.resize(n);
 
    fft(fa), fft(fb);
 
    for (int i = 0; i < n; ++i)
        fa[i] *= fb[i];
 
    fft (fa, -1);
 
    vi res(n);
    for (size_t i = 0; i < n; ++i)
        res[i] = llround(fa[i].real()) % MOD;
    // while (res.back() == 0) res.pop_back();
    return res;
}

int main(){
	int n;
	scanf("%d",&n);
	For(i,0,n){
		ll temp;
		scanf("%lld",&temp);
		a[i]=temp;
	}

	if(n<=2000){
		For(i,0,n){
			ll temp1=0;
			For(j,i,n){
				temp1=temp1+a[j];
				mp1[temp1]=1;
			}
		}
		printf("%d\n",(int)mp1.size()-1);
	}
	else{
		int sum1=0;
		For(i,0,n){
			sum1=sum1+a[i];
		}
		vi expres1(sum1+1,0);
		vi expres2(sum1+1,0);
		sum1=0;
		expres1[0]=1;
		For(i,0,n){
			expres1[sum1+a[i]]=1;
			sum1+=a[i];
		}
		For(i,0,n){
			expres2[sum1]=1;
			sum1-=a[i];
		}
		expres2[0]=1;
		vi res=multiply(expres1,expres2);
		// rep(t1,expres1){
		// 	printf("( %d )",t1);
		// }
		// printf("\n");
		// rep(t1,expres2){
		// 	printf("( %d )",t1);
		// }
		// printf("\n");
		int count1=0;
		For(i,0,n){
			sum1=sum1+a[i];
		}
		For(i,sum1+1,res.size()){
			if(res[i]>0){
				count1++;
			}
		}
		// rep(t1,res){
		// 	printf("( %d )",t1);
		// }
		// printf("\n");
		assert(count1>0);
		printf("%d\n",max(count1-1,0));
	}
return 0;}

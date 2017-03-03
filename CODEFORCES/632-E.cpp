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

const int MOD=998244353;
vector<ll> init(1001,0);

void fft(vector<complex_t>& a,int s=1){
	int n=(int)a.size();
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

typedef long long ll;
// change ll to complex_t if needed
vector <ll> multiply (const vector<ll>& a, const vector<ll>& b) {
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
    vector <ll> res(n);
    for (size_t i = 0; i < n; ++i)
        res[i] = ((ll)(fa[i].real() + 0.5))%MOD;
    return res;
}

void power(vector<ll> &res,int k){
	if(k==1){
		res=init;
		// error(1);
		// For(i,0,res.size()){
		// 	if(res[i]>0){
		// 		Error(i,res[i]);
		// 	}
		// }
		return ;
	}
	else{
		vector<ll> p;
		power(p,k/2);
		// Error("power for ",k);
		vector<ll> p1=p;
		// For(i,0,p.size()){
		// 	if(p[i]>0 && p1[i]>0){
		// 		Error3(i,p[i],p1[i]);
		// 	}
		// }
		For(i,0,p.size()) assert(p[i]==p1[i]);
		res=multiply(p,p1);
		For(i,0,res.size()){
			if(res[i]>0){
				Error(i,res[i]);
			}
		}
		// Error(k,res.size());
		if(k%2==1){
			vector<ll> res1;
			res1=multiply(res,init);
			// Error(k,res1.size());
			// For(i,0,res1.size()){
			// 	if(res1[i]>0){
			// 		Error(i,res1[i]);
			// 	}
			// }
			res=res1;
		}
		// error(k);
		For(i,0,res.size()){
			if(res[i]>0){
				// Error(i,res[i]);
				res[i]=1;
			}
		}
		return ;
	}
}

int main(){
	// vector<ll> a1={0,1,0,1};
	// vector<ll> b1={0,1};
	// vector<ll> c=multiply(a1,b1);
	// For(i,0,c.size()){
	// 	Error(i,c[i]);
	// }
	int n,k;
	scanf("%d%d",&n,&k);
	For(i,0,n){
		int temp;
		scanf("%d",&temp);
		init[temp]=1;
	}

	// For(i,0,init.size()){
	// 	if(init[i]>0){
	// 		Error(i,init[i]);
	// 	}
	// }

	vector<ll> c1;
	power(c1,k);
	// error(c1.size());
	For(i,1,c1.size()){
		if(c1[i]>=1){
			printf("%d ",i);
		}
	}
	printf("\n");
return 0;}
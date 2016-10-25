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
bool isPrime[50010];
vi primeList;
ll answer1=0;
vi Adj[50010];
int size1[50010];
bool deleted[50010];
int color[50010];

void calc(){
	For(i,2,50010){
		isPrime[i]=true;
	}

	For(i,2,50010){
		if(isPrime[i]){
			for(int j=i+i;j<50010;j=j+i){
				isPrime[j]=false;
			}
			primeList.pb(i);
		}
	}
}

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
    while (res.back() == 0) res.pop_back();
    return res;
}

void calcSize(int u,int p){
	size1[u]=1;
	rep(t1,Adj[u]){
		if(t1!=p && !deleted[t1]){
			calcSize(t1,u);
			size1[u]+=size1[t1];
		}
	}
}


int getCentriod(int u,int p,int compSize){
	rep(t1,Adj[u]){
		if(t1!=p && !deleted[t1]){
			if(2*size1[t1]>compSize){
				return getCentriod(t1,u,compSize);
			}
		}
	}
	return u;
}

void DFS(int u,int p,int l,vi &temp){
	temp.pb(l);
	// Error(u,p);
	rep(t1,Adj[u]){
		if(!deleted[t1] && t1!=p){
			DFS(t1,u,l+1,temp);
		}
	}
}

void decompose(int u,int p,int level){
	calcSize(u,-1);
	// Error(u,level);
	int center=getCentriod(u,-1,size1[u]);
	deleted[center]=true;
	color[center]=level;
	// error(center);
	//compute the answer
	vi expres;
	expres.clear();
	// debug;
	rep(t1,Adj[center]){
		if(!deleted[t1]){
			// Error(u,t1);
			vi temp; 
			temp.clear();
			DFS(t1,center,1,temp);
			// error(temp.size());
			// rep(t1,temp){
			// 	printf("( %d )",t1);
			// }
			// printf("\n");
			// error("dfs over");
			if(expres.empty()){
				int max1=-1;
				rep(t1,temp){
					if(isPrime[t1]){
						answer1++;
					}
					max1=max(max1,t1);
				}
				expres.resize(max1+1,0);
				rep(t1,temp){
					expres[t1]++;
				}
			}
			else{
				int max1=-1;
				rep(t1,temp){
					max1=max(max1,t1);
				}
				vi temp1(max1+1,0);
				rep(t1,temp){
					if(isPrime[t1]){
						answer1++;
					}
					temp1[t1]++;
				}
				vi res=multiply(expres,temp1);
				rep(prime,primeList){
					if(prime<res.size()){
						answer1=answer1+res[prime];
					}
					else{
						break;
					}
				}
				vi temp2(max(max1+1,(int)expres.size()),0);
				For(i,0,max(max1+1,(int)expres.size())){
					if(i<expres.size()){
						temp2[i]=temp2[i]+expres[i];
					}
					if(i<temp1.size()){
						temp2[i]=temp2[i]+temp1[i];
					}
				}
				expres=temp2;
			}
		}
	}
	// error(answer1);
	// debug;
	//decompose again
	rep(t1,Adj[center]){
		if(!deleted[t1]){
			decompose(t1,center,level+1);
		}
	}
}

int main(){
	calc();
	int n;
	scanf("%d",&n);

	For(i,1,n){
		int a,b;
		scanf("%d%d",&a,&b);
		Adj[a].pb(b);
		Adj[b].pb(a);
	}

	decompose(1,-1,0);
	ll totalPairs=((ll)n*(ll)(n-1))/2;
	double answer=(1.0*answer1)/(1.0*totalPairs);
	printf("%.6lf\n",answer);
return 0;}

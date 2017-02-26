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
#define MAX 50010
// #define N 100010
const string debug_line="yolo";
#define debug error(debug_line)
#define read() freopen("mergedoutput.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
//template <typename T> using os =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef unsigned long long ull;
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);
const long double eps=1e-6;
ull getRand(){return ((ull)rand()<<40)+((ull)rand()<<20)+((ull)rand());}

char s[610];
int arr[2010];
bitset<2010> v[2010],vv[2010],t,tt;
int p[2010];

void convertToBinary(){
	int n=strlen(s)-1;
	For(i,0,n+1){
		arr[i]=s[i]-'0';
	}
	For(i,0,2010){
		int rem=0;
		rof(j,n,-1){
			arr[j]+=rem*10;
			rem=(int)(arr[j] & 1);
			arr[j]>>=1;
		}
		t[i]=rem;
		while(n>=0 && arr[n]==0){
			n--;
		}
	}
}

int main(){
	int m;
	scanf("%d",&m);
	For(i,0,2010) p[i]=-1;
	For(index1,0,m){
		t=tt=0;
		scanf("%s",s);
		reverse(s,s+(int)strlen(s));
		convertToBinary();
		For(i,0,2010){
			if(t[i]){
				t^=v[i];
				tt^=vv[i];
			}
		}
		if(t==0){
			printf("%d ",(int)tt.count());
			For(i,0,2010){
				if(tt[i]){
					printf("%d ",i);
				}
			}
			printf("\n");
		}
		else{
			printf("0\n");
		}
		tt[index1]=1;
		if(t!=0){
			int l1=0;
			while(t[l1]==0){
				l1++;
			}
			For(i,0,2010){
				if(v[i][l1]!=0){
					v[i]^=t;
					vv[i]^=tt;
				}
			}
			v[l1]=t;vv[l1]=tt;
		}
	}
return 0;}
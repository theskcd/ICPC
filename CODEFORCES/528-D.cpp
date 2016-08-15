#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

#pragma comment(linker, "/STACK:16777216")

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
#define errop(a) cerr<<#a<<" = ( "<<((a).x)<<" , "<<((a).y)<<" )\n";
#define coud(a,b) cout<<fixed << setprecision((b)) << (a)
#define L(x) (((x)<<1)+1)
#define R(x) (((x)<<1)+2)
#define umap unordered_map
//#define double long double
#define mod 1000000007
// #define mod1 1000000009
#define LIMIT 10000000000000000LL
#define INF 10000000000LL
#define MAX1 1000000000
//#define si(n) scanf("%d",&n)
//#define sii(n,m) scanf("%d%d",&n,&m)
//#define pi(n) printf("%d\n",n)
const int inf=0x3f3f3f3f;
const long double pi=acos(-1.0);
#define MAX 50010
#define N 200010
#define M 2000010
const string debug_line="yolo";
#define debug error(debug_line)
const double PI=4*atan(1);
#define read() freopen("mergedoutput.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
//template <typename T> using os =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef complex<double> point;

bitset<N> bitMask[4]; 
bitset<N> bitMaskT[4];
bitset<N> res;
int prev1[N];

void getVector(string s,int index,char check,int extent){
	memset(prev1,0,sizeof(prev1));
	int n1=s.size();
	For(i,0,n1){
		if(s[i]==check){
			prev1[max(0,i-extent)]++;
			prev1[min(n1,i+extent+1)]--;
		}
	}
	int prevSum=0;
	For(i,0,n1){
		prevSum=prevSum+prev1[i];
		if(prevSum>0){
			bitMask[index][i]=true;
		}
		else{
			bitMask[index][i]=false;
		}
	}
}

void prepareT(string t,int index,char check){
	int n1=t.size();
	For(i,0,n1){
		if(t[i]==check){
			bitMaskT[index][i]=true;
		}
		else{
			bitMaskT[index][i]=false;
		}
	}
}

int main(){
	string s,t;
	int n,m,k;
	cin>>n>>m>>k>>s>>t;

	For(j,0,4){
		if(j==0){
			getVector(s,j,'A',k);
		}
		else if(j==1){
			getVector(s,j,'T',k);
		}
		else if(j==2){
			getVector(s,j,'G',k);
		}
		else if(j==3){
			getVector(s,j,'C',k);
		}
	}

	For(j,0,4){
		error(j);
		For(i,0,n){
			cout<<bitMask[j][i];
		}
		printf("\n");
	}

	if(t.size()>s.size()){
		printf("0\n");
	}
	else{
		For(i,0,n){
			res[i]=1;
		}
		For(i,0,m){
			if(t[i]=='A'){
				res=res&(bitMask[0]>>i);
			}
			else if(t[i]=='T'){
				res=res&(bitMask[1]>>i);
			}
			else if(t[i]=='G'){
				res=res&(bitMask[2]>>i);
			}
			else if(t[i]=='C'){
				res=res&(bitMask[3]>>i);
			}
			error(i);
			For(i,0,n){
				cout<<res[i];
			}
			printf("\n");
		}
		int answer1=0;
		For(i,0,n){
			if(res[i]){
				answer1++;
			}
		}
		printf("%d\n",answer1);
	}
return 0;}
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

char t[200010];
char p[200010];
int a[200010];
bool marked[200010];

bool isSub(string t1){
	int index1=0;
	int index2=0;
	int l1=strlen(p);
	while(index1<t1.size() && index2<l1){
		if(p[index2]==t1[index1]){
			index1++;index2++;
		}
		else{
			index1++;
		}
	}
	if(index2==l1){
		return true;
	}
	else{
		return false;
	}
}

bool poss(int length1){
	int n1=strlen(t);
	For(i,0,n1){
		marked[i]=true;
	}
	For(i,0,length1){
		marked[a[i]]=false;
	}
	string t1="";
	For(i,0,n1){
		if(marked[i]){
			t1+=(char)t[i];
		}
	}
	if(isSub(t1)){
		return true;
	}
	else{
		return false;
	}
}

int main(){
	scanf("%s",t);
	scanf("%s",p);
	int n1=strlen(t);
	For(i,0,n1){
		int temp;scanf("%d",&temp);a[i]=--temp;
	}

	int l1=0;
	int h1=n1;
	while(l1<h1){
		int mid=(l1+h1)/2;
		Error3(l1,h1,mid);
		if(l1+1==h1){
			if(poss(h1)){
				l1=h1;
			}
			else{
				h1=l1;
			}
			continue;
		}
		if(poss(mid)){
			l1=mid;
		}
		else{
			h1=mid-1;
		}
	}

	printf("%d\n",l1);
return 0;}
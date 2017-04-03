#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

// using namespace __gnu_pbds;
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
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef unsigned long long ull;
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);
const long double eps=1e-6;
// typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> os;
ull getRand(){return ((ull)rand()<<40)+((ull)rand()<<20)+((ull)rand());}

char query[100010];
ll n;

vector<char> findPos(ll startIndex){
	ll l1=1;
	ll h1=n;
	vector<char> possArr;
	while(true){
		ll mid=(l1+h1)/2;
		if(mid==startIndex){
			break;
		}
		else if(startIndex<mid){
			possArr.pb('L');
			h1=mid-1;
		}
		else if(startIndex>mid){
			possArr.pb('R');
			l1=mid+1;
		}
	}
	return possArr;
}

ll findNum(vector<char> &posArray){
	ll start1=1;
	ll end1=n;
	For(i,0,posArray.size()){
		if(posArray[i]=='L'){
			end1=(start1+end1)/2-1;
		}
		else{
			start1=(start1+end1)/2+1;
		}
		// Error(start1,end1);
	}
	return (start1+end1)/2;
}

void tryMove(char queryType,vector<char> &posArray){
	vector<char> finalPos=posArray;
	if(queryType=='U'){
		if(finalPos.size()!=0){
			finalPos.PB;
			posArray=finalPos;
		}
	}
	else{
		finalPos.pb(queryType);
		ll l1=1;
		ll h1=n;
		// debug;
		bool poss=true;
		For(i,0,finalPos.size()){
			if(finalPos[i]=='L'){
				h1=(l1+h1)/2-1;
			}
			else if(finalPos[i]=='R'){
				l1=(l1+h1)/2+1;
			}
		}
		if(l1<=h1){
			posArray=finalPos;
		}
	}
}

int main(){
	ll q;
	scanf("%lld%lld",&n,&q);

	while(q--){
		ll start1;
		scanf("%lld",&start1);
		scanf("%s",query);
		vector<char> posArray=findPos(start1);
		int l1=strlen(query);
		For(i,0,l1){
			tryMove(query[i],posArray);
			// For(i,0,posArray.size()){
			// 	printf("%c",posArray[i]);
			// }
			// printf("\n");
		}
		ll endPos=findNum(posArray);
		printf("%lld\n",endPos);
	}
return 0;}
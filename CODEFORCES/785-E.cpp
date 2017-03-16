#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
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
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> os;
ull getRand(){return ((ull)rand()<<40)+((ull)rand()<<20)+((ull)rand());}

os orderedSets[310];
ll answer1=0;
const int BLOCK=650;
int valAt[200010];

void changeCalc(int val1,int val2,int pos1,int pos2){
	int blockini=pos1/BLOCK;
	int blockfin=pos2/BLOCK;
	// Error4(pos1,pos2,blockini,blockfin);
	For(i,blockini+1,blockfin){
		answer1=answer1+(orderedSets[i].size()-
							orderedSets[i].order_of_key(val1));
		answer1=answer1-orderedSets[i].order_of_key(val1);
	}
	rof(i,blockfin-1,blockini){
		answer1=answer1-(orderedSets[i].size()-
							orderedSets[i].order_of_key(val2));
		answer1=answer1+orderedSets[i].order_of_key(val2);
	}
	if(blockini==blockfin){
		For(i,pos1+1,pos2){
			if(val1<valAt[i]){
				answer1++;
			}
			else{
				answer1--;
			}
		}
		rof(i,pos2-1,pos1){
			if(val2<valAt[i]){
				answer1--;
			}
			else{
				answer1++;
			}
		}
		if(val1>val2){
			answer1--;
		}
		else{
			answer1++;
		}
		// error(answer1);
	}
	else{
		int start1=blockfin*BLOCK;
		//add answers for finalBlock for val1
		For(i,start1,pos2){
			if(valAt[i]>val1){
				answer1++;
			}
			else{
				answer1--;
			}
		}
		//remove answers for origBlock for val2
		rof(i,pos2-1,start1-1){
			if(valAt[i]>val2){
				answer1--;
			}
			else{
				answer1++;
			}
		}
		int end1=blockini*BLOCK+BLOCK-1;
		//add answers for finalBlock of val2
		rof(i,end1,pos1){
			if(valAt[i]<val2){
				answer1++;
			}
			else{
				answer1--;
			}
		}
		//remove answers for origBlock of val1
		For(i,pos1+1,BLOCK*(blockini+1)){
			if(valAt[i]<val1){
				answer1--;
			}
			else{
				answer1++;
			}
		}
		if(val1>val2){
			answer1--;
		}
		else{
			answer1++;
		}
	}
}

int main(){
	int n,q;
	scanf("%d%d",&n,&q);
	For(i,1,n+1){
		valAt[i]=i;
		orderedSets[i/BLOCK].insert(i);
	}
	vector<ll> answers;
	while(q--){
		int x1,y1;
		scanf("%d%d",&x1,&y1);
		if(x1>y1)swap(x1,y1);
		if(x1==y1){
			answers.pb(answer1);
			continue;
		}
		int valX=valAt[x1];
		int valY=valAt[y1];
		orderedSets[x1/BLOCK].erase(valX);
		orderedSets[y1/BLOCK].erase(valY);
		// Error4(valX,valY,x1,y1);
		changeCalc(valX,valY,x1,y1);
		orderedSets[x1/BLOCK].insert(valY);
		orderedSets[y1/BLOCK].insert(valX);
		swap(valAt[x1],valAt[y1]);
		answers.pb(answer1);
	}

	rep(t1,answers){
		printf("%lld\n",t1);
	}
return 0;}
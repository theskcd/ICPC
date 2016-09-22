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
#define N 100000
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

class XorOrderDiv2
{
public:
	class TrieNode
	{
	public:
		int countNodes;
		TrieNode *left;
		TrieNode *right;
		TrieNode(){
			countNodes=0;
			left=NULL;
			right=NULL;
		}
	};

	vector<ll> num;
	TrieNode* startNode;
	int bitSize;

	void insertTrie(int num){
		TrieNode *currNode=startNode;
		rof(i,bitSize-1,-1){
			if(num & (1<<i)){
				if(currNode->right==NULL){
					currNode->right=new TrieNode();
				}
				currNode->right->countNodes++;
				currNode=currNode->right;
			}
			else{
				if(currNode->left==NULL){
					currNode->left=new TrieNode();
				}
				currNode->left->countNodes++;
				currNode=currNode->left;
			}
		}
	}

	void fill(ll number,vector<ll> &x1,vector<ll> &y1){
		TrieNode *currNode=startNode;
		rof(i,bitSize-1,-1){
			if(number & (1<<i)){
				x1.pb(0);
				if(currNode->left!=NULL){
					y1.pb(currNode->left->countNodes);
				}
				else{
					y1.pb(0);
				}
				currNode=currNode->right;
			}
			else{
				if(currNode->right!=NULL){
					x1.pb(currNode->right->countNodes);
				}
				else{
					x1.pb(0);
				}
				y1.pb(0);
				currNode=currNode->left;
			}
			assert(currNode!=NULL);
		}
	}

	int get(int m,int n,int a0,int b){
		num.pb(a0);
		bitSize=m;
		int start=a0;
		startNode=new TrieNode();
		int modulo=(int)(1<<m);
		For(i,1,n){
			start=(a0+i*b)%modulo;
			num.pb(start);
		}
		For(i,0,n){
			insertTrie(num[i]);
		}
		ll answer1=0;
		ll n1=n;
		n1=(n1*n1)%mod;
		// debug;
		For(i,0,n){
			vector<ll> x1;
			vector<ll> y1;
			fill(num[i],x1,y1);
			ll temp1=0;
			ll temp2=0;
			ll temp3=0;
			assert(x1.size()==bitSize && y1.size()==bitSize);
			// error(i);
			// For(j,0,m){
			// 	Error3(j,x1[j],y1[j]);
			// }
			For(j,0,m){
				temp2=(temp2+x1[j])%mod;
				temp3=(temp3+y1[j])%mod;
			}
			For(j,0,m){
				temp1=(temp1+(x1[j]+y1[j])*(temp2+temp3))%mod;
				temp1=((temp1-(2*x1[j]*y1[j]))%mod+mod)%mod;
				temp1=(temp1+(x1[j]*x1[j])%mod+(y1[j]*y1[j])%mod)%mod;
			}
			// temp1=(temp1+temp2*temp3*2)%mod;
			ll coff=(1LL<<(bitSize-2));
			coff%=mod;
			temp1=(temp1*coff)%mod;
			// ll temp4=(n1*coff)%mod;
			// ll temp5=((ll)n*coff)%mod;
			// temp5=(temp5*(temp3+temp2))%mod;
			// temp1=((temp4+temp1-2*temp5)%mod+mod)%mod;
			// Error(i,temp1);
			answer1=(answer1^temp1);
		}
		return answer1;
	}
};
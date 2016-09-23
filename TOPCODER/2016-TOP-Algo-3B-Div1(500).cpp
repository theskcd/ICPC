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

class MaterialImplication
{
public:
	vector<bool> visited;
	void recurse(int num,int remain,int l,int r,string &answer1){
		Error5(num,remain,l,r,answer1);
		if(num==2){
			assert(r-l==5);
			char f1,f2;
			For(i,0,visited.size()){
				if(!visited[i]){
					visited[i]=true;
					f1=(char)(i+'A');
					break;
				}
			}
			rof(i,visited.size()-1,-1){
				if(!visited[i]){
					visited[i]=true;
					f2=(char)(i+'A');
					break;
				}
			}
			assert(f1!=f2);
			answer1[l]=(char)'(';
			answer1[l+1]=(char)f1;
			answer1[l+2]=(char)'-';
			answer1[l+3]=(char)'>';
			answer1[l+4]=(char)f2;
			answer1[l+5]=(char)')';
			return ;
		}
		else{
			int temp1=(1<<(num-2));
			if(temp1>remain){
				char f1;
				For(i,0,visited.size()){
					if(!visited[i]){
						f1=(char)(i+'A');
						visited[i]=true;
						break;
					}
				}
				answer1[l]=(char)'(';
				answer1[l+1]=(char)f1;
				answer1[l+2]=(char)'-';
				answer1[l+3]=(char)'>';
				answer1[r]=(char)')';
				recurse(num-1,remain,l+4,r-1,answer1);
			}
			else{
				char f2;
				rof(i,visited.size()-1,-1){
					if(!visited[i]){
						f2=(char)(i+'A');
						visited[i]=true;
						break;
					}
				}
				answer1[r]=(char)')';
				answer1[r-1]=(char)f2;
				answer1[r-2]=(char)'>';
				answer1[r-3]=(char)'-';
				answer1[l]=(char)'(';
				remain=2*temp1-remain;
				recurse(num-1,remain,l+1,r-4,answer1);
			}
		}
	}

	string solve(int n,int num){
		string answer1="";
		For(i,0,4*(n-1)+n){
			answer1=answer1+" ";
		}
		visited.resize(n,0);
		recurse(n,num,0,answer1.size()-1,answer1);
		return answer1;
	}

	string construct(int n,int k){
		int countEven=0;
		if(k==0){
			return "Impossible";
		}
		if(n==1 && k>2){
			return "Impossible";
		}
		else if(n==1 && k==1){
			return "A";
		}
		else if(n==1 && k==2){
			return "(A->A)";
		}
		else if(n==2 && k==4){
			return "(A->A)";
		}
		else if(n==2 && k==3){
			return "(A->B)";
		}
		else if(n==2 && k==2){
			return "A";
		}
		else if(n==2 && k<2){
			return "Impossible";
		}
		assert(n>2);
		if(k<(1<<(n-1))){
			return "Impossible";
		}
		while(k%2==0){
			countEven++;
			k=k/2;
		}
		if(countEven==n){
			return "(A->A)";
		}
		else if(countEven==n-1){
			return "A";
		}
		else{
			int num=(1<<(n-countEven))-k;
			// Error(n-countEven,num);
			string answer1=solve(n-countEven,num);
			return answer1;
		}
	}
};

// int main(){
// 	MaterialImplication *mi=new MaterialImplication();
// 	int n,k;
// 	scanf("%d%d",&n,&k);
// 	error((*mi).construct(n,k));
// }
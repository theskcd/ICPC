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

class ConnectedSubgraph
{
public:
	map<int,int> mp2;
	map<int,int> mp1;
	map<int,int> mp3;
	vector<string> answer;
	
	void construct1(int k){
		answer.resize(mp2[k]);
		For(i,0,mp2[k]){
			For(j,0,mp2[k]){
				answer[i]+="N";
			}
		}
		vi res;
		For(i,0,mp2[k]){
			if((1<<i) & mp1[k]){
				res.pb(1);
			}
			else{
				res.pb(0);
			}
		}

		For(i,0,mp2[k]){
			if(res[i]){
				For(j,0,i){
					answer[i][j]='Y';
					answer[j][i]='Y';
				}
			}
		}
	}

	void construct2(int k,int k1){
		int size1=mp2[k]+mp2[k1];
		Error(mp2[k],mp2[k1]);
		answer.resize(size1);
		For(i,0,size1){
			For(j,0,size1){
				answer[i]+="N";
			}
		}
		vi res;
		vi res1;
		For(j,0,mp2[k]){
			if((1<<j) & mp1[k]){
				res.pb(1);
			}
			else{
				res.pb(0);
			}
		}
		For(i,0,mp2[k]){
			if(res[i]){
				For(j,0,i){
					answer[i][j]='Y';
					answer[j][i]='Y';
				}
			}
		}
		debug;
		int counter1=mp2[k];
		For(j,0,mp2[k1]){
			if((1<<j) & mp1[k1]){
				res1.pb(1);
			}
			else{
				res1.pb(0);
			}
		}
		debug;
		For(i,0,mp2[k1]){
			if(res1[i]){
				For(j,0,i){
					answer[counter1+i][counter1+j]='Y';
					answer[counter1+j][counter1+i]='Y';
				}
			}
		}
	}

	vector<string> construct(int k){
		For(i,1,65536){
			int currAnswer=0;
			int mask=0;
			For(j,0,16){
				if((1<<j) & i){
					currAnswer=currAnswer+(1<<j);
					mask+=(1<<j);
				}
				else{
					currAnswer++;
				}
				if(mp1.find(currAnswer)==mp1.end() || mp2[currAnswer]>j+1){
					mp1[currAnswer]=mask;
					mp2[currAnswer]=j+1;
				}
			}
		}
		if(mp1.find(k)!=mp1.end()){
			Error3("from one",mp1[k],mp2[k]);
			construct1(k);
		}
		else{
			For(i,0,16){
				if(mp1.find(k-i)!=mp1.end() && !(i==9 || i==10 || i==13)){
					Error3("from two",k-i,i);
					construct2(k-i,i);
					break;
				}
			}
		}
		return answer;
	}
};

// int main(){
// 	int temp;
// 	scanf("%d",&temp);
// 	ConnectedSubgraph *con=new ConnectedSubgraph();
// 	vector<string> res=(*con).construct(temp);
// 	assert(res.size()==res[0].size());
// 	// error(res.size());
// 	assert(res.size()<=20);
// 	For(i,0,res.size()){
// 		cout<<res[i]<<endl;
// 	}
// }
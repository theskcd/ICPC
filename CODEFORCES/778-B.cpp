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

struct query{
	string name;
	string val1;
	string val2;
	int opType;

	void print(){
		Error4(name,val1,val2,opType);
	}
};

vector<query> Q;

int solve(bool type,int index1){
	int n=Q.size();
	unordered_map<string,int> mp1;
	int res1=0;
	int res2=0;
	//choose 0
	mp1["?"]=0;
	For(i,0,n){
		if(Q[i].opType==-1){
			mp1[Q[i].name]=Q[i].val1[index1]-'0';
		}
		else if(Q[i].opType==1){
			mp1[Q[i].name]=mp1[Q[i].val1] ^ mp1[Q[i].val2];
		}
		else if(Q[i].opType==2){
			mp1[Q[i].name]=mp1[Q[i].val1] & mp1[Q[i].val2];
		}
		else if(Q[i].opType==3){
			mp1[Q[i].name]=mp1[Q[i].val1] | mp1[Q[i].val2];
		}
	}
	rep(t1,mp1){
		// Error3(index1,t1.x,t1.y);
		if(t1.y==1){
			res1++;
		}
	}

	//choose 1
	mp1.clear();
	mp1["?"]=1;
	For(i,0,n){
		if(Q[i].opType==-1){
			mp1[Q[i].name]=Q[i].val1[index1]-'0';
		}
		else if(Q[i].opType==1){
			mp1[Q[i].name]=mp1[Q[i].val1] ^ mp1[Q[i].val2];
		}
		else if(Q[i].opType==2){
			mp1[Q[i].name]=mp1[Q[i].val1] & mp1[Q[i].val2];
		}
		else if(Q[i].opType==3){
			mp1[Q[i].name]=mp1[Q[i].val1] | mp1[Q[i].val2];
		}
	}
	rep(t1,mp1){
		res2+=t1.y;
	}
	res2--;
	// Error3(index1,res1,res2);
	int finalAnswer=-1;
	if(type){
		(res1>=res2)? finalAnswer=0: finalAnswer=1;
	}
	else{
		(res1>res2)? finalAnswer=1: finalAnswer=0;
	}
	return finalAnswer;
}

void takeInput(vector<string> &tokens){
	string name1;
	cin>>name1;
	tokens.pb(name1);
	cin>>name1;tokens.pb(name1);
	cin>>name1;tokens.pb(name1);
	if(name1[0]=='0' || name1[0]=='1'){
		return ;
	}
	else{
		cin>>name1;tokens.pb(name1);
		cin>>name1;tokens.pb(name1);
	}
}

int main(){
	iOS;
	int n,m;
	cin>>n>>m;
	For(i,0,n){
		vector<string> tokens;
		takeInput(tokens);
		if(tokens.size()==3){
			query t1;
			t1.name=tokens[0];
			t1.val1=tokens[2];
			t1.opType=-1;
			Q.pb(t1);
		}
		else if(tokens.size()==5){
			query t1;
			t1.name=tokens[0];
			t1.val1=tokens[2];
			t1.val2=tokens[4];
			if(tokens[3]=="XOR"){
				t1.opType=1;
			}
			else if(tokens[3]=="AND"){
				t1.opType=2;
			}
			else if(tokens[3]=="OR"){
				t1.opType=3;
			}
			Q.pb(t1);
		}
	}
	debug;
	// getchar();

	// For(i,0,n){
	// 	Q[i].print();
	// }
	string answer1="";
	string answer2="";
	For(i,0,m){
		answer1+=(char)(solve(false,i)+'0');
	}
	For(i,0,m){
		answer2+=(char)(solve(true,i)+'0');
	}
	cout<<answer1<<endl;
	cout<<answer2<<endl;
return 0;}
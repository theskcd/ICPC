#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

// using namespace __gnu_pbds;
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
#define pow2(a) (((a) * (a)))
#define all(a) a.begin() , a.end()
#define error(x) cerr << #x << " = " << (x) <<endl
#define Error(a,b) cerr<<"( "<<#a<<" , "<<#b<<" ) = ( "<<(a)<<" , "<<(b)<<" )\n";
#define Error3(a,b,c) cerr<<"("<<#a<<" , "<<#b<<" , "<<#c<<" ) = ( "<<(a)<<" , "<<(b)<<" , "<<(c)<<")\n";
#define errop(a) cerr<<#a<<" = ( "<<((a).x)<<" , "<<((a).y)<<" )\n";
#define coud(a,b) cout<<fixed << setprecision((b)) << (a)
#define L(x) (((x)<<1)+1)
#define R(x) (((x)<<1)+2)
#define umap unordered_map
#define double long double
#define mod 1000000007
#define mod1 1000000009
#define LIMIT 4000000000000000000LL
#define N 510
const string debug_line="yolo";
#define debug error(debug_line)
// const double PI=4*atan(1);
// template <typename T> using os =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> Tree;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef complex<double> point;
const long long linf = 1e15+5;
const int BLOCK=330;

int a[211];
vector<string> s;
vi output[211];
ll sum1[211];
int f[211];
int g[211][26];
int numStates;
vector<vector<ll> >identity;

void merge1(int s1,int s2){
	output[s1].insert(output[s1].end(),output[s2].begin(),output[s2].end());
}

int buildMatchingMachine(const vector<string> &words){
	int states=1;
	memset(f,-1,sizeof(f));
	memset(g,-1,sizeof(g));
	memset(output,0,sizeof(output));

	For(i,0,words.size()){
		const string &word=words[i];
		int currentState=0;
		For(j,0,word.size()){
			int c=word[j]-'a';
			if(g[currentState][c]==-1){
				g[currentState][c]=states++;
			}
			// Error3(currentState,g[currentState][c],(char)(c+'a'));
			currentState=g[currentState][c];
		}
		output[currentState].pb(i);
	}

	For(c,0,26){
		if(g[0][c]==-1){
			g[0][c]=0;
		}
	}

	queue<int> Q1;
	debug;
	For(c,0,26){
		if(g[0][c]!=-1 && g[0][c]!=0){
			f[g[0][c]]=0;
			Q1.push(g[0][c]);
		}
	}

	while(!Q1.empty()){
		int state=Q1.front();
		// Error("ah-corsaik",state);
		Q1.pop();
		For(c,0,26){
			if(g[state][c]!=-1){
				int failure=f[state];
				while(g[failure][c]==-1){
					failure=f[failure];
				}
				failure=g[failure][c];
				f[g[state][c]]=failure;
				merge1(g[state][c],failure);
				Q1.push(g[state][c]);
			}
			// Error(state,c);
		}
	}

	return states;
}

void correct1(int state1){
	sort(all(output[state1]));
	output[state1].erase(unique(output[state1].begin(),output[state1].end()),output[state1].end());
	rep(t1,output[state1]){
		sum1[state1]+=a[t1];
	}
	// Error(state1,sum1[state1]);
}

void multiply(vector<vector<ll> > a,vector<vector<ll> > b,vector<vector<ll> >&res){
	res.resize(numStates+1,vector<ll>(numStates+1));
	For(i,0,numStates){
		For(j,0,numStates){
			res[i][j]=-1e18;
		}
	}

	For(i,0,numStates){
		For(j,0,numStates){
			For(k,0,numStates){
				{
					res[i][j]=max(a[i][k]+b[k][j]-sum1[k],res[i][j]);
				}
			}
		}
	}
}

void power1(vector<vector<ll> > &dp,ll k){
	if(k==1){
		dp.resize(numStates+1,vector<ll>(numStates+1));
		dp=identity;
		return ;
	}
	else{
		vector<vector<ll> > res;
		power1(res,k/2);
		if(k%2==0){
			multiply(res,res,dp);
		}
		else{
			multiply(res,res,dp);
			multiply(dp,identity,dp);
		}
		return ;
	}
}

int findNextState(int currState,int next1){
	int answer1=currState;
	int c=next1;
	while(g[answer1][c]==-1){
		answer1=f[answer1];
	}
	return g[answer1][c];
}

ll merge2(int s1,int s2){
	vi v1;
	// output[s1].insert(output[s1].end(),output[s2].begin(),output[s2].end());
	v1.insert(v1.end(),output[s1].begin(),output[s1].end());
	v1.insert(v1.end(),output[s2].begin(),output[s2].end());
	sort(all(v1));
	v1.erase(unique(v1.begin(),v1.end()),v1.end());
	ll answer1=0;
	// Error(s1,s2);
	rep(t1,v1){
		// error(t1);
		answer1=answer1+a[t1];
	}
	// Error3(s1,s2,answer1);
	return answer1;
}

int main(){
	int n;
	ll l;
	scanf("%d%lld",&n,&l);

	For(i,0,n){
		int temp;
		scanf("%d",&temp);
		a[i]=temp;
	}

	For(i,0,n){
		string temp;
		cin>>temp;
		s.pb(temp);
	}

	debug;

	numStates=buildMatchingMachine(s);

	debug;

	For(i,1,numStates){
		correct1(i);
	}

	debug;

	identity.resize(numStates+1,vector<ll>(numStates+1));

	debug;

	For(i,0,numStates){
		For(j,0,numStates){
			identity[i][j]=-1e18;
		}
	}

	For(i,0,numStates){
		// Error(i,sum1[i]);
		For(j,0,26){
			// Error(i,findNextState(i,j));
			identity[i][findNextState(i,j)]=max(identity[i][findNextState(i,j)],sum1[i]+sum1[findNextState(i,j)]);
		}
	}

	error("identity");
	// For(i,0,numStates){
	// 	For(j,0,numStates){
	// 		printf("%lld ",identity[i][j]);
	// 	}
	// 	printf("\n");
	// }

	vector<vector<ll> > dp;
	power1(dp,l);

	error("dp");
	// For(i,0,numStates){
	// 	For(j,0,numStates){
	// 		printf("%lld ",dp[i][j]);
	// 	}
	// 	printf("\n");
	// }

	ll answer1=0;
	For(i,0,numStates){
		answer1=max(answer1,dp[0][i]);
	}
	printf("%lld\n",answer1);
return 0;}
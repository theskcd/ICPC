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
#define N 100010
const string debug_line="yolo";
#define debug error(debug_line)
#define read() freopen("mergedoutput.txt","r",stdin)
#define write() freopen("output.txt","w",stdout)
//template <typename T> using os =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
typedef long long ll;
typedef pair<int,int>pii;
typedef vector<int> vi;
typedef complex <long double> complex_t;
const long double PI = acos((long double)-1.0);
const long double eps=1e-6;

struct node{
	int u,v,x1,y1,c;

	node(int _u,int _v,int _x1,int _y1,int _c){
		u=_u,v=_v,x1=_x1,y1=_y1,c=_c;
	}
};

vector<node> collect;
int n,m;
char s[1011][1011];
ll change1[1011][1011][26];
ll cost1[1011][1011];
ll counter1[1011][1011];

int getCost(int i,int j,char c){
	ll answer1=0;
	For(k,0,26){
		answer1=answer1+change1[i][j][k]*(ll)abs(k-c+'a');
	}
	return answer1;
}

void putValues(int i,int j,int mul,vector<ll> &res){
	For(k,0,26){
		// printf("%d ",change1[i][j][k]);
		res[k]+=mul*(ll)change1[i][j][k];
	}
	// printf("\n");
}

void print(vi res){
	For(i,0,res.size()){
		printf("%d ",res[i]);
	}
	printf("\n");
}

ll getCost1(int i1,int j1,int i2,int j2){
	i1--;j1--;
	ll answer1=0;
	if(i1>=0 && j1>=0){
		answer1+=cost1[i1][j1];
	}
	if(i1>=0 && j2>=0){
		answer1-=cost1[i1][j2];
	}
	if(i2>=0 && j1>=0){
		answer1-=cost1[i2][j1];
	}
	answer1+=cost1[i2][j2];
	return answer1;
}

int main(){
	int k;
	scanf("%d%d%d",&n,&m,&k);
	For(i,0,n){
		scanf("%s",s[i]);
	}

	counter1[0][0]+=k;

	For(i,0,k){
		int a1,b1,c1,d1;
		char e[2];
		scanf("%d%d%d%d%s",&a1,&b1,&c1,&d1,e);
		getchar();
		a1--,b1--,c1--,d1--;
		node n1={a1,b1,c1,d1,e[0]-'a'};
		collect.pb(n1);
		c1++,d1++;
		// Error5(a1,b1,c1,d1,e[0]);
		// assert(a1>=0 && b1>=0 && c1>=0 && d1>=0);
		change1[a1][b1][e[0]-'a']++;counter1[a1][b1]--;
		change1[a1][d1][e[0]-'a']--;counter1[a1][d1]++;
		change1[c1][d1][e[0]-'a']++;counter1[c1][d1]--;
		change1[c1][b1][e[0]-'a']--;counter1[c1][b1]++;
	}

	For(i,0,n+1){
		For(j,0,m+1){
			For(k,0,26){
				if(i==0 && j==0){
					//qwe
				}
				else if(i!=0 && j==0){
					change1[i][j][k]+=change1[i-1][j][k];
				}
				else if(i==0 && j!=0){
					change1[i][j][k]+=change1[i][j-1][k];
				}
				else if(i!=0 && j!=0){
					change1[i][j][k]+=change1[i-1][j][k]+change1[i][j-1][k]-change1[i-1][j-1][k];
				}
			}
		}
	}

	For(i,0,n+1){
		For(j,0,m+1){
			if(i==0 && j==0){
				//qwe
			}
			else if(i!=0 && j==0){
				counter1[i][j]+=counter1[i-1][j];
			}
			else if(i==0 && j!=0){
				counter1[i][j]+=counter1[i][j-1];
			}
			else if(i!=0 && j!=0){
				counter1[i][j]+=counter1[i-1][j]+counter1[i][j-1]-counter1[i-1][j-1];
			}
		}
	}

	For(i,0,n){
		For(j,0,m){
			change1[i][j][s[i][j]-'a']+=counter1[i][j];
		}
	}


	// For(k,0,26){
	// 	error((char)(k+'a'));
	// 	For(i,0,n){
	// 		For(j,0,m){
	// 			printf("%d ",change1[i][j][k]);
	// 		}
	// 		printf("\n");
	// 	}
	// }

	For(i,0,n){
		For(j,0,m){
			// error(getCost(i,j,s[i][j]));
			if(i==0 && j==0){
				cost1[i][j]=getCost(i,j,s[i][j]);
			}
			else if(i!=0 && j==0){
				cost1[i][j]=cost1[i-1][j]+getCost(i,j,s[i][j]);
			}
			else if(i==0 && j!=0){
				cost1[i][j]=cost1[i][j-1]+getCost(i,j,s[i][j]);
			}
			else if(i!=0 && j!=0){
				cost1[i][j]=cost1[i-1][j]+cost1[i][j-1]-cost1[i-1][j-1]+getCost(i,j,s[i][j]);
			}
		}
	}

	For(i,0,n+1){
		For(j,0,m+1){
			For(k,0,26){
				if(i==0 && j==0){
					//qwe
				}
				else if(i!=0 && j==0){
					change1[i][j][k]+=change1[i-1][j][k];
				}
				else if(i==0 && j!=0){
					change1[i][j][k]+=change1[i][j-1][k];
				}
				else if(i!=0 && j!=0){
					change1[i][j][k]+=change1[i-1][j][k]+change1[i][j-1][k]-change1[i-1][j-1][k];
				}
			}
		}
	}

	// For(i,0,n){
	// 	For(j,0,m){
	// 		printf("%d ",cost1[i][j]);
	// 	}
	// 	printf("\n");
	// }

	ll answer1=LIMIT;

	rep(n1,collect){
		ll currentAnswer=0;
		vector<ll> res;
		res.resize(26,0);
		int u1=n1.u-1;int v1=n1.v-1;
		int x1=n1.x1;int y1=n1.y1;
		// Error4(u1,v1,x1,y1);
		if(x1>=0 && y1>=0)
		putValues(x1,y1,1,res);
		// print(res);
		if(u1>=0 && y1>=0)
		putValues(u1,y1,-1,res);
		// print(res);
		if(x1>=0 && v1>=0)
		putValues(x1,v1,-1,res);
		// print(res);
		if(u1>=0 && v1>=0)
		putValues(u1,v1,1,res);
		// print(res);
		// and now get the rectangles
		// error(n1.c);
		For(k,0,26){
			currentAnswer+=(ll)res[k]*(ll)abs(k-n1.c);
			// printf("%d ",res[k]);
		}
		// printf("\n");
		// error(currentAnswer);
		currentAnswer+=cost1[n-1][m-1];
		// error(cost1[n-1][m-1]);
		u1++,v1++;
		currentAnswer-=getCost1(u1,v1,x1,y1);
		// error(getCost1(u1,v1,x1,y1));
		answer1=min(answer1,currentAnswer);
		// error(currentAnswer);
	}

	printf("%lld\n",answer1);
return 0;}

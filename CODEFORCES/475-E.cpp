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
#define N 2010
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

struct blockCutTree{
    int n;
    int m;
    bool visited[N];
    int component[N];
    int size1[N];
    int arr[N];
    bool isbridge[M];
    vector<pair<pii,int> > Adj[N];
    queue<int> Q[N];
    int comp2[N];
    vi tree[N];
    int P[N][36];
    int level1[N];
    vector<pair<pair<pii,int>,int> > edges; // here edges store the following information < < <u,v>,weight>,index> u : from node, v : to node
    int comcount;
    int countPairNodes;
    map<pii,int> mp1;
    vi edgeList[M];
    int dfs_timer;

    blockCutTree(){
        edges.clear();
        n=-1;
        m=-1;
        countPairNodes=0;
        comcount=0;
        dfs_timer=0;
    };

    blockCutTree(vector<pair<pair<pii,int>,int> > _edges,int _n,int _m){
    	// debug;
        n=_n;
        m=_m;
        comcount=0;
        edges=_edges;
        dfs_timer=0;
        For(i,0,n+1){
            Adj[i].clear();
            visited[i]=false;
        }
        For(i,0,m+1){
            isbridge[i]=false;
        }
        rep(t1,edges){
            {
                Adj[t1.x.x.x].pb(mp(mp(t1.x.x.y,t1.x.y),t1.y));
                Adj[t1.x.x.y].pb(mp(mp(t1.x.x.x,t1.x.y),t1.y));
            }
        }
    };

public:

    int DFS(int u,int p,int edge){
        visited[u]=true;
        component[u]=comcount;
        arr[u]=dfs_timer++;
        int dbe=arr[u];

        rep(t1,Adj[u]){
            if(!visited[t1.x.x] && t1.x.x!=p){
                dbe=min(dbe,DFS(t1.x.x,u,t1.y));
            }
            else if(edge!=t1.y){
                dbe=min(dbe,arr[t1.x.x]);
            }
        }
        if(dbe==arr[u] && edge!=-1){
            isbridge[edge]=true;
        }
        return dbe;
    };

    void DFS1(int u){
        int curcmp=comcount;
        Q[curcmp].push(u);
        visited[u]=true;
        while(!Q[curcmp].empty()){
            int v=Q[curcmp].front();
            comp2[v]=curcmp;
            size1[curcmp]++;
            Q[curcmp].pop();
            rep(t1,Adj[v]){
                if(visited[t1.x.x]){
                    continue;
                }
                else if(isbridge[t1.y]){
                    comcount++;
                    // Error3("edges between",curcmp,comcount);
                    tree[curcmp].pb(comcount);
                    tree[comcount].pb(curcmp);
                    DFS1(t1.x.x);
                }
                else{
                    Q[curcmp].push(t1.x.x);
                    visited[t1.x.x]=true;
                }
            }
        }
    };

    void DFS2(int u,int p){
        visited[u]=true;
        P[u][0]=p;
        level1[u]=level1[p]+1;
        For(i,1,35){
            P[u][i]=P[P[u][i-1]][i-1];
        }

        rep(t1,tree[u]){
            if(!visited[t1]){
                DFS2(t1,u);
            }
        }
    };

    int LCA(int u,int v){
        if(level1[u]<level1[v]){
            swap(u,v);
        }
        rof(i,34,-1){
            if(level1[P[u][i]]>=level1[v]){
                u=P[u][i];
            }
        }

        if(u==v){
            return u;
        }
        rof(i,34,-1){
            if(P[u][i]!=P[v][i]){
                u=P[u][i];
                v=P[v][i];
            }
        }
        return P[u][0];
    };

    void construct(){
        memset(visited,0,sizeof(visited));
        For(i,1,n+1){
            if(!visited[i]){
                DFS(i,0,-1);
                comcount++;
            }
        }
        memset(visited,0,sizeof(visited));
        For(i,1,n+1){
            if(!visited[i]){
                DFS1(i);
            }
        }
        memset(visited,0,sizeof(visited));
        For(i,1,n+1){
            if(!visited[i]){
                level1[i]=0;
                DFS2(i,i);
            }
        }
    }

    pii DFSRecurse(int u,int p){
    	pii answer1={0,0};
    	// Error("DFSRecurse in ",u);
    	rep(t1,tree[u]){
    		if(t1!=p){
    			// Error3("DFSRecurse pushing",u,t1);
    			pii temp1=DFSRecurse(t1,u);
    			answer1.x+=temp1.x;
    			answer1.y+=temp1.y;
    		}
    	}
    	answer1.x+=(size1[u]*answer1.y);
    	answer1.x+=(size1[u]*size1[u]);
    	answer1.y+=size1[u];
    	// Error4("DFS returining",u,answer1.x,answer1.y);
    	return answer1;
    }
};

vector<pair<pair<pii,int>,int> > edges;
ll answer1=0;

int main(){
	int n,m;
	scanf("%d%d",&n,&m);

	For(i,0,m){
		int a,b;
		scanf("%d%d",&a,&b);
		edges.pb(mp(mp(mp(a,b),0),i));
	}

	blockCutTree blckTree(edges,n,m);
	blckTree.construct();
	// error(blckTree.comcount);
	set<int> s1;
	For(i,1,n+1){
		s1.insert(blckTree.comp2[i]);
	}

	// rep(t1,s1){
	// 	Error3("nodes in tree are",t1,blckTree.size1[t1]);
	// }

	rep(node1,s1){
		ll current=(blckTree.size1[node1]*blckTree.size1[node1]);
		ll finalSize=0;
		vi sizes;
		// Error("starting for node1",node1);
		rep(node,blckTree.tree[node1]){
			pii t1;
			t1=blckTree.DFSRecurse(node,node1);
			// Error4("subtree part",node1,node,t1.x);
			current=current+t1.x;
			finalSize+=t1.y;
			sizes.pb(t1.y);
		}
		// Error3(node1,current,finalSize);
		ll totalSize=0;
		vi achievableSum(2010);
		achievableSum[0]=true;
		rep(size,sizes){
			rof(i,2000,size-1){
				if(achievableSum[i-size]){
					achievableSum[i]=true;
				}
			}
		}

		For(i,0,2010){
			if(achievableSum[i]){
				ll out=finalSize-i;
				// Error(i,out);
				// Error4(i,out,blckTree.size1[node1],(i+blckTree.size1[node1])*out+i*blckTree.size1[node1]+current);
				answer1=max(answer1,(i+blckTree.size1[node1])*out+i*blckTree.size1[node1]+current);
				// Error3(i,out,answer1);
			}
		}
	}

	printf("%lld\n",answer1);
return 0;}
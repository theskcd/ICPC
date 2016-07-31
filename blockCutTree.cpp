#define N 100010
#define M 100010

struct blockCutTree{
    int n;
    int m;
    bool visited[N];
    int component[N];
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
            if(t1.y!=ignoreEdge){
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
            Q[curcmp].pop();
            rep(t1,Adj[v]){
                if(visited[t1.x.x]){
                    continue;
                }
                else if(isbridge[t1.y]){
                    comcount++;
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
};
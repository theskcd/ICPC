#define N 100010
#define M 100010
#define vector<int> vi
#define pair<int,int> pii
#define first x
#define second y
#define For(i,a,b) for(int (i)=(a);(i) < (b); ++(i))
#define rof(i,a,b) for(int (i)=(a);(i) > (b); --(i))
#define rep(i, c) for(auto &(i) : (c))
#define push_back pb
#define make_pair mp
#define all(a) a.begin() , a.end()

struct auxilliaryTree{
	int dfs_timer;
	vector<vi> Adj;
	vi discovered;
	vi beginTime;
	vi endTime;
	vi sizeSubTree;
	vi level1;
	vector<set<int> > tree;
	vector<bool> marked;
	set<pii> edge;
	vector<bool> visited;
	vector<pii> v2;
	vector<vi> P;

	auxilliaryTree(){
		dfs_timer=0;
	}

	auxilliaryTree(int _n,vector<pii> &_edgesTrees){
		discovered.resize(n+10);
		beginTime.resize(n+10);
		endTime.resize(n+10);
		sizeSubTree.resize(n+10);
		tree.resize(n+10);
		marked.resize(n+10);
		visited.resize(n+10);
		P.resize(n,vector<int>(36));
		level1.resize(n+10);
		Adj.resize(n);

		For(i,0,_edgesTrees.size()){
			// bi-directional Edge
			Adj[_edgesTrees[i].x].pb(_edgesTrees[i].y);
			Adj[_edgesTrees[i].y].pb(_edgesTrees[i].x);
		}
	}

public:

	void DFS(int u,int p){
		visited[u]=true;
		discovered[dfs_timer]=u;
		beginTime[u]=dfs_timer;
		sizeSubTree[u]=1;
		level1[u]=level1[p]+1;
		P[u][0]=p;
		dfs_timer++;
		For(i,1,35){
			P[u][i]=P[P[u][i-1]][i-1];
		}

		rep(v,Adj[u]){
			if(!visited[v] && v!=p){
				DFS(v,u);
				sizeSubTree[u]+=sizeSubTree[v];
			}
		}
		endTime[u]=beginTime[u]+sizeSubTree[u]-1;
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

	void makeAuxilliaryTree(vi &_nodes){
		vector<pii> v1;
		vector<pii> v2;
		rep(u,_nodes){
			v1.pb(mp(beginTime[v],v));
		}
		sort(all(v1));
		set<int> setNodes;
		For(i,0,_nodes.size()-1){
			setNodes.insert(LCA(v1[i].y,v1[i+1].y));
		}
		rep(u,setNodes){
			v2.pb(mp(beginTime[u],u));
		}
		sort(all(v2));
		stack<int> stackNodes;
		assert(!v2.empty());
		stackNodes.push(v2[0].y);
		For(i,1,v2.size()){
			while(!(beginTime[stackNodes.top()]<=beginTime[v2[i].y] && end1[stackNodes.top()]>=end1[v2[i].y])){
				stackNodes.pop();
			}
			tree[stackNodes.top()].insert(v2[i].y);
			tree[v2[i].y].insert(stackNodes.top());
			stackNodes.push(v2[i].y);
		}
		// We have the auxilliary tree in vector<set<int> > tree and the 
		// list of nodes in stackNodes.
	}
}
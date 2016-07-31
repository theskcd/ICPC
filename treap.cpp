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
#define N 100100
#define M 300001
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

struct item{
	int c;
	int q;

	item(){};

	item(int _c,int _q){
		c=_c;
		q=_q;
	};

	bool operator<(const item &other) const{
		if(q!=other.q){
			return q>other.q;
		}
		return c<other.c;
	}
};

int ans[200010];

struct node{
	node *left;
	node *right;
	unsigned int pri;
	int val,lazyVal;
	int sum,lazySum;
	int i;
};

unsigned int genPri(){
	unsigned int x=rand();
	unsigned int y=rand();
	return (x<<16)|y;
}

node *reassign(node *n,node *l,node *r,unsigned int pri,int val,int sum,int i){
	n->left=l;
	n->right=r;
	n->pri=pri;
	n->val=val;
	n->sum=sum;
	n->i=i;
	n->lazySum=0;
	n->lazyVal=0;
	return n;
}

node *reassign(node *n,node *l,node *r){
	return reassign(n,l,r,n->pri,n->val,n->sum,n->i);
}

void apply(node *n,int lazyVal,int lazySum){
	n->val+=lazyVal;
	n->sum+=lazySum;
	n->lazySum+=lazySum;
	n->lazyVal+=lazyVal;
}

void down(node *n){
	if(n->left){
		apply(n->left,n->lazyVal,n->lazySum);
	}
	if(n->right){
		apply(n->right,n->lazyVal,n->lazySum);
	}
	n->lazyVal=0;
	n->lazySum=0;
}

node *getLeft(node *n){
	while(n->left){
		down(n);
		n=n->left;
	}
	return n;
}

node *getRight(node *n){
	while(n->right){
		down(n);
		n=n->right;
	}
	return n;
}

//{<,>=}
pair<node *,node *> split(node *n,int k){
	if(!n){
		return {nullptr,nullptr};
	}
	down(n);
	node *l;
	node *r;
	if(n->val<k){
		tie(l,r)=split(n->right,k);
		reassign(n,n->left,l);
		return {n,r};
	}
	tie(l,r)=split(n->left,k);
	reassign(n,r,n->right);
	return {l,n};
}

node *merge(node *l,node *r){
	if(!l){
		return r;
	}
	if(!r){
		return l;
	}
	down(l);
	down(r);
	if(l->pri<r->pri){
		return reassign(l,l->left,merge(l->right,r));
	}
	else{
		return reassign(r,merge(l,r->left),r->right);
	}
}

node *ins(node *root,node *n){
	node *l,*r;
	tie(l,r)=split(root,n->val);
	return merge(l,merge(n,r));
}

void traverse(node *n){
	if(!n){
		return ;
	}
	down(n);
	ans[n->i]=n->sum;
	traverse(n->left);
	traverse(n->right);
}

vector<item> listItems;

int main(){
	int n,m;
	scanf("%d",&n);

	For(i,0,n){
		int c,q;
		scanf("%d%d",&c,&q);
		item newItem(c,q);
		listItems.pb(newItem);
	}
	
	sort(all(listItems));

	node *root=nullptr;
	scanf("%d",&m);

	For(i,0,m){
		int temp;
		scanf("%d",&temp);
		node *newNode=reassign(new node(),nullptr,nullptr,genPri(),temp,0,i);
		if(!root){
			root=newNode;
		}
		else{
			root=ins(root,newNode);
		}
	}

	For(i,0,n){
		// error(i);
		int c=listItems[i].c;
		node *l,*r;
		tie(l,r)=split(root,c);
		if(!r){
			continue;
		}
		apply(r,-c,1);
		if(!l){
			root=r;
			continue;
		}
		node *rl=getLeft(r);
		node *lr=getRight(l);
		while(rl->val<lr->val){
			node *tl,*tr;
			tie(tl,tr)=split(r,rl->val+1);
			l=ins(l,tl);
			r=tr;
			if(!l || !r){
				break;
			}
			rl=getLeft(r);
			lr=getRight(l);
		}
		root=merge(l,r);
	}
	traverse(root);

	For(i,0,m){
		printf("%d ",ans[i]);
	}
	printf("\n");
return 0;}
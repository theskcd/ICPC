#include <bits/stdc++.h>

using namespace std;

struct node1 {
    int val;
    int lazyp;
};

node1 tree[8*35010];
int a[35010];
int dp[35010][51];
int prev1[35010];
int lastFound[35010];
int n, k;

void refresh(int node, int b, int e) {
    if (b>e) {
        return ;
    }
    if (b==e) {
        tree[node].val = 0;
        tree[node].lazyp = 0;
        return ;
    }
    refresh(2*node, (b+e)/2+1, e);
    refresh(2*node + 1, b, (b+e)/2);
    tree[node].val = tree[node].lazyp = 0;
    return;
}

void build(int node, int b, int e, int limit) {
    if (b>e) {
        return;
    }
    // printf("--%d %d\n", b, e);
    if (b==e) {
        tree[node].val = dp[b][limit-1];
        tree[node].lazyp = 0;
        return;
    }
    build(2*node, b, (b+e)/2, limit);
    build(2*node+1, (b+e)/2+1, e, limit);
    tree[node].val = max(tree[2*node].val, tree[2*node+1].val);
    tree[node].lazyp = 0;
    // printf("build %d %d %d\n", b, e, tree[node].val);
    return;
}

void push(int node) {
    if (tree[node].lazyp != 0) {
        tree[node].val += tree[node].lazyp;
        tree[2*node].lazyp += tree[node].lazyp;
        tree[2*node + 1].lazyp += tree[node].lazyp;
        tree[node].lazyp = 0;
    }
} 

void update(int node, int b, int e, int i, int j) {
    push(node);
    if (b>e || i>e || j<b) {
        return;
    }
    if (i<= b && j>=e) {
        // printf("updating %d %d\n", b, e);
        // printf("updating %d %d", b, e);
        tree[node].val ++;
        if (b != e) {
            tree[2*node].lazyp ++;
            tree[2*node+1].lazyp ++;
        }
        return;
    }
    else {
        update(2*node, b, (b+e)/2, i, j);
        update(2*node+1, (b+e)/2+1, e, i,j);
        tree[node].val = max(tree[2*node].val, tree[2*node+1].val);
    }
    return;
}

int query(int node, int b, int e, int i, int j) {
    push(node);
    if (b>e || i>e || j<b) {
        return 0;
    }
    if (i<= b && j>=e) {
        return tree[node].val;
    } else {
        int l1= query(2*node, b, (b+e)/2, i, j); 
        int l2= query(2*node+1, (b+e)/2+1, e, i, j);
        return max(l1, l2);
    }
}

void solve(int limit) {
    refresh(1, 0, n-1);
    build(1, 0, n-1, limit);
    for(int i=0; i<n; i++) {
        // if (i+1 <= limit) {
        //     dp[i][limit] = i+1;
        //     update(1, 0, n-1, prev1[i]+1, i);
        // } else {
        //     update(1, 0, n-1, prev1[i]+1, i);        
        //     dp[i][limit] = query(1, 0, n-1, 0, i);
        //     if (limit != 0) {
        //         dp[i][limit] = max(dp[i][limit], dp[i][limit-1]);
        //     }
        // }
        if (prev1[i] < i) {
            // printf("%d %d %d\n", prev1[i], i, limit);
            update(1 , 0, n-1, prev1[i], i-1);
        }
        dp[i][limit] = max(dp[i][limit-1], query(1, 0, n-1, 0, i));
        // printf("--%d %d\n", i, dp[i][limit]);
        // printf("%d %d %d\n", i, limit, dp[i][limit]);
    }
}

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 0; i<n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i= 0; i<=n; i++) {
        prev1[i] = -1;
        lastFound[i] = -1;
    }
    for (int i=0;i<n;i++) {
        prev1[i] = lastFound[a[i]];
        if (prev1[i] == -1) {
            prev1[i] = 0;
        }
        lastFound[a[i]] = i;
        // printf("prev %d %d\n", i, prev1[i]);
    }
    set<int> s1;
    for (int i=0;i < n;i++) {
        s1.insert(a[i]);
        dp[i][1] = s1.size();
        // printf("%d %d\n", i, dp[i][1]);
    }
    for (int i=2;i<=k;i++) {
        solve(i);
    }
    printf("%d\n", dp[n-1][k]);
}
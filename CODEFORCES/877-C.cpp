#include <bits/stdc++.h>

using namespace std;

map<pair<int,int>, int> mapPoints;
map<int, set<int>> mapx;
map<int, set<int>> mapy;
vector<pair<int,int>> points;
vector<int> Adj[100010];
set<int> distinctX;
set<int> distinctY;
bool inStack[100010];
bool visited[100010];
bool hasCycle = false;
long long int answer1 = 1LL;
long long int mod = 10e9+7;

void DFS(int u, int p) {
    printf("point => %d %d \n", points[u].first, points[u].second);
    inStack[u] = true;
    visited[u] = true;
    distinctX.insert(points[u].first);
    distinctY.insert(points[u].second);
    for (auto v: Adj[u]) {
        if (!visited[v]) {
            DFS(v, u);
        }
        if (inStack[v]) {
            hasCycle = true;
        }
    }
    inStack[u] = false;
}

long long int pow(int e) {
    if (e == 0) {
        return 1LL;
    }
    if (e == 1) {
        return 2LL;
    }
    else {
        long long int p1 = pow(e/2);
        p1 = (p1*p1)%mod;
        if (e%2 == 1) {
            p1 = (p1*2)%mod;
        }
        return p1;
    } 
}

int main() {
    int n;
    scanf("%d", &n);

    for(int i=0; i<n; i++) {
        int x1, y1;
        scanf("%d%d", &x1, &y1);
        mapPoints[make_pair(x1, y1)] = i;
        mapx[x1].insert(y1);
        mapy[y1].insert(x1);
        points.push_back(make_pair(x1, y1));
    }

    for (auto point: points) {
        set<int>::iterator t1 = mapx[point.first].lower_bound(point.second);
        set<int>::iterator t2 = mapy[point.second].lower_bound(point.first);
        // check above
        printf("searching for points %d %d\n", mapx[point.first].size(), mapy[point.second].size());
        t1--;
        if (t1 != mapx[point.first].begin()) {
            printf("found x1");
            int nextY = *(t1);
            Adj[mapPoints[point]].push_back(mapPoints[make_pair(point.first, nextY)]);
            Adj[mapPoints[make_pair(point.first, nextY)]].push_back(mapPoints[point]);            
            printf("%d %d\n", mapPoints[point], mapPoints[make_pair(point.first, nextY)]);            
        }
        // check below
        t1 = mapx[point.first].upper_bound(point.second);
        // t1++;
        if (t1 != mapx[point.first].end()) {
            int nextY = *(t1);
            printf("found x2");
            Adj[mapPoints[make_pair(point.first, nextY)]].push_back(mapPoints[point]);
            Adj[mapPoints[point]].push_back(mapPoints[make_pair(point.first, nextY)]);
            printf("%d %d\n", mapPoints[point], mapPoints[make_pair(point.first, nextY)]);
        }
        // check left
        t2--;
        if (t2 != mapy[point.second].begin()) {
            int nextX = *(t2);
            printf("found y1");
            Adj[mapPoints[point]].push_back(mapPoints[make_pair(nextX, point.second)]);
            Adj[mapPoints[make_pair(nextX, point.second)]].push_back(mapPoints[point]);
            printf("%d %d\n", mapPoints[point], mapPoints[make_pair(nextX, point.second)]);
        }
        // check right
        t2 = mapy[point.second].upper_bound(point.first);
        // t2++;
        if (t2 != mapy[point.second].end()) {
            int nextX = *(t2);
            printf("found y2");
            Adj[mapPoints[point]].push_back(mapPoints[make_pair(nextX, point.second)]);
            Adj[mapPoints[make_pair(nextX, point.second)]].push_back(mapPoints[point]);
            printf("%d %d\n", mapPoints[point], mapPoints[make_pair(nextX, point.second)]);
        }
        printf("\n");
    }

    for (int i=0; i<n; i++) {
        for (auto v: Adj[i]) {
            printf("%d %d\n", i, v);
        }
    }

    for(int i=0; i<n; i++) {
        if (!visited[i]) {
            DFS(i, -1);
            int x1 = (int)distinctX.size();
            int y1 = (int)distinctY.size();
            printf("===%d %d %d\n", x1, y1, hasCycle);
            if (hasCycle) {
                answer1 = (answer1 * pow(x1+y1))%mod;
            } else {
                answer1 = (answer1 * ((pow(x1+y1)-1)%mod+mod)%mod)%mod;
            }
            hasCycle = false;
            distinctX.clear();
            distinctY.clear();
        }
    }

    printf("%lld\n", answer1);
return 0;}
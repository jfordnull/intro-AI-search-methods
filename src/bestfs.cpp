#include "bestfs.h"
#include "heuristic.h"

pair<vector<int>,int> bestFS(const vector<vector<int>>& adjList, const vector<pair<float,float>>& coordinates, int src, int dest){
    vector<bool> visited(adjList.size(),false);
    vector<int> parent(adjList.size(),-1);
    vector<float> heuristics = generateHeuristics(coordinates, dest);
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push({src, heuristics[src]});
    
    auto start = high_resolution_clock::now();
    while(!pq.empty()){
        Node currentNode = pq.top();
        pq.pop();
        int u = currentNode.vertex; 

        // Solution found, reconstruct path
        if(u == dest){
            vector<int> path;
            for(int i = dest; i != -1; i = parent[i]) path.push_back(i);
            reverse(path.begin(), path.end());
            auto end = high_resolution_clock::now();
            int delta = duration_cast<microseconds>(end - start).count();
            return{path, delta};
        }

        if(visited[u]) continue;
        visited[u] = true;

        // Explore neighbors
        for(int neighbor : adjList[u]){
            if(!visited[neighbor]){
                pq.push({neighbor, heuristics[neighbor]});
                parent[neighbor] = u;
            }
        }
    }
    return{{},-1};
}
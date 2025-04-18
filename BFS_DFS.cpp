#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;

void DFS(int v) {
    visited[v] = true;
    cout << v << " ";
    for (int u : adj[v]) {
        if (!visited[u])
            DFS(u);
    }
}

void BFS(int start) {
    queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        cout << v << " ";
        for (int u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
}

int main() {
    int V = 7;
    adj.resize(V);

    // Add edges (undirected)
    adj[0] = {1, 2, 3};
    adj[1] = {0, 3};
    adj[2] = {0, 6};
    adj[3] = {0, 1, 4};
    adj[4] = {3, 5};
    adj[5] = {4};
    adj[6] = {2};

    int choice;
    cout << "Enter 0 for DFS or 1 for BFS: ";
    cin >> choice;

    visited.assign(V, false);
    if (choice == 0) {
        cout << "DFS Traversal: ";
        DFS(0);
    } else {
        cout << "BFS Traversal: ";
        BFS(0);
    }
    cout << endl;
    return 0;
}

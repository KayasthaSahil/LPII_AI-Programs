#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Graph class
class Graph {
    int V;                     // Number of vertices
    vector<vector<int>> adj;    // Adjacency list

public:
    Graph(int V);               // Constructor
    void addEdge(int v, int w); // Function to add an edge
    void DFS(int start);        // Function to perform DFS
    void BFS(int start);        // Function to perform BFS
    void DFSUtil(int v, vector<bool> &visited); // Recursive DFS utility function
    void inputGraph();          // Function to take input from user
};

// Constructor
Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}

// Function to add an edge to the graph
void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v); // Since it's an undirected graph
}

// Recursive DFS function
void Graph::DFSUtil(int v, vector<bool> &visited) {
    visited[v] = true;
    cout << v << " ";

    for (int i : adj[v]) {
        if (!visited[i])
            DFSUtil(i, visited);
    }
}

// DFS traversal function
void Graph::DFS(int start) {
    vector<bool> visited(V, false);
    cout << "DFS Traversal: ";
    DFSUtil(start, visited);
    cout << endl;
}

// BFS traversal function
void Graph::BFS(int start) {
    vector<bool> visited(V, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "BFS Traversal: ";
    while (!q.empty()) {
        int v = q.front();
        cout << v << " ";
        q.pop();

        for (int i : adj[v]) {
            if (!visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}

// Function to take user input for the graph
void Graph::inputGraph() {
    int edges, v, w;
    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter " << edges << " edges (vertex1 vertex2):\n";
    for (int i = 0; i < edges; i++) {
        cin >> v >> w;
        addEdge(v, w);
    }
}

// Main function
int main() {
    int V, start;
    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);
    g.inputGraph();

    cout << "Enter starting vertex for traversal: ";
    cin >> start;

    g.DFS(start);
    g.BFS(start);

    return 0;
}

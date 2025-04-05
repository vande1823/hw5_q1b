#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm> // For reverse function

using namespace std;

// Function to implement Dijkstra's algorithm
void dijkstra(const unordered_map<char, unordered_map<char, int>>& graph, char source) {
    unordered_map<char, int> distances; // Distance vector
    unordered_map<char, int> cost_vector; // Cost vector
    unordered_map<char, char> parents; // Parent tracking for paths
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;

    // Initialize distances and cost vector
    for (const auto& node : graph) {
        distances[node.first] = INT_MAX;
        cost_vector[node.first] = INT_MAX;
    }
    distances[source] = 0;
    cost_vector[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int current_distance = pq.top().first;
        char current_node = pq.top().second;
        pq.pop();

        // Skip outdated entries in the priority queue
        if (current_distance > distances[current_node]) continue;

        for (const auto& neighbor : graph.at(current_node)) {
            int new_distance = current_distance + neighbor.second;

            if (new_distance < distances[neighbor.first]) {
                distances[neighbor.first] = new_distance;
                cost_vector[neighbor.first] = new_distance;
                parents[neighbor.first] = current_node;
                pq.push({new_distance, neighbor.first});
            }
        }
    }

    // Print the distance vector
    cout << "Distance Vector:\n";
    for (const auto& pair : distances) {
        cout << "Node " << pair.first << ": " << pair.second << endl;
    }

    // Print the cost vector
    cout << "\nCost Vector:\n";
    for (const auto& pair : cost_vector) {
        cout << "Node " << pair.first << ": " << pair.second << endl;
    }

    // Print shortest-path tree
    cout << "\nShortest-path tree:\n";
    for (const auto& pair : distances) {
        if (pair.first != source && pair.second != INT_MAX) {
            vector<char> path;
            char current = pair.first;
            while (current != source) {
                path.push_back(current);
                current = parents[current];
            }
            path.push_back(source);
            reverse(path.begin(), path.end());
            cout << "Node " << pair.first << ": Path = ";
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i < path.size() - 1) cout << " -> ";
            }
            cout << ", Distance = " << pair.second << endl;
        }
    }
}

int main() {
    // Define the graph (based on Figure 2)
    unordered_map<char, unordered_map<char, int>> graph = {
            {'A', {{'B', 10}, {'E', 5}}},
            {'B', {{'C', 1}, {'E', 3}}},
            {'C', {{'D', 4}, {'E', 6}}},
            {'D', {{'E', 2}}},
            {'E', {{'B', 2}, {'C', 9}, {'D', 7}}}
    };

    // Compute shortest-path tree rooted at node A
    dijkstra(graph, 'A');

    return 0;
}
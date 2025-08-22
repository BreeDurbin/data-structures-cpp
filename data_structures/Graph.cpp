class Graph {
    unordered_map<string, vector<pair<string, double>>> adj_list;

public:
    Graph(vector<vector<string>>& vertices, vector<double>& edges) {
        int n = vertices.size();
        for(int i=0; i<n; i++){
            adj_list[vertices[i][0]].push_back(make_pair(vertices[i][1], edges[i]));
            adj_list[vertices[i][1]].push_back(make_pair(vertices[i][0], edges[i]));
        }
    }

    double traverse(string start, string end){
        unordered_map<string, bool> visited;
        dfs(start, end, visited);
    }

private:
    double dfs(string start, string end, unordered_map<string, bool> &visited){
        //not found
        if(!adj_list[start].size() || visited[start]) return -1.0;
        //set visited
        visited[start] = true;
        //dfs all adjacent nodes
        for(int i=0; i<adj_list[start].size(); i++){
            pair<string, double> next_node = adj_list[start][i];
            // found
            if(next_node.first == end) return next_node.second;
            // dig deeper
            double result = dfs(next_node.first, end, visited);
            // recursive dfs found the node
            if(result != -1.0) return next_node.second + result;
        }
        return -1;
        
    }
};
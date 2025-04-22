#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;



struct Edge{
    int u;
    int v;
    int weight;
    bool chosen;
}; // define a new type to store the edge information

//using sorttool from PA1
class SortTool {
public:
    void QuickSort(vector<Edge>& data) {
        QuickSortSubVector(data, 0, data.size() - 1);
    }

    void QucikSort_directed(vector <int> &data,vector <int> finish_time){
        QuickSortSubVector_directed(data, finish_time, 0, data.size() - 1);
    }

private:
    void QuickSortSubVector(vector<Edge>& data, int low, int high) {
        if (low < high) {
            int q = RandomizedPartition(data, low, high);
            QuickSortSubVector(data, low, q - 1);
            QuickSortSubVector(data, q + 1, high);
        }
    }

    int Partition(vector<Edge>& data, int low, int high) {
        int pivot = data[high].weight; // Use weight as the pivot, data[] is the pair 
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (data[j].weight <= pivot) { // Compare weights
                i++;
                swap(data[i], data[j]);
            }
        }
        swap(data[i + 1], data[high]);
        return i + 1;
    }

    int RandomizedPartition(vector<Edge>& data, int low, int high) {
        int i = low + rand() % (high - low + 1);
        swap(data[i], data[high]);
        return Partition(data, low, high);
    }



    void QuickSortSubVector_directed(vector <int> &data, vector <int> finish_time, int low, int high) {
        if (low < high) {
            int q = RandomizedPartition_directed(data,finish_time,  low, high);
            QuickSortSubVector_directed(data, finish_time,low, q - 1);
            QuickSortSubVector_directed(data, finish_time,q + 1, high);
        }
    }

    int Partition_directed(vector <int> &data,vector <int> finish_time, int low, int high) {
        int pivot = finish_time[data[high]]; // Use weight as the pivot, data[] is the pair 
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (finish_time[data[j]] <= pivot) { // Compare weights
                i++;
                swap(data[i], data[j]);
            }
        }
        swap(data[i + 1], data[high]);
        return i + 1;
    }

    int RandomizedPartition_directed(vector <int> &data, vector <int> finish_time, int low, int high) {
        int i = low + rand() % (high - low + 1);
        swap(data[i], data[high]);
        return Partition_directed(data, finish_time, low, high);
    }
};
//using sorttool from PA1

// AI generated begin
class DisjointSet {
private:
    vector<int> parent;  // Stores the parent of each element
    vector<int> rank;    // Stores the rank (depth) of each tree

public:
    // Constructor to initialize the disjoint set for 'n' elements
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;  // Each element is its own parent initially
        }
    }

    // FIND-SET: Find the leader (representative) of the set containing x
    int findSet(int x) {
        if (parent[x] != x) {
            parent[x] = findSet(parent[x]);  // Path compression
        }
        return parent[x];
    }
    void link(int x, int y){
        if(rank[x]>rank[y]){
            parent[y] = x;
        }
        else{
            parent[x] = y;
            if(rank[x] == rank[y]){
                rank[y] = rank[y] + 1;
            }
        }
    }
    // UNION: Union of sets containing x and y
    void unionSets(int x, int y) {
        int X = findSet(x);
        int Y = findSet(y);
        link(X, Y);
    }
};

// AI generated end

//to remove the minimum weight, --> maximum spanning tree, turn the weight to be negative??

// Ai generated begin, with a little modification on choosing order
void Kruskal(vector<Edge>& edge, int n, int m) {
    SortTool sortTool;
    sortTool.QuickSort(edge);// Sort edges by weight in non-decreasing order
    DisjointSet ds(n);
    int sum = 0;
    for (int i = m-1; i >=0 ; i--) { // 從最大的開始選 因為要一處最少的edge
        if (ds.findSet(edge[i].u) != ds.findSet(edge[i].v)) {
            ds.unionSets(edge[i].u, edge[i].v);
            sum += edge[i].weight;
            edge[i].chosen = true;
        }
    }

}

// AI generated end


//AI generated begin
void DFS_visit(vector<vector<pair<int, int>>> &Adj_list, vector<int> &color, vector<int> &parent, vector<int> &start_time, vector<int> &finish_time, int u, bool &cycle, int &time_counter){
    
    color[u] = 1;
    time_counter++;
    start_time[u] = time_counter;
    for(int i=0; i<Adj_list[u].size(); i++){
        int v = Adj_list[u][i].first;
        if(color[v] == 0){
            parent[v] = u;
            DFS_visit(Adj_list, color, parent, start_time, finish_time, v, cycle, time_counter);
        }
//Ai generated end
        if(color[v] == 1){
            cycle = true;
            
        }
    }
    color[u] = 2;
    time_counter++;
    finish_time[u] = time_counter;
}

void DFS(vector<vector<pair<int, int>>> &Adj_list, vector<int> &color, vector<int> &parent, vector<int> &start_time, vector<int> &finish_time, bool &cycle, int &time_counter){
    for(int i=0; i<Adj_list.size(); i++){
        if(color[i] == 0){
            parent[i] = -1;
            DFS_visit(Adj_list, color, parent, start_time, finish_time, i, cycle, time_counter);
        }
    }


}





int main(int argc, char* argv[]){
//AI generated begin
    if (argc != 3){
        cout << "usage: ./cb <input file name> <output file name>" << endl;
        return 1;
    }
    char buffer[200];
    fstream fin(argv[1], ios::in);
    fstream fout;
    fout.open(argv[2],ios::out);
    char c;
    int n, m;
    fin >> c;
    fin >> n >> m;
    int end;
    vector < Edge > edge;
    if(c == 'u'){
        for(int i = 0; i<m; i++){
            int a, b, w;
            fin >> a >> b >> w;
            edge.push_back({a, b, w, false});
        }
        fin >> end;
        
//AI generated end

        Kruskal(edge, n, m);
        int total_removed_weight = 0;
        for(int i=0 ;i<m ;i++){
            if(edge[i].chosen == false){
                total_removed_weight += edge[i].weight;
            }
        }
        fout << total_removed_weight << endl;

        for(int i=0 ;i<m ;i++){
            if(edge[i].chosen == false){
                fout << edge[i].u << " " << edge[i].v << " " << edge[i].weight << endl;
            }

        }
    }


    else if(c == 'd'){
        
        //AI generated begin
        vector<vector<pair<int, int>>> Adj_list(n); // Adjacency list
        vector<int> color(n, 0); // 0: White, 1: Gray, 2: Black
        vector<int> parent(n, -1); // Parent array
        vector<int> start_time(n, 0); // Start time of each vertex
        vector<int> finish_time(n, 0); // Finish time of each vertex
        //AI generated end

        for(int i = 0; i<m; i++){
            int a, b, w;
            fin >> a >> b >> w;
            edge.push_back({a, b, w, false});
            

        }
        fin >> end;

        Kruskal(edge, n, m);
        int total_removed_weight = 0;
        for(int i=0 ;i<m ;i++){
            if(edge[i].chosen == false){
                total_removed_weight += edge[i].weight;
            }
        }

        //don't add negative edge to the maximum spanning tree, add the biggest edge to the maximum spanning tree and see if there is a cycle, 
                //until add all
        
        for(int i=0; i<m; i++){
            if(edge[i].chosen == true){
                Adj_list[edge[i].u].push_back({edge[i].v, edge[i].weight});
            }
        }

        for(int i=m-1; i>=0; i--){
            if(edge[i].weight < 0){
                break;
            }
            
            //add the edge that is not choose to the mximum spanning tree, and see if there is a cycle
            if(edge[i].chosen == false){
                //with AI help
                Adj_list[edge[i].u].push_back({edge[i].v, edge[i].weight});
                //AI generated begin
                fill(color.begin(), color.end(), 0);
                fill(parent.begin(), parent.end(), -1);
                fill(start_time.begin(), start_time.end(), 0);
                fill(finish_time.begin(), finish_time.end(), 0);

                bool cycle = false;
                int time_counter = 0;
                //AI generated end
                DFS(Adj_list, color, parent, start_time, finish_time, cycle, time_counter);
                if(cycle == true){
                    edge[i].chosen = false;
                    Adj_list[edge[i].u].pop_back();
                }
                else{
                    edge[i].chosen = true;
                    total_removed_weight -= edge[i].weight;
                }
                //with AI help
            }
            


            
        } 

        fout << total_removed_weight << endl;
        for(int i=0; i<m; i++){
            if(edge[i].chosen == false){
                fout << edge[i].u << " " << edge[i].v << " " << edge[i].weight << endl;
            }
        }

    }

    
    return 0;



}


#include <tsm.h>

struct node{
    int weight;
    bool visited;
    int pre_vertex;
    
    bool* visitedNode;

    node() {
        weight = INT_MAX;
        visited = false;
        pre_vertex = -1;
        visitedNode = NULL;
    }
    node(int size){
        weight = INT_MAX;
        visited = false;
        pre_vertex = -1;
        visitedNode = new bool[size];
        for (int i = 0; i < size; i++) visitedNode[i] = false;
    }
};

string Traveling(int weight_matrix[20][20], int num_vertices, char start_char){

    class TSP{
        private:
        int graphSize;
        int start;
        int graph[20][20];
        int* path;
        bool done;
        int min_cost = INT_MAX;

        node** saveStatus;

        public:
        TSP(int weight_matrix[20][20], int size, char start_char) : graphSize(size) {
            start = start_char - 'A';
            done = false;
            for (int i = 0; i < graphSize; i++){
                for (int j = 0; j < graphSize; j++) {
                    graph[i][j] = weight_matrix[i][j];
                    if(graph[i][j] == 0) graph[i][j] = 9999999;
                    }
            }
            saveStatus = new node*[graphSize];
            for (int i = 0; i < graphSize; i++){
                int k = 1;
                for (int j = 0; j < graphSize; j++) k = k * 2;
                saveStatus[i] = new node[k];
                for (int j = 0; j < k; j++) saveStatus[i][j] = node(graphSize);
            }
            path = new int[graphSize + 1];
        }

        ~TSP() {
            for (int i = 0; i < graphSize; i++) delete[] saveStatus[i];
            delete[] saveStatus;
            delete[] path;
        }

        void execute() {
            bool* visited = new bool[graphSize];
            for (int i = 0; i < graphSize; ++i) visited[i] = false;
            visited[start] = true;
            min_cost = recursionTSP(start, visited);

            int i = start, t = 0;
            while(true) {
                path[t++] = i;
                int next_i = saveStatus[i][convertBit(visited)].pre_vertex;
                if(next_i == -1) break;
                visited[next_i] = true;
                i = next_i;
            }
            path[t] = start;
            done = true;
            delete[] visited;
        }

        bool checkVisited(bool* visited) {
            for(int i = 0; i < graphSize; i++){
                if(visited[i] == false) return false;
            }
            return true;
        }

        int recursionTSP(int vertex, bool* visited) {
            int pos = convertBit(visited);
            if (checkVisited(visited) == true) return graph[vertex][start];
            if (saveStatus[vertex][pos].visited == true) return saveStatus[vertex][pos].weight;

            int min = INT_MAX;
            int index = -1;
            for (int j = 0; j < graphSize; j++){
                if (visited[j] == true) continue;
                visited[j] = true;
                int temp = graph[vertex][j] + recursionTSP(j, visited);
                visited[j] = false;
                if (temp < min){
                    min = temp;
                    index = j;
                } 
            }

            saveStatus[vertex][pos].visited = true;
            saveStatus[vertex][pos].weight = min;
            saveStatus[vertex][pos].pre_vertex = index;
            copy(saveStatus[index][pos].visitedNode, visited);

            return min;
        }

        void copy(bool* t1, bool* t2) {
            for (int i = 0; i < graphSize; ++i) t1[i] = t2[i];
        }

        int convertBit(bool* visited) {
            int pos = 0;
            int k = 1;
            for (int i = 0; i < graphSize; ++i) {
                if (visited[i]) pos = pos + k;
                k = k * 2;
            }
            return pos;
        }

        int* getPath() {
            if(done == false) execute();
            return path;
        }
    };

    TSP tsm(weight_matrix, num_vertices, start_char);
    int* circuit = tsm.getPath();
    string str = "";
    
    for (int i = 0; i <= num_vertices; i++){
        char temp = char(circuit[i] + 'A');
        str = str + temp + " ";
    }
    return str;
}
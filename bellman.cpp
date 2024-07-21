#include "bellman.h"

void assignArray(int t[], const int arr[], int size) {
    for (int i = 0; i < size; i++) t[i] = arr[i];
}
bool compareArray(int arr1[], int arr2[], int size){
    for (int i = 0; i < size; i++){
        if (arr1[i] != arr2[i]) return false;
    }
    return true;
}
bool checkFirstArray(int arr[20], int n){
    for (int i = 0; i < n; i++){
        if(arr[i] != -1) return false;
    }
    return true;
}
void BF(int weight_matrix[20][20], int num_vertices, char start_char, int cur_value[20], int cur_pre[20]) {
    int start = start_char - 'A';
    if (checkFirstArray(cur_value, num_vertices) == true){
        for (int i = 0; i < num_vertices; i++){
            if(weight_matrix[start][i] != 0){
            cur_value[i] = weight_matrix[start][i];
            cur_pre[i] = start;
            }
        }
        cur_value[start] = 0;
        cur_pre[start] = -1;
        return;
    }
    int temp_value[num_vertices];
    assignArray(temp_value, cur_value, num_vertices);

    for (int i = 0; i < num_vertices; i++) {
        if (cur_value[i] != -1){
        for (int j = 0; j < num_vertices; j++) {
            if(i == j || weight_matrix[i][j] == 0) continue;
            if (temp_value[j] > cur_value[i] + weight_matrix[i][j] || temp_value[j] == -1) {
                temp_value[j] = cur_value[i] + weight_matrix[i][j];
                cur_pre[j] = i;
            }
        }
        }
    }

    if(!compareArray(temp_value, cur_value, num_vertices)) {
        assignArray(cur_value, temp_value, num_vertices);
    }
}

string BF_Path(int weight_matrix[20][20], int num_vertices, char start_char, char goal_char) {
    int start = start_char - 'A', goal = goal_char - 'A';
    int cur_pre[num_vertices], cur_value[num_vertices];
    for (int i = 0; i < num_vertices; i++) {
        cur_pre[i] = -1;
        cur_value[i] = -1;
    }
    for(int i = 0; i < num_vertices - 1; i++) BF(weight_matrix, num_vertices, start_char, cur_value, cur_pre);

    string str_path = "";
    int count = 0;
    if(cur_value[goal] == -1) return str_path + goal_char;
    for (int i = goal; cur_pre[i] != -1; i = cur_pre[i]){
        char temp = char(i + 'A');
        str_path = " " + str_path;
        str_path = temp + str_path;
    }
    str_path = " " + str_path;
    str_path = start_char + str_path;
    return str_path;
}

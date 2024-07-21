
#ifndef _H_BELLMAN_H_
#define _H_BELLMAN_H_

#include <iostream>
#include <string>
#include <fstream>



using namespace std;

void BF(int weight_matrix[20][20], int num_vertices, char start_char, int cur_value[20], int cur_pre[20]);

string BF_Path(int weight_matrix[20][20], int num_vertices, char start_char, char goal_char);

#endif /* _H_BELLMAN_H_ */
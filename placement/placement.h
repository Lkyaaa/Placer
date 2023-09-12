#ifndef BUILD_PLACEMENT_PLACEMENT_H_
#define BUILD_PLACEMENT_PLACEMENT_H_

#include <iostream>
#include "../database/database.h"

void placement(InputDataBase &data_base, OutputDataBase &output_data_base);
void List_init(std::vector<List> &list_, InputDataBase &data_base);
void perm(std::vector<List> &list_,
          InputDataBase &data_base,
          int &min,
          std::vector<int> &result,
          std::vector<std::vector<int>> &adjMatrix);
void sort(int k, int *M);
bool ifover(int n, int *M, InputDataBase &data_base);
void swap(int &a, int &b);
void fullperm(int *a,
              int k,
              int m,
              InputDataBase &data_base,
              std::vector<List> &list_,
              int &min,
              std::vector<int> &result,
              std::vector<std::vector<int>> &adjMatrix);
int wirelength(List &l1, List &l2);
void adjMatrix_init(InputDataBase &data_base, std::vector<std::vector<int>> &adjMatrix);
bool check_x(int *a, std::vector<List> &List, int &col, int &inst_count);
bool check_y(int *a, std::vector<List> &List, int &col, int &inst_count);
bool cut_x(InputDataBase &data_base, int *a, std::vector<List> &List);
bool cut_y(InputDataBase &data_base, int *a, std::vector<List> &List);

#endif //BUILD_PLACEMENT_PLACEMENT_H_
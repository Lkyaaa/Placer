#include "placement.h"
#include <iostream>
#include "../database/database.h"
#include <algorithm>

void placement(InputDataBase &data_base, OutputDataBase &output_data_base) {
  int min = 10000;
  std::vector<std::vector<int>> adjMatrix;
  adjMatrix.resize(data_base.get_instance().inst_count, std::vector<int>(data_base.get_instance().inst_count, 0));
  std::vector<List> list_;
  list_.resize(data_base.get_instance().Col * data_base.get_instance().Row);
  std::vector<int> result;
  result.resize(data_base.get_instance().inst_count);

  adjMatrix_init(data_base, adjMatrix);
  List_init(list_, data_base);
  perm(list_, data_base, min, result, adjMatrix);

  std::cout << min << std::endl;
  for (int i = 0; i < data_base.get_instance().inst_count; i++) {

    std::cout << data_base.get_instance().v_inst[i] << ' ' << list_[result[i]].x << ' ' << list_[result[i]].y
              << std::endl;
  }

  output_data_base.get_consequence().v_inst.assign(data_base.get_instance().v_inst.begin(),
                                                   data_base.get_instance().v_inst.end());
  output_data_base.get_consequence().result.assign(result.begin(), result.end());

  output_data_base.get_consequence().list_.assign(list_.begin(), list_.end());

}

void List_init(std::vector<List> &list_, InputDataBase &data_base) {
  int size = 0;
  for (int i = 0; i < data_base.get_instance().Col; i++) {
    for (int j = 0; j < data_base.get_instance().Row; j++) {
      list_[size].x = i;
      list_[size].y = j;
      size++;
    }
  }
}

void perm(std::vector<List> &list_,
          InputDataBase &data_base,
          int &min,
          std::vector<int> &result,
          std::vector<std::vector<int>> &adjMatrix) {
  int M[data_base.get_instance().Row * data_base.get_instance().Col]{};
  int m[data_base.get_instance().Row * data_base.get_instance().Col];
  int a[data_base.get_instance().inst_count];
  for (int i = 0; i < data_base.get_instance().inst_count; i++)
    M[i] = 1;

  for (int i = 0; i < data_base.get_instance().Col * data_base.get_instance().Row; i++)
    m[i] = i;

  int j = 0;
  for (int i = 0; i < data_base.get_instance().Row * data_base.get_instance().Col; i++) {
    if (M[i]) {
      a[j] = m[i];
      j++;
    }
  }

  fullperm(a, 0, data_base.get_instance().inst_count - 1, data_base, list_, min, result, adjMatrix);

  for (int i = 0; i < data_base.get_instance().Col * data_base.get_instance().Row; i++) {
    if (M[i] == 1 && M[i + 1] == 0) {
      M[i] = 0;
      M[i + 1] = 1;
      sort(i, M);
      //for(int i=0;i<data_base.get_instance().Col*data_base.get_instance().Row;i++)
      //std::cout<<M[i];
      //std::cout<<std::endl;
      j = 0;
      for (int k = 0; k < data_base.get_instance().Col * data_base.get_instance().Row; k++) {
        if (M[k]) {
          a[j] = m[k];
          j++;
        }
      }
      //for(int l=0;l<data_base.get_instance().inst_count;l++)
      //   std::cout<<a[l];
      //std::cout<<std::endl;
      if (cut_x(data_base, a, list_) == 1 && cut_y(data_base, a, list_) == 1) {
        fullperm(a, 0, data_base.get_instance().inst_count - 1, data_base, list_, min, result, adjMatrix);
      }
      i = -1;
    }
    if (ifover(data_base.get_instance().inst_count, M, data_base))
      break;
  }

}

void sort(int k, int *M) {
  for (int i = k; i >= 0; i--) {
    for (int j = i - 1; j >= 0; j--) {
      if (M[i] > M[j]) {
        int tmp = M[i];
        M[i] = M[j];
        M[j] = tmp;

      }
    }
  }
}

bool ifover(int n, int *M, InputDataBase &data_base) {
  for (int i = data_base.get_instance().Row * data_base.get_instance().Col - n;
       i < data_base.get_instance().Row * data_base.get_instance().Col; i++) {
    if (M[i] == 0)
      return 0;
  }
  return 1;
}

void swap(int &a, int &b) {
  int tmp = a;
  a = b;
  b = tmp;

}

void fullperm(int *a,
              int k,
              int m,
              InputDataBase &data_base,
              std::vector<List> &list_,
              int &min,
              std::vector<int> &result,
              std::vector<std::vector<int>> &adjMatrix) {
  if (k == m) {

    int total = 0;
    //for (int i=0;i<=m;i++)
    //std::cout<<a[i];
    //std::cout<<std::endl;
    for (int i = 0; i < data_base.get_instance().inst_count; i++) {
      for (int j = 0; j < data_base.get_instance().inst_count; j++) {
        if (adjMatrix[i][j] != 0) {
          total += adjMatrix[i][j] * wirelength(list_[a[i]], list_[a[j]]);

        }

      }

    }

    if (min > total) {
      min = total;
      for (int i = 0; i < data_base.get_instance().inst_count; i++)
        result[i] = a[i];
    }

    total = 0;
  }
  for (int i = k; i <= m; i++) {
    swap(a[k], a[i]);
    fullperm(a, k + 1, m, data_base, list_, min, result, adjMatrix);
    swap(a[k], a[i]);
  }
}

int wirelength(List &l1, List &l2) {
  int length;
  length = (l1.x - l2.x) * (l1.x - l2.x) + (l1.y - l2.y) * (l1.y - l2.y);

  return length;

}

void adjMatrix_init(InputDataBase &data_base, std::vector<std::vector<int>> &adjMatrix) {
  for (int i = 0; i < data_base.get_instance().NumNets; i++) {
    for (int j = 0; j < data_base.get_instance().each_net_inst_count[i]; j++) {
      if (j != data_base.get_instance().each_net_inst_count[i] - 1) {
        auto iter1 = std::find(data_base.get_instance().v_inst.begin(),
                               data_base.get_instance().v_inst.end(),
                               data_base.get_instance().net[i][j]);
        size_t a = std::distance(data_base.get_instance().v_inst.begin(), iter1);
        auto iter2 = std::find(data_base.get_instance().v_inst.begin(),
                               data_base.get_instance().v_inst.end(),
                               data_base.get_instance().net[i][j + 1]);
        size_t b = std::distance(data_base.get_instance().v_inst.begin(), iter2);
        adjMatrix[a][b] += 1;
      }

    }
  }

}

bool check_x(int *a, std::vector<List> &List, int &cr, int &inst_count) {
  for (int i = 0; i < inst_count; i++) {
    if (List[a[i]].x == cr)
      return 1;
  }
  return 0;
}

bool check_y(int *a, std::vector<List> &List, int &cr, int &inst_count) {
  for (int i = 0; i < inst_count; i++) {
    if (List[a[i]].y == cr)
      return 1;
  }
  return 0;
}

bool cut_x(InputDataBase &data_base, int *a, std::vector<List> &List) {
  std::vector<int> nums;
  int count = 0;
  bool foundFirstOne = false;
  for (int i = 0; i < data_base.get_instance().Col; i++)
    nums.push_back(check_x(a, List, i, data_base.get_instance().inst_count));

  for (int num : nums) {
    if (num == 1) {
      if (!foundFirstOne) {
        foundFirstOne = true;
      } else {
        if (count > 0) {
          return 0;
        }
      }
      count = 0;
    } else if (foundFirstOne && num == 0) {
      count++;
    }
  }
  return 1;
}

bool cut_y(InputDataBase &data_base, int *a, std::vector<List> &List) {
  std::vector<int> nums;
  int state = 0;
  int count;
  bool foundFirstOne = false;
  for (int i = 0; i < data_base.get_instance().Row; i++)
    nums.push_back(check_y(a, List, i, data_base.get_instance().inst_count));
  for (int num : nums) {
    if (num == 1) {
      if (!foundFirstOne) {
        foundFirstOne = true;
      } else {
        if (count > 0) {
          return 0;
        }
      }
      count = 0;
    } else if (foundFirstOne && num == 0) {
      count++;
    }
  }
  return 1;
}
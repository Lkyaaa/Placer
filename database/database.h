#ifndef BUILD_DATABASE_DATABASE_H_
#define BUILD_DATABASE_DATABASE_H_

#include <string>
#include <vector>
#include <cstring>

typedef struct {
  int x;
  int y;
} List;

class InputDataBase {
 public:
  struct Instances {
    int inst_count{};
    int NumNets{};
    int Row{};
    int Col{};
    std::vector<std::string> v_inst{};
    std::vector<int> each_net_inst_count;
    std::vector<std::vector<std::string>> net{};

  };

  Instances &get_instance() {

    return instances_;

  }

 private:
  Instances instances_;

};

class OutputDataBase {
 public:
  struct Consequence {
    std::vector<std::string> v_inst{};
    std::vector<int> result{};
    std::vector<List> list_{};

  };

  Consequence &get_consequence() {

    return consequence_;

  }

 private:
  Consequence consequence_;

};

#endif //BUILD_DATABASE_DATABASE_H_
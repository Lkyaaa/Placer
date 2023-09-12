#ifndef BUILD_PARSER_PARSER_H_
#define BUILD_PARSER_PARSER_H_

#include "../database/database.h"
#include <fstream>
#include <iostream>

class Parser {
 public:
  explicit Parser(InputDataBase &data_base, const std::string &filename) :
      data_base_(data_base),
      filename_(filename),
      file_() {};

  void parse();

 private:
  InputDataBase &data_base_;
  std::string filename_;
  std::ifstream file_;

};
#endif //BUILD_PARSER_PARSER_H_
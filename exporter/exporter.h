#ifndef BUILD_EXPORTER_EXPORTER_H_
#define BUILD_EXPORTER_EXPORTER_H_

#include "../database/database.h"
#include <fstream>
#include <iostream>

class Exporter {
 public:
  explicit Exporter(OutputDataBase &data_base, std::string filename) :
      database_(data_base),
      filename_(std::move(filename)) {}

  void output() {
    return output_();

  };
 private:
  OutputDataBase &database_;
  std::string filename_;
  std::string output_path_;
  std::ofstream file_;

  void output_();

};

#endif //BUILD_EXPORTER_EXPORTER_H_

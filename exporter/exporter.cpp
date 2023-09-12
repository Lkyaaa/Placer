#include "exporter.h"

void Exporter::output_() {
  file_.open(filename_);
  if (!file_.is_open()) {
    std::cerr << "Failed to open file" << filename_ << std::endl;
    return;

  }

  for (int i = 0; i < database_.get_consequence().result.size(); i++)
    file_ << database_.get_consequence().v_inst[i] << ' '
          << database_.get_consequence().list_[database_.get_consequence().result[i]].x << ' '
          << database_.get_consequence().list_[database_.get_consequence().result[i]].y << std::endl;

  file_.close();

}
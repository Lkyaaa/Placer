void Parser::parse() {
  file_.open(filename_);
  if (!file_.is_open()) {
    std::cerr << "Failed to open file" << filename_ << std::endl;
    return;

  }
  std::string line;
  std::size_t pos = -1;
  while (getline(file_, line)) {
    pos = line.find("DieSize");
    if (pos != -1)
      break;

  }

  std::string sub1 = line.substr(8);
  std::stringstream s0(sub1);
  s0 >> data_base_.get_instance().Row;
  s0 >> data_base_.get_instance().Col;

  pos = -1;
  while (getline(file_, line)) {

    pos = line.find("NumInstances");
    if (pos != -1)
      break;

  }
  sub1 = line.substr(13);
  std::stringstream s1(sub1);
  s1 >> data_base_.get_instance().inst_count;

  for (int i = 0; i < data_base_.get_instance().inst_count; i++) {

    getline(file_, line);
    sub1 = line.substr(5);
    data_base_.get_instance().v_inst.push_back(sub1);

  }

  pos = -1;
  while (getline(file_, line)) {
    pos = line.find("NumNets");
    if (pos != -1)
      break;

  }

  sub1 = line.substr(8);
  std::stringstream s2(sub1);
  s2 >> data_base_.get_instance().NumNets;

  data_base_.get_instance().net.resize(data_base_.get_instance().NumNets);

  int j = 0;
  int size = 0;

  for (int k = 0; k < data_base_.get_instance().NumNets; k++) {
    getline(file_, line);

    for (int i = 0; i < sizeof(line); i++) {
      if (line[i] == ' ')
        j++;

      if (j == 2) {
        sub1 = line.substr(i + 1);
        std::stringstream s3(sub1);
        s3 >> size;

        data_base_.get_instance().each_net_inst_count.push_back(size);

        j = 0;
        size = 0;
        break;
      }

    }
    for (int i = 0; i < data_base_.get_instance().each_net_inst_count[k]; i++) {
      getline(file_, line);
      sub1 = line.substr(4);
      data_base_.get_instance().net[k].push_back(sub1);

    }

  }

  file_.close();

}
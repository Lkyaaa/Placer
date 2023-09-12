#include <iostream>
#include "database/database.h"
#include "placement/placement.h"
#include "parser/parser.h"
#include "exporter/exporter.h"
#include <tclap/CmdLine.h>

int main(int argc, char **argv) {
  std::string input_filename;
  std::string output_filename;
  try {
    TCLAP::CmdLine cmd("Commond line argument example", ' ', "1.0");
    TCLAP::ValueArg<std::string> inputArg("i", "input", "the path of input file", true, "", "string");
    TCLAP::ValueArg<std::string> outputArg("o", "output", "the path of output file", true, "", "string");

    cmd.add(inputArg);
    cmd.add(outputArg);

    cmd.parse(argc, argv);

    input_filename = inputArg.getValue();
    output_filename = outputArg.getValue();

  } catch (TCLAP::ArgException &e) {
    std::cerr << "error" << e.error() << "for arg" << e.argId() << std::endl;
  }

  auto *input_database = new InputDataBase();
  auto *output_database = new OutputDataBase();

  auto *parser = new Parser(*input_database, input_filename);
  parser->parse();
  delete parser;

  placement(*input_database, *output_database);

  auto *exporter = new Exporter(*output_database, output_filename);
  exporter->output();
  delete exporter;

  delete input_database;
  delete output_database;

  return 0;
}
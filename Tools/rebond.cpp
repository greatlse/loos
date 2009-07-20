/*
  rebond.cpp

  (c) 2009 Tod D. Romo, Grossfield Lab
  Department of Biochemistry
  University of Rochester School of Medicine and Dentistry
*/



/*

  This file is part of LOOS.

  LOOS (Lightweight Object-Oriented Structure library)
  Copyright (c) 2008-2009, Tod D. Romo
  Department of Biochemistry and Biophysics
  School of Medicine & Dentistry, University of Rochester

  This package (LOOS) is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation under version 3 of the License.

  This package is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <loos.hpp>
#include <boost/format.hpp>
#include <boost/program_options.hpp>


using namespace std;
using namespace loos;
namespace po = boost::program_options;

bool append_bonds = false;
bool full_model_output = true;
string model_name;
string selection;
double radius;


void fullHelp(void) {
  cout << "Extended help not available at this time...\n";
  exit(-1);
}


void parseOptions(int argc, char *argv[]) {

  try {

    po::options_description generic("Allowed options");
    generic.add_options()
      ("help", "Produce this help message")
      ("fullhelp", "Extended help")
      ("selection,s", po::value<string>(&selection)->default_value("all"), "Subset to search for bonds over")
      ("radius,r", po::value<double>(&radius)->default_value(1.25), "Radius cutoff for bonding")
      ("add,a", po::value<bool>(&append_bonds)->default_value(false), "Add to existing bonds")
      ("full,f", po::value<bool>(&full_model_output)->default_value(true), "Output the entire model (or just the subset if =0)");


    po::options_description hidden("Hidden options");
    hidden.add_options()
      ("model", po::value<string>(&model_name), "Model filename");

    po::options_description command_line;
    command_line.add(generic).add(hidden);

    po::positional_options_description p;
    p.add("model", 1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
              options(command_line).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help") || vm.count("fullhelp") || !vm.count("model")) {
      cerr << "Usage- " << argv[0] << " [options] model-name\n";
      cerr << generic;
      if (vm.count("fullhelp"))
        fullHelp();
      exit(-1);
    }

  }
  catch(exception& e) {
    cerr << "Error - " << e.what() << endl;
    exit(-1);
  }
}




int main(int argc, char *argv[]) {
  string hdr = invocationHeader(argc, argv);
  parseOptions(argc, argv);

  AtomicGroup model = createSystem(model_name);
  if (!append_bonds)
    model.clearBonds();

  AtomicGroup subset = selectAtoms(model, selection);
  subset.findBonds(radius);

  PDB pdb;
  if (full_model_output)
    pdb = PDB::fromAtomicGroup(model);
  else
    pdb = PDB::fromAtomicGroup(subset);

  pdb.remarks().add(hdr);
  cout << pdb;
}

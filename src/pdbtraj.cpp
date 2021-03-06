/*
  This file is part of LOOS.

  LOOS (Lightweight Object-Oriented Structure library)
  Copyright (c) 2008, Tod D. Romo, Alan Grossfield
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


#include <pdbtraj.hpp>
#include <boost/format.hpp>

namespace loos {
  void PDBTraj::rewindImpl(void) { seekFrame(0); }
  uint PDBTraj::nframes(void) const { return(_nframes); }
  uint PDBTraj::natoms(void) const { return(_natoms); }


  void PDBTraj::updateGroupCoords(AtomicGroup& g) {

    for (AtomicGroup::iterator i = g.begin(); i != g.end(); ++i) {
      int idx = (*i)->index();
      (*i)->coords(frame[idx]->coords());
    }
  }

  bool PDBTraj::hasPeriodicBox(void) const { return(frame.isPeriodic()); }
  GCoord PDBTraj::periodicBox(void) const { return(frame.periodicBox()); }
  float PDBTraj::timestep(void) const { return(0.001); }
  std::string PDBTraj::currentName(void) const { return(current_name); }
  PDB PDBTraj::currentFrame(void) const { return(frame); }
  

  void PDBTraj::init(void) {
    seekFrame(0);
    parseFrame();
    _natoms = frame.size();
    _nframes = (end - start) / stride + 1;
  }


  void PDBTraj::seekFrameImpl(const uint i) {

    uint idx = i * stride + start;
    if (idx < start || i > end)
      throw(FileError(_filename, "Attempting to seek to frame beyond the end of the trajectory"));

    std::stringstream s;
    s << boost::format(pattern) % idx;
    current_name = s.str();
    ifs.setStream(current_name);
    current_index = i;
    at_end = false;
  }


  void PDBTraj::seekNextFrameImpl(void) {
    if (at_end)
      return;

    if (current_index >= _nframes)
      at_end = true;
    else {
      seekFrame(current_index);
      ++current_index;
    }
  }


  bool PDBTraj::parseFrame(void) {

    if (at_end)
      return(false);
  
    PDB newframe;
    newframe.read(*(ifs()));
    frame = newframe;
    if (frame.size() == 0) {
      at_end = true;
      return(false);
    }

    return(true);
  }



  std::vector<GCoord> PDBTraj::coords(void) {
    std::vector<GCoord> result(_natoms);

    for (uint i=0; i<_natoms; i++)
      result[i] = frame[i]->coords();

    return(result);
  }


}

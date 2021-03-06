/*
  This file is part of LOOS.

  LOOS (Lightweight Object-Oriented Structure library)
  Copyright (c) 2009, Tod D. Romo, Alan Grossfield
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

#if !defined(LOOS_AMBER_RST_HPP)
#define LOOS_AMBER_RST_HPP


#include <string>

#include <loos_defs.hpp>
#include <Coord.hpp>
#include <Trajectory.hpp>


namespace loos {

  //! Class for reading amber restart files as a single-frame trajectory

  class AmberRst : public Trajectory {
  public:
    explicit AmberRst(const std::string& s, const int na) : Trajectory(s), _natoms(na),
                                                             current_time(0.0),
                                                            periodic(false), seek_flag(false) {

      parseFrame();
      cached_first = true;
    }



    std::string description() const { return("Amber restart (single frame trajectory)"); }
    static pTraj create(const std::string& fname, const AtomicGroup& model) {
      return(pTraj(new AmberRst(fname, model.size())));
    }
 
    
    virtual uint nframes(void) const { return(1); }
    virtual uint natoms(void) const { return(_natoms); }
    virtual std::vector<GCoord> coords(void) { return(frame); }

    virtual bool hasPeriodicBox(void) const { return(periodic); }
    virtual GCoord periodicBox(void) const { return(box); }

    virtual float timestep(void) const { return(0.0); }  // Dummy routine...
    greal currentTime(void) const { return(current_time); }

    virtual bool parseFrame(void);

  private:
    virtual void updateGroupCoordsImpl(AtomicGroup&);
    virtual void rewindImpl(void) { seek_flag = false; cached_first = true; }
    virtual void seekNextFrameImpl(void);
    virtual void seekFrameImpl(const uint);

    

  private:
    uint _natoms;
    greal current_time;
    bool periodic;
    GCoord box;
    std::vector<GCoord> frame;

    bool seek_flag;
  };


}
#endif

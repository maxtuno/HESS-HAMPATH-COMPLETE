# HESS HAMILTONIAN PATH COMPLETE (2021) black-box for Hamiltonian Path Problem

The original HESS (Hyper Exponential Space Sorting) is a polynomial black-box optimization algorithm, that work very well with any NP-Complete, or NP-Hard problem, at 2021 thanks to suggestions of Daniel Mattes, work like a complete algorithm. 

HESS is an Algorithm was developed by Oscar Riveros (@maxtuno, Chile) from 2012 to 2018.

HESS = Hyper Exponential Space Sorting 

(old repository https://github.com/www-PEQNP-science/HESS_HP)

More info (HESS SAT COMPLETE) https://github.com/maxtuno/HESS-SAT-COMPLETE

Example for TSP:
https://colab.research.google.com/drive/1crfbZyVXahi54zzQp0ENN-bNzMzWCYAa

FHCP Challenge Set (Instances for Hamiltonian Cycle but work for Hamiltonian Path)
https://sites.flinders.edu.au/flinders-hamiltonian-cycle-project/fhcp-challenge-set/

TSPLIB
http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/hcp/

Remarks: Is an open question if HESS is complete for SAT and ofcourse for HAMPATH. (Original HESS is polynomial black box approximator)

# Build

	mkdir build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Release ..
	make

# Usage
	
	./hess-hp instance

	./hc_check instance path

This software and is released with MIT licence:

Copyright (c) 2012-2022 Oscar Riveros (@maxtuno, Chile).

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

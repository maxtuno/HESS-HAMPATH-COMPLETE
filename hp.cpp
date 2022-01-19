/*
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
 */

#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <hess/hess.hh>
#include <limits>

int main(int argc, char *argv[]) {

    struct cpu box{};

    std::string data_file(argv[1]);
    std::string path_file(data_file);
    path_file.erase(std::find(path_file.begin(), path_file.end(), '.'), path_file.end());
    path_file += ".path";

    std::fstream graph(data_file);
    std::string buffer;
    I x{0}, y{0};
    while (graph >> buffer) {
        if (buffer == "DIMENSION") {
            graph >> buffer;
            if (buffer == ":") {
                graph >> box.len;
                box.seq = (I *) calloc(box.len, sizeof(I));
                box.map = (bool **) calloc(box.len, sizeof(bool *));
                for (I i = 0; i < box.len; i++) {
                    box.map[i] = (bool *) calloc(box.len, sizeof(bool));
                    box.seq[i] = i;
                }
            }
        }
        if (buffer == "EDGE_DATA_SECTION") {
            break;
        }
    }
    while (graph.good()) {
        graph >> buffer;
        if (buffer == "-1" || buffer == "EOF") {
            break;
        }
        x = static_cast<I>(std::atoll(buffer.c_str()) - 1);
        graph >> buffer;
        y = static_cast<I>(std::atoll(buffer.c_str()) - 1);
        box.map[x][y] = true;
        box.map[y][x] = true;
    }
    graph.close();

    box.log = [](struct cpu *box) {
        std::cout << box->glb << std::endl;
    };

    hess(&box);

    if (box.glb == 0) {
        std::cout.precision(std::numeric_limits<I>::max_digits10 + 1);
        std::cout << "SATISFIABLE : " << data_file << std::endl;
        std::ofstream os(path_file);
        os << "NAME : Solution for \"" << data_file << "\"" << std::endl;
        os << "TYPE : PATH" << std::endl;
        os << "DIMENSION : " << box.len << std::endl;
        os << "TOUR_SECTION" << std::endl;
        std::size_t k{0};
        for (std::size_t i{0}; i < box.len; i++) {
            os << box.seq[i] + 1 << (++k < box.len ? "\n" : "");
        }
        os << std::endl;
        os << "-1" << std::endl;
        os << "EOF" << std::endl;
    } else {
        std::cout << "UNSATISFIABLE : " << data_file << std::endl;
    }

    return EXIT_SUCCESS;
}

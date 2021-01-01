# sycl-project-template
[SYCL](https://www.khronos.org/sycl/) project template with integration of ComputeCpp and Conan

### External libraries
1. [cxxopts](https://github.com/jarro2783/cxxopts)

### Build prerequisites
1. [CMake](https://cmake.org/) (version >= 3.8)
2. [ComputeCpp](https://www.codeplay.com/solutions/ecosystem/) - Codeplay's SYCL implementation
2. [Conan](https://conan.io/) package manager
### Build
<pre>
mkdir build && cd build
cmake -DComputeCpp_DIR=&lt;Path to ComputeCpp&gt; -DCMAKE_CXX_COMPILER=compute++ -DCMAKE_BUILD_TYPE=Release -GNinja ..
cmake --build .
</pre>
### Example output
<pre>
Running on Intel(R) HD Graphics

  A { 1, 2, 3, 4 }
+ B { 4, 3, 2, 1 }
------------------
= C { 5, 5, 5, 5 }
</pre>

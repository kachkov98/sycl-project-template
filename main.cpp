#include <CL/sycl.hpp>
#include <cxxopts.hpp>
#include <iostream>

class vector_addition;

int main(int argc, char **argv) {
  using namespace cl;

  cxxopts::Options options("example", "Simple SYCL demo");
  // clang-format off
  options.add_options()
    ("help", "Print help")
  ;
  // clang-format on

  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  // create vectors
  sycl::float4 a = {1.0, 2.0, 3.0, 4.0};
  sycl::float4 b = {4.0, 3.0, 2.0, 1.0};
  sycl::float4 c = {0.0, 0.0, 0.0, 0.0};

  // use default device selector
  sycl::default_selector selector;
  // create sycl queue
  sycl::queue queue(selector);

  // get device info
  std::cout << "Running on " << queue.get_device().get_info<sycl::info::device::name>() << "\n\n";

  // set up buffers
  {
    sycl::buffer<sycl::float4, 1> a_sycl(&a, sycl::range<1>(1));
    sycl::buffer<sycl::float4, 1> b_sycl(&b, sycl::range<1>(1));
    sycl::buffer<sycl::float4, 1> c_sycl(&c, sycl::range<1>(1));

    // create command  group
    queue.submit([&](sycl::handler &cgh) {
      // set up accessors
      auto a_acc = a_sycl.get_access<sycl::access::mode::read>(cgh);
      auto b_acc = b_sycl.get_access<sycl::access::mode::read>(cgh);
      auto c_acc = c_sycl.get_access<sycl::access::mode::discard_write>(cgh);

      // execute on device
      cgh.single_task<class vector_addition>([=]() { c_acc[0] = a_acc[0] + b_acc[0]; });
    });
  }

  // show results
  std::cout << "  A { " << a.x() << ", " << a.y() << ", " << a.z() << ", " << a.w() << " }\n"
            << "+ B { " << b.x() << ", " << b.y() << ", " << b.z() << ", " << b.w() << " }\n"
            << "------------------\n"
            << "= C { " << c.x() << ", " << c.y() << ", " << c.z() << ", " << c.w() << " }\n";

  return 0;
}

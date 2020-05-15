#include <iostream>
#include <ctime>
#include <fstream>
#include "../libs/recursion/recursion_and_merge.h"


namespace ra = recursion::auxiliary;
namespace rw = recursion::wrappers;

int main() {
    clock_t start, end;
    std::ofstream out_file;
    long time_to_process;
    int t[] = {1, 2, 3, -1, 4, 2};
    double p[] = {.5, .25};
    double a[] = {4., 2., 1.};
    int d[] = {1, 2, 3, 4};
    double s = 5;

    out_file.open("time_results.txt", std::ios::out);

    if (not out_file) {
        std::cerr << "[Error] Output file cannot be opened!" << std::endl;
        return EXIT_FAILURE;
    }

    start = clock();
    std::cout << rw::f_wielomian(5, t, 3) << std::endl;
    end = clock();
    time_to_process = long(end - start);

    out_file << "f_wielomian: " << time_to_process << std::endl;

    start = clock();
    std::cout << *rw::f_maximum(6, t) << std::endl;
    end = clock();
    time_to_process = long(end - start);

    out_file << "f_maximum: " << time_to_process << std::endl;

    start = clock();
    std::cout << rw::f_newton(15, 6) << std::endl;
    end = clock();
    time_to_process = long(end - start);

    out_file << "f_newton: " << time_to_process << std::endl;

    start = clock();
    std::cout << rw::f_suma_wazona(s, p, p + 2, a);
    end = clock();
    time_to_process = long(end - start);

    out_file << "f_suma_wazona: " << time_to_process << std::endl;

    std::cout << ", " << s << std::endl;
    start = clock();
    std::cout << rw::f_srednia_warunkowa(s, ra::FALSE, d, d + 4);
    end = clock();
    time_to_process = long(end - start);

    out_file << "f_srednia_warunkowa: " << time_to_process << std::endl;

    std::cout << ", " << s << std::endl;
    std::cout << rw::f_srednia_warunkowa(s, ra::TRUE, d, d + 4);

    out_file.close();

    return 0;
}

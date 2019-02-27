#include <iostream>
#include "vec3.h"

int main(int argc, char* argv[]) {
    int nx = 200;
    int ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 color(float(i) / float(nx), float(j) / float(ny), 0.2);
            int ir = int(255.99 * color[0]);
            int ig = int(255.99 * color[1]);
            int ib = int(255.99 * color[2]);
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}
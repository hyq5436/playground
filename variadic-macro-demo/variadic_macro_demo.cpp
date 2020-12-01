#include <iostream>
#include <cstdarg>
#include <cmath>
#include <tuple>

#define VARIADIC_FUNC(...) func()

template <typename T>
void _write(const T& t)
{
    std::cout << t << std::endl;
}
 
template <typename T, typename... Args> void _write(const T& t, Args... args) {
    std::cout << t << ", ";
    _write(args...);
}
 
template <typename T, typename... Args>
inline void write_line(const T& t, const Args& ... data){
	_write(t, data...);
}

double stddev(int count, ...) 
{
    double sum = 0;
    double sum_sq = 0;
    std::va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        double num = va_arg(args, double);
        sum += num;
        sum_sq += num*num;
    }
    va_end(args);
    return std::sqrt(sum_sq/count - (sum/count)*(sum/count));
}

int main(int argc, char* argv[])
{
    write_line(11, 22, 33, "aaaa");

    std::cout << stddev(4, 25.0, 27.3, 26.9, 25.7) << std::endl;

    return 0;
}
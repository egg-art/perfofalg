#ifndef timer_H
#define timer_H

#include <chrono>
#include <string>

class timer
{
private:
    using hr_clock_ = std::chrono::high_resolution_clock;
    using time_point_t = std::chrono::time_point<hr_clock_>;
    using nanoseconds_t = std::chrono::duration<size_t, std::nano>;

public:
    explicit timer() :
        start_time(hr_clock_::now())
    {}

    nanoseconds_t::rep elapced() const
    {
        return std::chrono::duration_cast<nanoseconds_t>(
                    hr_clock_::now() - start_time).count();
    }

    void reset()
    {
        start_time = hr_clock_::now();
    }

protected:
    time_point_t start_time;
};

#endif // timer_H

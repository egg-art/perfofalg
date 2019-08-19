#include "sort_algs.h"
#include "timer.h"
#include "data_generator.h"

const size_t MAX_DATA_SIZE = 10ULL;

int main()
{
    timer main_timer;
    timer local_timer;

    local_timer.reset();
    data_generator data_gen(MAX_DATA_SIZE);

    if (!data_gen.initialize())
    {
        return 1;
    }
    cout << "\ndata generated for [" << static_cast<double>(local_timer.elapced())/1000 << "] microseconds" << endl;
    local_timer.reset();

    sort_algs sort_algs(data_gen);
    sort_algs.run(sorting_order::ascending());
    sort_algs.run(sorting_order::descending());
    cout << "\nsort_algs runned for [" << static_cast<double>(local_timer.elapced())/1000 << "] microseconds" << endl;
    local_timer.reset();

    size_t elapced = main_timer.elapced();
    cout << "\nmain runned for [" << static_cast<size_t>(elapced)/1000 << "] microseconds" << endl;

    return 0;
}

// Improve data generator
// Add logger
// Add statistic colector and nice output
// Add plot for data

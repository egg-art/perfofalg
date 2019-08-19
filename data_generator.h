#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include "common.h"

class data_generator
{
public:
    explicit data_generator(const size_t data_size);
    data_generator(const data_generator & obj) = delete;
    data_generator(data_generator && obj) = delete;

    virtual ~data_generator() {}

    data_generator & operator=(const data_generator & obj) = delete;
    data_generator & operator=(data_generator && obj) = delete;

    bool initialize();
    container_t get_data() const;

private:
    const size_t data_size_;
    container_t data_;
};

#endif // DATA_GENERATOR_H

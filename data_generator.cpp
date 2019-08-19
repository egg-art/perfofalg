#include <algorithm>

#include "data_generator.h"

namespace
{

const size_t BEGIN_FROM_INDEX = 0ULL;

class incremental
{
public:
    incremental(const size_t begin_from_index) :
        index_(begin_from_index)
    {}
    size_t operator()()
    {
        return index_++;
    }
private:
    size_t index_;
} increment(BEGIN_FROM_INDEX);

}

data_generator::data_generator(const size_t size) :
    data_size_(size)
{}

bool data_generator::initialize()
{
    bool result = false;

    do
    {
        if (data_size_ > data_.max_size())
        {
            std::cout << "data requested size:" << data_size_ << " is bigger then ";
            std::cout << "data max size:" << data_.max_size() << std::endl;
            break;
        }

        try
        {
            data_.resize(data_size_);
        }
        catch (...)
        {
            std::cout << "exception on reserve" << std::endl;
            break;
        }

        std::generate(data_.begin(), data_.end(), increment);

        std::cout << "data size:" << data_.size() << std::endl;
        std::cout << "generated data:" << std::endl;
        for (auto && i : data_)
        {
            std::cout << static_cast<size_t>(i) << " ";
        }
        std::cout << std::endl;

        result = true;
    }
    while(false);

    return result;
}

container_t data_generator::get_data() const
{
    return data_;
}

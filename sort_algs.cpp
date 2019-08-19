#include <functional>
#include <algorithm>
#include <iterator>

#include "sort_algs.h"

#include "timer.h"

// Add if def check for c++17 and lower
#define CALL_MEMBER_FN(obj, pointer) ((obj).*(pointer))

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

using std::literals::operator""s;

namespace templates
{
template <typename input_iterator, typename comparison_fn_t>
void insertion_sort(input_iterator begin, input_iterator end, comparison_fn_t && comp)
{
    input_iterator i = begin;
    while (i != (end - 1))
    {
        input_iterator j = i;
        input_iterator key = j + 1;
        while (j >= begin && comp(*key, *j))
        {
            *(j + 1) = *j;
            //(j + 1) = j;
            --j;
        }
        *j = *key;
        ++i;
    }
}

}

namespace sorting_order
{

sorting_order_i::~sorting_order_i() {}

bool ascending::operator()(const data_t & a, const data_t & b) const
{
    return a < b;
}

std::string ascending::name()
{
    return "ascending"s;
}

bool descending::operator() (const data_t & a, const data_t & b) const
{
    return a > b;
}

std::string descending::name()
{
    return "descending"s;
}

}

sort_algs::sort_algs(const data_generator & data_gen) :
    data_gen_(data_gen),
    funcs({
        {"insertion_sort"s, std::bind(&sort_algs::insertion_sort, _1, _2, _3)},
        {"selection_sort"s, std::bind(&sort_algs::selection_sort, _1, _2, _3)},
        {"merge_sort_bu"s, std::bind(&sort_algs::merge_sort_bu, _1, _2, _3)},
        {"merge_sort_td"s, std::bind(&sort_algs::merge_sort_td, _1, _2, _3)}
    })
{}

bool sort_algs::verify_data(container_t & data, const comparator_fn_t & comp)
{
    bool result = true;

    if (1 < data.size())
    {
        for(auto i = data.begin() + 1; i != data.end(); ++i)
        {
            if (!comp(*(i - 1), *i))
            {
                result = false;
                break;
            }
        }
    }

    return result;
}

void sort_algs::run(comparator_fn_t && sort_order)
{
    container_t orig_data(data_gen_.get_data());

    internal_func_containter::iterator it_curr = funcs.begin();
    internal_func_containter::iterator it_end = funcs.end();
    for (;it_curr != it_end; ++it_curr)
    {
        container_t data(orig_data);

        std::cout << "\n===SORTING ALG: " << (*it_curr).first << "===" << std::endl;
        std::cout << "=sorting order: " << sort_order.name() << "=" << std::endl;

        timer local_timer;
        std::invoke((*it_curr).second, *this, data, sort_order);
        local_timer.elapced();
        cout << "sorted for [" << static_cast<double>(local_timer.elapced())/1000/1000 << "] milliseconds" << endl;

        // Verify data after each sorting is done
        if (verify_data(data, sort_order))
        {
            std::cout << "===success: data sorted correctly===" << std::endl;
        }
        else
        {
            std::cout << "***ERROR: DATA NOT SORTED CORRECTLY***" << std::endl;
        }
    }
}

void sort_algs::insertion_sort(container_t & data, const comparator_fn_t & comp)
{
    //templates::insertion_sort(data.begin(), data.end(), comp);

//    auto begin = data.begin();
//    auto end = data.end();
//    auto i = begin;
//    while (i != (end - 1))
//    {
//        auto j = i;
//        auto key = j + 1;
//        while (j >= begin && comp(*key, *j))
//        {
//            *(j + 1) = *j;
//            --j;
//        }
//        *(j + 1) = *key;
//        ++i;
//    }
    for (size_t i = 1; i < data.size(); ++i)
    {
        auto key = data[i];

        size_t j = i - 1;

        while (static_cast<int>(j) >= 0 && comp(key, data[j]))
        {
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = key;
    }
}

void sort_algs::selection_sort(container_t & data, const comparator_fn_t & comp)
{
    for(size_t i = 1; i < data.size(); ++i)
    {
        size_t j = i;
        while (comp(data[j], data[i - 1]))
        {
            data_t temp = data[j];
            data[j] = data[i - 1];
            data[i - 1] = temp;

            ++j;
        }
    }
}

void sort_algs::merge_sort_bu_impl(const container_t & data_in,
                                   const container_t::size_type begin,
                                   const container_t::size_type middle,
                                   const container_t::size_type end,
                                   container_t & data_out,
                                   const comparator_fn_t & comp)
{
    container_t::size_type counter = begin;
    container_t::size_type left_head = begin;
    container_t::size_type right_head = middle;

    for (; counter < end; ++counter)
    {
        //if ((left_head < middle) && (right_head < end) && comp(data_in[left_head], data_in[right_head]))
        if ((left_head < middle) && ((right_head >= end) || comp(data_in[left_head], data_in[right_head])))
        {
            data_out[counter] = data_in[left_head];
            ++left_head;
        }
        else
        {
            data_out[counter] = data_in[right_head];
            ++right_head;
        }
    }
}

void sort_algs::merge_sort_bu(container_t & data, const comparator_fn_t & comp)
{
    container_t work_data(data);

    container_t::size_type chunk_size = 1;
    container_t::size_type data_size = work_data.size();

    for (; chunk_size < data_size; chunk_size *= 2)
    {
        for (container_t::size_type i = 0; i < data_size; i = i + 2 * chunk_size)
        {
            merge_sort_bu_impl(work_data,
                               i,
                               std::min(i + chunk_size, data_size),
                               std::min(i + 2 * chunk_size, data_size),
                               data,
                               comp);
        }
        work_data = data;
    }
}

void sort_algs::merge_sort_td_impl(const container_t & data_in,
                                   const container_t::size_type begin,
                                   const container_t::size_type middle,
                                   const container_t::size_type end,
                                   container_t & data_out,
                                   const comparator_fn_t & comp)
{
    container_t::size_type counter = begin;
    container_t::size_type left_head = begin;
    container_t::size_type right_head = middle;

    for (; counter < end; ++counter)
    {
        if ((left_head < middle) && ((right_head >= end) || comp(data_in[left_head], data_in[right_head])))
        {
            data_out[counter] = data_in[left_head];
            ++left_head;
        }
        else
        {
            data_out[counter] = data_in[right_head];
            ++right_head;
        }
    }
}

void sort_algs::merge_sort_td_split(container_t & data_in,
                                    const container_t::size_type begin,
                                    const container_t::size_type end,
                                    container_t & data_out,
                                    const comparator_fn_t & comp)
{
    do
    {
        if (2 > (end - begin))
        {
            break;
        }

        const container_t::size_type middle = (end + begin) / 2;

        merge_sort_td_split(data_out, begin, middle, data_in, comp);
        merge_sort_td_split(data_out, middle, end, data_in, comp);

        merge_sort_td_impl(data_in, begin, middle, end, data_out, comp);

        std::cout << "=" << begin << ":" << middle << ":" << end << std::endl;
        for (auto val : data_out) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    while (false);
}

void sort_algs::merge_sort_td(container_t & data, const comparator_fn_t & comp)
{
    container_t work_data(data);

    merge_sort_td_split(work_data, 0, work_data.size(), data, comp);
}

#ifndef SORT_ALGS_H
#define SORT_ALGS_H

#include <vector>
#include <functional>

#include "common.h"
#include "data_generator.h"

namespace sorting_order
{
class sorting_order_i
{
public:
    virtual ~sorting_order_i();
    virtual bool operator() (const data_t &, const data_t &) const = 0;
    virtual std::string name() = 0;
};

class ascending : public sorting_order_i
{
public:
    bool operator()(const data_t & a, const data_t & b) const override;
    std::string name() override;
};

class descending : public sorting_order_i
{
public:
    bool operator() (const data_t & a, const data_t & b) const override;
    std::string name() override;
};
}

class sort_algs
{
private:
    //using comparator_fn_t = std::function<bool(const data_t & val1, const data_t & val2)>;
    using comparator_fn_t = sorting_order::sorting_order_i;

    //using sort_fn_t = std::function<void (sort_algs::*) (container_t &, comparator_fn_t &)>;
    //using sort_fn_t = std::function<void(container_t &, comparator_fn_t &&)>;
    using sort_fn_t = std::function<void(sort_algs & obj, container_t &, const comparator_fn_t &)>;
    using internal_func_containter = std::vector<std::pair<std::string, sort_fn_t>>;

public:
    sort_algs(const data_generator & data_gen);
    sort_algs(sort_algs & obj) = delete;
    sort_algs(sort_algs && obj) = delete;

    virtual ~sort_algs() {}

    sort_algs & operator=(sort_algs & obj) = delete;
    sort_algs & operator=(sort_algs && obj) = delete;

    void run(comparator_fn_t && sort_order);

private:
    /**
     * @brief insertion_sort
     * @param data - container of sortable objects with implemented operators less(<) and more(>)
     * @param comp - binary callable object that returns true if the first argument is considered to go before the second
     */
    void insertion_sort(container_t & data, const comparator_fn_t & comp);
    void selection_sort(container_t & data, const comparator_fn_t & comp);
    void merge_sort_bu(container_t & data, const comparator_fn_t & comp);
    void merge_sort_bu_impl(const container_t & data_in,
                            const container_t::size_type begin,
                            const container_t::size_type middle,
                            const container_t::size_type end,
                            container_t & data_out,
                            const comparator_fn_t & comp);
    void merge_sort_td(container_t & data, const comparator_fn_t & comp);
    void merge_sort_td_split(container_t & data_in,
                             const container_t::size_type begin,
                             const container_t::size_type end,
                             container_t & data_out,
                             const comparator_fn_t & comp);
    void merge_sort_td_impl(const container_t & data_in,
                            const container_t::size_type begin,
                            const container_t::size_type middle,
                            const container_t::size_type end,
                            container_t & data_out,
                            const comparator_fn_t & comp);

    bool verify_data(container_t & data, const comparator_fn_t & comp);

private:
    const data_generator & data_gen_;
    internal_func_containter funcs;
};

#endif // SORT_ALGS_H

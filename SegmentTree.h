#ifndef DUALLABTESTTASK_SEGMENTTREE_H
#define DUALLABTESTTASK_SEGMENTTREE_H

#include <vector>
#include <exception>
#include <stdexcept>


class SegmentTree {
public:
    explicit SegmentTree(const std::vector<int> &data);

    int Rgq(int left, int right);

    void Switch(int index);

private:
    std::vector<int> data_;
    int pow_ = 1;
};

#endif //DUALLABTESTTASK_SEGMENTTREE_H

#include "SegmentTree.h"

SegmentTree::SegmentTree(const std::vector<int> &data) {
    while (pow_ < data.size()) {
        pow_ *= 2;
    }

    data_.resize(2 * pow_);

    for (int i = 0; i < data.size(); i++) {
        data_[i + pow_] = data[i];
    }

    for (int i = pow_ - 1; i >= 1; i--) {
        data_[i] = data_[i * 2] + data_[i * 2 + 1];
    }
}

int SegmentTree::Rgq(int left, int right) {
    /*
     * return sum from left to right, indexed from zero
    */
    left += pow_;
    right += pow_;
    int result = 0;

    while (left <= right) {
        if (left % 2 == 1) {
            result += data_[left];
            left++;
        }
        if (right % 2 == 0) {
            result += data_[right];
            right--;
        }
        left /= 2;
        right /= 2;
    }
    return result;
}

void SegmentTree::Switch(int index) {
    /*
     * switch element in index position and recalculate DO, indexed from zero
    */
    index += pow_;
    int new_value = data_[index] == 1 ? 0 : 1;
    int extra = new_value - data_[index];
    data_[index] = new_value;
    while (index != 1) {
        index /= 2;
        data_[index] += extra;
    }
}
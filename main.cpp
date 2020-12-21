#include <iostream>

#include "SegmentTree.h"

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<int> start_state(n);

    for (auto& x : start_state) {
        std::cin >> x;
    }

    SegmentTree segment_tree(start_state);

    int number_querys = 0;
    std::cin >> number_querys;

    for (int i = 0; i < number_querys; ++i) {
        int query_type = 0;
        std::cin >> query_type;
        try {
            if (query_type == 1) {
                int index_to_switch = 0;
                std::cin >> index_to_switch; // from one
                segment_tree.Switch(index_to_switch - 1); // change indexed from zero
            } else if (query_type == 2) {
                int left = 0, right = 0;
                std::cin >> left >> right; // from one
                int result = segment_tree.Rgq(left - 1, right - 1); // change indexed from zero
                std::cout << result << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    return 0;
}

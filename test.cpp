#include <catch.hpp>
#include <vector>
#include <chrono>
#include <random>

#include "SegmentTree.h"

static std::mt19937_64 gen(1234);

constexpr int MAX_N = 1'000'000;
constexpr int MAX_Q = 1'000'000;

struct Query {
    int type;
    int first;
    int second = -1;

    Query(int type, int index) : type(type), first(index) {
    }

    Query(int type, int left, int right) : type(type), first(left), second(right) {
    }
};

void Test(const std::vector<int>& initial_state, const std::vector<Query>& querys,
          const std::vector<int>& truth = std::vector<int>()) {
    SegmentTree segment_tree(initial_state);

    std::vector<int> response;

    auto start = std::chrono::system_clock::now();

    for (auto q : querys) {
        if (q.type == 1) {
            segment_tree.Switch(q.first - 1);
        } else if (q.type == 2) {
            response.push_back(segment_tree.Rgq(q.first - 1, q.second - 1));
        }
    }

    auto finish = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

    REQUIRE(elapsed <= 2000);
    if (!truth.empty()) {
        REQUIRE(truth.size() == response.size());

        if (truth.size() == response.size()) {
            for (size_t i = 0; i < truth.size(); ++i) {
                REQUIRE(truth[i] == response[i]);
            }
        }
    }
}

TEST_CASE("Simple") {
    std::vector<int> initial_state{0, 1, 0, 0, 1};
    std::vector<Query> querys{
            Query(1, 1),
            Query(1, 3),
            Query(2, 2, 4),
            Query(1, 5),
            Query(2, 3, 5)
    };

    std::vector<int> truth{2, 1};

    Test(initial_state, querys, truth);
}

TEST_CASE("Custom") {
    std::vector<int> initial_state{0, 1, 0, 0, 1, 0, 0, 1, 1};
    std::vector<Query> querys{
            Query(2, 1, 9),
            Query(1, 2),
            Query(2, 1, 9),
            Query(1, 3),
            Query(1, 6),
            Query(2, 1, 9),
    };

    std::vector<int> truth{4, 3, 5};

    Test(initial_state, querys, truth);
}

TEST_CASE("Long") {
    std::vector<int> initial_state(MAX_N, 1);
    std::vector<Query> querys(MAX_Q, Query(2, 1, MAX_N));

    std::vector<int> truth(MAX_Q, MAX_N);

    Test(initial_state, querys, truth);
}

std::vector<int> GenRandomInitialState(size_t n) {
    std::vector<int> result(n);
    for (size_t i = 0; i < n; ++i) {
        result[i] = gen() % 2;
    }
    return result;
}

std::vector<Query> GenRandomQuerys(size_t n, size_t state_lenght) {
    std::vector<Query> result;
    result.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        int type = gen() % 2 + 1;
        if (type == 1) {
            result.emplace_back(type, gen() % state_lenght + 1);
        } else {
            int left = gen() % state_lenght + 1;
            int right = gen() % state_lenght + 1;
            result.emplace_back(type, std::min(left, right), std::max(left, right));
        }
    }
    return result;
}

std::vector<int> CalculateTruthResponse(std::vector<int> initial_state, const std::vector<Query>& querys) {
    std::vector<int> result;
    for (auto q : querys) {
        if (q.type == 1) {
            initial_state[q.first - 1] = initial_state[q.first - 1] == 1 ? 0 : 1;
        } else if (q.type == 2) {
            result.push_back(std::accumulate(initial_state.begin() + q.first - 1,
                                             initial_state.begin() + q.second,
                                             0));
        }
    }
    return result;
}

TEST_CASE("Correctness") {
    std::vector<int> initial_state = GenRandomInitialState(MAX_N);
    std::vector<Query> querys = GenRandomQuerys(100000, MAX_N);

    std::vector<int> truth = CalculateTruthResponse(initial_state, querys);

    Test(initial_state, querys, truth);
}

TEST_CASE("Stress") {
    std::vector<int> initial_state = GenRandomInitialState(MAX_N);
    std::vector<Query> querys = GenRandomQuerys(MAX_Q, MAX_N);

    Test(initial_state, querys);
}

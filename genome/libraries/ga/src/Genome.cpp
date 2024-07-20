#include "ga/Genome.hpp"

#include <algorithm>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

namespace genome {

std::string assembly(size_t k, const std::vector<std::string>& reads) {
    if (k == 0) {
        return "";
    }

    std::unordered_map<std::string_view, std::vector<std::string_view>> graph;
    std::unordered_map<std::string_view, int> in_degree;
    std::unordered_map<std::string_view, int> out_degree;

    for (const auto& fragment : reads) {
        std::string_view fragment_view(fragment);
        for (size_t i = 0; i <= fragment.size() - k - 1; ++i) {
            std::string_view prefix = fragment_view.substr(i, k);
            std::string_view suffix = fragment_view.substr(i + 1, k);
            graph[prefix].push_back(suffix);
            out_degree[prefix]++;
            in_degree[suffix]++;
        }
    }

    std::string_view start_vertex;
    for (const auto& [vertex, degree] : out_degree) {
        if (out_degree[vertex] > in_degree[vertex]) {
            start_vertex = vertex;
            break;
        }
    }
    if (start_vertex.empty() && !reads.empty()) {
        start_vertex = reads[0].substr(0, k);
    }

    std::stack<std::string_view> stack;
    std::vector<std::string_view> path;
    stack.push(start_vertex);

    while (!stack.empty()) {
        std::string_view v = stack.top();
        if (graph[v].empty()) {
            path.push_back(v);
            stack.pop();
        } else {
            std::string_view u = graph[v].back();
            graph[v].pop_back();
            stack.push(u);
        }
    }
    std::reverse(path.begin(), path.end());

    std::string genome;
    if (!path.empty()) {
        genome = std::string(path[0]);
        for (size_t i = 1; i < path.size(); ++i) {
            genome += path[i].back();
        }
    }

    return genome;
}

}  // namespace genome

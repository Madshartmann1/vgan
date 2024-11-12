#include "extract_reads.h"
#include <iostream>

void extractAndPrint(const std::vector<ReadData>& reads) {
    for (const auto& read : reads) {
        std::cout << read.read_name;
        if (!read.node_ids.empty()) {
            std::cout << "\t";
            for (size_t i = 0; i < read.node_ids.size(); ++i) {
                std::cout << read.node_ids[i];
                if (i != read.node_ids.size() - 1) {
                    std::cout << ",";
                }
            }
        }
        std::cout << std::endl;
    }
}

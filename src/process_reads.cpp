#include "process_reads.h"
#include <vg/io/stream.hpp>
#include <vg/vg.pb.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional> // Required for std::function

std::vector<ReadData> processReads(const std::string& inputFilePath) {
    std::vector<ReadData> reads;

    // Open the GAM file as a binary input stream
    std::ifstream input_stream(inputFilePath, std::ios::in | std::ios::binary);
    if (!input_stream.is_open()) {
        std::cerr << "Unable to open file: " << inputFilePath << std::endl;
        return reads;
    }

    // Define a std::function to match the expected signature of for_each
    std::function<void(vg::Alignment&)> process_alignment = [&](vg::Alignment& alignment) {
        // Extract the read name
        std::string read_name = alignment.name();
        ReadData read(read_name);

        // Extract node_ids from the path mappings
        for (int i = 0; i < alignment.path().mapping_size(); ++i) {
            auto mapping = alignment.path().mapping(i);
            if (mapping.has_position() && mapping.position().node_id() != 0) {
                read.addNodeId(std::to_string(mapping.position().node_id()));
            }
        }

        // Add the read to the vector if it has node IDs
        if (!read.node_ids.empty()) {
            reads.push_back(read);
        }
    };

    // Use vg::io::for_each to iterate through the alignments in the input file
    vg::io::for_each(input_stream, process_alignment);

    input_stream.close();
    return reads;
}

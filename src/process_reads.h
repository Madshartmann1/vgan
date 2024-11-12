#ifndef PROCESS_READS_H
#define PROCESS_READS_H

#include <string>
#include <vector>

class ReadData {
public:
    std::string read_name;
    std::vector<std::string> node_ids;

    ReadData(const std::string& name) : read_name(name) {}
    void addNodeId(const std::string& node_id) {
        node_ids.push_back(node_id);
    }
};

std::vector<ReadData> processReads(const std::string& inputFilePath);

#endif // PROCESS_READS_H

#ifndef THE4_THE4_H
#define THE4_THE4_H

#include <string>
#include <vector>
#include <memory>
#include <random>
#include <tuple>
#include <utility>
#include <iostream>

struct AncientScroll{
    int scrollId;
    std::string scrollName;
    std::string writer;
    operator std::string() const {
        // String conversion operator is defined for debugging.
        return "AncientScroll(" + std::to_string(this->scrollId) + ", " + this->scrollName + ", " + this->writer + ")";
    }
    // Please do not change above lines
    // You can add public or private methods/attributes below.
};

class MachineNode {
    private:
        AncientScroll scroll;
    public:
        MachineNode *leftChild;
        MachineNode *rightChild;
        operator std::string() const {
            return (std::string) this->scroll;
        }
    // Please do not change above lines
    // You can add public or private methods/attributes below.
    MachineNode (const AncientScroll& new_scroll)
    {
        scroll = new_scroll;
        leftChild = NULL;
        rightChild = NULL;
    }
    
    AncientScroll get_scroll() const
    {
        return scroll;
    }
};


class ArchivistMachine {
    private:
        MachineNode* root;
        int machineId;

    void printStructureHelper(MachineNode* current_node,
                              const int depth,
                              const std::string type,
                              std::string& structure) const {
        if(current_node == nullptr) return;
        for(int idx=0; idx < depth; idx++)
            structure += "|\t";
        structure += type + ": " + std::string(*current_node) + "\n";
        printStructureHelper(current_node->leftChild, depth + 1, "L", structure);
        printStructureHelper(current_node->rightChild, depth + 1, "R", structure);
    }
        // Please do not change above lines
        // You can add private methods or attributes.

    public:
        ArchivistMachine();
        explicit ArchivistMachine(const std::vector<AncientScroll>& initialElements);
        ArchivistMachine(const ArchivistMachine& existingMachine);
        ~ArchivistMachine();

        void operator<<(const AncientScroll& scroll);
        void operator>>(AncientScroll& scroll);
        AncientScroll operator[](int id) const;
        std::vector<int> operator()(std::string type) const;

        operator std::string() const {
            std::string structure = "-----------------------------------------------------------------------\n";
            structure += "Machine ID: " + std::to_string(this->machineId) + '\n';
            this->printStructureHelper(this->root, 0, "O", structure);
            structure += "-----------------------------------------------------------------------";
            return structure;
        };

        // Please do not change above lines
        // You can add public methods/attributes
};

#endif //THE4_THE4_H

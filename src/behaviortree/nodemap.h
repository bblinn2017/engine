#ifndef NODEMAP_H
#define NODEMAP_H

#include "engine/util/CommonIncludes.h"
#include "behaviortree/basicsbehaviortree.h"

#define ROOTNAME "root"

class NodeMap {
public:
    NodeMap() {
        m_map = std::map<std::string,node_p>();
    }

    template <typename NodeType>
    std::shared_ptr<NodeType> getNode(std::string key) {
        return std::static_pointer_cast<NodeType>(m_map[key]);
    }

    void addNode(std::string parent, std::string key, node_p node) {
        m_map[key] = node;
        if (parent != "") {
            std::static_pointer_cast<Composite>(m_map[parent])->addChild(node);
        }
    }

    std::shared_ptr<BTreeNode> getRoot() {
        return m_map[ROOTNAME];
    }

private:
    std::map<std::string,node_p> m_map;
};

typedef std::shared_ptr<NodeMap> nodemap_p;


#endif // NODEMAP_H

#ifndef BTREENODE_H
#define BTREENODE_H

#include "engine/util/CommonIncludes.h"

enum status_t {SUCCESS,FAIL,RUNNING};
enum leaf_t {ACTION,CONDITION};
enum composite_t {SELECTOR,SEQUENCE};

class NodeMap;
typedef std::shared_ptr<NodeMap> nodemap_p;

class BTreeNode {
public:
    BTreeNode(nodemap_p nodeMap, bool isLeaf, int type, bool negate) {
        m_nodeMap = nodeMap;
        m_isLeaf = isLeaf;
        m_type = type;
        m_negate = negate;
    }

    bool isLeaf() {return m_isLeaf;}
    int type() {return m_type;}

    status_t update(float seconds) {
        status_t determined = determine(seconds);
        if (m_negate) {
            if (determined == SUCCESS) determined = FAIL;
            else if (determined == FAIL) determined = SUCCESS;
        }
        return determined;
    }
    virtual status_t determine(float seconds) = 0;
    virtual void reset() = 0;

protected:
    nodemap_p m_nodeMap;
private:
    bool m_isLeaf;
    int m_type;
    bool m_negate;
};

typedef std::shared_ptr<BTreeNode> node_p;

#endif // BTREENODE_H

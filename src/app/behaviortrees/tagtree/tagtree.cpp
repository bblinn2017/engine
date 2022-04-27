#include "tagtree.h"

using namespace std;
using namespace glm;

TagTree::TagTree(shared_ptr<GameObject> o, vector<shared_ptr<GameObject>> targets, shared_ptr<GameObject> navigable) : BehaviorTree() {

    m_nodeMap->addNode("",ROOTNAME,selector_p(m_nodeMap));
    m_nodeMap->addNode(ROOTNAME,"hidingSelector",selector_p(m_nodeMap,true));
    m_nodeMap->addNode("hidingSelector","isChasing",make_shared<isChasing>(m_nodeMap,o));
    m_nodeMap->addNode("hidingSelector","hide",make_shared<Hide>(m_nodeMap,o,navigable,"isChasing"));
    m_nodeMap->addNode(ROOTNAME,"chasingSequence",sequence_p(m_nodeMap));
    m_nodeMap->addNode("chasingSequence","pickTarget",make_shared<pickTarget>(m_nodeMap,targets,"chase"));
    m_nodeMap->addNode("chasingSequence","wait",make_shared<Wait>(m_nodeMap,1.f));
    m_nodeMap->addNode("chasingSequence","chase",make_shared<Chase>(m_nodeMap,o,navigable,"isChasing","hide"));

}

void TagTree::setTagger(std::shared_ptr<GameObject> o) {
    m_nodeMap->getNode<Hide>("hide")->setTarget(o);
}

#include "tagcomponent.h"
#include "app/behaviortrees/tagtree/tagtree.h"

using namespace std;
using namespace glm;

TagComponent::TagComponent(shared_ptr<GameObject> o, vector<shared_ptr<GameObject>> targets, shared_ptr<GameObject> navigable) :
    Component(o.get())
{
    m_tree = make_shared<TagTree>(o,targets,navigable);
    m_isTagger = false;
}

void TagComponent::tick(float seconds) {
    m_tree->update(seconds);
}

void TagComponent::setTagger(std::shared_ptr<GameObject> tagger) {
    m_tree->setTagger(tagger);
}

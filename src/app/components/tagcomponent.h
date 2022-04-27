#ifndef TAGCOMPONENT_H
#define TAGCOMPONENT_H

#include "engine/util/CommonIncludes.h"
#include "components/basiccomponents.h"

class TagTree;

class TagComponent : public Component {
public:
    TagComponent(std::shared_ptr<GameObject> o, std::vector<std::shared_ptr<GameObject>> targets, std::shared_ptr<GameObject> navigable);

    void setTagging(bool val) {m_isTagger=val;}
    void setTagger(std::shared_ptr<GameObject> tagger);
    bool isTagger() {return m_isTagger;}

    void tick(float seconds) override;
    void buildTree();
private:
    std::shared_ptr<TagTree> m_tree;
    bool m_isTagger;
};

#endif // TAGCOMPONENT_H

#include "composite.h"

using namespace std;
using namespace glm;

Composite::Composite(composite_t i)  : BTreeNode(false,i) {
    m_prev = 0;
}

status_t Composite::update() {
    int i = getStart();
    bool cont = true;
    status_t status;
    while (true) {
        // Update status and determine if must break
        status = updaate_child(m_children[i]);
        cont = getContinue(status);

        // If must break, break
        if (!cont) break;

        // Move to next child
        i += 1;
    }
    // Set last running
    m_prev = i;
}

status_t Composite::updateChild(node_p child) {

}

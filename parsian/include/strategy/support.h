//
// Created by parsian-ai on 9/14/19.
//

#ifndef PARSIAN_SUPPORT_H
#define PARSIAN_SUPPORT_H


void Soccer::Support(std::vector<size_t> ids) {
    gotopoint(ids[0], {0, 0});
    if (ids.size() > 1) {
        gotopoint(ids[1], {1, 0});
    }
}

#endif //PARSIAN_SUPPORT_H

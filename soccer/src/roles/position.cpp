//
// Created by parsian-ai on 10/14/19.
//

#include <soccer.h>


void Soccer::position(std::vector<int> ids) {
    switch (ids.size()) {
        case 1: {
            const auto &id = ids.at(0);
            auto ball = wm->ball.pos + wm->ball.vel; ball.x -= 0.5;
            std::cout << field.ourBigPenalty.size().width() << std::endl;
            if (wm->ball.pos.absY() > field.ourBigPenalty.size().width() / 2) {
                move(id, Vector2D{ball.x, 0.0}, 0);
            } else if (wm->ball.pos.y > 0.0) {
                move(id, Vector2D{ball.x, field.ourBigPenalty.size().width() / 2 + 0.2}, 0);
            } else {
                move(id, Vector2D{ball.x, -field.ourBigPenalty.size().width() / 2 - 0.2}, 0);
            }
            break;
        }
        case 2: {
            const auto &a = ids.at(0);
            const auto &b = ids.at(1);
            auto ball = wm->ball.pos + wm->ball.vel; ball.x -= 0.5;
            std::cout << field.ourBigPenalty.size().width() << std::endl;
            if (wm->ball.pos.absY() > field.ourBigPenalty.size().width() / 2) {
                move(a, Vector2D{ball.x, 0.0}, 0);
                move(b, Vector2D{ball.x - 1, ball.y}, 0);
            } else if (wm->ball.pos.y > 0.0) {
                move(a, Vector2D{ball.x, field.ourBigPenalty.size().width() / 2 + 0.2}, 0);
                move(b, Vector2D{ball.x, -field.ourBigPenalty.size().width() / 2 - 0.2}, 0);
            } else {
                move(a, Vector2D{ball.x, -field.ourBigPenalty.size().width() / 2 - 0.2}, 0);
                move(b, Vector2D{ball.x, field.ourBigPenalty.size().width() / 2 + 0.2}, 0);
            }
        }
        default:break;
    }
}

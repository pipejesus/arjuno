//
// Created by greg on 15.02.2022.
//

#ifndef ARJUNO_INPUTHANDLER_H
#define ARJUNO_INPUTHANDLER_H


#include "../Entities/Hero.h"

class InputHandler {
public:
    ~InputHandler() = default;
    explicit InputHandler( Hero &h );
    void HandleInput( float dt, double et );
private:
    Hero &hero;

};


#endif //ARJUNO_INPUTHANDLER_H

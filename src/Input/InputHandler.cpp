//
// Created by greg on 15.02.2022.
//

#include "InputHandler.h"

InputHandler::InputHandler( Hero &h ): hero{h} {
}

void InputHandler::HandleInput( float dt, double et ) {
    if (IsGamepadAvailable(0))
    {
        if ( IsGamepadButtonDown(0, GAMEPAD_AXIS_RIGHT_X ) ) {
            hero.H_AccelerateRight( dt, et );
        }
        else if ( IsGamepadButtonDown(0, 4 ) ) {
            hero.H_AccelerateLeft( dt, et );
        }
        else {
            hero.Decelerate( dt, et );
        }

        /**
         * Handle direction change
         */
        if ( IsGamepadButtonPressed( 0, GAMEPAD_AXIS_RIGHT_X ) ) {
            hero.H_ChangeDirectionRight();
        }

        if ( IsGamepadButtonPressed( 0, 4 ) ) {
            hero.H_ChangeDirectionLeft();
        }

        if ( IsGamepadButtonPressed( 0, 8 ) ) {
            hero.H_AddCar(" ");
        }

        if ( IsGamepadButtonPressed( 0, 7 ) ) {
            hero.H_RemoveLastCar();
        }

    }
}

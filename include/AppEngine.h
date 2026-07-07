#pragma once
#include "AppState.h"

class AppEngine{
    private:
        bool isRunning;
        AppState* currentState;
    public:
        AppEngine();
        ~AppEngine();
        void run();
        void changeState(AppState* newState);
        void quit();
};
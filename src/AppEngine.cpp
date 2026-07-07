#include "AppEngine.h"

AppEngine::AppEngine(){
    currentState = nullptr;
    isRunning = true;
}
AppEngine::~AppEngine(){
    if (currentState){
        delete currentState;
    }
}
void AppEngine::run(){
    while (isRunning && currentState){
        currentState->handleInput();
        currentState->update();
        currentState->render();

    }
}   
void AppEngine::changeState(AppState* newState){
    if (currentState != nullptr){
        delete currentState;
    }
    currentState = newState;
}
void AppEngine::quit(){
    isRunning = false;
}
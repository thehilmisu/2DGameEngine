#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <vector>
#include <memory>
#include "GameState.h"

class StateManager {
public:
    virtual ~StateManager() = default;
    void Clean();
    void Render();
    void Update();

    void PopState();
    void PushState(GameState* current);
    void ChangeState(GameState* target);
    static StateManager* GetInstance(){return s_Instance = (s_Instance != nullptr)? s_Instance : new StateManager();}

private:
    StateManager(){}
    static StateManager* s_Instance;
    std::vector<GameState*> m_GameStates;
};

#endif // STATEMANAGER_H
#ifndef CAMERA_H
#define CAMERA_H

#include "SDL2/SDL.h"
#include "../Physics/Point.h"
#include "../Core/Engine.h"
#include "../Physics/Vector2D.h"

class Camera {

    public:

        void Update();
        inline int GetSceneWidth(){return m_SceneWidth;}
        inline int GetSceneHeight(){return m_SceneHeight;}

        inline SDL_Rect GetViewBox(){return m_ViewBox;}
        inline Vector2D GetPosition(){return m_Position;}

        inline void MoveX(float x){m_Position.X = x;}
        inline void MoveY(float y){m_Position.Y = y;}

        inline void SetTarget(Point* target){m_Target = target;}
        inline void SetSceneLimit(int w, int h){m_SceneWidth = w; m_SceneHeight = h;}

        inline static Camera* GetInstance(){return s_Instance = (s_Instance != nullptr) ? s_Instance : new Camera();}

    private:

        Camera();
        Point* m_Target;
        SDL_Rect m_ViewBox;
        Vector2D m_Position;
        static Camera* s_Instance;
        int m_SceneWidth, m_SceneHeight;
};

#endif // CAMERA_H

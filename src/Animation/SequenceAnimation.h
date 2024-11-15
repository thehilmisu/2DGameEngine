#ifndef SEQUENCEANIMATION_H
#define SEQUENCEANIMATION_H

#include <map>
#include <string>
#include <vector>
#include "SDL2/SDL.h"
#include "Animation.h"

struct Sequence{
    int Speed;
    int FrameCount;
    int Width;
    int Height;
    std::vector<std::string> TextureIDs;
};

class SequenceAnimation : public Animation {
public:
    SequenceAnimation(bool repeat = true);

    virtual void Update(float deltaTime);
    void Parse(std::string source);
    void SetCurrentSequence(std::string sequenceID);
    void SetRepeat(bool repeat) { m_Repeat = repeat; }
    void DrawFrame(float x, float y, float scaleX =1.0f, float scaleY =1.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
    Sequence m_CurrentSequence;
    std::map<std::string, Sequence> m_SequenceMap;
};

#endif // SEQUENCEANIMATION_H
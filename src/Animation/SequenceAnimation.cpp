
#include "SequenceAnimation.h"
#include "../Graphics/TextureManager.h"
#include "../Core/Log.h"
#include "tinyxml.h"

SequenceAnimation::SequenceAnimation(bool repeat) : Animation(repeat) 
{
}

void SequenceAnimation::DrawFrame(float x, float y, float scaleX, float scaleY, SDL_RendererFlip flip) 
{
    TextureManager::GetInstance()->DrawMultiple(m_CurrentSequence.TextureIDs[m_CurrentFrame], x, y, m_CurrentSequence.Width, m_CurrentSequence.Height, flip);
}

void SequenceAnimation::Update(float deltaTime) 
{
    if(m_Repeat || !m_IsEnded)
    {
       m_IsEnded = false;
       m_CurrentFrame = (SDL_GetTicks() / m_CurrentSequence.Speed) % m_CurrentSequence.FrameCount;
    }

    if(!m_Repeat && m_CurrentFrame == m_CurrentSequence.FrameCount - 1)
    {
        m_IsEnded = true;
        m_CurrentFrame = (m_CurrentSequence.FrameCount - 1);
    }
}

void SequenceAnimation::SetCurrentSequence(std::string sequenceID) 
{
    if (m_SequenceMap.count(sequenceID) > 0) 
    {
        m_CurrentSequence = m_SequenceMap[sequenceID];
    }
    else
    {
        CORE_ERROR("Given sequence animation is not matching");
    }
}

void SequenceAnimation::Parse(std::string source) 
{
    TiXmlDocument xml;
    xml.LoadFile(source);
    if(xml.Error())
    {
        CORE_ERROR("failed to load file : {0}", source);
    }

    TiXmlElement* root = xml.RootElement();
    for(TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
    {
        if(e->Value() == std::string("sequence"))
        {
            Sequence seq;
            std::string seqID = e->Attribute("id");
            e->Attribute("speed", &seq.Speed);
            e->Attribute("frameCount", &seq.FrameCount);
            e->Attribute("width", &seq.Width);
            e->Attribute("height", &seq.Height);
            
            for(TiXmlElement* t = e->FirstChildElement(); t != nullptr; t = t->NextSiblingElement())
            {
                seq.TextureIDs.push_back(t->Attribute("textureID"));
            }

            m_SequenceMap[seqID] = seq;
        }
       
    }
}




#ifndef LAYER_H
#define LAYER_H

class Layer
{
    public:
        virtual ~Layer() = default;
        virtual void Render() = 0;
        virtual void Update() = 0;
        
    private:

};

#endif
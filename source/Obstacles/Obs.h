#ifndef OBS_H
#define OBS_H

#include"Character.h"

class Obs:public Character
{
    public:
        Obs(Properties* props);
        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);

    protected:

    private:
};

#endif // OBS_H

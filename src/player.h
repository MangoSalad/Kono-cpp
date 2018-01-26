#ifndef PLAYER_H
#define PLAYER_H

class player{
    public:
        player();
        virtual void play(std::vector< std::vector <char> > &boardTable);
};

#endif
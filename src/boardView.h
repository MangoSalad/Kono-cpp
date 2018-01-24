#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include "stdafx.h"

class boardView {
    public:
        boardView();

        // Prints board in proper format.
        void showBoard(std::vector< std::vector <int> > &boardTable);
    
    protected:

    private:
};

#endif
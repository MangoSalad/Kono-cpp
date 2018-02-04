#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include "stdafx.h"

class boardView {
    public:

        // Default Constructor.
        boardView();

        // Prints board in proper format.
        void showBoard(std::vector< std::vector <char> > &boardTable) const;
    
    protected:

    private:
    
};

#endif
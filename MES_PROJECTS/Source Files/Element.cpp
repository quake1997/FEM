//
// Created by new on 2018-10-18.
//

#include "../Header Files/Element.h"



Element::Element()
{
}


Element::~Element()
{
}

void Element::showId() {

    for (int i = 0; i < 4; i++)
    {
        cout << id[i] << endl;
    }

}


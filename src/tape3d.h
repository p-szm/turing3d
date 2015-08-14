//
//  tape3d.h
//  turing3d
//
//  Created by Patrick on 11/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#ifndef __turing3d__tape3d__
#define __turing3d__tape3d__

#include <stdio.h>
#include "typedefs.h"
#include "infinite3dArray.h"

#define TAPE_SIZE 65

class Tape3d: public Infinite3dArray<Symbol>
{
    friend class Renderer;
public:
    Tape3d(Symbol default_symbol);
};

#endif /* defined(__turing3d__tape3d__) */

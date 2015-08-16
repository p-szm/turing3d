//
//  loader.h
//  turing3d
//
//  Created by Patrick on 12/08/2015.
//  Copyright (c) 2015 Patrick. All rights reserved.
//

#ifndef __turing3d__loader__
#define __turing3d__loader__

#include <stdio.h>
#include <string>
#include "typedefs.h"

class Tape3d;
class RuleBook;
class Renderer;
class TuringMachine3d;

int load_from_file(std::string filename, bool verbose, Tape3d*& tape, RuleBook*& rulebook,
                    TuringMachine3d*& machine, Renderer*& renderer);

#endif /* defined(__turing3d__loader__) */

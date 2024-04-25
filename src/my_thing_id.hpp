//
// Copyright Neil McGill, goblinhack@gmail.com
//

#pragma once
#ifndef _MY_THING_ID_HPP_
#define _MY_THING_ID_HPP_

#include "my_minimal.hpp"

#define THING_ID_ENTROPY_BITS 6
#define THING_ID_X_BITS       5
#define THING_ID_Y_BITS       5

//
// IDs below this are for templates
//
#define THING_ID_BASE (1U << (THING_ID_X_BITS + THING_ID_Y_BITS))

//
// A thing ID is composed like:
// [ Entropy bits] [ X bits ] [ Y bits]
//
#define THING_ID_ENTROPY_MASK (((1U << THING_ID_ENTROPY_BITS) - 1) << (THING_ID_X_BITS + THING_ID_Y_BITS))
#define THING_ID_X_MASK       (((1U << THING_ID_X_BITS) - 1) << THING_ID_Y_BITS)
#define THING_ID_Y_MASK       ((1U << THING_ID_Y_BITS) - 1)

#define THING_ID_GET_ENTROPY(id) ((id & THING_ID_ENTROPY_MASK) >> (THING_ID_X_BITS + THING_ID_Y_BITS))
#define THING_ID_GET_X(id)       ((id & THING_ID_X_MASK) >> (THING_ID_Y_BITS))
#define THING_ID_GET_Y(id)       ((id & THING_ID_Y_MASK))

#endif

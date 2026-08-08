#pragma once

#include <windows.h>

// Draw the four-story old-style building
// on the left side of 8A.
//
// Bottom floor = interactive storefronts
// Upper three floors = non-interactive apartments

void DrawOldBuilding(
    HDC hdc,
    int boardStartX,
    int boardStartY
);


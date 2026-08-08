#include "OldBuilding.h"
#include "Board.h"

void DrawOldBuilding(
    HDC hdc,
    int boardStartX,
    int boardStartY)
{
    // ==================================================
    // 9A POSITION
    // ==================================================
    //
    // Columns:
    //
    // 1  2  3  4  5  6  7  8  9  10 ...
    //
    // Rows:
    //
    // A = bottom
    // B
    // C
    // D
    // E
    // F = top
    //
    // Jackson Square occupies columns 7 and 8.
    //
    // Column 7 = 30px
    // Road      = 10px
    // Column 8 = 30px
    // Road      = 10px
    //
    // Therefore column 9 begins after:
    //
    // 30 + 10 + 30 + 10
    //
    // beyond the beginning of column 7.
    //
    // The building sits on the LEFT side of 9A.
    //


    // ==================================================
    // FIND 9A
    // ==================================================

    const int tileX =
        boardStartX +
        ROAD_SIZE +
        (6 * (TILE_SIZE + ROAD_SIZE)) +
        HALF_TILE +
        ROAD_SIZE +
        HALF_TILE +
        ROAD_SIZE;


    const int tileY =
        boardStartY +
        ROAD_SIZE +
        (5 * (TILE_SIZE + ROAD_SIZE));


    // ==================================================
    // BUILDING POSITION
    // ==================================================
    //
    // 9A is a normal 60px-wide tile.
    //
    // The building occupies the LEFT side of 9A.
    //
    // The road running vertically through 9A
    // remains to the RIGHT of the building.
    //

    const int buildingX =
        tileX;

    const int buildingWidth =
        HALF_TILE;


    // ==================================================
    // FOUR STORIES
    // ==================================================
    //
    // The 60px tile is divided into four floors.
    //

    const int floorHeight =
        TILE_SIZE / 4;


    // ==================================================
    // BUILDING BODY
    // ==================================================

    HBRUSH buildingBrush =
        CreateSolidBrush(
            RGB(145, 95, 65)
        );


    RECT buildingRect =
    {
        buildingX,
        tileY,
        buildingX + buildingWidth,
        tileY + TILE_SIZE
    };


    FillRect(
        hdc,
        &buildingRect,
        buildingBrush
    );


    DeleteObject(
        buildingBrush
    );


    // ==================================================
    // UPPER APARTMENT FLOORS
    // ==================================================
    //
    // Floors 2, 3 and 4.
    //
    // These are visual only.
    //

    HBRUSH apartmentBrush =
        CreateSolidBrush(
            RGB(185, 135, 90)
        );


    for (int floor = 1;
         floor < 4;
         floor++)
    {
        int top =
            tileY +
            floor * floorHeight;


        int bottom =
            top +
            floorHeight;


        RECT apartmentFloor =
        {
            buildingX + 1,
            top + 1,
            buildingX + buildingWidth - 1,
            bottom - 1
        };


        FillRect(
            hdc,
            &apartmentFloor,
            apartmentBrush
        );
    }


    DeleteObject(
        apartmentBrush
    );


    // ==================================================
    // STORE FRONT
    // ==================================================
    //
    // Ground floor.
    //
    // This will eventually be the interactive
    // portion of the building.
    //

    HBRUSH storefrontBrush =
        CreateSolidBrush(
            RGB(75, 65, 55)
        );


    RECT storefront =
    {
        buildingX + 2,
        tileY +
            (3 * floorHeight) +
            2,

        buildingX +
            buildingWidth -
            2,

        tileY +
            TILE_SIZE -
            2
    };


    FillRect(
        hdc,
        &storefront,
        storefrontBrush
    );


    DeleteObject(
        storefrontBrush
    );


    // ==================================================
    // WINDOWS
    // ==================================================
    //
    // Three apartment floors.
    //
    // Because the building is narrow, use one
    // centered window per floor.
    //

    HBRUSH windowBrush =
        CreateSolidBrush(
            RGB(190, 220, 225)
        );


    for (int floor = 0;
         floor < 3;
         floor++)
    {
        int windowTop =
            tileY +
            floor * floorHeight +
            3;


        RECT windowRect =
        {
            buildingX + 8,
            windowTop,

            buildingX +
                buildingWidth -
                8,

            windowTop +
                floorHeight -
                6
        };


        FillRect(
            hdc,
            &windowRect,
            windowBrush
        );
    }


    DeleteObject(
        windowBrush
    );


    // ==================================================
    // STOREFRONT DOOR
    // ==================================================

    HBRUSH doorBrush =
        CreateSolidBrush(
            RGB(55, 40, 30)
        );


    RECT doorRect =
    {
        buildingX + 3,
        tileY +
            (3 * floorHeight) +
            4,

        buildingX +
            buildingWidth -
            3,

        tileY +
            TILE_SIZE -
            3
    };


    FillRect(
        hdc,
        &doorRect,
        doorBrush
    );


    DeleteObject(
        doorBrush
    );


    // ==================================================
    // FLOOR DIVIDERS
    // ==================================================

    HPEN floorPen =
        CreatePen(
            PS_SOLID,
            1,
            RGB(70, 45, 30)
        );


    HPEN oldPen =
        (HPEN)SelectObject(
            hdc,
            floorPen
        );


    for (int floor = 1;
         floor < 4;
         floor++)
    {
        int y =
            tileY +
            floor * floorHeight;


        MoveToEx(
            hdc,
            buildingX,
            y,
            NULL
        );


        LineTo(
            hdc,
            buildingX + buildingWidth,
            y
        );
    }


    SelectObject(
        hdc,
        oldPen
    );


    DeleteObject(
        floorPen
    );
}


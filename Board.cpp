#include "Board.h"


void DrawBoard(
    HDC hdc,
    int clientWidth,
    int clientHeight)
{
    // ==================================================
    // CENTER BOARD
    // ==================================================

    int startX =
        (clientWidth - BOARD_WIDTH) / 2;

    int startY =
        (clientHeight - BOARD_HEIGHT) / 2;


    // ==================================================
    // DRAW ROAD BACKGROUND
    // ==================================================

    HBRUSH roadBrush =
        CreateSolidBrush(
            RGB(70, 70, 70)
        );


    RECT boardRect =
    {
        startX,
        startY,
        startX + BOARD_WIDTH,
        startY + BOARD_HEIGHT
    };


    FillRect(
        hdc,
        &boardRect,
        roadBrush
    );


    DeleteObject(
        roadBrush
    );


    // ==================================================
    // DRAW TILES
    // ==================================================

    int currentX =
        startX + ROAD_SIZE;


    for (int col = 0;
         col < BOARD_COLS;
         col++)
    {
        int columnWidth;


        // G and H are half-width columns.
        if (col == 6 || col == 7)
        {
            columnWidth =
                HALF_TILE;
        }
        else
        {
            columnWidth =
                TILE_SIZE;
        }


        for (int row = 0;
             row < BOARD_ROWS;
             row++)
        {
            int y =
                startY +
                ROAD_SIZE +
                row *
                (TILE_SIZE + ROAD_SIZE);


            // ==================================================
            // G6 AND H6
            // ==================================================
            //
            // These two blocks are Jackson Square.
            //
            // Jackson Square will be drawn separately.
            //

            if (row == 5 &&
                (col == 6 || col == 7))
            {
                continue;
            }


            // ==================================================
            // NORMAL TILE
            // ==================================================

            COLORREF color =
                RGB(240, 217, 181);


            HBRUSH brush =
                CreateSolidBrush(
                    color
                );


            RECT tile =
            {
                currentX,
                y,
                currentX + columnWidth,
                y + TILE_SIZE
            };


            FillRect(
                hdc,
                &tile,
                brush
            );


            DeleteObject(
                brush
            );
        }


        // Move to next column.
        currentX +=
            columnWidth +
            ROAD_SIZE;
    }
}

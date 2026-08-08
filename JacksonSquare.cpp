#include "JacksonSquare.h"
#include "Board.h"


void DrawJacksonSquare(
    HDC hdc,
    int boardStartX,
    int boardStartY)
{
    // ==================================================
    // JACKSON SQUARE
    // ==================================================
    //
    // G6 = 30px
    // H6 = 30px
    //
    // There is a 10px road between them.
    //
    // Therefore:
    //
    // 30 + 10 + 30 = 70px
    //
    // The vertical sidewalk is centered inside
    // that 10px road.
    // ==================================================


    // ==================================================
    // G6 POSITION
    // ==================================================

    const int jacksonX =
        boardStartX +
        ROAD_SIZE +
        (6 * (TILE_SIZE + ROAD_SIZE));


    const int jacksonY =
        boardStartY +
        ROAD_SIZE +
        (5 * (TILE_SIZE + ROAD_SIZE));


    // ==================================================
    // JACKSON SQUARE WIDTH
    // ==================================================
    //
    // G = 30
    // Road = 10
    // H = 30
    //
    // Total = 70
    //

    const int jacksonWidth =
        HALF_TILE +
        ROAD_SIZE +
        HALF_TILE;


    const int jacksonHeight =
        TILE_SIZE;


    // ==================================================
    // DRAW G6 AND H6 GREEN
    // ==================================================

    HBRUSH greenBrush =
        CreateSolidBrush(
            RGB(100, 150, 85)
        );


    // G6

    RECT g6 =
    {
        jacksonX,
        jacksonY,
        jacksonX + HALF_TILE,
        jacksonY + TILE_SIZE
    };


    FillRect(
        hdc,
        &g6,
        greenBrush
    );


    // H6

    RECT h6 =
    {
        jacksonX + HALF_TILE + ROAD_SIZE,
        jacksonY,
        jacksonX + HALF_TILE + ROAD_SIZE + HALF_TILE,
        jacksonY + TILE_SIZE
    };


    FillRect(
        hdc,
        &h6,
        greenBrush
    );


    DeleteObject(
        greenBrush
    );


    // ==================================================
    // JACKSON SQUARE CENTER
    // ==================================================
    //
    // The center is the center of the 10px road
    // between G6 and H6.
    //
    // 30 + 5 = 35
    //

    const int centerX =
        jacksonX +
        HALF_TILE +
        (ROAD_SIZE / 2);


    const int centerY =
        jacksonY +
        (jacksonHeight / 2);


    // ==================================================
    // SIDEWALK PEN
    // ==================================================

    HPEN sidewalkPen =
        CreatePen(
            PS_SOLID,
            SIDEWALK_SIZE,
            RGB(225, 220, 200)
        );


    HPEN oldPen =
        (HPEN)SelectObject(
            hdc,
            sidewalkPen
        );


    HBRUSH oldBrush =
        (HBRUSH)SelectObject(
            hdc,
            GetStockObject(
                NULL_BRUSH
            )
        );


    // ==================================================
    // VERTICAL SIDEWALK
    // ==================================================
    //
    // Runs through the road between G6 and H6.
    //

    MoveToEx(
        hdc,
        centerX,
        jacksonY,
        NULL
    );


    LineTo(
        hdc,
        centerX,
        jacksonY + jacksonHeight
    );


    // ==================================================
    // HORIZONTAL SIDEWALK
    // ==================================================
    //
    // Runs through the center of the square.
    //

    MoveToEx(
        hdc,
        jacksonX,
        centerY,
        NULL
    );


    LineTo(
        hdc,
        jacksonX + jacksonWidth,
        centerY
    );


    // ==================================================
    // THREE CENTERED OVAL SIDEWALKS
    // ==================================================

    const int outerWidth = 46;
    const int outerHeight = 28;

    const int middleWidth = 34;
    const int middleHeight = 20;

    const int innerWidth = 22;
    const int innerHeight = 12;


    // ==================================================
    // OUTER OVAL
    // ==================================================

    Ellipse(
        hdc,
        centerX - outerWidth / 2,
        centerY - outerHeight / 2,
        centerX + outerWidth / 2,
        centerY + outerHeight / 2
    );


    // ==================================================
    // MIDDLE OVAL
    // ==================================================

    Ellipse(
        hdc,
        centerX - middleWidth / 2,
        centerY - middleHeight / 2,
        centerX + middleWidth / 2,
        centerY + middleHeight / 2
    );


    // ==================================================
    // INNER OVAL
    // ==================================================

    Ellipse(
        hdc,
        centerX - innerWidth / 2,
        centerY - innerHeight / 2,
        centerX + innerWidth / 2,
        centerY + innerHeight / 2
    );


    // ==================================================
    // RESTORE GDI OBJECTS
    // ==================================================

    SelectObject(
        hdc,
        oldBrush
    );


    SelectObject(
        hdc,
        oldPen
    );


    DeleteObject(
        sidewalkPen
    );


    // ==================================================
    // LABEL
    // ==================================================

    SetBkMode(
        hdc,
        TRANSPARENT
    );


    SetTextColor(
        hdc,
        RGB(255, 255, 255)
    );


    HFONT font =
        CreateFont(
            9,
            0,
            0,
            0,
            FW_BOLD,
            FALSE,
            FALSE,
            FALSE,
            DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS,
            "Arial"
        );


    HFONT oldFont =
        (HFONT)SelectObject(
            hdc,
            font
        );


    RECT labelRect =
    {
        jacksonX,
        jacksonY + 2,
        jacksonX + jacksonWidth,
        jacksonY + 14
    };


    DrawText(
        hdc,
        "JACKSON SQUARE",
        -1,
        &labelRect,
        DT_CENTER |
        DT_SINGLELINE |
        DT_NOPREFIX
    );


    SelectObject(
        hdc,
        oldFont
    );


    DeleteObject(
        font
    );
}


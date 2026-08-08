#include <windows.h>

const int BOARD_COLS = 14;
const int BOARD_ROWS = 6;

const int TILE_SIZE = 60;
const int HALF_TILE = TILE_SIZE / 2;

const int ROAD_SIZE = 10;
const int SIDEWALK_SIZE = 3;


// ==================================================
// BOARD DIMENSIONS
// ==================================================

const int TILE_AREA_WIDTH =
    (12 * TILE_SIZE) +
    (2 * HALF_TILE) +
    ((BOARD_COLS - 1) * ROAD_SIZE);

const int TILE_AREA_HEIGHT =
    (BOARD_ROWS * TILE_SIZE) +
    ((BOARD_ROWS - 1) * ROAD_SIZE);

const int BOARD_WIDTH =
    TILE_AREA_WIDTH +
    (2 * ROAD_SIZE);

const int BOARD_HEIGHT =
    TILE_AREA_HEIGHT +
    (2 * ROAD_SIZE);


// ==================================================
// WINDOW PROCEDURE
// ==================================================

LRESULT CALLBACK WindowProc(
    HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_PAINT:
        {
            PAINTSTRUCT ps;

            HDC hdc =
                BeginPaint(hwnd, &ps);


            // ==================================================
            // CLIENT AREA
            // ==================================================

            RECT clientRect;

            GetClientRect(
                hwnd,
                &clientRect
            );

            int clientWidth =
                clientRect.right -
                clientRect.left;

            int clientHeight =
                clientRect.bottom -
                clientRect.top;


            // ==================================================
            // CENTER BOARD
            // ==================================================

            int startX =
                (clientWidth - BOARD_WIDTH) / 2;

            int startY =
                (clientHeight - BOARD_HEIGHT) / 2;


            // ==================================================
            // ROAD BACKGROUND
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
            // DRAW GRID
            // ==================================================

            int currentX =
                startX + ROAD_SIZE;


            for (int col = 0;
                 col < BOARD_COLS;
                 col++)
            {
                int columnWidth;


                // G and H are half-width.
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
                    // Both remain separate green blocks.
                    // The 10px road between them remains visible.
                    //

                    bool jacksonSquare =
                        (row == 5 &&
                         (col == 6 || col == 7));


                    COLORREF color;


                    if (jacksonSquare)
                    {
                        color =
                            RGB(100, 150, 85);
                    }
                    else
                    {
                        color =
                            RGB(240, 217, 181);
                    }


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


            // ==================================================
            // JACKSON SQUARE GEOMETRY
            // ==================================================
            //
            // G6 = 30px
            // H6 = 30px
            // Road = 10px
            //
            // Total area = 70px wide.
            //
            // The CENTER is therefore exactly:
            //
            // G width 30
            // + road 10
            // + H width 30
            //
            // 70 / 2 = 35
            // ==================================================


            const int jacksonX =
                startX +
                ROAD_SIZE +
                (6 * (TILE_SIZE + ROAD_SIZE));


            const int jacksonY =
                startY +
                ROAD_SIZE +
                (5 * (TILE_SIZE + ROAD_SIZE));


            const int jacksonWidth =
                HALF_TILE +
                ROAD_SIZE +
                HALF_TILE;


            const int jacksonHeight =
                TILE_SIZE;


            // ==================================================
            // EXACT CENTER
            // ==================================================

            const int centerX =
                jacksonX +
                (jacksonWidth / 2);


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
            // IMPORTANT:
            //
            // This is centered INSIDE the 10px road
            // between G6 and H6.
            //
            // Road:
            //
            //      30px       10px       30px
            //    ┌────────┐ ┌────────┐ ┌────────┐
            //    │        │ │  ROAD  │ │        │
            //    │   G6   │ │   │    │ │   H6   │
            //    │        │ │ SIDE-  │ │        │
            //    │        │ │  WALK  │ │        │
            //    └────────┘ └────────┘ └────────┘
            //
            // The sidewalk is 5px wide and centered
            // inside the 10px road.
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
            // This crosses the exact vertical center
            // of Jackson Square.
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
            // JACKSON SQUARE LABEL
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


            // ==================================================
            // FINISH
            // ==================================================

            EndPaint(
                hwnd,
                &ps
            );


            return 0;
        }


        // ==================================================
        // WINDOW RESIZED
        // ==================================================

        case WM_SIZE:
        {
            InvalidateRect(
                hwnd,
                NULL,
                TRUE
            );

            return 0;
        }


        // ==================================================
        // WINDOW CLOSED
        // ==================================================

        case WM_DESTROY:
        {
            PostQuitMessage(0);

            return 0;
        }
    }


    return DefWindowProc(
        hwnd,
        uMsg,
        wParam,
        lParam
    );
}


// ==================================================
// WIN MAIN
// ==================================================

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int nCmdShow)
{
    const char CLASS_NAME[] =
        "BoardGame";


    WNDCLASS wc = {};


    wc.lpfnWndProc =
        WindowProc;

    wc.hInstance =
        hInstance;

    wc.lpszClassName =
        CLASS_NAME;

    wc.hbrBackground =
        (HBRUSH)(COLOR_WINDOW + 1);


    RegisterClass(
        &wc
    );


    // ==================================================
    // WINDOW
    // ==================================================

    const int windowWidth =
        1200;

    const int windowHeight =
        700;


    HWND hwnd =
        CreateWindowEx(
            0,
            CLASS_NAME,
            "GameBoard",
            WS_OVERLAPPEDWINDOW,

            CW_USEDEFAULT,
            CW_USEDEFAULT,

            windowWidth,
            windowHeight,

            NULL,
            NULL,
            hInstance,
            NULL
        );


    if (hwnd == NULL)
        return 0;


    ShowWindow(
        hwnd,
        nCmdShow
    );


    UpdateWindow(
        hwnd
    );


    // ==================================================
    // MESSAGE LOOP
    // ==================================================

    MSG msg = {};


    while (
        GetMessage(
            &msg,
            NULL,
            0,
            0
        ))
    {
        TranslateMessage(
            &msg
        );

        DispatchMessage(
            &msg
        );
    }


    return 0;
}


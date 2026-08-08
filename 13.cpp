#include <windows.h>

const int BOARD_COLS = 14;
const int BOARD_ROWS = 6;

const int TILE_SIZE = 60;
const int HALF_TILE = TILE_SIZE / 2;

const int ROAD_SIZE = 10;


// --------------------------------------------------
// BOARD DIMENSIONS
// --------------------------------------------------

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


// --------------------------------------------------
// WINDOW PROCEDURE
// --------------------------------------------------

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
            HDC hdc = BeginPaint(hwnd, &ps);


            // -----------------------------------------
            // GET CLIENT AREA
            // -----------------------------------------

            RECT clientRect;

            GetClientRect(
                hwnd,
                &clientRect
            );

            int clientWidth =
                clientRect.right - clientRect.left;

            int clientHeight =
                clientRect.bottom - clientRect.top;


            // -----------------------------------------
            // CENTER BOARD
            // -----------------------------------------

            int startX =
                (clientWidth - BOARD_WIDTH) / 2;

            int startY =
                (clientHeight - BOARD_HEIGHT) / 2;


            // -----------------------------------------
            // DRAW ROAD BACKGROUND
            // -----------------------------------------

            COLORREF roadColor =
                RGB(70, 70, 70);

            HBRUSH roadBrush =
                CreateSolidBrush(roadColor);


            RECT boardArea =
            {
                startX,
                startY,
                startX + BOARD_WIDTH,
                startY + BOARD_HEIGHT
            };


            FillRect(
                hdc,
                &boardArea,
                roadBrush
            );


            DeleteObject(roadBrush);


            // -----------------------------------------
            // DRAW TILES
            // -----------------------------------------

            int currentX =
                startX + ROAD_SIZE;


            for (int col = 0; col < BOARD_COLS; col++)
            {
                int columnWidth;

                if (col == 6 || col == 7)
                    columnWidth = HALF_TILE;
                else
                    columnWidth = TILE_SIZE;


                for (int row = 0; row < BOARD_ROWS; row++)
                {
                    int y =
                        startY +
                        ROAD_SIZE +
                        row * (TILE_SIZE + ROAD_SIZE);


                    // ---------------------------------
                    // JACKSON SQUARE
                    // ---------------------------------
                    //
                    // G6 and H6 together form
                    // one 60 x 60 square.
                    //

                    bool isJacksonSquare =
                        (row == 5 &&
                         (col == 6 || col == 7));


                    COLORREF color;


                    if (isJacksonSquare)
                    {
                        // Jackson Square
                        color = RGB(100, 150, 85);
                    }
                    else
                    {
                        // Normal building block
                        color = RGB(240, 217, 181);
                    }


                    HBRUSH brush =
                        CreateSolidBrush(color);


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


                    DeleteObject(brush);
                }


                currentX +=
                    columnWidth + ROAD_SIZE;
            }


            // -----------------------------------------
            // LABEL JACKSON SQUARE
            // -----------------------------------------
            //
            // G6 + H6 form one 60px wide area.
            //

            int jacksonX =
                startX +
                ROAD_SIZE +
                (6 * (TILE_SIZE + ROAD_SIZE));

            int jacksonY =
                startY +
                ROAD_SIZE +
                (5 * (TILE_SIZE + ROAD_SIZE));


            RECT jacksonRect =
            {
                jacksonX,
                jacksonY,
                jacksonX + TILE_SIZE,
                jacksonY + TILE_SIZE
            };


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
                    11,
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


            DrawText(
                hdc,
                "JACKSON\nSQUARE",
                -1,
                &jacksonRect,
                DT_CENTER |
                DT_VCENTER |
                DT_NOPREFIX
            );


            SelectObject(
                hdc,
                oldFont
            );

            DeleteObject(font);


            EndPaint(
                hwnd,
                &ps
            );

            return 0;
        }


        // -----------------------------------------
        // RECENTER WHEN RESIZED
        // -----------------------------------------

        case WM_SIZE:
        {
            InvalidateRect(
                hwnd,
                NULL,
                TRUE
            );

            return 0;
        }


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


// --------------------------------------------------
// WIN MAIN
// --------------------------------------------------

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


    RegisterClass(&wc);


    int windowWidth = 1200;
    int windowHeight = 700;


    HWND hwnd = CreateWindowEx(
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


    UpdateWindow(hwnd);


    MSG msg = {};


    while (GetMessage(
        &msg,
        NULL,
        0,
        0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


    return 0;
}

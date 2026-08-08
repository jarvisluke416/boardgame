#include <windows.h>

const int BOARD_COLS = 14;
const int BOARD_ROWS = 6;

const int TILE_SIZE = 60;
const int HALF_TILE = TILE_SIZE / 2;

const int ROAD_SIZE = 10;


// --------------------------------------------------
// TILE AREA
// --------------------------------------------------
//
// 12 full columns = 12 * 60
// 2 half columns  = 2 * 30
// 13 internal roads = 13 * 10
//
// Width = 910 pixels
//
// 6 rows = 6 * 60
// 5 internal roads = 5 * 10
//
// Height = 410 pixels
//

const int TILE_AREA_WIDTH =
    (12 * TILE_SIZE) +
    (2 * HALF_TILE) +
    ((BOARD_COLS - 1) * ROAD_SIZE);

const int TILE_AREA_HEIGHT =
    (BOARD_ROWS * TILE_SIZE) +
    ((BOARD_ROWS - 1) * ROAD_SIZE);


// --------------------------------------------------
// COMPLETE BOARD
// --------------------------------------------------
//
// Add a 10px road around ALL four edges.
//

const int BOARD_WIDTH =
    TILE_AREA_WIDTH +
    (2 * ROAD_SIZE);

const int BOARD_HEIGHT =
    TILE_AREA_HEIGHT +
    (2 * ROAD_SIZE);


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
            // CENTER COMPLETE BOARD
            // -----------------------------------------

            int startX =
                (clientWidth - BOARD_WIDTH) / 2;

            int startY =
                (clientHeight - BOARD_HEIGHT) / 2;


            // -----------------------------------------
            // DRAW ENTIRE BOARD AS ROAD
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
            //
            // Start 10 pixels inside the board.
            // This creates the outer road.
            //

            int currentX =
                startX + ROAD_SIZE;


            for (int col = 0; col < BOARD_COLS; col++)
            {
                // Columns 7 and 8 are half-width
                int columnWidth;

                if (col == 6 || col == 7)
                    columnWidth = HALF_TILE;
                else
                    columnWidth = TILE_SIZE;


                for (int row = 0; row < BOARD_ROWS; row++)
                {
                    // Start 10 pixels below the top edge.
                    //
                    // ROAD_SIZE between each row creates
                    // the internal horizontal roads.

                    int y =
                        startY +
                        ROAD_SIZE +
                        row * (TILE_SIZE + ROAD_SIZE);


                    // Tile color
                    COLORREF color =
                        RGB(240, 217, 181);


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


                // Move to the next column.
                //
                // The ROAD_SIZE creates the road
                // between each column.

                currentX +=
                    columnWidth + ROAD_SIZE;
            }


            EndPaint(
                hwnd,
                &ps
            );


            return 0;
        }


        // -----------------------------------------
        // KEEP BOARD CENTERED WHEN RESIZED
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


int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE,
    LPSTR,
    int nCmdShow)
{
    const char CLASS_NAME[] =
        "BoardGame";


    // -----------------------------------------
    // WINDOW CLASS
    // -----------------------------------------

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


    // -----------------------------------------
    // WINDOW
    // -----------------------------------------

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


    // -----------------------------------------
    // MESSAGE LOOP
    // -----------------------------------------

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


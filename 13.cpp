#include <windows.h>

const int BOARD_COLS = 14;
const int BOARD_ROWS = 6;

const int TILE_SIZE = 60;
const int HALF_TILE = TILE_SIZE / 2;

const int ROAD_SIZE = 10;

// Board dimensions
//
// Width:
// 12 full tiles  = 12 * 60
// 2 half tiles   = 2 * 30
// 13 roads       = 13 * 10
//
// Total = 880 pixels
//
// Height:
// 6 tiles        = 6 * 60
// 5 roads        = 5 * 10
//
// Total = 410 pixels

const int BOARD_WIDTH =
    (12 * TILE_SIZE) +
    (2 * HALF_TILE) +
    ((BOARD_COLS - 1) * ROAD_SIZE);

const int BOARD_HEIGHT =
    (BOARD_ROWS * TILE_SIZE) +
    ((BOARD_ROWS - 1) * ROAD_SIZE);


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

            // Get the actual drawable area
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);

            int clientWidth =
                clientRect.right - clientRect.left;

            int clientHeight =
                clientRect.bottom - clientRect.top;


            // -----------------------------------------
            // CENTER THE BOARD
            // -----------------------------------------

            int startX =
                (clientWidth - BOARD_WIDTH) / 2;

            int startY =
                (clientHeight - BOARD_HEIGHT) / 2;


            // -----------------------------------------
            // DRAW ROAD BACKGROUND
            // -----------------------------------------

            COLORREF roadColor = RGB(70, 70, 70);

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

            int currentX = startX;


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
                    // Vertical position includes the road
                    int y =
                        startY +
                        row * (TILE_SIZE + ROAD_SIZE);


                    // Alternate tile colors
                    COLORREF color;

                    if ((row + col) % 2 == 0)
                        color = RGB(240, 217, 181);
                    else
                        color = RGB(240, 217, 181);


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
                // The extra ROAD_SIZE creates
                // the road between tiles.
                currentX +=
                    columnWidth + ROAD_SIZE;
            }


            EndPaint(hwnd, &ps);

            return 0;
        }


        // Recenter whenever the window changes size
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
    const char CLASS_NAME[] = "BoardGame";


    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

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


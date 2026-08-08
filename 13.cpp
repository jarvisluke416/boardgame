#include <windows.h>

const int BOARD_COLS = 14;
const int BOARD_ROWS = 6;
const int TILE_SIZE = 70;
const int HALF_TILE = TILE_SIZE / 2;

// Board dimensions:
// 12 full columns + 2 half columns
const int BOARD_WIDTH = (12 * TILE_SIZE) + (2 * HALF_TILE);
const int BOARD_HEIGHT = BOARD_ROWS * TILE_SIZE;


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

            // Get the EXACT drawable/client area
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);

            int clientWidth = clientRect.right;
            int clientHeight = clientRect.bottom;


            // -----------------------------------------
            // PERFECTLY CENTER THE BOARD
            // -----------------------------------------

            int startX =
                (clientWidth - BOARD_WIDTH) / 2;

            int startY =
                (clientHeight - BOARD_HEIGHT) / 2;


            // -----------------------------------------
            // DRAW BOARD
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
                    int x = currentX;
                    int y = startY + (row * TILE_SIZE);


                    // Checkerboard colors
                    COLORREF color;

                    if ((row + col) % 2 == 0)
                        color = RGB(240, 217, 181);
                    else
                        color = RGB(181, 136, 99);


                    HBRUSH brush =
                        CreateSolidBrush(color);


                    RECT tile =
                    {
                        x,
                        y,
                        x + columnWidth,
                        y + TILE_SIZE
                    };


                    FillRect(
                        hdc,
                        &tile,
                        brush
                    );


                    DeleteObject(brush);
                }


                currentX += columnWidth;
            }


            EndPaint(hwnd, &ps);

            return 0;
        }


        // Repaint when the window is resized
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
    // WINDOW SIZE
    // -----------------------------------------

    int windowWidth = 1200;
    int windowHeight = 700;


    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "My Board Game",
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

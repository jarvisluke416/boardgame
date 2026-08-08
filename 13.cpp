#include <windows.h>

const int BOARD_COLS = 14;
const int BOARD_ROWS = 6;
const int TILE_SIZE = 70;
const int HALF_TILE = TILE_SIZE / 2;

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

            // Get the size of the window's client area
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);

            int clientWidth = clientRect.right - clientRect.left;
            int clientHeight = clientRect.bottom - clientRect.top;

            // ------------------------------------------------
            // Board layout
            //
            // Columns 1-6  = 70 pixels
            // Column 7     = 35 pixels
            // Column 8     = 35 pixels
            // Columns 9-14 = 70 pixels
            //
            // Total width:
            // 12 * 70 + 2 * 35 = 910 pixels
            // ------------------------------------------------

            int boardWidth = (12 * TILE_SIZE) + (2 * HALF_TILE);
            int boardHeight = BOARD_ROWS * TILE_SIZE;

            // Center the board
            int startX = (clientWidth - boardWidth) / 2;
            int startY = (clientHeight - boardHeight) / 2;

            // Current X position
            int currentX = startX;

            // Draw all 14 visual columns
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
                    int y = startY + row * TILE_SIZE;

                    // Alternate colors
                    COLORREF color;

                    if ((row + col) % 2 == 0)
                        color = RGB(240, 217, 181);
                    else
                        color = RGB(181, 136, 99);

                    HBRUSH brush = CreateSolidBrush(color);

                    RECT tile =
                    {
                        x,
                        y,
                        x + columnWidth,
                        y + TILE_SIZE
                    };

                    FillRect(hdc, &tile, brush);

                    DeleteObject(brush);
                }

                // Move to the next column
                currentX += columnWidth;
            }

            EndPaint(hwnd, &ps);

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
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    // Window size
    int windowWidth = 1100;
    int windowHeight = 600;

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


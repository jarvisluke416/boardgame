#include <windows.h>

const int BOARD_COLS = 13;
const int BOARD_ROWS = 6;
const int TILE_SIZE = 70;

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

            // Calculate the total board size
            int boardWidth = BOARD_COLS * TILE_SIZE;
            int boardHeight = BOARD_ROWS * TILE_SIZE;

            // Center the board in the window
            int startX = (clientWidth - boardWidth) / 2;
            int startY = (clientHeight - boardHeight) / 2;

            // Draw the board
            for (int row = 0; row < BOARD_ROWS; row++)
            {
                for (int col = 0; col < BOARD_COLS; col++)
                {
                    int x = startX + col * TILE_SIZE;
                    int y = startY + row * TILE_SIZE;

                    // Alternate tile colors
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
                        x + TILE_SIZE,
                        y + TILE_SIZE
                    };

                    FillRect(hdc, &tile, brush);

                    DeleteObject(brush);
                }
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

    // Desired client area size.
    // The board itself is 910 x 420.
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


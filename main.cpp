#include <windows.h>

#include "Board.h"
#include "JacksonSquare.h"


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
        // ==================================================
        // PAINT
        // ==================================================

        case WM_PAINT:
        {
            PAINTSTRUCT ps;

            HDC hdc =
                BeginPaint(
                    hwnd,
                    &ps
                );


            // ==================================================
            // CLIENT SIZE
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
            // BOARD POSITION
            // ==================================================

            int boardStartX =
                (clientWidth - BOARD_WIDTH) / 2;

            int boardStartY =
                (clientHeight - BOARD_HEIGHT) / 2;


            // ==================================================
            // DRAW BOARD
            // ==================================================

            DrawBoard(
                hdc,
                clientWidth,
                clientHeight
            );


            // ==================================================
            // DRAW JACKSON SQUARE
            // ==================================================

            DrawJacksonSquare(
                hdc,
                boardStartX,
                boardStartY
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
            PostQuitMessage(
                0
            );

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


    // ==================================================
    // WINDOW CLASS
    // ==================================================

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


    // ==================================================
    // SHOW WINDOW
    // ==================================================

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


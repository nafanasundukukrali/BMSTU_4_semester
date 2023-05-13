.386  
.model flat, stdcall 
option casemap:none 

include \masm32\include\windows.inc
include \masm32\include\user32.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\user32.lib
includelib \masm32\lib\kernel32.lib

.data
class_name        db    "win_class", 0     
win_name          db    "Сумма чисел", 0
text_name         db    "static", 0
text_text         db    "+", 0 
button_name       db    "button", 0        
button_text       db    "=", 0           
edit_name         db    "edit", 0          
format_result     db    "%d", 0   
button_id   equ    1 
edit_id     equ    2
text_id     equ    0        

.data?
hinstance        HINSTANCE ?     
command_line     LPSTR ?         
hwnd_button      HWND ?           
hwnd_text        HWND ?         
hwnd_edit1       HWND ?           
hwnd_edit2       HWND ?           
buf              db             2 dup(?)   


.code

main_window    proc    hinst:HINSTANCE, hPrevInst:HINSTANCE, CmdLine:DWORD, CmdShow:DWORD
    LOCAL    wc:WNDCLASSEX 
    LOCAL    msg:MSG 
    LOCAL    hwnd:HWND 


    mov wc.cbSize,         sizeof WNDCLASSEX
    mov wc.style,          CS_HREDRAW or CS_VREDRAW 
    mov wc.lpfnWndProc,    offset numbers_sum
    mov wc.cbClsExtra,     NULL
    mov wc.cbWndExtra,     NULL
    push   hinst
    pop    wc.hInstance 
    mov wc.hbrBackground,COLOR_BTNFACE+1
    mov    wc.lpszMenuName, NULL
    mov    wc.lpszClassName, offset class_name 
    invoke    LoadCursor, NULL, IDC_ARROW
    mov       wc.hCursor, eax
    invoke    RegisterClassEx, addr wc 
    
    invoke    CreateWindowEx, WS_EX_CLIENTEDGE, addr class_name,\
        addr win_name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,\
        CW_USEDEFAULT, 300, 300, NULL, NULL, hinst, NULL
    mov    hwnd, eax 

    invoke    ShowWindow, hwnd, SW_SHOWNORMAL 
    invoke    UpdateWindow, hwnd 

.WHILE TRUE
    invoke    GetMessage, addr msg, NULL, 0, 0
.BREAK .IF(!eax)
    invoke    TranslateMessage, addr msg
    invoke    DispatchMessage, addr msg
.ENDW
    mov    eax, msg.wParam
    ret
main_window    endp


numbers_sum    proc  hwnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
.IF uMsg == WM_DESTROY
    invoke    PostQuitMessage, NULL
.ELSEIF uMsg == WM_CREATE
    invoke    CreateWindowEx,WS_EX_CLIENTEDGE,addr edit_name,\
        NULL, WS_CHILD or WS_VISIBLE or WS_BORDER or ES_LEFT or\
        ES_AUTOHSCROLL, 50, 35, 200, 25, hwnd, 8, hinstance, NULL
    mov    hwnd_edit1, eax
    
    invoke    CreateWindowEx, WS_EX_CLIENTEDGE, addr edit_name,\
        NULL, WS_CHILD or WS_VISIBLE or WS_BORDER or ES_LEFT or\
        ES_AUTOHSCROLL, 50, 105, 200, 25, hwnd, 8, hinstance, NULL
    mov    hwnd_edit2, eax

    invoke    CreateWindowEx, NULL, addr button_name, addr button_text,\
        WS_CHILD or WS_VISIBLE or BS_DEFPUSHBUTTON,
        75, 140, 140, 25, hwnd, button_id, hinstance, NULL
    mov    hwnd_button, eax

    invoke CreateWindowEx, 0,
            addr text_name, addr text_text,
            WS_CHILD or WS_VISIBLE or ES_LEFT,
            75,70,140,25, hwnd, text_id,
            hinstance, NULL
            
    mov    hwnd_text, eax


.ELSEIF uMsg == WM_COMMAND
    mov    eax, wParam 
    .IF ax == button_id 
        shr eax, 16
        .IF ax == BN_CLICKED
            push    edi
            push    ebx
            invoke GetWindowText, hwnd_edit1, addr buf, 2
            xor    edi, edi
            xor    eax, eax
            xor    ebx, ebx            
            mov    cx, 10
            mov    bl, byte ptr buf[edi]
            sub    bl, '0'
            mul    cx
            add    eax, ebx
            push   eax
            invoke GetWindowText, hwnd_edit2, addr buf, 2
            xor    edi, edi
            xor    eax, eax
            xor    ebx, ebx
            mov    cx, 10
            mov    bl, byte ptr buf[edi]
            sub    bl, '0'
            mul    cx
            add    eax, ebx
            pop    ebx
            add eax, ebx
            invoke wsprintf, addr buf, addr format_result, eax
            invoke MessageBox, hwnd, addr buf, addr win_name, MB_OK

            pop    ebx
            pop    edi
        .ENDIF
   .ENDIF
.ELSE 
    invoke    DefWindowProc,hwnd,uMsg,wParam,lParam
    ret
.ENDIF
    xor    eax, eax
    ret
numbers_sum    endp

start:
    invoke    GetModuleHandle, NULL
    mov       hinstance, eax 
    invoke    main_window, hinstance, NULL, NULL, SW_SHOWDEFAULT
    invoke    ExitProcess, eax 

end    start
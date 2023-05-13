struc xserver
    .pDisplay:              resd 1
    .pScreen:               resd 1
    .screen_number:         resd 1
    .size:
endstruc

struc xswa
    .background_pixmap:     resd 1
    .background_pixel:      resd 1
    .border_pixmap:         resd 1
    .border_pixel:          resd 1
    .bit_gravity:           resd 1
    .win_gravity:           resd 1
    .backing_store:         resd 1
    .backing_planes:        resd 1
    .backing_pixel:         resd 1
    .save_under:            resd 1
    .event_mask:            resd 1
    .do_not_propagate_mask: resd 1
    .override_redirect:     resd 1
    .colormap:              resd 1
    .cursor:                resd 1
    .size:
endstruc

struc xwin
    .rootwindow:            resd 1
    .window:                resd 1
    .x:                     resd 1
    .y:                     resd 1
    .width:                 resd 1
    .height:                resd 1
    .border_width:          resd 1
    .depth:                 resd 1
    .class:                 resd 1
    .visual:                resd 1
    .valuemask:             resd 1
    .wm_delete_msg:         resd 1
    .atom_name:             resd 4
    .size:
endstruc

struc xevent
    .data:                  resd 24
    .size: 
endstruc

; ---- section read/write data --------------------------------------
section .data

gui_t:
    istruc xserver
    at xserver.pDisplay,           dd 0      ;+0
    at xserver.pScreen,            dd 0      ;+1
    at xserver.screen_number,      dd 0      ;+2
    iend

    istruc xswa
    at xswa.background_pixmap,     dd 0      ;+3
    at xswa.background_pixel,      dd 0      ;+4
    at xswa.border_pixmap,         dd 0      ;+5
    at xswa.border_pixel,          dd 0      ;+6
    at xswa.bit_gravity,           dd 0      ;+7
    at xswa.win_gravity,           dd 0      ;+8
    at xswa.backing_store,         dd 0      ;+9
    at xswa.backing_planes,        dd 0      ;+10
    at xswa.backing_pixel,         dd 0      ;+11
    at xswa.save_under,            dd 0      ;+12
    at xswa.event_mask,            dd 0b0000000000000000000000100 ;+13
    at xswa.do_not_propagate_mask, dd 0      ;+14
    at xswa.override_redirect,     dd 0      ;+15
    at xswa.colormap,              dd 0      ;+16
    at xswa.cursor,                dd 0      ;+17
    iend

    istruc xwin
    at xwin.rootwindow,            dd 0      ;+18
    at xwin.window,                dd 0      ;+19
    at xwin.x,                     dd 100    ;+20
    at xwin.y,                     dd 100    ;+21
    at xwin.width,                 dd 640    ;+22
    at xwin.height,                dd 480    ;+23
    at xwin.border_width,          dd 4      ;+24
    at xwin.depth,                 dd 24     ;+25
    at xwin.class,                 dd 1      ;+26
    at xwin.visual,                dd 0      ;+27
    at xwin.valuemask,             dd 0b000100000001010 ;+28
    at xwin.wm_delete_msg,         dd 0      ;+29
    at xwin.atom_name,             dd "WM_D" ;+30
                                   dd "ELET" ;+31
                                   dd "E_WI" ;+32
                                   dd "NDOW" ;+33
    iend

    istruc xevent
    at xevent.data,       times 24 dd 0
    iend

; ---- section instruction code -------------------------------------
section .text

extern XOpenDisplay
extern XDisplayName
extern XDefaultScreen
extern XDefaultScreenOfDisplay
extern XRootWindow
extern XWhitePixel
extern XBlackPixel
extern XCreateWindow
extern XMapWindow
extern XNextEvent
extern XCloseDisplay
extern XInternAtom
extern XSetWMProtocols

global _start
_start:

; -------------------------------------------------------------------
; connect to x server by calling:
; Display *XOpenDisplay(char *display_name)
;
; Set display_name=NULL because we want the XOpenDisplay()
; to connect to the server specified in the UNIX environment
; DISPLAY variable. Use BASH command "echo $DISPLAY" to view
; the current contents of the DISPLAY environment variable.
; -------------------------------------------------------------------
    sub    esp, 4                        ;reserve 4 bytes
    mov    dword [esp], 0                ;arg1: NULL
    call   XOpenDisplay
    add    esp, 4                        ;restore 4 bytes
    mov    [gui_t+xserver.pDisplay], eax

; -------------------------------------------------------------------
; get default screen by calling:
; int XDefaultScreen(Display *display)
;
; This function should be used to retrieve the screen number in
; applications that will use only a single screen.
; -------------------------------------------------------------------
    sub    esp, 4                             ;reserve 4 bytes
    mov    eax, [gui_t+xserver.pDisplay]
    mov    [esp], eax                         ;arg1: pDisplay
    call   XDefaultScreen
    add    esp, 4                             ;restore 4 bytes
    mov    [gui_t+xserver.screen_number], eax

; -------------------------------------------------------------------
; get pointer to the default screen:
; Screen *XDefaultScreenOfDisplay(Display *display)
;
; This function returns a pointer to the default screen.
; -------------------------------------------------------------------
    sub    esp, 4                        ;reserve 4 bytes
    mov    eax, [gui_t+xserver.pDisplay]
    mov    [esp], eax                    ;arg1: pDisplay
    call   XDefaultScreenOfDisplay
    add    esp, 4                        ;restore 4 bytes
    mov    [gui_t+xserver.pScreen], eax

; -------------------------------------------------------------------
; set atom delete window message:
; Atom XInternAtom(Display *display,
;                  char    *atom_name,
;                  Bool     only_if_exists)
;
; This function returns the atom identifier associated with the
; specified atom_name string.
; -------------------------------------------------------------------
    sub    esp, 12        ;reserve 12 bytes
    mov    eax, [gui_t+xserver.pDisplay]
    mov    ebx, gui_t
    add    ebx, xserver.size
    add    ebx, xswa.size
    add    ebx, xwin.atom_name
    xor    ecx, ecx
    mov    [esp    ], eax ;arg1: pDisplay
    mov    [esp + 4], ebx ;arg2: atom_name
    mov    [esp + 8], ecx ;arg3: FALSE
    call   XInternAtom
    add    esp, 12        ;restore 12 bytes
    mov    [gui_t+xserver.size+xswa.size+xwin.wm_delete_msg], eax

; -------------------------------------------------------------------
; get rootwindow by calling:
; Window XRootWindow(Display *display, int screen_number)
;
; Useful function if want a drawable of a particular screen
; and for creating top-level windows.
; -------------------------------------------------------------------
    sub    esp, 8                             ;reserve 8 bytes
    mov    eax, [gui_t+xserver.pDisplay]
    mov    ebx, [gui_t+xserver.screen_number]
    mov    [esp    ], eax                     ;arg1: pDisplay
    mov    [esp + 4], ebx                     ;arg2: screen_number
    call   XRootWindow
    add    esp, 8                             ;restore 8 bytes
    mov    [gui_t+xserver.size+xswa.size+\
           xwin.rootwindow], eax

; -------------------------------------------------------------------
; set window attribute background pixel color:
; unsigned long XBlackPixel(Display *display, int screen_number)
;
; This function returns the black pixel value.
; -------------------------------------------------------------------
    sub    esp, 8                             ; reserve 8 bytes
    mov    eax, [gui_t+xserver.pDisplay]
    mov    ebx, [gui_t+xserver.screen_number]
    mov    [esp    ], eax                     ; arg1: pDisplay
    mov    [esp + 4], ebx                     ; arg2: screen_number
    call   XBlackPixel
    add    esp, 8                             ; restore 8 bytes
    mov    [gui_t+xserver.size+\
           xswa.background_pixel], eax

; -------------------------------------------------------------------
; set window attribute border pixel color:
; unsigned long XWhitePixel(Display *display, int screen_number)
;
; This function returns the white pixel value.
; -------------------------------------------------------------------
    sub    esp, 8                             ; reserve 8 bytes
    mov    eax, [gui_t+xserver.pDisplay]
    mov    ebx, [gui_t+xserver.screen_number]
    mov    [esp    ], eax                     ; arg1: pDisplay
    mov    [esp + 4], ebx                     ; arg2: screen_number
    call   XWhitePixel
    add    esp, 8                             ; restore 8 bytes
    mov    [gui_t+xserver.size+\
           xswa.border_pixel], eax

; -------------------------------------------------------------------
; create the window:
; Window XCreateWindow(Display display,
;                      Window parent,
;                      int x,
;                      int y,
;                      unsigned int width,
;                      unsigned int height,
;                      unsigned int border_width,
;                      int depth,
;                      unsigned int class,
;                      Visual *visual,
;                      unsigned long valuemask,
;                      XSetWindowAttributes *attributes)
;
; This function creates an unmapped subwindow for a specified
; parent window. It returns the window ID of the created window
; and causes X server to generate a CreateNotify event.
; -------------------------------------------------------------------
    sub    esp, 48 ;reserve 48 bytes
    mov    eax, [gui_t+xserver.pDisplay]
    mov    ebx, [gui_t+xserver.size+xswa.size+xwin.rootwindow]
    mov    ecx, [gui_t+xserver.size+xswa.size+xwin.x]
    mov    edx, [gui_t+xserver.size+xswa.size+xwin.y]
    mov    [esp     ], eax ;arg1
    mov    [esp +  4], ebx ;arg2
    mov    [esp +  8], ecx ;arg3
    mov    [esp + 12], edx ;arg4
    mov    eax, [gui_t+xserver.size+xswa.size+xwin.width]
    mov    ebx, [gui_t+xserver.size+xswa.size+xwin.height]
    mov    ecx, [gui_t+xserver.size+xswa.size+xwin.border_width]
    mov    edx, [gui_t+xserver.size+xswa.size+xwin.depth]
    mov    [esp + 16], eax ;arg5
    mov    [esp + 20], ebx ;arg6
    mov    [esp + 24], ecx ;arg7
    mov    [esp + 28], edx ;arg8
    mov    eax, [gui_t+xserver.size+xswa.size+xwin.class]
    mov    ebx, [gui_t+xserver.size+xswa.size+xwin.visual]
    mov    ecx, [gui_t+xserver.size+xswa.size+xwin.valuemask]
    mov    edx, gui_t
    add    edx, xserver.size
    mov    [esp + 32], eax ;arg9
    mov    [esp + 36], ebx ;arg10
    mov    [esp + 40], ecx ;arg11
    mov    [esp + 44], edx ;arg12
    call   XCreateWindow
    add    esp, 48 ;restore 48 bytes
    mov    [gui_t+xserver.size+xswa.size+xwin.window], eax

; -------------------------------------------------------------------
; overwrite WM_PROTOCOLS property with specified atom:
; Status XSetWMProtocols(Display *display,
;                        Window   w,
;                        Atom    *protocols,
;                        int      count)
;
; If the function failed to intern the WM_PROTOCOLS, the return
; status will be zero.
; -------------------------------------------------------------------
    sub    esp, 16 ;reserve 16 bytes
    mov    eax, [gui_t+xserver.pDisplay]
    mov    ebx, [gui_t+xserver.size+xswa.size+xwin.window]
    mov    ecx, gui_t
    add    ecx, xserver.size
    add    ecx, xswa.size
    add    ecx, xwin.wm_delete_msg
    mov    edx, 1
    mov    [esp     ], eax ;arg1: pDisplay
    mov    [esp +  4], ebx ;arg2: window
    mov    [esp +  8], ecx ;arg3: wm_delete_msg
    mov    [esp + 12], edx ;arg4: 1
    call   XSetWMProtocols
    add    esp, 16 ;restore 16 bytes

; -------------------------------------------------------------------
; map the window:
; void XMapWindow(Display *display, Window w)
;
; This function maps the window and all of its subwindows that have
; map requests.
; -------------------------------------------------------------------
    sub    esp, 8                               ;reserve 8 bytes
    mov    eax, [gui_t+xserver.pDisplay]
    mov    ebx, [gui_t+xserver.size+xswa.size+\
                xwin.window]
    mov    [esp    ], eax                       ;arg1
    mov    [esp + 4], ebx                       ;arg2
    call   XMapWindow
    add    esp, 8                               ;restore 8 bytes

mainloop:

; -------------------------------------------------------------------
; Get event:
; XNextEvent(Display *display, XEvent *event_return)
;
; This function copies the first event from the event queue into the
; specified XEvent structure and then removes it from the queue. If
; the event queue is empty, XNextEvent flushes the output buffer and
; blocks until an event is received.
; -------------------------------------------------------------------
    sub    esp, 8                        ;reserve 8 bytes
    mov    eax, [gui_t+xserver.pDisplay]
    mov    ebx, gui_t
    add    ebx, xserver.size
    add    ebx, xswa.size
    add    ebx, xwin.size
    mov    [esp    ], eax                ;arg1
    mov    [esp + 4], ebx                ;arg2
    call   XNextEvent
    add    esp, 8                        ;restore 8 bytes

; -------------------------------------------------------------------
; exit if type of event is buttonpress
; -------------------------------------------------------------------
    mov    eax, [gui_t+xserver.size+xswa.size+\
                xwin.size+xevent.data+0]
    cmp    eax, 0b0100
    je     exit

; -------------------------------------------------------------------
; exit if button "X" is clicked
; -------------------------------------------------------------------
    mov    eax, [gui_t+xserver.size+xswa.size+\
                xwin.size+xevent.data+0]
    cmp    eax, 0b100001
    jne    is_not_msg_delete
is_msg_delete:
    mov    eax, [gui_t+xserver.size+xswa.size+\
                xwin.size+xevent.data+28]
    mov    ebx, [gui_t+xserver.size+xswa.size+\
                xwin.wm_delete_msg]
    cmp    eax, ebx
    je     exit
is_not_msg_delete:

    jmp    mainloop

exit:

; -------------------------------------------------------------------
; disconnect from X Server:
; void XCloseDisplay(Display *display)
;
; This function destroys all windows, resource IDs, and other
; resources created by the client on this display.
; -------------------------------------------------------------------
    sub    esp, 4                        ;reserve 4 bytes
    mov    eax, [gui_t+xserver.pDisplay]
    mov    [esp], eax                    ;arg1
    call   XCloseDisplay
    add    esp, 4                        ;restore 4 bytes

; -------------------------------------------------------------------
; system call exit
; -------------------------------------------------------------------
    mov    eax, 0x1
    mov    ebx, 0x0
    int    0x80

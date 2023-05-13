global _start
extern gtk_init
extern gtk_window_new
extern gtk_signal_connect
extern g_list_append
extern gtk_combo_new
extern gtk_container_add
extern gtk_container_set_border_width
extern gtk_widget_show
extern gtk_main
extern gtk_main_quit
extern g_print
extern gtk_combo_set_popdown_strings
extern gtk_signal_connect

GTK_WINDOW_TOPLEVEL equ 0

section .text
_start:
mov ebp,esp ;create stack frame
sub esp,12 ;allocate local storage
; [ebp-4] pointer to window structure
; [ebp-8] pointer to combo box
; [ebp-12] list pointer

; Initialize GTK
; gtk_init (&argc, &argv);
push argv ;argv pointer
push argc ;argc pointer
call gtk_init
add esp,8 ;clean up stack
;
; Create the new window
push GTK_WINDOW_TOPLEVEL
call gtk_window_new
add esp,4 ;clean up stack
mov [ebp-4],eax ;-> window structure

; /*--Connect the window to the destroyapp function --*/
; gtk_signal_connect(GTK_OBJECT(window), "delete_event", GTK_SIGNAL_FUNC(destroyapp), NULL);
push 0
push close
push eventstr
push dword [ebp-4] ;window ptr
call gtk_signal_connect

; Items to be added to combo widget
mov dword [ebp-12],0 ;null list
push item1
push dword [ebp-12]
call g_list_append
add esp,8
mov [ebp-12],eax
push item2
push dword [ebp-12]
call g_list_append
add esp,8
mov [ebp-12],eax
push item3
push dword [ebp-12]
call g_list_append
add esp,8
mov [ebp-12],eax
push item4
push dword [ebp-12]
call g_list_append
add esp,8
mov [ebp-12],eax
push item5
push dword [ebp-12]
call g_list_append
add esp,8
mov [ebp-12],eax
push item6
push dword [ebp-12]
call g_list_append
add esp,8
mov [ebp-12],eax

; Create a new combo widget
call gtk_combo_new
mov [ebp-8],eax ;-> combo box structure

; Set items in the popup list
push dword [ebp-12] ;items list
push dword [ebp-8] ;combo box
call gtk_combo_set_popdown_strings
add esp,8

; Add combo widget to window
push dword [ebp-8] ;combo
push dword [ebp-4] ;window
call gtk_container_add
add esp,8 ;clean up stack

; Add a border to the window to give the button a little room
push 15 ;border width
push dword [ebp-4] ;window
call gtk_container_set_border_width
add esp,8 ;clean up stack

; Display the widgets
push dword [ebp-8] ;combo
call gtk_widget_show
add esp,4 ;clean up stack
push dword [ebp-4] ;window
call gtk_widget_show
add esp,4 ;clean up stack

; /*-- Start the GTK event loop--*/
call gtk_main
;------------------------------------------------
;exit with return = 0
;------------------------------------------------
exit: mov eax,1 ;linux exit
xor ebx,ebx ;return code
int 80h ;does not return
;------------------------------------------------
;callback routines
;------------------------------------------------
; This function allows the program to exit properly when the window is closed
close: push quitstr
call g_print;
add esp,4
call gtk_main_quit
ret
;-----------------------------------------------
;data section
;-----------------------------------------------
section .data
argv dd arglist
arglist dd title
dd 0
argc dd 1
quitstr db 'Quitting...',10,0
title db 'Assemblers',0
item1 db 'NASM',0
item2 db 'FASM',0
item3 db 'YASM',0
item4 db 'RosAsm',0
item5 db 'MASM',0
item6 db 'HLA',0
eventstr db 'delete_event',0

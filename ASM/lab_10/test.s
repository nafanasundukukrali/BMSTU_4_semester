.equ STDOUT,              1     @ Linux output console
.equ EXIT,                1     @ Linux syscall
.equ WRITE,               4     @ Linux syscall
/* constantes X11 */
.equ KeyPressed,          2
.equ ButtonPress,         4
.equ MotionNotify,        6
.equ EnterNotify,         7
.equ LeaveNotify,         8
.equ Expose,              12
.equ ClientMessage,       33
.equ KeyPressMask,        1
.equ ButtonPressMask,     4
.equ ButtonReleaseMask,   8
.equ ExposureMask,        1<<15
.equ StructureNotifyMask, 1<<17
.equ EnterWindowMask,     1<<4
.equ LeaveWindowMask,     1<<5 
.equ ConfigureNotify,     22

/*******************************************/
/* DONNEES INITIALISEES                    */
/*******************************************/ 
.data
szWindowName:            .asciz "Windows Raspberry"
szRetourligne:           .asciz  "\n"
szMessDebutPgm:          .asciz "Program start. \n"
szMessErreur:            .asciz "Server X not found.\n"
szMessErrfen:            .asciz "Can not create window.\n"
szMessErreurX11:         .asciz "Error call function X11. \n"
szMessErrGc:             .asciz "Can not create graphics context.\n"
szTitreFenRed:           .asciz "Pi"    
szTexte1:                .asciz "Hello world."
.equ LGTEXTE1, . - szTexte1
szTexte2:                .asciz "Press q for close window or clic X in system menu."
.equ LGTEXTE2, . - szTexte2
szLibDW: .asciz "WM_DELETE_WINDOW"    @ special label for correct close error

/*************************************************/
szMessErr: .ascii	"Error code hexa : "
sHexa: .space 9,' '
         .ascii "  decimal :  "
sDeci: .space 15,' '
         .asciz "\n"

/*******************************************/
/* DONNEES NON INITIALISEES                    */
/*******************************************/ 
.bss
.align 4
ptDisplay:          .skip 4      @ pointer display
ptEcranDef:         .skip 4      @ pointer screen default
ptFenetre:          .skip 4      @ pointer window
ptGC:               .skip 4      @ pointer graphic context
key:                .skip 4      @ key code
wmDeleteMessage:    .skip 8      @ ident close message
event:              .skip 400    @ TODO event size ??
PrpNomFenetre:      .skip 100    @ window name proprety
buffer:             .skip 500 
iWhite:             .skip 4      @ rgb code for white pixel
iBlack:             .skip 4      @ rgb code for black pixel
/**********************************************/
/* -- Code section                            */
/**********************************************/
.text
.global main

main:                               @ entry of program 
    ldr r0,iAdrszMessDebutPgm   @
    bl affichageMess            @ display start message on console linux
    /* attention r6  pointer display*/
    /* attention r8  pointer graphic context   */
    /* attention r9 ident window  */
    /*****************************/
    /*    OPEN SERVER X11        */
    /*****************************/
    mov r0,#0
    bl XOpenDisplay             @ open X server
    cmp r0,#0                   @ error ?
    beq erreurServeur
    ldr r1,iAdrptDisplay
    str r0,[r1]                 @ store display address 
    mov r6,r0                   @ and in register r6
    ldr r2,[r0,#+132]           @ load default_screen
    ldr r1,iAdrptEcranDef
    str r2,[r1]                 @ store default_screen
    mov r2,r0
    ldr r0,[r2,#+140]           @ load pointer screen list
    ldr r5,[r0,#+52]            @ load value white pixel
    ldr r4,iAdrWhite            @ and store in memory
    str r5,[r4]
    ldr r3,[r0,#+56]            @ load value black pixel
    ldr r4,iAdrBlack            @ and store in memory
    str r3,[r4]
    ldr r4,[r0,#+28]            @ load bits par pixel
    ldr r1,[r0,#+8]             @ load root windows
    /**************************/
    /* CREATE WINDOW          */
    /**************************/
    mov r0,r6                   @ address display
    mov r2,#0                   @ window position X
    mov r3,#0                   @ window position Y
    mov r8,#0                   @ for stack alignement
    push {r8}
    push {r3}                   @  background  = black pixel
    push {r5}                   @  border = white pixel
    mov r8,#2                   @  border size
    push {r8}
    mov r8,#400                 @ hauteur
    push {r8}
    mov r8,#600                 @ largeur 
    push {r8}   
    bl XCreateSimpleWindow
    add sp,#24                  @ stack alignement  6 push (4 bytes * 6)
    cmp r0,#0                   @ error ?
    beq erreurF

    ldr r1,iAdrptFenetre
    str r0,[r1]                 @ store window address in memory
    mov r9,r0                   @ and in register r9
    /*****************************/
    /* add window property       */
    /*****************************/
    mov r0,r6                   @ display address
    mov r1,r9                   @ window address
    ldr r2,iAdrszWindowName     @ window name
    ldr r3,iAdrszTitreFenRed    @ window name reduced
    mov r4,#0
    push {r4}                   @ parameters not use
    push {r4}
    push {r4}
    push {r4}
    bl XSetStandardProperties
    add sp,sp,#16               @ stack alignement for 4 push
    /**************************************/
    /* for correction window close error  */
    /**************************************/
    mov r0,r6                   @ display address
    ldr r1,iAdrszLibDW          @ atom address
    mov r2,#1                   @ False  créate atom if not exists
    bl XInternAtom
    cmp r0,#0                   @ error X11 ?
    ble erreurX11
    ldr r1,iAdrwmDeleteMessage  @ recept address
    str r0,[r1]
    mov r2,r1                   @ return address
    mov r0,r6                   @ display address
    mov r1,r9                   @ window address
    mov r3,#1                   @ number of protocols
    bl XSetWMProtocols
    cmp r0,#0                   @ error X11 ?
    ble erreurX11
    /**********************************/
    /*  create graphic context        */
    /**********************************/
    mov r0,r6                   @ display address
    mov r1,r9                   @ window address
    mov r2,#0                   @ not use for simply context
    mov r3,#0
    bl XCreateGC
    cmp r0,#0                   @ error ?
    beq erreurGC
    ldr r1,iAdrptGC
    str r0,[r1]                 @ store address graphic context
    mov r8,r0                   @ and in r8
    /****************************/
    /* modif window background  */
    /****************************/
    mov r0,r6                   @ display address
    mov r1,r9                   @ window address
    ldr r2,iGris1               @ background color
    bl XSetWindowBackground   
    cmp r0,#0                   @ error ?
    ble erreurX11
    /***************************/
    /* OUF!! window display    */
    /***************************/
    mov r0,r6                   @ display address
    mov r1,r9                   @ window address
    bl XMapWindow
    /****************************/
    /* Write text in the window */
    /****************************/
    mov r0,r6                   @ display address
    mov r1,r9                   @ window address
    mov r2,r8                   @ address graphic context
    mov r3,#50                  @ position x 
    sub sp,#4                   @ stack alignement
    mov r4,#LGTEXTE1  - 1       @ size string 
    push {r4}                   @ on the stack
    ldr r4,iAdrszTexte1            @ string address
    push {r4}
    mov r4,#100                 @ position y 
    push {r4}
    bl XDrawString
    add sp,sp,#16               @ stack alignement 3 push and 1 stack alignement
    cmp r0,#0                   @ error ?
    blt erreurX11
    /* write text 2 */
    mov r0,r6                   @ display address
    mov r1,r9                   @ window address
    mov r2,r8                   @ address graphic context
    mov r3,#10                  @ position x 
    sub sp,#4                   @ stack alignement
    mov r4,#LGTEXTE2  - 1       @ size string 
    push {r4}                   @ on the stack
    ldr r4,iAdrszTexte2            @ string address
    push {r4}
    mov r4,#350                 @ position y 
    push {r4}
    bl XDrawString
    add sp,sp,#16               @ stack alignement 3 push and 1 stack alignement
    cmp r0,#0                   @ error ?
    blt erreurX11
    /****************************/
    /* Autorisations            */
    /****************************/
    mov r0,r6                   @ display address
    mov r1,r9                   @ window address
    ldr r2,iFenetreMask         @ autorisation mask
    bl XSelectInput
    cmp r0,#0                   @ error ?
    ble erreurX11
    /****************************/
    /* Events loop              */
    /****************************/
1:
    mov r0,r6                   @ display address
    ldr r1,iAdrevent            @ events address
    bl XNextEvent               @ event ?
    ldr r0,iAdrevent
    ldr r0,[r0]                 @ code event
    cmp r0,#KeyPressed          @ key ?
    bne 2f
    ldr r0,iAdrevent            @ yes read key in buffer
    ldr r1,iAdrbuffer
    mov r2,#255
    ldr r3,iAdrkey
    mov r4,#0
    push {r4}                   @ stack alignement
    push {r4}
    bl XLookupString 
    add sp,#8                   @ stack alignement 2 push
    cmp r0,#1                   @ is character key ?
    bne 2f
    ldr r0,iAdrbuffer           @ yes -> load first buffer character
    ldrb r0,[r0]
    cmp r0,#0x71                @ character q for quit
    beq 5f                      @ yes -> end
    b 4f
2:
    /*                                  */
    /* for example  clic mouse button   */
    /************************************/
    cmp r0,#ButtonPress         @ clic mouse buton
    bne 3f
    ldr r0,iAdrevent
    ldr r1,[r0,#+32]            @ position X mouse clic
    ldr r2,[r0,#+36]            @ position Y
    @ etc for eventuel use
    b 4f
3:
    cmp r0,#ClientMessage       @ code for close window within error
    bne 4f
    ldr r0,iAdrevent
    ldr r1,[r0,#+28]            @ code message address 
    ldr r2,iAdrwmDeleteMessage  @ equal code window créate ???
    ldr r2,[r2]
    cmp r1,r2
    beq 5f                      @ yes -> end window 

4:  @ loop for other event
    b 1b
    /***********************************/
    /* Close window -> free ressources */
    /***********************************/
5:
    mov r0,r6                  @ display address
    ldr r1,iAdrptGC
    ldr r1,[r1]                @ load context graphic address 
    bl XFreeGC
    cmp r0,#0
    blt erreurX11
    mov r0,r6                  @ display address 
    mov r1,r9                  @ window address
    bl XDestroyWindow
    cmp r0,#0
    blt erreurX11
    mov r0,r6                  @ display address
    bl XCloseDisplay
    cmp r0,#0
    blt erreurX11
    mov r0,#0                  @ return code OK
    b 100f
erreurF:   @ create error window but possible not necessary. Display error by server
    ldr r1,iAdrszMessErrfen
    bl   displayError
    mov r0,#1                  @ return error code
    b 100f
erreurGC:                      @ error create graphic context
    ldr r1,iAdrszMessErrGc
    bl   displayError
    mov r0,#1
    b 100f
erreurX11:    @ erreur X11
    ldr r1,iAdrszMessErreurX11
    bl   displayError
    mov r0,#1
    b 100f
erreurServeur:                 @ error no found X11 server see doc putty and Xming
    ldr r1,iAdrszMessErreur
    bl   displayError
    mov r0,#1
    b 100f

100:                           @ standard end of the program 
    mov r7, #EXIT
    svc 0 
iFenetreMask:        .int  KeyPressMask|ButtonPressMask|StructureNotifyMask
iGris1:              .int 0xFFA0A0A0
iAdrWhite:           .int iWhite
iAdrBlack:           .int iBlack
iAdrptDisplay:       .int ptDisplay
iAdrptEcranDef:      .int ptEcranDef
iAdrptFenetre:       .int ptFenetre
iAdrptGC:            .int ptGC
iAdrevent:           .int event
iAdrbuffer:          .int buffer
iAdrkey:             .int key
iAdrszLibDW:         .int szLibDW
iAdrszMessDebutPgm:  .int szMessDebutPgm
iAdrszMessErreurX11: .int szMessErreurX11
iAdrszMessErrGc:     .int szMessErrGc
iAdrszMessErreur:    .int szMessErreur
iAdrszMessErrfen:    .int szMessErrfen
iAdrszWindowName:    .int szWindowName
iAdrszTitreFenRed:   .int szTitreFenRed
iAdrszTexte1:        .int szTexte1
iAdrszTexte2:        .int szTexte2
iAdrPrpNomFenetre:   .int PrpNomFenetre
iAdrwmDeleteMessage: .int wmDeleteMessage
/******************************************************************/
/*     display text with size calculation                         */ 
/******************************************************************/
/* r0 contains the address of the message */
affichageMess:
    push {r0,r1,r2,r7,lr}                   @ save  registres
    mov r2,#0                               @ counter length 
1:                                          @ loop length calculation 
    ldrb r1,[r0,r2]                         @ read octet start position + index 
    cmp r1,#0                               @ if 0 its over 
    addne r2,r2,#1                          @ else add 1 in the length 
    bne 1b                                  @ and loop 
                                            @ so here r2 contains the length of the message 
    mov r1,r0                               @ address message in r1 
    mov r0,#STDOUT                          @ code to write to the standard output Linux 
    mov r7, #WRITE                          @ code call system "write" 
    svc #0                                  @ call systeme 
    pop {r0,r1,r2,r7,lr}                    @ restaur registers */ 
    bx lr                                   @ return
/***************************************************/
/*   affichage message d erreur              */
/***************************************************/
/* r0 contains error code  r1 : message address */
displayError:
    push {r0-r2,lr}                         @ save registers
    mov r2,r0                               @ save error code
    mov r0,r1
    bl affichageMess
    mov r0,r2                               @ error code
    ldr r1,iAdrsHexa
    bl conversion16                         @ conversion hexa
    mov r0,r2                               @ error code
    ldr r1,iAdrsDeci                        @ result address
    bl conversion10                         @ conversion decimale
    ldr r0,iAdrszMessErr                    @ display error message
    bl affichageMess
100:
    pop {r0-r2,lr}                          @ restaur registers
    bx lr                                   @ return 
iAdrszMessErr:                 .int szMessErr
iAdrsHexa:                     .int sHexa
iAdrsDeci:                     .int sDeci
/******************************************************************/
/*     Converting a register to hexadecimal                      */ 
/******************************************************************/
/* r0 contains value and r1 address area   */
conversion16:
    push {r1-r4,lr}                                    @ save registers
    mov r2,#28                                         @ start bit position
    mov r4,#0xF0000000                                 @ mask
    mov r3,r0                                          @ save entry value
1:                                                     @ start loop
    and r0,r3,r4                                       @value register and mask
    lsr r0,r2                                          @ move right 
    cmp r0,#10                                         @ compare value
    addlt r0,#48                                       @ <10  ->digit	
    addge r0,#55                                       @ >10  ->letter A-F
    strb r0,[r1],#1                                    @ store digit on area and + 1 in area address
    lsr r4,#4                                          @ shift mask 4 positions
    subs r2,#4                                         @  counter bits - 4 <= zero  ?
    bge 1b                                             @  no -> loop

100:
    pop {r1-r4,lr}                                     @ restaur registers 
    bx lr                                              @return
/******************************************************************/
/*     Converting a register to a decimal unsigned                */ 
/******************************************************************/
/* r0 contains value and r1 address area   */
/* r0 return size of result (no zero final in area) */
/* area size => 11 bytes          */
.equ LGZONECAL,   10
conversion10:
    push {r1-r4,lr}                                 @ save registers 
    mov r3,r1
    mov r2,#LGZONECAL
1:                                                  @ start loop
    bl divisionpar10U                               @ unsigned  r0 <- dividende. quotient ->r0 reste -> r1
    add r1,#48                                      @ digit
    strb r1,[r3,r2]                                 @ store digit on area
    cmp r0,#0                                       @ stop if quotient = 0 
    subne r2,#1                                     @ else previous position
    bne 1b                                          @ and loop
                                                    @ and move digit from left of area
    mov r4,#0
2:
    ldrb r1,[r3,r2]
    strb r1,[r3,r4]
    add r2,#1
    add r4,#1
    cmp r2,#LGZONECAL
    ble 2b
                                                      @ and move spaces in end on area
    mov r0,r4                                         @ result length 
    mov r1,#' '                                       @ space
3:
    strb r1,[r3,r4]                                   @ store space in area
    add r4,#1                                         @ next position
    cmp r4,#LGZONECAL
    ble 3b                                            @ loop if r4 <= area size
 
100:
    pop {r1-r4,lr}                                    @ restaur registres 
    bx lr                                             @return
 
/***************************************************/
/*   division par 10   unsigned                    */
/***************************************************/
/* r0 dividende   */
/* r0 quotient    */
/* r1 remainder   */
divisionpar10U:
    push {r2,r3,r4, lr}
    mov r4,r0                                          @ save value
    ldr r3,iMagicNumber                                @ r3 <- magic_number    raspberry 1 2
    umull r1, r2, r3, r0                               @ r1<- Lower32Bits(r1*r0) r2<- Upper32Bits(r1*r0) 
    mov r0, r2, LSR #3                                 @ r2 <- r2 >> shift 3
    add r2,r0,r0, lsl #2                               @ r2 <- r0 * 5 
    sub r1,r4,r2, lsl #1                               @ r1 <- r4 - (r2 * 2)  = r4 - (r0 * 10)
    pop {r2,r3,r4,lr}
    bx lr                                              @ leave function 
iMagicNumber:  	.int 0xCCCCCCCD

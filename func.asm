global f1
global f2
global f3
global f1p
global f2p
global f3p
f1: 
    push ebp
    mov ebp, esp
    sub esp, 8
    finit
    mov dword[esp], 1
    fild dword[esp]
    fld qword[ebp + 8]
    fyl2x
    fldln2
    fmulp
    add esp, 8
    mov esp, ebp
    pop ebp
    ret

f2:
    push ebp
    mov ebp, esp
    sub esp, 8
    finit
    mov dword[esp], 14
    fild dword[esp]
    mov dword[esp], 2
    fild dword[esp]
    fld qword[ebp + 8]
    fmulp
    fsubp    
    add esp, 8
    mov esp, ebp
    pop ebp
    ret

f3:
    push ebp
    mov ebp, esp
    sub esp, 8
    finit
    mov dword[esp], 1
    fild dword[esp]
    mov dword[esp], 2
    fild dword[esp]
    fld qword[ebp + 8]
    fsubp
    fdivp
    mov dword[esp], 6
    fild dword[esp]
    faddp
    add esp, 8
    mov esp, ebp
    pop ebp
    ret

f1p:
    push ebp
    mov ebp, esp
    sub esp, 8
    finit
    mov dword[esp], 1
    fild dword[esp]
    fld qword[ebp + 8]
    fdivp
    add esp, 8
    mov esp, ebp
    pop ebp
    ret

f2p:
    sub esp, 4
    finit
    mov dword[esp], -2
    fild dword[esp]
    add esp, 4
    ret

f3p:
    push ebp
    mov ebp, esp
    sub esp, 8
    finit
    mov dword[esp], 1
    fild dword[esp]
    fld qword[ebp + 8]
    mov dword[esp], 2
    fild dword[esp]
    fsubp
    fld st0
    fmulp
    fdivp
    add esp, 8
    mov esp, ebp
    pop ebp
    ret






.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib "../Debug/StaticLib.lib"
ExitProcess PROTO :DWORD

EXTRN _strlen: proc
EXTRN _strcopy: proc
EXTRN _random: proc
EXTRN _exp: proc
EXTRN BREAKL: proc
EXTRN IntOut: proc
EXTRN IntOutLn: proc
EXTRN StrOut: proc
EXTRN StrOutLn: proc

.stack 4096

.const
	Lit1 DD 1
	Lit2 DD 5
	Lit3 DD 0
	Lit4 BYTE "rand value is bigger then 5", 0
	Lit5 BYTE "rand value is lower than 5 ", 0
	Lit6 DD 46
	Lit7 DD 0
	Lit8 DD 1
	Lit9 BYTE "aaaaa", 0
	Lit10 BYTE "aaagh", 0
	Lit11 BYTE "Length of str: ", 0
	Lit12 DD 6
	Lit13 DD 20
	Lit14 BYTE "a", 0
	Lit15 DD 9
	Lit16 DD 3
	Lit17 DD 10
	Lit18 BYTE "right", 0
	Lit19 BYTE "left", 0
	Lit20 DD 2
	Lit21 BYTE "result = ", 0
	Lit22 BYTE "unlooka", 0
	Lit23 BYTE "func ret: ", 0

.data
	buffer BYTE 256 dup(0)
	funcbi DD 0
	fbi DD 0
	fav DD 0
	mainres DD 0
	mainfromf DD 0
	mainfi DD 0
	mainl DD 0
	mainstrok DWORD ?
	mainlel DWORD ?
	maingh DD 0

.code

func PROC funcg : DWORD
	push Lit1
	pop funcbi
	mov eax, funcg
	cmp eax, Lit2
	jg m0
	jl m1
	je m1
m0:
	push Lit1
	pop funcbi
	jmp e0
m1:
	push Lit3
	pop funcbi
e0:
	mov eax, funcbi
	cmp eax, 1
	jz m2
	jnz m3
	je m3
m2:
	push offset Lit4
	call StrOutLn
	jmp e1
m3:
	push offset Lit5
	call StrOutLn
e1:
	push Lit6
	call IntOutLn
	push 0
	jmp local0
local0:
	pop eax
	ret
func ENDP

f PROC fa : DWORD, fb : DWORD
	push Lit8
	pop fav
	push fa
	push fb
	pop edx
	pop edx
	push fb
	push fa
	call _random
	push eax
	pop fav
	push fav
	jmp local1
local1:
	pop eax
	ret
f ENDP

main PROC
	push offset Lit9
	pop mainstrok
	push mainstrok
	pop edx
	push mainstrok
	call _strlen
	push eax
	pop mainl
	push offset Lit10
	pop mainlel
	push mainstrok
	push mainlel
	pop edx
	pop edx
	push mainlel
	push mainstrok
	call _strcopy
	push eax
	pop mainstrok
	push mainstrok
	call StrOutLn
	push offset Lit11
	call StrOut
	push mainl
	call IntOutLn
	push Lit12
	push Lit13
	pop edx
	pop edx
	push Lit13
	push Lit12
	call _random
	push eax
	pop mainfi
	push offset Lit14
	push Lit15
	pop edx
	pop edx
	push Lit15
	push offset Lit14
	call _exp
	push eax
	pop mainfromf
	push mainfromf
	call IntOutLn
	push Lit8
	push Lit16
 	pop eax 
  	pop eax 
  	shl eax,  3
 	push eax 
 	pop mainfromf
	push mainfromf
	call IntOutLn
	push mainfi
	call IntOutLn
	mov eax, mainfi
	cmp eax, Lit17
	jg m4
	jl m5
	je m5
m4:
	push offset Lit18
	call StrOutLn
	jmp e2
m5:
	push offset Lit19
	call StrOutLn
e2:
push mainfi
pop ebx
cyclenext0:
	mov eax, mainl
	cmp eax, Lit12
	jg m6
	jl m7
	je m7
m6:
	push Lit20
	push Lit17
	pop edx
	pop edx
	push Lit17
	push Lit20
	call f
	push eax
	pop mainfromf
	push offset Lit21
	call StrOut
	push mainfromf
	call IntOutLn
	jmp e3
m7:
	push offset Lit22
	call StrOutLn
e3:
	sub ebx, 1
	cmp ebx, 0
	jz endcycle0
	loop cyclenext0
	endcycle0:
	push Lit12
	pop edx
	push Lit12
	call func
	push eax
	pop maingh
	push offset Lit23
	call StrOut
	push maingh
	call IntOutLn
	push 0
		jmp theend
theend:
	call ExitProcess
main ENDP
end main

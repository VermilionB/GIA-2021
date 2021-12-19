.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/StaticLib.lib
ExitProcess PROTO :DWORD

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
	Lit2 DD 6
	Lit3 DD 20
	Lit4 DD 10
	Lit5 BYTE "right", 0
	Lit6 BYTE "left", 0
	Lit7 DD 2
	Lit8 BYTE "result = ", 0
	Lit9 DD 11

.data
	buffer BYTE 256 dup(0)
	fav DD 0
	mainres DD 0
	mainfromf DD 0
	mainfu DD 0

.code

f PROC fa : DWORD, fb : DWORD
	push Lit1
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
	jmp local0
local0:
	pop eax
	ret
f ENDP

main PROC
	push Lit2
	push Lit3
	pop edx
	pop edx
	push Lit3
	push Lit2
	call _random
	push eax
	pop mainfu
	push mainfu
	call IntOutLn
	mov eax, mainfu
	cmp eax, Lit4
	jg m0
	jl m1
	je m1
m0:
	push offset Lit5
	call StrOutLn
	jmp e0
m1:
	push offset Lit6
	call StrOutLn
e0:
push mainfu
pop ebx
cyclenext0:
	push Lit7
	push Lit4
	pop edx
	pop edx
	push Lit4
	push Lit7
	call f
	push eax
	pop mainfromf
	push offset Lit8
	call StrOut
	push mainfromf
	call IntOutLn
	sub ebx, 1
	cmp ebx, 0
	jz endcycle0
	loop cyclenext0
	endcycle0:
	push Lit4
	push Lit9
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop mainfromf
	push mainfromf
	call IntOutLn
	push mainres
		jmp theend
theend:
	call ExitProcess
main ENDP
end main
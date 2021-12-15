.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/StaticLib.lib
ExitProcess PROTO :DWORD

EXTRN Random: proc
EXTRN Exp: proc
EXTRN BREAKL: proc
EXTRN IntOut: proc
EXTRN IntOutLn: proc
EXTRN StrOut: proc
EXTRN StrOutLn: proc

.stack 4096

.const
	Lit1 DD 2
	Lit2 DD 65
	Lit3 DD 180
	Lit4 DD 135
	Lit5 DD 15
	Lit6 DD 4

.data
	buffer BYTE 256 dup(0)
	fav DD 0
	fg DD 0
	mainres DD 0
	maing DD 0
	mainpro DD 0

.code

f PROC fa : DWORD, fb : DWORD
	push Lit1
	push Lit2
	pop fg
	push fg
	call IntOutLn
	push fa
	push fg
	pop eax
	pop ebx
	mul ebx
	push eax
	push Lit3
	push fb
	pop ebx
	pop eax
	cdq
	idiv ebx
	push eax
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	pop fav
	push fav
	jmp local0
local0:
	pop eax
	ret
	ret
f ENDP

main PROC
	push Lit4
	push Lit5
	pop edx
	pop edx
	push Lit5
	push Lit4
	call f
	push eax
	pop maing
	push maing
	call IntOutLn
	push Lit6
	pop mainpro
	push mainpro
	push Lit6
 	pop eax 
  	shl eax,  4
 	push eax 
 	pop mainres
	push mainres
	call IntOut
	push mainres
		jmp theend
theend:
	call ExitProcess
main ENDP
end main
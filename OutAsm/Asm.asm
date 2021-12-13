.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib ../Debug/StaticLib.lib
ExitProcess PROTO :DWORD

EXTRN BREAKL: proc
EXTRN IntOut: proc
EXTRN IntOutLn: proc
EXTRN StrOut: proc
EXTRN StrOutLn: proc

.stack 4096

.const
	Lit1 DD 4
	Lit2 DD 2

.data
	buffer BYTE 256 dup(0)
	fav DD 0
	mainres DD 0
	mainpro DD 0

.code

f proc fa : DWORD, fb : DWORD
	push fa
	push fb
	pop eax
	pop ebx
	add eax, ebx
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
	push Lit1
	pop mainpro
	push mainpro
	push Lit2
 	pop eax 
  	shl eax,  2 
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
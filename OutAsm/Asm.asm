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
	Lit1 BYTE 1
	Lit2 BYTE 2

.data
	buffer BYTE 256 dup(0)
	mainres BYTE 0

.code

main PROC
	push mainres
	pop eax
	pop ebx
	add eax, ebx
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
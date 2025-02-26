.arch armv7a

.section .vitalink.fstubs.kC2R,"ax",%progbits

	.align 4
	.global kDecryptSpkgFile
	.type kDecryptSpkgFile, %function
kDecryptSpkgFile:
.if GEN_WEAK_EXPORTS
	.word 0x00010008
.else
	.word 0x00010000
.endif //GEN_WEAK_EXPORTS
	.word 0xF5FBE69A
	.word 0x294F2EAB
	.align 4


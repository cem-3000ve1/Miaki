.arch armv7a

.section .vitalink.fstubs.uC2R,"ax",%progbits

	.align 4
	.global dd
	.type dd, %function
dd:
.if GEN_WEAK_EXPORTS
	.word 0x00010008
.else
	.word 0x00010000
.endif //GEN_WEAK_EXPORTS
	.word 0x64709012
	.word 0x9B7ECC6E
	.align 4


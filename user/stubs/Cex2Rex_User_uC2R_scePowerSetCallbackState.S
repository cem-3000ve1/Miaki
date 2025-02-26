.arch armv7a

.section .vitalink.fstubs.uC2R,"ax",%progbits

	.align 4
	.global scePowerSetCallbackState
	.type scePowerSetCallbackState, %function
scePowerSetCallbackState:
.if GEN_WEAK_EXPORTS
	.word 0x00010008
.else
	.word 0x00010000
.endif //GEN_WEAK_EXPORTS
	.word 0x64709012
	.word 0xCEBB63D9
	.align 4


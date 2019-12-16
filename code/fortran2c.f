! 线路1--P侧
SUBROUTINE F_LINE_1_P(vma, vmb, vmc, ima, imb, imc, vna, vnb, vnc, ina, inb, inc, time, p1, p2, p3)

REAL vma, vmb, vmc, ima, imb, imc, vna, vnb, vnc, ina, inb, inc, time, p1, p2, p3

! Fortran 90 interface to a C procedure
INTERFACE
 SUBROUTINE LINE_1_P (vma, vmb, vmc, ima, imb, imc, vna, vnb, vnc, ina, inb, inc, time, p1, p2, p3)
    !DEC$ ATTRIBUTES C :: LINE_1_P
    !DEC$ ATTRIBUTES REFERENCE :: vma, vmb, vmc, ima, imb, imc, vna, vnb, vnc, ina, inb, inc, time
    !DEC$ ATTRIBUTES REFERENCE :: p1, p2, p3
! in, out are passed by REFERENCE 
    REAL vma, vmb, vmc, ima, imb, imc, vna, vnb, vnc, ina, inb, inc, time, p1, p2, p3
 END SUBROUTINE
END INTERFACE

! call of the C procedure
CALL LINE_1_P (vma, vmb, vmc, ima, imb, imc, vna, vnb, vnc, ina, inb, inc, time, p1, p2, p3)

END



! 线路1--Q侧
SUBROUTINE F_LINE_1_Q(vma, vmb, vmc, ima, imb, imc, vna, vnb, vnc, ina, inb, inc, time, p1, p2, p3)

REAL vma, vmb, vmc, ima, imb, imc, vna, vnb, vnc, ina, inb, inc, time, p1, p2, p3

! Fortran 90 interface to a C procedure
INTERFACE
 SUBROUTINE LINE_1_Q (vma, vmb, vmc, ima, imb, imc, vna, vnb, vnc, ina, inb, inc, time, p1, p2, p3)
    !DEC$ ATTRIBUTES C :: LINE_1_Q
    !DEC$ ATTRIBUTES REFERENCE :: vma, vmb, vmc, ima, imb, imc, vna, vnb, vnc, ina, inb, inc, time
    !DEC$ ATTRIBUTES REFERENCE :: p1, p2, p3
! in, out are passed by REFERENCE 
    REAL vma, vmb, vmc, ima, imb, imc, vna, vnb, vnc, ina, inb, inc, time, p1, p2, p3
 END SUBROUTINE
END INTERFACE

! call of the C procedure
CALL LINE_1_Q (vma, vmb, vmc, ima, imb, imc, vna, vnb, vnc, ina, inb, inc, time, p1, p2, p3)

END
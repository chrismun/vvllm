#ifndef T1
!T1:data construct detach clause,V:2.7-2.3
      LOGICAL FUNCTION test1()
        USE OPENACC
        IMPLICIT NONE
        INCLUDE "acc_testsuite.Fh"
        
        INTEGER :: errors = 0
        INTEGER, DIMENSION(10) :: a, b, c
        INTEGER :: i
        INTEGER, POINTER :: ap, bp, cp

        ap => a
        bp => b
        cp => c

        !$acc enter data copyin(a, b, c)
        !$acc parallel present(a, b, c)
          DO i = 1, 10
            a(i) = i
            b(i) = i * 2
            c(i) = i * 3
          END DO
        !$acc end parallel

        !$acc exit data detach(ap, bp, cp)

        DO i = 1, 10
          IF (a(i) .NE. i .OR. b(i) .NE. i * 2 .OR. c(i) .NE. i * 3) THEN
            errors = errors + 1
          END IF
        END DO

        IF (errors .eq. 0) THEN
          test1 = .FALSE.
        ELSE
          test1 = .TRUE.
        END IF
      END
#endif

      PROGRAM main
        IMPLICIT NONE
        INTEGER :: failcode, testrun
        LOGICAL :: failed
        INCLUDE "acc_testsuite.Fh"
#ifndef T1
        LOGICAL :: test1
#endif
        failed = .FALSE.
        failcode = 0
#ifndef T1
        DO testrun = 1, NUM_TEST_CALLS
          failed = failed .or. test1()
        END DO
        IF (failed) THEN
          failcode = failcode + 2 ** 0
          failed = .FALSE.
        END IF
#endif
        CALL EXIT (failcode)
      END PROGRAM
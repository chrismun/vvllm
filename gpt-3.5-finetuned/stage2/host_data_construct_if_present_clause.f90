!T1:host_data ,V:2.7-2.3
     LOGICAL FUNCTION test1()
       USE OPENACC
       IMPLICIT NONE
       INCLUDE "acc_testsuite.Fh"
       INTEGER :: errors = 0

       INTEGER :: x
       x = 1
       !$acc enter data copyin(x)
       !$acc host_data if_present(x)
         x = x + 1
       !$acc end host_data
       !$acc exit data copyout(x)
       IF (x) NEQ 2 THEN
         errors = errors + 1
       END IF

       IF (errors .eq. 0) THEN
         test1 = .FALSE.
       ELSE
         test1 = .TRUE.
       END IF
     END

     PROGRAM main
       IMPLICIT NONE
       INTEGER :: failcode, testrun
       LOGICAL :: failed
       INCLUDE "acc_testsuite.Fh"
       LOGICAL :: test1
       failed = .FALSE.
       failcode = 0
       DO testrun = 1, NUM_TEST_CALLS
         failed = failed .or. test1()
       END DO
       IF (failed) THEN
         failcode = failcode + 2 ** 0
         failed = .FALSE.
       END IF
       CALL EXIT (failcode)
     END PROGRAM
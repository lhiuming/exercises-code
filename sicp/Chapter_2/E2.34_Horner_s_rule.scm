(define (horner-eval x coefficient-sequence)
  (accumulate (lambda (this-coeff higher-terms) (+ (* higher-terms x)
                                                   this-coeff))
              0
              coefficient-sequence))

;;; test code
(horner-eval 2 (list 1 3 0 5 0 1))
(horner-eval 2 (list 0 1 0 0 1))

(define (1-e-1-successive i)
  (let ((m (modulo i 3)))
  (cond ((or (= m 0) (= m 1))
           1)
        (else (* 2 (/ (+ i 1) 3))))))

(define (cf-e k)
  (+ 2
     (count-frac (lambda (i) 1.0)
                 1-e-1-successive
                 k)))

(cf-e 20)

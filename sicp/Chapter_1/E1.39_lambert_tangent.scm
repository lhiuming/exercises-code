(define (tan-cf x k)
  (define (N i)
    (if (= i 1)
        x
        (- 0 (* x x))))
  (define (D i) (- (* 2 i) 1))
  (define (cf-iter i result)
    (if (= i 0)
        result
        (cf-iter (- i 1)
                 (/ (N i) (+ (D i) result)))))
  (cf-iter K 0))

(tan-cf 1.0 9)


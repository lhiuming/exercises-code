(define (repeated f n)
  (define (repeated-rec i)
    (if (= i 1)
        f
        (lambda (x) (f ((repeated-rec (- i 1))
                        x)))))
  (repeated-rec n))

((repeated square 2) 5)

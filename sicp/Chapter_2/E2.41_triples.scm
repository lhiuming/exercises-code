(define (s-sum-triples n s)
  (define (s-sum? triple)
    (= s (+ (car triple) (cadr triple) (cadr (cdr triple)))))
  (define (k-j-i-pairs k)
    (map (lambda (pair) (append pair (list k))) (unique-pairs (- k 1))))
  (define (unique-triples n)
    (flatmap k-j-i-pairs (range 3 n)))
  (filter s-sum? (unique-triples n)))

;;; test code
(display (s-sum-triples 3 6))
(display (s-sum-triples 3 5))
(display (s-sum-triples 5 9))

(define (triples s t u)
  (define (pairs2triples pairs stm)
    (let ((first-row (stream-map (lambda (x) (append (stream-car pairs)
                                                     (list x)))
                                 stm)))
      (cons-stream
        (stream-car first-row)
        (interleave
          (stream-cdr first-row)
          (pairs2triples (stream-cdr pairs) (stream-cdr stm))))))
  (let ((first-plane
          (pairs2triples (stream-map (lambda (x) (list (stream-car s) x))
                                     t)
                         u)))
  (cons-stream
    (stream-car first-plane)
    (interleave
      (stream-cdr first-plane)
      (triples (stream-cdr s) (stream-cdr t) (stream-cdr u))))))

(define (pythagorean? triple)
  (let ((a (list-ref triple 0))
        (b (list-ref triple 1))
        (c (list-ref triple 2)))
    (= (+ (square a) (square b))
       (square c))))


;;; test
(define (show-stream-interval stm a b)
  (define (iter s n)
    (cond ((< n a) (iter (stream-cdr s) (+ n 1)))
          ((> n b) 'done)
          (else (display (stream-car s))
                (newline)
                (iter (stream-cdr s) (+ n 1)))))
  (iter stm 1))

(define (integers-starting-from n)
  (cons-stream n (integers-starting-from (+ n 1))))

(define (integers) (integers-starting-from 1))
(define (tri stm)
  (triples stm stm stm))

(define (pytha) (stream-filter pythagorean? (tri (integers))))

(stream-ref (pytha) 3)


;;; suppliment
(define (interleave s1 s2)
  (if (stream-null? s1)
      s2
      (cons-stream (stream-car s1)
                   (interleave s2 (stream-cdr s1)))))

;;; useful version
(define (interleave s1 s2)
  (if (< (list-ref (stream-car s1) 2)
         (list-ref (stream-car s2) 2))
      (cons-stream (stream-car s1)
                   (interleave s2 (stream-cdr s1)))
      (cons-stream (stream-car s2)
                   (interleave s1 (stream-cdr s2)))))




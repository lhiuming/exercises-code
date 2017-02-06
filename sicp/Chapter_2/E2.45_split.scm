(define right-split (split beside below))
(define up-split (split below beside))

(define (split smaller-op id-op)
  (define (combine2 painter n)
    (if (= 0 n)
        painter
        (let ((half (smaller-op painter (combine2 painter (- n 1)))))
          (ip-op half half))))
  combine2)

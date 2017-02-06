(define (dot-product v w)
  (accumulate + 0 (map * v w)))


(define (matrix-*-vector m v)
  (map (lambda (row) (dot-product row v)) m))
(define (transpose mat)
  (accumulate-n cons nil mat))
(define (matrix-*-matrix m n)
  (let ((cols (transpose n)))
    (map (lambda (v) (matrix-*-vector cols v)) m)))

;;; test code
(define L (list (list 1 0 0) (list 1 1 0) (list 1 2 1)))
(define U (transpose L))
(define v1 (list 1 1 1))
(display L)
(display U)
(display v1)
(matrix-*-vector L v1)
(matrix-*-matrix L U)

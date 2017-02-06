(define (div-interval x y)
  (let ((u-y (upper-bound y))
        (l-y (lower-bound y)))
  (if (< 0 (* u-y l-y))
      (mul-interval x 
                   (make-interval (/ 1.0 u-y)
                                  (/ 1.0 l-y)))
      (error "The interval of y spans ZERO !" y))))

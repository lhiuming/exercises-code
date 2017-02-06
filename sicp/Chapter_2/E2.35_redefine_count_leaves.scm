(define (count-leaves t)
  (accumulate + 0 (map (lambda (b) (if (pair? b) (count-leaves b) 1)) t)))

;;; test code
(define testl (list 1 2 3 (list 3 (list (list 4 4))) 4 5))
(count-leaves testl)
(newline)

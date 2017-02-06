(define (C-detect x)
  (define (constituent? pair list)
    (cond ((null? list)
             false)
          ((eq? pair list)
             true)
          (else (constituent? pair (cdr list)))))
  (define (iter current)
    (cond ((null? current) false)
          ((null? (cdr current)) false)
          (else
            (let ((next (cdr current))) ;;; keep the next pair
              (set-cdr! current '())    ;;; cut the list before check next
              (cond ((constituent? next x)
                       (set-cdr! current next)   ;;; restore the list
                       true)
                    (else
                       (set-cdr! current next)   ;;; restore the list
                       (iter next)))))))
  (iter x))

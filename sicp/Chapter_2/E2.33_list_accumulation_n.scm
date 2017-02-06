(define (accumulate-n op init seqs)
  (if (null? (car seqs))
      nil
      (cons (accumulate op init (map car seqs))
            (accumulate-n op init (map cdr seqs)))))

;;; test code
(accumulate-n + 0 (list (list 1 2 3) (list 1 3 7) (list 2 8 16)))
(map + (list 1 2 3) (list 1 3 7) (list 2 8 16))


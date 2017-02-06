(define (stream-map proc . argstreams)
  (if (stream-null? (car argstreams))
      the-empty-stream
      (cons-stream
       (apply proc (map (lambda (st) (stream-car st)) argstreams))
       (apply stream-map
              (cons proc (map (lambda (st) (stream-cdr st))  argstreams))))))

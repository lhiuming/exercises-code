# 1.2

    (/ (+ 5
          4
          (- 2
             (- 3
                (+ 6 
                   (/ 4 3)))))
       (* 3
          (- 6 2)
          (- 2 7)))

# 1.3

    (define (sum_of_squares_of_larger_two a b c)
      (- (+ (* a a) (* b b) (* c c))
        (* (if (c < (if (a < b) a b)) c (if (a < b) a b))
           (if (c < (if (a < b) a b)) c (if (a < b) a b)))))

# 1.5

Applicative-order evaluation will recurse till reach certain limitation or
infinitly. Because procedure p will recurse that way, and applicative-order 
evaluation will eval all the args including (p) when (test 0 (p)) is evaled.

Normal-order evaluation will return 0. For it can return 0 without evaluating
(p).

# 1.6

Recurse infinitly or until reach limitation. Because new-if is a procedure, 
which will evaluate all args when called, including
(sqrt-iter (improve guess x)) which will attempt to eval
(sqrt-iter (improve guess x) again without conditioning, thus recurse 
 infinitly.

#  1.7

If x is very small, say, 0.001, then 0.447 wil be "good enough", which is 41% 
larger than the true one.

If x is very large, say, 10^12, then (sqrt(x) - sqrt(x - 0.001)) is about
4.6 * 10^-10, which means it demands a very high precision for the computer
to get a "good enough" guess.

# 1.8

## The first one:

    (+ 4 5)
    (inc (+ 3 5))
    (inc (inc (+ 2 5)))
    (inc (inc (inc (+ 1 5))))
    (inc (inc (inc (inc (+ 0 5)))))
    (inc (inc (inc (inc 5))))
    (inc (inc (inc 6)))
    (inc (inc 7))
    (inc 8)
    9

recursive.

## The second one:

    (+ 4 5)
    (+ 3 6)
    (+ 2 7)
    (+ 1 8)
    (+ 0 9)
    9

iterative.

# 1.10

    (A 1 10) = 2^10
    (A 2 4) = 2^^4
    (A 3 3) = (A 2 4)

    (f n) = 2n
    (g n) = (A 0 (A 1 (- n 1))) = (* 2 (f (- n 1))) = 2^n
    (h n) = 2^(g (- n 1)) = 2^^n

# 1.11

    (define (recursive-f n)
      (if (< n 3 )
          n
          (+ (f (- n 1))
             (* 2 (f (- n 2)))
             (* 3 (f (- n 3))))))

    (define (interative-f n)
      (f-iter (- n 2) 2 1 0))
    (define (f-iter count a b c)
      (if (= count 0)
          a
          (f-iter (- n 1)
                  (+ a (* 2 b) (* 3 c))
                  a
                  b)))

# 1.12

    (define (szu-yuen depth n)
      (if (or (= n 1) (= n depth))
          1
          (+ (szu-yuen (- depth 1) (- n 1))
             (szu-yuen (- depth 1) n))))

# 1.13

    ((1 + sqrt(5)) / 2) ^ 2 = ((1 + sqrt(5) / 2 + 1)

# 1.14

space: theta of n
steps: theta of n^2

# 1.15

## a

    12.15 / 3^5 = 0.05

thus p applied 5 times.

## b

    (log 3 (* 10 a))

both log(a)

# 1.16

    (define (fast-expt b n)
      (iter-expt 1 b n))
    (define (iter-expt a b n)
      (cond ((= n 0) a)
            ((even? n) (iter-expt a (square b) (/ n 2)))
            (else (iter-expt (* a b) b (- n 1))))
    (define (square a) (* a a))
    (define (even? n) (= (remainder n 2) 0))

# 1.17

    (define (fast-* a b)
      (cond ((= b 0) 0)
            ((even? b) (double (fast-* a (halve b))))
            (else (+ a (fast-* a (- b 1))))))

# 1.18

    (define (fast-* a b)
      (iter-* 0 a b))
    (define (iter-* r a b)
      (cond ((= b 0) r)
            ((even? b) (iter-* r (double a) (halve b)))
            (else (iter-* (+ r a) a (- b 1)))))

# 1.19

    (+ (square p) (square q)
    (* q (+ q (* 2 p)))

# 1.20

    (gcd 206 40)
    (gcd 40 (remainder 206 40))
    (if (= remainder-1 0)
        40
        (gcd remainder-1 ) (remainder 40 remainder-1))
    (if (= remainder-2 0)
        remainder-1
        (gcd remainder-2 (remainder remainder-1 remainder-2)))
    (if (= remainder-4 0)
        remainder-2
        (gcd remainder-4 (remainder remainder-2 remainder-4)))
    (if (= remainder-7 0)
        remainder-4
        (gcd remainder-7 (remainder remainder-4 remainder-7))

Above, remainder-n means it eval n remainder operations. If evaled,
- r-1: 206 / 40 is 6
- r-2: 40 / 6 is 4
- r-4: 6 / 4 is 2
- r-7: 4 / 2 = 0

Thus, normal-order performed 1 + 2 + 4 + 7 + 4 = 18 remainder operations. 
Only 4 for applicative-order.

# 1.21

    199, 1999, 7.

# 1.22

    (define (search-for-primes start end n)
      (cond ((even? start) (search-for-primes (+ start 1) end n))
            ((even? end) (search-for-primes start (- end 1) n))
            ((or (> start end) (= n 0))
               (newline)
               (display " fin. "))
            ((prime? start)
               (timed-prime-test start)
               (search-for-primes (+ start 2) end (- n 1)))
            (else (search-for-primes (+ start 2) end n))))

Time needed to test a prime grows in order of theta(n^0.5) only when the
prime is large enough like, in my computer, larger than 100000000.

# 1.23

The ratio vibrates for primes above. But once make them even larger, it
become stable and is approximate to 2:

    100000000003 *** .8
    100000000019 *** .7799999999999998
    100000000057 *** .7700000000000005
    fin. 
    1000000000039 *** 2.5199999999999996
    1000000000061 *** 2.4800000000000004
    1000000000063 *** 2.5
    fin. 
    10000000000037 *** 7.969999999999999
    10000000000051 *** 7.989999999999995
    10000000000099 *** 8.060000000000002
    fin.  -----------------------------------------------
    100000000003 *** .46000000000000796
    100000000019 *** .4399999999999977
    100000000057 *** .45000000000000284
    fin. 
    1000000000039 *** 1.3799999999999955
    1000000000061 *** 1.3999999999999915
    1000000000063 *** 1.3299999999999983
    fin. 
    10000000000037 *** 4.310000000000002
    10000000000051 *** 4.310000000000002
    10000000000099 *** 4.27000000000001
    fin. 

# 1.24

The ratio should be 2, and is 1.924, with times 99999. Since it is only 3.8%
less, the data bear the prediction well.

# 1.25

She can be correct, but it doesn't serve well for fast-prime. For testing
numbers like 1 000 000, it may raise 500 000 to 1 000 000th power, which is far
too large.

# 1.26

Without taking adavantage of the applicative evaluation order of scheme, this
procedure break a n-step process to **two** n/2-step processes. Therefore,
there are still n steps to go, and the process becomes a theta(n) one.

# 1.27

    (define (fast-prime? n)
      (iter-fermat-test n 1))
    (define (iter-fermat-test n a)
      (cond ((= n a) true)
            ((= (expmod a n n) a) (iter-fermat-test n (+ a 1)))
            (else false)))
    (define (expmod base exp m)
      (cond ((= exp 0) 1)
            ((even? exp) (remainder (square (expmod base (/ exp 2) m)) m))
            (else (remainder (* base (expmod base (- exp 1) m)) m))))

    (define (carmichael-test n)
      (newline)
      (display n)
      (if (fast-prime? n) (display " is 'prime'! ")
                          (display " is not!")))

    ;test for correctness
    (carmichael-test 1000037)
    (carmichael-test 1000036)
    ;domonstration
    (carmichael-test 561)
    (carmichael-test 1105)
    (carmichael-test 1729)
    (carmichael-test 2465)
    (carmichael-test 2821)
    (carmichael-test 6601)

# 1.28

    (define (fast-prime? n)
      (iter-MR-test n 1))
    (define (iter-MR-test n a)
      (cond ((= n a) true)
            ((= (expmod a (- n 1) n) 1) (iter-MR-test n (+ a 1)))
            (else false)))

    (define (expmod base exp m)
      (cond ((= exp 0) 1)
            ((even? exp)
               (remainder (tested-square (expmod base (/ exp 2) m) m) m))
            (else (remainder (* base (expmod base (- exp 1) m)) m))))

    (define (tested-square root n)
      (define sq (square root))
      (if (or (= root 1) (= root (- n 1)) (not (= (remainder sq n) 1)))
          sq
          0))

# 1.29

    (define (simpson f a b n)
      (define h (/ (- b a) n))
      (define (term x) (+ (f x)
                          (* (f (+ x h)) 4)
                          (f (+ x (* 2 h)))))
      (define (add-2h x) (+ x (* 2 h)))
      (* (/ h 3)
         (sum term a add-2h b)))
    
# 1.30

    (define (sum term a next b)
      (define (iter a result)
        (if (> a b)
            result
            (iter (next a) (+ result (term a)))))
      (iter a 0))

# 1.31

    (define (product term a next b)
      (if (> a b)
          1
          (* (term a) (product term (next a) next b))))

    (define (pi n)
      (define (term a)
        (if (even? a)
            (/ a (+ a 1.0))
            (/ (+ a 1.0) a)))
      (define (next a) (+ a 1))
      (* (product term 2 next n)
         4))

    (define (product term a next b)
      (define (iter-product a result)
        (if (> a b)
             result
             (iter-product (next a) (* result (term a)))))
      (iter-product 2 1))

# 1.32

    (define (accumulate combinator null-value term a next b)
      (if (> a b)
          null-value
          (combinator 
            (term a)
            (accumulate combinator null-value term (next a) next b))))

    (define (accumulate combinator null-value term a next b)
      (define (iter-accumulate a result)
        (if (> a b)
            result
            (iter-accumulate (next a) (combinator result (term a)))))
      (iter-accumulate a null-value))

    (define (sum term a next b)
      (accumulate + 0 term a next b))
    (define (product term a next b)
      (accumulate * 1 term a next b))

# 1.33
     
    (define (filtered-accumulate combinator filtor null-value term a next b)
      (cond ((> a b)
               null-value)
            ((filtor a)
               (combinator (term a)
                           (filtered-accumulate combinator filtor null-value
                            term (next a) next b)))
            (else
              (filtered-accumulate combinator filtor null-value term (next a)
                  next b))))

## a.

    (define (prime-sum a b)
      (define (id a) a)
      (define (step-odd a)
        (if (even? a) (+ a 1)
            (+ a 2)))
      (filtered-accumulate + prime? 0 id a step-odd b))

## b.
        
    (define (relative-prime-product n)
      (define (id a) a)
      (define (relative-prime? a) (= (gcd a n) 1))
      (define (step a) (+ a 1))
      (filtered-accumulate * relative-prime? 1 id 1 step (- n 1)))

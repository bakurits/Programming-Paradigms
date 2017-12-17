(define (range l r)
    (if (> l r) '()
        (cons l (range (+ 1 l) r))
    )
)

(define (div-count n p)
    (if (= n 1) 0
        (if (not (= (remainder n p) 0)) 0
            (+ 1 (div-count (/ n p) p))
        )
    )
)

(define (square n)
    (* n n)
)

(define (binpow a x)
    (if (= x 0) 1
        (if (= 0 (remainder x 2)) (square (binpow a (quotient x 2)))
            (* (square (binpow a (quotient x 2))) a)
        )
    )
)

(define (factorize n i)
    (if (= n 1) '()
        (if (< n i) '()
            (if (not (= 0 (remainder n i))) (factorize n (+ 1 i))
                ((lambda (divCount) 
                    (cons (list i divCount) (factorize (quotient n (binpow i divCount)) (+ 1 i)))
                ) (div-count n i))
            )
        )
    )
)

(define (factorization n)
    (if (= n 1) '()
        (factorize n 2)
    )
)
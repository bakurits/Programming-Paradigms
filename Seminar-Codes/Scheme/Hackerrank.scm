/* Hello World N Times */
/* Print "Hello World" n amount of times. */
(define (nth n)
    (if (= n 0) '()
    (cons "Hello World\n" (nth (- n 1)))
    )
)

/* List Replication */
/* Given a list, repeat each element in the list, n amount of times */
(define (replOne x n)
    (if (= n 0) '()
        (cons x (replOne x (- n 1)))
    )
)

(define (repl n seq)
    (flatten (map (lambda(x) (replOne x n)) seq))
)

(define (flatten seq)
    (if (= (length seq) 0) '()
        (if (list? (car seq)) (append (flatten (car seq)) (flatten (cdr seq)))
            (cons (car seq) (flatten (cdr seq)))
        )
    )
)

/* Filter Array */
/* Filter a given array of integers and output only those values that are less than a specified value n */
(define (filter n seq)
    (if (= (length seq) 0) '()
        (if (< n (car seq)) (filter n (cdr seq))
            (cons (car seq) (filter n (cdr seq)))
        )
    )
)

/* Filter Positions in a List */
/* For a given list with n integers, return a new list removing the elements at odd positions */
(define (filterw n seq)
    (if (= (length seq) 0) '()
        (if (= (remainder (- n (length seq)) 2) 1) (filterw n (cdr seq))
            (cons (car seq) (filterw n (cdr seq)))
        )
    )
)

(define (filter seq)
    (filterw (length seq) seq)
)

/* Array Of N Elements */
/* Create an array of n integers */
(define (array n)
    (if (= n 0) '()
        (cons n (array (- n 1)))
    )
)

/* Reverse a List */
(define (reverse seq)
    (if (= (length seq) 0) '()
        (append (reverse (cdr seq)) (list(car seq)))
    )
)

/* Sum of Odd Elements */
(define (sum seq)
    (if (= (length seq) 0) 0
        (if (= (remainder (car seq) 2) 1) (+ (car seq) (sum (cdr seq)))
            (sum (cdr seq))
        )
    )
)

/* List Length */
(define (Length seq)
    (if (null? seq) 0
        (+ 1 (Length (cdr seq)))
    )
)